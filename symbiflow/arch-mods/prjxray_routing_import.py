""" Imports 7-series routing fabric to the rr graph.

For ROI configurations, this also connects the synthetic IO tiles to the routing
node specified.

Rough structure:

Add rr_nodes for CHANX and CHANY from the database.  IPIN and OPIN rr_nodes
should already be present from the input rr_graph.

Create a mapping between database graph_nodes and IPIN, OPIN, CHANX and CHANY
rr_node ids in the rr_graph.

Add rr_edge for each row in the graph_edge table.

Import channel XML node from connection database and serialize output to
rr_graph XML.

"""

import argparse
import datetime
import functools
import re

import lib.rr_graph_xml.graph2 as xml_graph2
import prjxray.db
import prjxray.grid as grid
import progressbar
import simplejson as json
from lib.connection_database import (get_track_model,
                                     get_wire_in_tile_from_pin_name,
                                     get_wire_pkey)
from lib.rr_graph import graph2, tracks
from lib.rr_graph_xml.utils import read_xml_file
from prjxray.roi import Roi
from prjxray_constant_site_pins import feature_when_routed
from prjxray_db_cache import DatabaseCache
from prjxray_tile_import import remove_vpr_tile_prefix

now = datetime.datetime.now

HCLK_CK_BUFHCLK_REGEX = re.compile("HCLK_CK_BUFHCLK[0-9]+")
CASCOUT_REGEX = re.compile("BRAM_CASCOUT_ADDR((?:BWR)|(?:ARD))ADDRU([0-9]+)")


def check_feature(feature):
    """Check if enabling this feature requires other features to be enabled.

    Some pips imply other features.  Example:

    .HCLK_LEAF_CLK_B_BOTL0.HCLK_CK_BUFHCLK10
    implies:
    .ENABLE_BUFFER.HCLK_CK_BUFHCLK10
    """

    feature_path = feature.split(".")

    if HCLK_CK_BUFHCLK_REGEX.fullmatch(feature_path[-1]):
        enable_buffer_feature = "{}.ENABLE_BUFFER.{}".format(
            feature_path[0], feature_path[-1]
        )

        return " ".join((feature, enable_buffer_feature))

    m = CASCOUT_REGEX.fullmatch(feature_path[-2])
    if m:
        enable_cascout = "{}.CASCOUT_{}_ACTIVE".format(feature_path[0], m.group(1))

        return " ".join((feature, enable_cascout))

    parts = feature.split(".")

    wire_feature = feature_when_routed(parts[1])
    if wire_feature is not None:
        return "{} {}.{}".format(feature, parts[0], wire_feature)

    return feature


# CLBLL_L.CLBLL_LL_A1[0] -> (CLBLL_L, CLBLL_LL_A1)
PIN_NAME_TO_PARTS = re.compile(r"^([^\.]+)\.([^\]]+)\[0\]$")


def import_graph_nodes(conn, graph, node_mapping):
    cur = conn.cursor()
    tile_loc_to_pkey = {}

    for node in graph.nodes:
        if node.type not in (graph2.NodeType.IPIN, graph2.NodeType.OPIN):
            continue

        gridloc = graph.loc_map[(node.loc.x_low, node.loc.y_low)]
        pin_name = graph.pin_ptc_to_name_map[(gridloc.block_type_id, node.loc.ptc)]

        # Synthetic blocks are handled below.
        if pin_name.startswith("SYN-"):
            continue

        m = PIN_NAME_TO_PARTS.match(pin_name)
        assert m is not None, pin_name

        tile_type = m.group(1)
        tile_type = remove_vpr_tile_prefix(tile_type)

        pin = m.group(2)

        (wire_in_tile_pkeys, _) = get_wire_in_tile_from_pin_name(
            conn=conn, tile_type_str=tile_type, wire_str=pin
        )

        cur.execute(
            """
SELECT site_as_tile_pkey FROM tile WHERE grid_x = ? AND grid_y = ?;
        """,
            (node.loc.x_low, node.loc.y_low),
        )
        site_as_tile_pkey = cur.fetchone()[0]

        if site_as_tile_pkey is not None:
            cur.execute(
                """
SELECT site_pkey FROM site_as_tile WHERE pkey = ?;
                """,
                (site_as_tile_pkey,),
            )
            site_pkey = cur.fetchone()[0]
            wire_in_tile_pkey = wire_in_tile_pkeys[site_pkey]
        else:
            assert len(wire_in_tile_pkeys) == 1
            _, wire_in_tile_pkey = wire_in_tile_pkeys.popitem()

        if gridloc not in tile_loc_to_pkey:
            cur.execute(
                """
            SELECT pkey FROM tile WHERE grid_x = ? AND grid_y = ?;""",
                (gridloc[0], gridloc[1]),
            )

            result = cur.fetchone()
            assert result is not None, (tile_type, gridloc)
            (tile_pkey,) = result
            tile_loc_to_pkey[gridloc] = tile_pkey
        else:
            tile_pkey = tile_loc_to_pkey[gridloc]

        cur.execute(
            """
        SELECT
            top_graph_node_pkey, bottom_graph_node_pkey,
            left_graph_node_pkey, right_graph_node_pkey FROM wire
            WHERE
              wire_in_tile_pkey = ? AND tile_pkey = ?;""",
            (wire_in_tile_pkey, tile_pkey),
        )

        result = cur.fetchone()
        assert result is not None, (wire_in_tile_pkey, tile_pkey)
        (
            top_graph_node_pkey,
            bottom_graph_node_pkey,
            left_graph_node_pkey,
            right_graph_node_pkey,
        ) = result

        side = node.loc.side
        if side == tracks.Direction.LEFT:
            assert left_graph_node_pkey is not None, (tile_type, pin_name)
            node_mapping[left_graph_node_pkey] = node.id
        elif side == tracks.Direction.RIGHT:
            assert right_graph_node_pkey is not None, (tile_type, pin_name)
            node_mapping[right_graph_node_pkey] = node.id
        elif side == tracks.Direction.TOP:
            assert top_graph_node_pkey is not None, (tile_type, pin_name)
            node_mapping[top_graph_node_pkey] = node.id
        elif side == tracks.Direction.BOTTOM:
            assert bottom_graph_node_pkey is not None, (tile_type, pin_name)
            node_mapping[bottom_graph_node_pkey] = node.id
        else:
            assert False, side


def is_track_alive(conn, tile_pkey, roi, synth_tiles):
    cur = conn.cursor()
    cur.execute(
        """SELECT name, grid_x, grid_y FROM tile WHERE pkey = ?;""", (tile_pkey,)
    )
    tile, grid_x, grid_y = cur.fetchone()

    return (
        roi.tile_in_roi(grid.GridLoc(grid_x=grid_x, grid_y=grid_y))
        or tile in synth_tiles["tiles"]
    )


def import_tracks(conn, alive_tracks, node_mapping, graph, segment_id):
    cur = conn.cursor()
    for (
        graph_node_pkey,
        track_pkey,
        graph_node_type,
        x_low,
        x_high,
        y_low,
        y_high,
        ptc,
        capacitance,
        resistance,
    ) in cur.execute(
        """
SELECT
    pkey,
    track_pkey,
    graph_node_type,
    x_low,
    x_high,
    y_low,
    y_high,
    ptc,
    capacitance,
    resistance
FROM
    graph_node WHERE track_pkey IS NOT NULL;"""
    ):
        if track_pkey not in alive_tracks:
            continue

        node_type = graph2.NodeType(graph_node_type)

        if node_type == graph2.NodeType.CHANX:
            direction = "X"
            x_low = max(x_low, 1)
        elif node_type == graph2.NodeType.CHANY:
            direction = "Y"
            y_low = max(y_low, 1)
        else:
            assert False, node_type

        track = tracks.Track(
            direction=direction,
            x_low=x_low,
            x_high=x_high,
            y_low=y_low,
            y_high=y_high,
        )
        assert graph_node_pkey not in node_mapping
        node_mapping[graph_node_pkey] = graph.add_track(
            track=track,
            segment_id=segment_id,
            ptc=ptc,
            timing=graph2.NodeTiming(
                r=resistance,
                c=capacitance,
            ),
        )


def import_dummy_tracks(conn, graph, segment_id):
    cur = conn.cursor()

    num_dummy = 0
    for (
        graph_node_pkey,
        track_pkey,
        graph_node_type,
        x_low,
        x_high,
        y_low,
        y_high,
        ptc,
    ) in cur.execute(
        """
    SELECT pkey, track_pkey, graph_node_type, x_low, x_high, y_low, y_high, ptc FROM
        graph_node WHERE (graph_node_type = ? or graph_node_type = ?) and capacity = 0;""",
        (graph2.NodeType.CHANX.value, graph2.NodeType.CHANY.value),
    ):

        node_type = graph2.NodeType(graph_node_type)

        if node_type == graph2.NodeType.CHANX:
            direction = "X"
            x_low = x_low
        elif node_type == graph2.NodeType.CHANY:
            direction = "Y"
            y_low = y_low
        else:
            assert False, node_type

        track = tracks.Track(
            direction=direction,
            x_low=x_low,
            x_high=x_high,
            y_low=y_low,
            y_high=y_high,
        )

        graph.add_track(track=track, segment_id=segment_id, capacity=0, ptc=ptc)
        num_dummy += 1

    return num_dummy


def create_track_rr_graph(
    conn, graph, node_mapping, use_roi, roi, synth_tiles, segment_id
):
    cur = conn.cursor()
    cur.execute("""SELECT count(*) FROM track;""")
    (num_channels,) = cur.fetchone()

    print("{} Import alive tracks".format(now()))
    alive_tracks = set()
    for (track_pkey,) in cur.execute("SELECT pkey FROM track WHERE alive = 1;"):
        alive_tracks.add(track_pkey)

    print("{} Importing alive tracks".format(now()))
    import_tracks(conn, alive_tracks, node_mapping, graph, segment_id)

    print("{} Importing dummy tracks".format(now()))
    num_dummy = import_dummy_tracks(conn, graph, segment_id)

    print(
        "original {} final {} dummy {}".format(
            num_channels, len(alive_tracks), num_dummy
        )
    )


def add_synthetic_edges(conn, graph, node_mapping, grid, synth_tiles, prflow=False):
    cur = conn.cursor()
    delayless_switch = graph.get_switch_id("__vpr_delayless_switch__")

    for tile_name, synth_tile in synth_tiles["tiles"].items():
        assert len(synth_tile["pins"]) == 1
        for pin in synth_tile["pins"]:
            if pin["port_type"] in ["input", "output"]:
                if not prflow:
                    wire_pkey = get_wire_pkey(conn, tile_name, pin["wire"])
                    cur.execute(
                        """
SELECT
  track_pkey
FROM
  node
WHERE
  pkey = (
    SELECT
      node_pkey
    FROM
      wire
    WHERE
      pkey = ?
  );""",
                        (wire_pkey,),
                    )
                    (track_pkey,) = cur.fetchone()
                    assert track_pkey is not None, (tile_name, pin["wire"], wire_pkey)
                else:
                    tile_name, wire = pin["wire"].split("/")
                    wire_pkey = get_wire_pkey(conn, tile_name, wire)
                    cur.execute(
                        "SELECT graph_node_pkey FROM wire WHERE pkey=?;", (wire_pkey,)
                    )
                    (graph_node_pkey,) = cur.fetchone()
                    inode = node_mapping[graph_node_pkey]
                    # import ipdb; ipdb.set_trace()
            elif pin["port_type"] == "VCC":
                cur.execute("SELECT vcc_track_pkey FROM constant_sources")
                (track_pkey,) = cur.fetchone()
            elif pin["port_type"] == "GND":
                cur.execute("SELECT gnd_track_pkey FROM constant_sources")
                (track_pkey,) = cur.fetchone()
            else:
                assert False, pin["port_type"]

            if not prflow or pin["port_type"] in ["VCC", "GND"]:
                tracks_model, track_nodes = get_track_model(conn, track_pkey)

                option = list(
                    tracks_model.get_tracks_for_wire_at_coord(synth_tile["loc"])
                )
                assert len(option) > 0, (pin, len(option))

            if pin["port_type"] == "input":
                tile_type = "SYN-OUTPAD"
                wire = "outpad"
            elif pin["port_type"] == "output":
                tile_type = "SYN-INPAD"
                wire = "inpad"
            elif pin["port_type"] == "VCC":
                tile_type = "SYN-VCC"
                wire = "VCC"
            elif pin["port_type"] == "GND":
                tile_type = "SYN-GND"
                wire = "GND"
            else:
                assert False, pin

            if not prflow or pin["port_type"] in ["VCC", "GND"]:
                track_node = track_nodes[option[0][0]]
                assert track_node in node_mapping, (track_node, track_pkey)

            pin_name = graph.create_pin_name_from_tile_type_and_pin(tile_type, wire)

            pin_node = graph.get_nodes_for_pin(tuple(synth_tile["loc"]), pin_name)

            if not prflow:
                if pin["port_type"] == "input":
                    graph.add_edge(
                        src_node=node_mapping[track_node],
                        sink_node=pin_node[0][0],
                        switch_id=delayless_switch,
                        name="synth_{}_{}".format(tile_name, pin["wire"]),
                    )
                elif pin["port_type"] in ["VCC", "GND", "output"]:
                    graph.add_edge(
                        src_node=pin_node[0][0],
                        sink_node=node_mapping[track_node],
                        switch_id=delayless_switch,
                        name="synth_{}_{}".format(tile_name, pin["wire"]),
                    )
                else:
                    assert False, pin
            else:
                if pin["port_type"] == "input":
                    graph.add_edge(
                        src_node=inode,
                        sink_node=pin_node[0][0],
                        switch_id=delayless_switch,
                        name="synth_{}_{}".format(tile_name, pin["wire"]),
                    )
                elif pin["port_type"] == "output":
                    graph.add_edge(
                        src_node=pin_node[0][0],
                        sink_node=inode,
                        switch_id=delayless_switch,
                        name="synth_{}_{}".format(tile_name, pin["wire"]),
                    )
                elif pin["port_type"] in ["VCC", "GND"]:
                    graph.add_edge(
                        src_node=pin_node[0][0],
                        sink_node=node_mapping[track_node],
                        switch_id=delayless_switch,
                        name="synth_{}_{}".format(tile_name, pin["wire"]),
                    )
                else:
                    assert False, pin


def get_switch_name(conn, graph, switch_name_map, switch_pkey):
    assert switch_pkey is not None
    if switch_pkey not in switch_name_map:
        cur = conn.cursor()
        cur.execute("""SELECT name FROM switch WHERE pkey = ?;""", (switch_pkey,))
        (switch_name,) = cur.fetchone()
        switch_id = graph.get_switch_id(switch_name)
        switch_name_map[switch_pkey] = switch_id
    else:
        switch_id = switch_name_map[switch_pkey]

    return switch_id


def create_get_tile_name(conn):
    cur = conn.cursor()

    @functools.lru_cache(maxsize=None)
    def get_tile_name(tile_pkey):
        cur.execute(
            """
        SELECT name FROM phy_tile WHERE pkey = ?;
        """,
            (tile_pkey,),
        )
        return cur.fetchone()[0]

    return get_tile_name


def create_get_pip_wire_names(conn):
    cur = conn.cursor()

    @functools.lru_cache(maxsize=None)
    def get_pip_wire_names(pip_pkey):
        cur.execute(
            """SELECT src_wire_in_tile_pkey, dest_wire_in_tile_pkey
            FROM pip_in_tile WHERE pkey = ? AND is_directional = 1 AND is_pseudo = 0;""",
            (pip_pkey,),
        )
        src_wire_in_tile_pkey, dest_wire_in_tile_pkey = cur.fetchone()

        cur.execute(
            """SELECT name FROM wire_in_tile WHERE pkey = ?;""",
            (src_wire_in_tile_pkey,),
        )
        (src_net,) = cur.fetchone()

        cur.execute(
            """SELECT name FROM wire_in_tile WHERE pkey = ?;""",
            (dest_wire_in_tile_pkey,),
        )
        (dest_net,) = cur.fetchone()

        return (src_net, dest_net)

    return get_pip_wire_names


def import_graph_edges(conn, graph, node_mapping):
    # First yield existing edges
    print("{} Importing existing edges.".format(now()))
    for edge in graph.edges:
        yield (edge.src_node, edge.sink_node, edge.switch_id, None)

    # Then yield edges from database.
    cur = conn.cursor()

    cur.execute("SELECT count() FROM graph_edge;" "")
    (num_edges,) = cur.fetchone()

    get_tile_name = create_get_tile_name(conn)
    get_pip_wire_names = create_get_pip_wire_names(conn)

    switch_name_map = {}

    print("{} Importing edges from database.".format(now()))
    with progressbar.ProgressBar(max_value=num_edges) as bar:
        for idx, (
            src_graph_node,
            dest_graph_node,
            switch_pkey,
            phy_tile_pkey,
            pip_pkey,
        ) in enumerate(
            cur.execute(
                """
SELECT
  src_graph_node_pkey,
  dest_graph_node_pkey,
  switch_pkey,
  phy_tile_pkey,
  pip_in_tile_pkey
FROM
  graph_edge;
                """
            )
        ):
            if src_graph_node not in node_mapping:
                continue

            if dest_graph_node not in node_mapping:
                continue

            if pip_pkey is not None:
                tile_name = get_tile_name(phy_tile_pkey)
                src_net, dest_net = get_pip_wire_names(pip_pkey)

                pip_name = "{}.{}.{}".format(tile_name, dest_net, src_net)
            else:
                pip_name = None

            switch_id = get_switch_name(conn, graph, switch_name_map, switch_pkey)

            src_node = node_mapping[src_graph_node]
            sink_node = node_mapping[dest_graph_node]

            if pip_name is not None:
                yield (
                    src_node,
                    sink_node,
                    switch_id,
                    (("fasm_features", check_feature(pip_name)),),
                )
            else:
                yield (src_node, sink_node, switch_id, ())

            if idx % 1024 == 0:
                bar.update(idx)


def create_channels(conn):
    cur = conn.cursor()

    cur.execute(
        """
    SELECT chan_width_max, x_min, x_max, y_min, y_max FROM channel;"""
    )
    chan_width_max, x_min, x_max, y_min, y_max = cur.fetchone()

    cur.execute("SELECT idx, info FROM x_list;")
    x_list = []
    for idx, info in cur:
        x_list.append(graph2.ChannelList(idx, info))

    cur.execute("SELECT idx, info FROM y_list;")
    y_list = []
    for idx, info in cur:
        y_list.append(graph2.ChannelList(idx, info))

    return graph2.Channels(
        chan_width_max=chan_width_max,
        x_min=x_min,
        y_min=y_min,
        x_max=x_max,
        y_max=y_max,
        x_list=x_list,
        y_list=y_list,
    )


def yield_nodes(nodes):
    with progressbar.ProgressBar(max_value=len(nodes)) as bar:
        for idx, node in enumerate(nodes):
            yield node

            if idx % 1024 == 0:
                bar.update(idx)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--db_root", required=True, help="Project X-Ray Database")
    parser.add_argument("--read_rr_graph", required=True, help="Input rr_graph file")
    parser.add_argument("--write_rr_graph", required=True, help="Output rr_graph file")
    parser.add_argument(
        "--connection_database", help="Database of fabric connectivity", required=True
    )
    parser.add_argument(
        "--synth_tiles",
        help="If using an ROI, synthetic tile defintion from prjxray-arch-import",
    )
    parser.add_argument("--prflow", required=False)

    args = parser.parse_args()

    db = prjxray.db.Database(args.db_root)
    grid = db.grid()

    if args.synth_tiles:
        use_roi = True
        with open(args.synth_tiles) as f:
            synth_tiles = json.load(f)

        roi = Roi(
            db=db,
            x1=synth_tiles["info"]["GRID_X_MIN"],
            y1=synth_tiles["info"]["GRID_Y_MIN"],
            x2=synth_tiles["info"]["GRID_X_MAX"],
            y2=synth_tiles["info"]["GRID_Y_MAX"],
        )

        print("{} generating routing graph for ROI.".format(now()))
    else:
        use_roi = False

    # Convert input rr graph into graph2.Graph object.
    input_rr_graph = read_xml_file(args.read_rr_graph)

    xml_graph = xml_graph2.Graph(
        input_rr_graph,
        progressbar=progressbar.progressbar,
        output_file_name=args.write_rr_graph,
    )

    graph = xml_graph.graph

    tool_version = input_rr_graph.getroot().attrib["tool_version"]
    tool_comment = input_rr_graph.getroot().attrib["tool_comment"]

    with DatabaseCache(args.connection_database, True) as conn:
        cur = conn.cursor()
        for (
            name,
            internal_capacitance,
            drive_resistance,
            intrinsic_delay,
            switch_type,
        ) in cur.execute(
            """
SELECT
    name,
    internal_capacitance,
    drive_resistance,
    intrinsic_delay,
    switch_type
FROM
    switch;"""
        ):
            # Add back missing switchs, which were unused in arch xml, and so
            # were not  emitted in rrgraph XML.
            #
            # TODO: This can be removed once
            # https://github.com/verilog-to-routing/vtr-verilog-to-routing/issues/354
            # is fixed.

            try:
                graph.get_switch_id(name)
                continue
            except KeyError:
                xml_graph.add_switch(
                    graph2.Switch(
                        id=None,
                        name=name,
                        type=graph2.SwitchType[switch_type.upper()],
                        timing=graph2.SwitchTiming(
                            r=drive_resistance,
                            c_in=0.0,
                            c_out=0.0,
                            c_internal=internal_capacitance,
                            t_del=intrinsic_delay,
                        ),
                        sizing=graph2.SwitchSizing(
                            mux_trans_size=0,
                            buf_size=0,
                        ),
                    )
                )

        # Mapping of graph_node.pkey to rr node id.
        node_mapping = {}

        # Match site pins rr nodes with graph_node's in the connection_database.
        print("{} Importing graph nodes".format(now()))
        import_graph_nodes(conn, graph, node_mapping)

        # Walk all track graph nodes and add them.
        print("{} Creating tracks".format(now()))
        segment_id = graph.get_segment_id_from_name("dummy")
        create_track_rr_graph(
            conn, graph, node_mapping, use_roi, roi, synth_tiles, segment_id
        )

        # Set of (src, sink, switch_id) tuples that pip edges have been sent to
        # VPR.  VPR cannot handle duplicate paths with the same switch id.
        if use_roi:
            print("{} Adding synthetic edges".format(now()))
            add_synthetic_edges(
                conn, graph, node_mapping, grid, synth_tiles, args.prflow
            )

        print("{} Creating channels.".format(now()))
        channels_obj = create_channels(conn)

        print("{} Serializing to disk.".format(now()))
        with xml_graph:
            # import ipdb; ipdb.set_trace()
            xml_graph.start_serialize_to_xml(
                tool_version=tool_version,
                tool_comment=tool_comment,
                channels_obj=channels_obj,
            )

            xml_graph.serialize_nodes(yield_nodes(xml_graph.graph.nodes))
            xml_graph.serialize_edges(import_graph_edges(conn, graph, node_mapping))


if __name__ == "__main__":
    main()

import argparse

import prjxray.db
import simplejson as json
from prjxray.roi import Roi
from prjxray_db_cache import DatabaseCache

# from numpy import array



def map_tile_to_vpr_coord(conn, tile):
    """Converts prjxray tile name into VPR tile coordinates.

    It is assumed that this tile should only have one mapped tile.

    """
    c = conn.cursor()
    c.execute("SELECT pkey FROM phy_tile WHERE name = ?;", (tile,))
    phy_tile_pkey = c.fetchone()[0]

    # It is expected that this tile has only one logical location,
    # because why split a tile with no sites?
    c.execute(
        "SELECT tile_pkey FROM tile_map WHERE phy_tile_pkey = ?", (phy_tile_pkey,)
    )
    mapped_tiles = c.fetchall()
    assert len(mapped_tiles) == 1, tile
    tile_pkey = mapped_tiles[0][0]

    c.execute("SELECT grid_x, grid_y FROM tile WHERE pkey = ?", (tile_pkey,))
    grid_x, grid_y = c.fetchone()

    return grid_x, grid_y


def read_partition_pins(filename, conn):
    part_pins = dict()
    with open(filename, "r") as f:
        f1 = f.readlines()
        for x in f1:
            x = x.strip("\n")
            y = x.split(" ")
            if len(y) >= 2:
                port = y[0]
                if len(y) > 2:
                    print(
                        "Port: "
                        + port
                        + " has more than one partition pin, using the first one"
                    )
                if port.startswith("dout_"):
                    port_type = "input"
                    is_clock = False
                elif port.startswith("din_"):
                    is_clock = False
                    port_type = "output"
                elif port.startswith("clk_"):
                    port_type = "output"
                    is_clock = True
                elif port.startswith("resend_"):
                    port_type = "output"
                    is_clock = False
                elif port.startswith("reset_"):
                    port_type = "output"
                    is_clock = False
                else:
                    assert False, port
                (tile, wire) = y[1].split("/")
                vpr_loc = map_tile_to_vpr_coord(conn, tile)
                part_pins[port] = {
                    "port": port,
                    "vpr_loc": vpr_loc,
                    "wire": y[1],
                    "port_type": port_type,
                    "is_clock": is_clock,
                }
        return part_pins


def main():
    parser = argparse.ArgumentParser(description="Generate synth_tiles.json")
    parser.add_argument("--db_root", required=True)
    parser.add_argument("--roi", required=True)
    parser.add_argument(
        "--connection_database", help="Connection database", required=True
    )
    parser.add_argument("--synth_tiles", required=True)
    parser.add_argument("--partition_pins", required=False)

    args = parser.parse_args()

    db = prjxray.db.Database(args.db_root)
    g = db.grid()

    synth_tiles = {}
    synth_tiles["tiles"] = {}

    with open(args.roi) as f:
        j = json.load(f)

    roi = Roi(
        db=db,
        x1=j["info"]["GRID_X_MIN"],
        y1=j["info"]["GRID_Y_MIN"],
        x2=j["info"]["GRID_X_MAX"],
        y2=j["info"]["GRID_Y_MAX"],
    )

    filled_state = dict()

    # import pdb; pdb.set_trace()
    with DatabaseCache(args.connection_database, read_only=True) as conn:
        vbrk_in_use = set()
        synth_tiles["info"] = j["info"]
        if not args.partition_pins:
            for port in j["ports"]:
                if port["name"].startswith("dout["):
                    port_type = "input"
                    is_clock = False
                elif port["name"].startswith("din["):
                    is_clock = False
                    port_type = "output"
                elif port["name"].startswith("clk"):
                    port_type = "output"
                    is_clock = True
                else:
                    assert False, port

                tile, wire = port["wire"].split("/")

                vbrk_in_use.add(tile)

                # Make sure connecting wire is not in ROI!
                loc = g.loc_of_tilename(tile)
                if roi.tile_in_roi(loc):
                    # Or if in the ROI, make sure it has no sites.
                    gridinfo = g.gridinfo_at_tilename(tile)
                    assert (
                        len(db.get_tile_type(gridinfo.tile_type).get_sites()) == 0
                    ), tile

                vpr_loc = map_tile_to_vpr_coord(conn, tile)

                if tile not in synth_tiles["tiles"]:
                    synth_tiles["tiles"][tile] = {
                        "pins": [],
                        "loc": vpr_loc,
                    }

                synth_tiles["tiles"][tile]["pins"].append(
                    {
                        "roi_name": port["name"].replace("[", "_").replace("]", "_"),
                        "wire": wire,
                        "pad": port["pin"],
                        "port_type": port_type,
                        "is_clock": is_clock,
                    }
                )

        # Find two VBRK's in the corner of the fabric to use as the synthetic VCC/
        # GND source.
        vbrk_loc = None
        vbrk_tile = None
        vbrk2_loc = None
        vbrk2_tile = None

        for tile in g.tiles():
            if tile in vbrk_in_use:
                continue

            loc = g.loc_of_tilename(tile)
            if not roi.tile_in_roi(loc):
                continue
            # filled_state[loc] = "roi"

            gridinfo = g.gridinfo_at_tilename(tile)
            if "VBRK" not in gridinfo.tile_type:
                continue

            assert len(db.get_tile_type(gridinfo.tile_type).get_sites()) == 0, tile

            if vbrk_loc is None:
                vbrk2_loc = vbrk_loc
                vbrk2_tile = vbrk_tile
                vbrk_loc = loc
                vbrk_tile = tile
            else:
                if (
                    loc.grid_x < vbrk_loc.grid_x
                    and loc.grid_y < vbrk_loc.grid_y
                    or vbrk2_loc is None
                ):
                    vbrk2_loc = vbrk_loc
                    vbrk2_tile = vbrk_tile
                    vbrk_loc = loc
                    vbrk_tile = tile

        assert vbrk_loc is not None
        assert vbrk_tile is not None
        assert vbrk_tile not in synth_tiles["tiles"]

        vbrk_vpr_loc = map_tile_to_vpr_coord(conn, vbrk_tile)
        filled_state[vbrk_vpr_loc] = "used"
        synth_tiles["tiles"][vbrk_tile] = {
            "loc": vbrk_vpr_loc,
            "pins": [
                {
                    "wire": "VCC",
                    "pad": "VCC",
                    "port_type": "VCC",
                    "is_clock": False,
                },
            ],
        }

        assert vbrk2_loc is not None
        assert vbrk2_tile is not None
        assert vbrk2_tile not in synth_tiles["tiles"]
        vbrk2_vpr_loc = map_tile_to_vpr_coord(conn, vbrk2_tile)
        filled_state[vbrk2_vpr_loc] = "used"
        synth_tiles["tiles"][vbrk2_tile] = {
            "loc": vbrk2_vpr_loc,
            "pins": [
                {
                    "wire": "GND",
                    "pad": "GND",
                    "port_type": "GND",
                    "is_clock": False,
                },
            ],
        }

        if args.partition_pins:

            # only types I know are ok so far
            acceptable_tile_types = set(
                filter(
                    lambda x: x.startswith("VBRK")
                    or x.startswith("INT")
                    or ("CLK" in x),
                    map(lambda t: t["type"], g.tilegrid.values()),
                )
            )
            (x_min, x_max, y_min, y_max) = g.dims()

            def in_grid(ds, x, y):
                return (
                    x - ds >= x_min
                    or x + ds <= x_max
                    or y - ds >= y_min
                    or y + ds <= y_max
                )

            partition_pins = read_partition_pins(args.partition_pins, conn)
            for pin in partition_pins:
                print(str(pin))
                (x, y) = partition_pins[pin]["vpr_loc"]
                best = None
                ds = 0
                i = 0
                while in_grid(ds, x, y) and best is None:
                    i += 1
                    candidates = filter(
                        lambda p: p in g.loc,
                        set([(x - ds, y), (x + ds, y), (x, y - ds), (x, y + ds)]),
                    )
                    candidates = filter(
                        lambda p: (
                            g.gridinfo_at_loc(p).tile_type in acceptable_tile_types
                        )
                        or (
                            not roi.tile_in_roi(prjxray.grid_types.GridLoc(p[0], p[1]))
                        ),
                        candidates,
                    )
                    # filter out filled cells, or maybe change this later to accept io sharing
                    candidates = list(
                        filter(lambda p: p not in filled_state, candidates)
                    )
                    # candidates = list(filter(lambda p: (p not in filled_state) or filled_state[p] is sharable, candidates))
                    if len(candidates) > 0:
                        best = candidates[0]
                    ds += 1
                assert best is not None
                filled_state[best] = "used"
                print("Best: " + str(best))
                tile = g.tilename_at_loc(best)
                if tile not in synth_tiles["tiles"]:
                    synth_tiles["tiles"][tile] = {
                        "pins": [],
                        "loc": best,
                        "node_loc": [x, y],
                        "ds": ds - 1,
                    }
                # import pdb; pdb.set_trace()
                synth_tiles["tiles"][tile]["pins"].append(
                    {
                        "roi_name": partition_pins[pin]["port"],
                        "wire": partition_pins[pin]["wire"],
                        "pad": partition_pins[pin]["port"],
                        "port_type": partition_pins[pin]["port_type"],
                        "is_clock": partition_pins[pin]["is_clock"],
                    }
                )

    with open(args.synth_tiles, "w") as f:
        json.dump(synth_tiles, f, indent=2)


if __name__ == "__main__":
    main()

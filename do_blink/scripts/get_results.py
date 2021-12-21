import glob
import os
import pyparsing as pp
import logging

logging.basicConfig()
log = logging.getLogger(__name__)
log.setLevel(logging.INFO)

def get_results(path):
    # build path from relative path
    #import pdb; pdb.set_trace()
    curr_build_dir = os.path.join(os.getcwd(), path)
    top_eblif_logs = glob.glob(
            "{}/**/nexys_video.eblif.time".format(curr_build_dir), recursive=True
        )
    pack_logs = glob.glob(
            "{}/**/nexys_video.net.time".format(curr_build_dir), recursive=True
        )
    place_logs = glob.glob(
            "{}/**/nexys_video.place.time".format(curr_build_dir), recursive=True
        )
    route_logs = glob.glob(
            "{}/**/nexys_video.route.time".format(curr_build_dir), recursive=True
        )
    # fasm_logs = glob.glob(
    #         "{}/**/nexys_video.fasm.time".format(curr_build_dir), recursive=True
    #     )
    bitgen_logs = glob.glob(
            "{}/**/nexys_video.bit.time".format(curr_build_dir), recursive=True
        )
    # sort logs by name
    top_eblif_logs.sort()
    pack_logs.sort()
    place_logs.sort()
    route_logs.sort()
    # fasm_logs.sort()
    bitgen_logs.sort()

    for idx in range(len(top_eblif_logs)):
        top_eblif_log = open(
            top_eblif_logs[idx], "r"
        ).read()
        pack_log = open(
            pack_logs[idx], "r"
        ).read()
        place_log = open(
            place_logs[idx], "r"
        ).read()
        route_log = open(
            route_logs[idx], "r"
        ).read()
        # fasm_log = open(
        #     fasm_logs[idx], "r"
        # ).read()
        bitgen_log = open(
            bitgen_logs[idx], "r"
        ).read()

        time_pattern = pp.Word(pp.nums)

        top_eblif_time = float(
            time_pattern.searchString(top_eblif_log).asList()[0][0]
        )
        pack_time_time = float(
            time_pattern.searchString(pack_log).asList()[0][0]
        )
        place_log_time = float(
            time_pattern.searchString(place_log).asList()[0][0]
        )
        route_log_time = float(
            time_pattern.searchString(route_log).asList()[0][0]
        )
        # fasm_log_time = float(
        #     time_pattern.searchString(fasm_log).asList()[0][0]
        # )
        bitgen_log_time = float(
            time_pattern.searchString(bitgen_log).asList()[0][0]
        )

        total_time = (
            top_eblif_time
            + pack_time_time
            + place_log_time
            + route_log_time
            # + fasm_log_time
            + bitgen_log_time
        )
        bench = path.split("/")[-2]
        print(
            f"{bench},{int(top_eblif_time)},{int(pack_time_time)},{int(place_log_time)},{int(route_log_time)},{int(bitgen_log_time)},{int(total_time)}"
        )

if __name__ == "__main__":
    import argparse
    argparser = argparse.ArgumentParser(
        description="Get results from a build directory"
    )
    argparser.add_argument(
        "path",
        help="Path to the build directory",
        type=str,
        default="build",
    )

    args = argparser.parse_args()
    get_results(args.path)
import json


def sign(x):
    if x >= 0:
        return 1
    else:
        return -1


def get_cell(num, res):
    cell = abs(num) // res
    remainder = abs(num) % res
    if remainder > 0:
        cell += 1

    return cell * sign(num)


prim_file = "../data/primitives_tests/acc_primitive_library_BVP_3_-1.51.5_-4.54.5.json"
prim_dest_file = "../data/primitives_tests/acc_primitive_library_BVP_3_-1.51.5_-4.54.5_cells.json"
resolution = 0.05

cells_prim = {"primitives": []}

with open(prim_file, "r") as f:
    original_data = json.load(f)["primitives"]

test = []

for prim in original_data:

    curr_prim = {
        "cost": prim["cost"],
        "initial_pos": [(abs(prim["initial_pos"][1]) // resolution) * sign(prim["initial_pos"][1]),
                        (abs(prim["initial_pos"][0]) // resolution) * sign(prim["initial_pos"][0]),
                        (abs(prim["initial_pos"][2]) // resolution) * sign(prim["initial_pos"][2])],
        "initial_vel": prim["initial_vel"],
        "final_pos": [(abs(prim["final_pos"][1]) // resolution) * sign(prim["final_pos"][1]),
                      (abs(prim["final_pos"][0]) // resolution) * sign(prim["final_pos"][0]),
                      (abs(prim["final_pos"][2]) // resolution) * sign(prim["final_pos"][2])],
        "final_vel": prim["final_vel"],
        "path": []
    }
    # "traj_pos": prim["traj_pos"],
    # "traj_vel": prim["traj_vel"],
    # "traj_acc": prim["traj_acc"],
    # "traj_jrk": prim["traj_jrk"],
    # "traj_snp": prim["traj_snp"]}

    for p in prim["path"]:
        curr_prim["path"].append([(abs(p[1]) // resolution) * sign(p[1]),
                                  (abs(p[0]) // resolution) * sign(p[0]),
                                  (abs(p[2]) // resolution) * sign(p[2]),
                                  ])

    cells_prim["primitives"].append(curr_prim)

with open(prim_dest_file, "w") as f:
    json.dump(cells_prim, f)

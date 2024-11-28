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


def interpolate_points(p1, p2, num_points):
    interpolated = []
    for i in range(1, num_points + 1):
        t = i / (num_points + 1)
        interpolated_point = [
            (1 - t) * p1[0] + t * p2[0],
            (1 - t) * p1[1] + t * p2[1],
            (1 - t) * p1[2] + t * p2[2],
        ]
        interpolated.append(interpolated_point)
    return interpolated


prim_file = "../data/primitives_tests/acc_primitive_library_BVP_36_-1.51.5_-4.54.5.json"
prim_dest_file = "../data/primitives_tests/acc_primitive_library_BVP_36_-1.51.5_-4.54.5_cells.json"
resolution = 0.025
interpolation_points = 5

cells_prim = {"primitives": []}

with open(prim_file, "r") as f:
    original_data = json.load(f)["primitives"]

for prim in original_data:
    curr_prim = {
        "cost": prim["cost"],
        "initial_pos": [((abs(prim["initial_pos"][1]) // resolution) * sign(prim["initial_pos"][1])),
                        (abs(prim["initial_pos"][0]) // resolution) * sign(prim["initial_pos"][0]),
                        (abs(prim["initial_pos"][2]) // resolution) * sign(prim["initial_pos"][2])],
        "initial_vel": prim["initial_vel"],
        "final_pos": [-((abs(prim["final_pos"][1]) // resolution) * sign(prim["final_pos"][1])) + (1 if ((abs(prim["final_pos"][1]) // resolution) * sign(prim["final_pos"][1])) != 0 else 0),
                      (abs(prim["final_pos"][0]) // resolution) * sign(prim["final_pos"][0]) + (1 if ((abs(prim["final_pos"][0]) // resolution) * sign(prim["final_pos"][0])) != 0 else 0),
                      (abs(prim["final_pos"][2]) // resolution) * sign(prim["final_pos"][2])],
        "final_vel": prim["final_vel"],
        "path": [],
        "pos_traj": prim["traj_pos"],
        "vel_traj": prim["traj_vel"]
    }

    path_points = prim["path"]
    for i in range(len(path_points) - 1):
        p1 = path_points[i]
        p2 = path_points[i + 1]

        # Add the current point
        curr_prim["path"].append([
            -((abs(p1[1]) // resolution) * sign(p1[1])),
            (abs(p1[0]) // resolution) * sign(p1[0]),
            (abs(p1[2]) // resolution) * sign(p1[2])
        ])

        # Interpolate and add intermediate points
        interpolated_points = interpolate_points(p1, p2, interpolation_points)
        for ip in interpolated_points:
            curr_prim["path"].append([
                -((abs(ip[1]) // resolution) * sign(ip[1])),
                (abs(ip[0]) // resolution) * sign(ip[0]),
                (abs(ip[2]) // resolution) * sign(ip[2])
            ])

    # Add the final point
    p_last = path_points[-1]
    curr_prim["path"].append([
        -((abs(p_last[1]) // resolution) * sign(p_last[1])),
        (abs(p_last[0]) // resolution) * sign(p_last[0]),
        (abs(p_last[2]) // resolution) * sign(p_last[2])
    ])

    cells_prim["primitives"].append(curr_prim)

with open(prim_dest_file, "w") as f:
    json.dump(cells_prim, f)

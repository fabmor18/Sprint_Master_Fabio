from random import randint
import json

map2d = []

size_x = 15
size_y = 15

for i in range(size_x):
    curr_row = []
    for j in range(size_y):
        curr_row.append(randint(0, 3) % 2)

    map2d.append(curr_row)

map_info = {"info": {
    "size_x": size_x,
    "size_y": size_y,
    "size_z": 0
}, 'map': map2d}

with open('../data/maps_tests/random_map.json', 'w') as f:
    json.dump(map_info, f)

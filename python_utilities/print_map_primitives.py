import json
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

prims = 'output_path6'
mapname = 'map_2D'
# mapname = 'map_FABIO_quadrata2'
info = 'path_info'

map_path = f'../data/maps_tests/{mapname}.json'
# map_path = f'../data/maps_FABIO/{mapname}.json'
primtives_path = f'../data/path_primitives/{prims}.json'
path_info = f'../data/path_info/{info}.json'
expanded_nodes_path = '../data/nodi_espansi/nodi_espansi_file.json'

plain = False
path_complete = True

with open(map_path) as f:
    map_data = json.load(f)

with open(primtives_path) as f:
    prim_data = json.load(f)['primitives']

with open(path_info) as f:
    path_info_data = json.load(f)

# Carica i nodi espansi
with open(expanded_nodes_path) as f:
    expanded_nodes_data = json.load(f)

# Punto iniziale
start_x = int(path_info_data["start"]["position"][0])
start_y = int(path_info_data["start"]["position"][1])

x = start_x
y = start_y

# Punto finale
end_x = int(path_info_data["end"]["position"][0])
end_y = int(path_info_data["end"]["position"][1])

color_map = ListedColormap(['white', 'red', 'yellow', 'blue'])
map_data = map_data['map']

# Lista per tracciare tutti i punti del percorso
path_points = []
primitive_end_points = []

if not plain:
    map_data[x][y] = 3

    for prim in prim_data:
        if path_complete:
            starting_x = x
            starting_y = y
            for elem in prim['path']:
                path_x = starting_x + int(elem[0])
                path_y = starting_y + int(elem[1])
                path_points.append((path_x, path_y))

                try:
                    if map_data[path_x][path_y] == 1:
                        map_data[path_x][path_y] = 2
                    else:
                        map_data[path_x][path_y] = 3
                except IndexError:
                    print(
                        f'At location [{starting_x - elem[0]}][{starting_y - elem[1]}] '
                        f'trying to move x += [{elem[0]}], y += [{elem[1]}]'
                    )

            # Aggiungi il punto finale della primitiva
            x += int(prim['final_pos'][0])
            y += int(prim['final_pos'][1])
            primitive_end_points.append((x, y))

            try:
                if map_data[x][y] == 1:
                    map_data[x][y] = 2
                else:
                    map_data[x][y] = 3
            except IndexError:
                continue

# Filtra i nodi espansi per posizione unica
plotted_positions = set((px, py) for px, py in path_points)  # Nodi del percorso
plotted_positions.update((pex, pey) for pex, pey in primitive_end_points)  # Punti finali delle primitive
plotted_positions.update((start_x, start_y))  # Nodo iniziale
plotted_positions.update((end_x, end_y))  # Nodo finale

filtered_expanded_nodes = []
for node in expanded_nodes_data:
    position_tuple = tuple(node["position"][:2])  # Usa solo i primi due valori della posizione (x, y)
    if position_tuple not in plotted_positions:
        plotted_positions.add(position_tuple)  # Aggiungi al set
        filtered_expanded_nodes.append(position_tuple)  # Aggiungi ai nodi filtrati

# Plot della mappa
plt.figure()
plt.imshow(map_data, cmap=color_map, interpolation='nearest')

# Disegna i punti del percorso
for px, py in path_points:
    plt.scatter(py, px, color='blue', s=5)  # Punti normali del percorso

# Disegna i punti finali delle primitive
for pex, pey in primitive_end_points:
    plt.scatter(pey, pex, color='green', s=25, label='Primitive End Point')  # Punti finali delle primitive

# Disegna i nodi espansi
for ex, ey in filtered_expanded_nodes:
    plt.scatter(ey, ex, color='orange', s=10, label='Expanded Node')  # Nodi espansi

# Disegna il punto iniziale del percorso
plt.scatter(start_y, start_x, color='black', s=50, label='Start Point')  # Punto iniziale del percorso

# Disegna il punto finale del percorso
plt.scatter(end_y, end_x, color='red', s=50, label='End Point')  # Punto finale del percorso

# Imposta il titolo e mostra la legenda
plt.title('2D Map')

# Grafico velocità-tempo
time = 0
time_points = []
velocity_x = []
velocity_y = []

for prim in prim_data:
    cost = prim['cost']
    vel_traj = prim['vel_traj']
    for velocity in vel_traj:
        time_points.append(time)
        velocity_x.append(velocity[0])
        velocity_y.append(velocity[1])
        time += cost / len(vel_traj)

plt.figure()
plt.plot(time_points, velocity_x, label='Velocity X')
plt.plot(time_points, velocity_y, label='Velocity Y')
plt.xlabel('Time (s)')
plt.ylabel('Velocity (m/s)')
plt.title('Velocity vs Time')
plt.legend()
plt.show()

#plt.savefig(f'../data/plots/{mapname}_{prims}_euclideancost.pdf')

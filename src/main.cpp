#include <iostream>
#include <nlohmann/json.hpp>
#include "../include/map.h"
#include "../include/setup.h"
#include "../include/algorithms_utilities.h"
#include "../include/heuristics.h"
#include "../include/algorithms.h"
#include "boost/tuple/tuple.hpp"
#include <time.h>

using json = nlohmann::json;

#include <vector>


int main()
{
    std::vector<std::vector<int>> map;
    int rows, cols;

    // boost::tie(map, rows, cols) = read_2d_map("../data/maps_FABIO/map_FABIO_quadrata2.json");
    boost::tie(map, rows, cols) = read_2d_map("../data/maps_tests/map_2D.json");
    // std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives = load_primitives(
        // "../data/primitives_FABIO/primitives_library_interp0025-vel3.json", VEL);
    std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives = load_primitives(
    "../data/primitives_tests/test_primitives_step_1.json", VEL);

    auto start = Node(
        {20.0,40.0,0.0},
        {0.0,0.0,0.0},
        {0.0,0.0,0.0},
        {0.0,0.0,0.0}
        );

    auto end = Node(
        {140.0,760.0,0.0},
        {0.0,0.0,0.0},
        {0.0,0.0,0.0},
        {0.0,0.0,0.0}
        );

    // Salvataggio delle informazioni iniziali e finali in path_info.json
    std::ofstream path_info_file("C:\\Sprint-master\\data\\path_info\\path_info.json");
    if (path_info_file) {
        nlohmann::json path_info = {
            {"start", {{"position", {start.data.position[0], start.data.position[1], start.data.position[2]}}}},
            {"end", {{"position", {end.data.position[0], end.data.position[1], end.data.position[2]}}}}
        };
        path_info_file << path_info.dump(4); // Salvataggio formattato
    }

    std::unordered_map<Node, int, NodeDataHash> first_visit;

    Heuristic* heuristic = new EuclideanHeuristic();
    // Heuristic* heuristic = new ManhattanHeuristic();

    clock_t tStart = clock();
    std::vector<Primitive> path = a_star(map, rows, cols, start,
                                         end, heuristic, primitives, VEL);
    printf("\nTime taken by A*: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    if (!path.empty()) {
        float cost = 0;
        std::cout << "\nNumber of primitives: "<< path.size() << std::endl;

        // Creazione del file output_path
        std::ofstream output_file("C:\\Sprint-master\\data\\path_primitives\\output_path6.json");
        if (output_file) {
            json json_path;
            json_path["primitives"] = json::array();

            for (const auto& primitive : path) {

                json_path["primitives"].push_back(primitive.to_json());
            }

            output_file << json_path.dump(4); // Salvataggio formattato
        } else {
            std::cout << "empty path" << std::endl;
        }

        return 0;
    }
}
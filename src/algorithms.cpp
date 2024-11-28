#include "../include/algorithms.h"
#include <iomanip>
#include <nlohmann/json.hpp>
#include <fstream>



float euclidean_test(const Node& nodeA, const Node& nodeB) {
    auto euclidean_distance = static_cast<float>(
            sqrt(
            pow((nodeA.data.position[0] - nodeB.data.position[0]), 2) +
            pow((nodeA.data.position[1] - nodeB.data.position[1]), 2) +
            pow((nodeA.data.position[2] - nodeB.data.position[2]), 2)
            )
    );

    return euclidean_distance;
}


//! Algorithm class
/*!
 * @file
 * This class contains the implementation of all the algorithms for path finding used in the project.
 */

std::vector<Primitive> a_star( const std::vector<std::vector<int>>& map,
                               const int rows,
                               const int cols,
                               const Node& start,
                               const Node& goal,
                               Heuristic* heuristic,
                               const std::unordered_map<node_data, std::vector<Primitive>,
                                       PrimDataHash, PrimEqualNodes>& all_primitives,
                               Controls control_level) {

    /*! \brief Implementation of A* algorithm \n
     *  This is the implementation of A* algorithm used by Sprint.
     *  @param map vector of vectors of int describing the map.
     *  @param rows int defining the number of rows of the map.
     *  @param cols int defining the number of cols of the map.
     *  @param start Node defining the initial position of the algorithm.
     *  @param goal Node defining the final position that the algorithm should reach.
     *  @param heuristic An Heuristic object used to calculate the heuristic that the algorithm will use.
     *  @param all_primitives An unordered map that contains the primitives that will be used by the algorithm to
     *  create the neighbors of any given Node.
     *  @param control_level Controls enum member defining which control level is adopted for the current
     *  run of the algorithm.
     *  @returns An ordered vector of the primitives applied to perform the best path from start to goal.
     *  An empty vector if no path exists.
     */

    /*!
     * The implementation uses unordered_map to organize the data, this choice is justidfied by the need to access
     * at constant time based on data unique to each Node. Since there is no way to identify any two given nodes a priori
     * with an id the chosen solution is to use a custom Hash Function and an hashmap.
     */
    std::unordered_map<Node, Node, NodeDataHash, NodeDataEqual> predecessors;
    std::unordered_map<Node, Primitive, NodeDataHash, NodeDataEqual> primitives_applied;
    std::unordered_map<Node, float, NodeDataHash, NodeDataEqual> gCost;
    std::unordered_map<Node, float, NodeDataHash, NodeDataEqual> fCost;
    std::unordered_map<Node, float, NodeDataHash, NodeDataEqual> hCost; //AGGIUNTA
    std::unordered_map<Node, int, NodeDataHash, NodeDataEqual> first_visit;

    gCost[start] = 0;
    fCost[start] = heuristic->calculateHeuristic(start, goal) * heuristicWeight;
    first_visit[start] = 1;

    std::priority_queue<std::pair<Node, float>,
        std::deque<std::pair<Node, float>>, openListCompare> open_list;

    open_list.emplace(start, fCost[start]);

    std::unordered_map<Node, int, NodeDataHash, NodeDataEqual> in_open_set;
    in_open_set[start] = 1;

    std::vector<Node> neighbours;

    int expanded_nodes = 0;

    Node current_best_backup = start;
    float lowest_distance = start.get_euclidean_dist(goal);

    std::vector<nlohmann::json> expanded_nodes_json; // Contenitore per i nodi espansi

    while (!open_list.empty()) {

        auto current_node = open_list.top();
        open_list.pop();
        in_open_set[current_node.first] -= 1;

        // Riga da inserire se togli parte sotto:
        // return constructPath(predecessors, primitives_applied, current_node.first, start, control_level);

        if (current_node.first.compare_nodes(goal, control_level, true)) {
            std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
            std::cout << "gCost: " << gCost[current_node.first] << std::endl;
            std::cout << "hCost: " << hCost[current_node.first] << std::endl; //AGGIUNTA

            // Salva i nodi espansi in JSON
            std::ofstream json_file("C:\\Sprint-master\\data\\nodi_espansi\\nodi_espansi_file0.json");
            json_file << nlohmann::json(expanded_nodes_json).dump(4);
            json_file.close();

            auto final_path = constructPath(predecessors, primitives_applied, current_node.first, start, control_level); //AGGIUNTA

            std::cout << "\nPrimitives on the final path:\n";
            std::cout << std::setw(15) << "gCost" << std::setw(15) << "hCost" << "\n";

            Node current_node = start;
            float prev_g_cost = gCost[start];

            std::cout << std::setw(15) << std::fixed << std::setprecision(6) << gCost[start]
                      << std::setw(15) << std::fixed << std::setprecision(6) << fCost[start] << "\n";

            for (const auto& prim : final_path) {
                auto next_node = prim.apply_primitive(current_node);

                float current_g_cost = gCost[next_node];
                float primitive_g_cost = current_g_cost - prev_g_cost;
                float h_cost = hCost[next_node];

                std::cout << std::setw(15) << std::fixed << std::setprecision(6) << primitive_g_cost
                << std::setw(15) << std::fixed << std::setprecision(6) << h_cost << "\n";

                prev_g_cost = current_g_cost;
                current_node = next_node;
            }

            return final_path;
        }

        auto possible_primitives = get_possible_primitives(current_node.first.data, all_primitives);

        for (const auto& curr_prim: possible_primitives) {
            if (isPrimAppliable(curr_prim, current_node.first.data, map, rows, cols)) {

                auto curr_neigh = curr_prim.apply_primitive(current_node.first);

                if (first_visit[curr_neigh] == 0) {
                    expanded_nodes += 1;
                    first_visit[curr_neigh] = 1;
                    gCost[curr_neigh] = std::numeric_limits<float>::max();

                    // Aggiungi il nodo al contenitore JSON
                    nlohmann::json node_json = {
                        {"position", {
                            curr_neigh.data.position[0],
                            curr_neigh.data.position[1],
                            curr_neigh.data.position[2]
                        }},
                        {"velocity", {
                            curr_neigh.data.velocity[0],
                            curr_neigh.data.velocity[1],
                            curr_neigh.data.velocity[2]
                        }}
                    };
                    expanded_nodes_json.push_back(node_json);
                }

                auto tentative_gscore = gCost[current_node.first] + curr_prim.get_cost(); //+ curr_prim.get_euclidean_dist();

                if (tentative_gscore < gCost[curr_neigh]) {

                    if (curr_neigh.get_euclidean_dist(goal) < lowest_distance) {
                        lowest_distance = curr_neigh.get_euclidean_dist(goal);
                        current_best_backup = curr_neigh;
                    }

                    predecessors[curr_neigh] = current_node.first;

                    gCost[curr_neigh] = tentative_gscore;
                    fCost[curr_neigh] = tentative_gscore
                                        + heuristic->calculateHeuristic(curr_neigh, goal) * heuristicWeight;
                    hCost[curr_neigh] = heuristic->calculateHeuristic(curr_neigh, goal) * heuristicWeight; //AGGIUNTA

                    if ((heuristic->calculateHeuristic(current_node.first, goal) - heuristic->calculateHeuristic(curr_neigh, goal)) > curr_prim.get_cost())
                    {
                        std::cout << "Inconsistence found:" << std::endl;
                        std::cout << "Current node: " << current_node.first << std::endl;
                        std::cout << "Neighbour node: " << curr_neigh << std::endl;
                        std::cout << "Primitive: " << curr_prim << std::endl;
                    }

                    primitives_applied[curr_neigh] = curr_prim;

                    if (in_open_set[curr_neigh] == 0) {
                        open_list.emplace(curr_neigh, fCost[curr_neigh]);
                        in_open_set[curr_neigh] = 1;
                    }
                }
            }
        }
    }

    std::cout << "Found alternative path" << std::endl;
    std::cout << "gCost to best alternative: " << gCost[current_best_backup] << std::endl;
    std::cout << "hCost to best alternative: " << hCost[current_best_backup] << std::endl; //AGGIUNTA

    return constructPath(predecessors, primitives_applied, current_best_backup, start, control_level);
}

#include "../include/algorithms_utilities.h"

//! Algorithm utilities file
/*!
 * @file
 * This file contains functions that performs routines used by the A* algorithm
 */

std::vector<Primitive> constructPath(std::unordered_map<Node, Node, NodeDataHash, NodeDataEqual> predecessors,
                                     std::unordered_map<Node, Primitive, NodeDataHash, NodeDataEqual> primitives_applied,
                                     const Node& goal,
                                     const Node& start,
                                     const Controls control_level) {
    /*!
     * This function retrieves and orderds the correct path from start to goal and returns a vector of primitives in the
     * correct application order.
     * @param predecessors unordered_map that associates at each Node its predecessor.
     * @param primitives_applied unordered_map that associates at each Node the Primitive applied to its predecessor to reach it.
     * @param goal Node defining the starting position of the path.
     * @param start Node defining the final position of the path.
     * @param control_level Controls variable defining the control level adopted.
     * @returns An ordered vector of the primitives applied to perform the best path from start to goal.
     */
    std::vector<Primitive> path = {};
    auto curr = goal;
    while (!curr.compare_nodes(start, control_level, false)) {
        path.insert(path.begin(), primitives_applied[curr]);
        curr = predecessors[curr];
    }
    return path;
}

bool isPrimAppliable(Primitive prim, node_data curr_pos, const std::vector<std::vector<int>>& map, int rows, int cols) {
    /*!
     * This function checks if a given primitive is appliable. A primitive is considered appliable if and only if
     * the final position and each position in the collision checking path are inside the map's border and not colliding
     * with any obstacle.
     * @param prim Primitive object currently checked.
     * @param curr_pos node_data of the node in which the primitive should be applied
     * @param map vector of vectors of int describing the map.
     * @param rows int defining the number of rows of the map.
     * @param cols int defining the number of cols of the map.
     *
     * @returns bool value defining if the primitive is appliable or not.
     */
    auto initial_x = static_cast<int>(curr_pos.position[0]);
    auto initial_y = static_cast<int>(curr_pos.position[1]);

    auto final_x = initial_x + static_cast<int>(prim.get_final_condition().position[0]);
    auto final_y = initial_y + static_cast<int>(prim.get_final_condition().position[1]);

    if ((final_x < 0 || final_x >= rows) || (final_y < 0 || final_y >= cols)) {
        return false;
    }

    if (map[final_x][final_y] != 0) {
        return false;
    }

    for (auto elem : prim.get_path()) {
        auto curr_x = initial_x + elem[0];
        auto curr_y = initial_y + elem[1];

        if ((curr_x < 0 || curr_x >= rows) || (curr_y < 0 || curr_y >= cols)) {
            return false;
        }

        if (map[curr_x][curr_y] != 0) {
            return false;
        }
    }
    return true;
}
#ifndef ALGORITHMS_UTILITIES_H
#define ALGORITHMS_UTILITIES_H

#include <vector>
#include <unordered_map>

#include "map_objects.h"
#include "primitives.h"
#include "hash_functions.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;


std::vector<Primitive> constructPath(std::unordered_map<Node, Node, NodeDataHash, NodeDataEqual> predecessors,
                                     std::unordered_map<Node, Primitive, NodeDataHash, NodeDataEqual> primitives_applied,
                                     const Node& goal, const Node& start, Controls control_level);

bool isPrimAppliable(Primitive prim, node_data curr_pos, const std::vector<std::vector<int>>& map, int rows, int cols);

#endif //ALGORITHMS_UTILITIES_H

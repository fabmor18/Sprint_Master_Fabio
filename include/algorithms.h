#ifndef SPRINT_ALGORITHMS_H
#define SPRINT_ALGORITHMS_H

#include "heuristics.h"
#include "map_objects.h"
#include "heuristics.h"
#include "setup.h"
#include "algorithms_utilities.h"
#include "hash_functions.h"
#include <vector>
#include <queue>
#include <unordered_map>

std::vector<Primitive> a_star(const std::vector<std::vector<int>>& map, int rows,
                              int cols, const Node& start, const Node& goal, Heuristic* heuristic,
                              const std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash,
                              PrimEqualNodes>& all_primitives, Controls control_level);


#endif //SPRINT_ALGORITHMS_H

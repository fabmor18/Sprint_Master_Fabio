#include <vector>
#include <cmath>

#include "control_levels.h"
#include "parameters.h"
#include "primitives.h"

#include "boost/tuple/tuple.hpp"

#ifndef SPRINT_MAP_INTERACTION_H
#define SPRINT_MAP_INTERACTION_H

boost::tuple<std::vector<std::vector<int>>, int, int> read_2d_map(const std::string& map_file);

#endif //SPRINT_MAP_INTERACTION_H

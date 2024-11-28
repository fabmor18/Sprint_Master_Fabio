#ifndef SPRINT_HEADERS_SETUP_H_
#define SPRINT_HEADERS_SETUP_H_
#include "vector"
#include "primitives.h"
#include "hash_functions.h"
#include "map_objects.h"
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"

std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> load_primitives(
        const std::string& primitives_file, Controls control_level);

std::vector<Primitive> get_possible_primitives(
        node_data node, std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash,PrimEqualNodes> primitives);

class openListCompare {
public:
    bool operator()(const std::pair<Node, float>& a, const std::pair<Node, float>& b) const
    {
        if (a.second >= b.second) {
            return true;
        }
        return false;
    }
};


#endif //SPRINT_HEADERS_SETUP_H_

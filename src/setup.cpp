#include "../include/setup.h"

using json = nlohmann::json;

std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> load_primitives(
        const std::string& primitives_file, Controls control_level)
{
    std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash,PrimEqualNodes> primitives;

    std::ifstream input_file(primitives_file);
    if (!input_file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return {};
    }
    json data_primitive;
    input_file >> data_primitive;
    input_file.close();

    auto id = 0;

    for(const auto& elem : data_primitive["primitives"]) {

        auto prim = Primitive(elem, id, control_level);
        primitives[prim.get_initial_condition()].push_back(prim);
        id += 1;
    }
    return primitives;
};

std::vector<Primitive> get_possible_primitives(node_data node,
                                               std::unordered_map<node_data, std::vector<Primitive>,
                                                       PrimDataHash, PrimEqualNodes> primitives) {
    if (primitives.count(node) == 0) {
        return {};
    }
    return primitives[node];
}
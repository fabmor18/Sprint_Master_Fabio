#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <queue>

#include "../include/primitives.h"
#include "../include/map_objects.h"
#include "../include/setup.h"
#include "../include/algorithms_utilities.h"

using json = nlohmann::json;

BOOST_AUTO_TEST_SUITE(AlgoTest)

    BOOST_AUTO_TEST_CASE(TestOpenListStructure) {
        std::priority_queue<std::pair<Node, float>,
            std::vector<std::pair<Node, float>>, openListCompare> open_list;

        std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives = load_primitives(
          "Boost_test/primitives_test_files/output_list_4.json"
          );

        auto start = Node(
              {0.0,0.0,0.0},
              {0.0,0.0,0.0},
              {0.0,0.0,0.0},
              {0.0,0.0,0.0}
            );


        open_list.emplace(start, 0);


        while(!open_list.empty()) {
            auto current = open_list.top();
            open_list.pop();
            for(const auto& prim : get_possible_primitives(current.first.data, primitives)) {
                auto new_node = prim.apply_primitive(current.first);
                open_list.emplace(new_node, current.second + prim.get_cost());
            }
        }
        BOOST_CHECK(open_list.empty());
    }


BOOST_AUTO_TEST_SUITE_END()
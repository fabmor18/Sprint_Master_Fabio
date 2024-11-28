#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../include/primitives.h"
#include "../include/map_objects.h"
#include "../include/setup.h"
#include <fstream>

using json = nlohmann::json;

BOOST_AUTO_TEST_SUITE(SetupTest)
    BOOST_AUTO_TEST_CASE(LoadIntoMapAndApply) {
        std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives = load_primitives(
                "../data/primitives_tests/test_primitives_step_1.json", VEL);


        BOOST_CHECK(!primitives.empty());

        auto start = Node(
            {1.0,1.0,1.0},
            {1.0,1.0,1.0},
            {1.0,1.0,1.0},
            {1.0,1.0,1.0});

        node_data data = {{2.0,2.0,2.0},{1.0,1.0,1.0},{1.0,1.0,1.0}};
        auto end = primitives[data][0].apply_primitive(start);

        BOOST_CHECK_EQUAL(1.0, start.data.position[0]);
        BOOST_CHECK_EQUAL(1.0, start.data.position[1]);
        BOOST_CHECK_EQUAL(1.0, start.data.position[2]);
        BOOST_CHECK_EQUAL(1.0, start.data.velocity[0]);
        BOOST_CHECK_EQUAL(1.0, start.data.velocity[1]);
        BOOST_CHECK_EQUAL(1.0, start.data.velocity[2]);
        BOOST_CHECK_EQUAL(1.0, start.data.acceleration[0]);
        BOOST_CHECK_EQUAL(1.0, start.data.acceleration[1]);
        BOOST_CHECK_EQUAL(1.0, start.data.acceleration[2]);

        BOOST_CHECK_EQUAL(5.0, end.data.position[0]);
        BOOST_CHECK_EQUAL(5.0, end.data.position[1]);
        BOOST_CHECK_EQUAL(5.0, end.data.position[2]);
        BOOST_CHECK_EQUAL(1.0, end.data.velocity[0]);
        BOOST_CHECK_EQUAL(1.0, end.data.velocity[1]);
        BOOST_CHECK_EQUAL(1.0, end.data.velocity[2]);
        BOOST_CHECK_EQUAL(1.0, end.data.acceleration[0]);
        BOOST_CHECK_EQUAL(1.0, end.data.acceleration[1]);
        BOOST_CHECK_EQUAL(1.0, end.data.acceleration[2]);
    }

    BOOST_AUTO_TEST_CASE(TestGetPossiblePrimitives) {
        std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives = load_primitives(
          "Boost_test/primitives_test_files/output_list_2.json"
          );

        std::vector<Primitive> applicable_primitives = get_possible_primitives(
            {{2.0,2.0,2.0},{1.0,1.0,1.0},{1.0,1.0,1.0}},
            primitives);

        BOOST_CHECK_EQUAL(4, applicable_primitives.size());

        std::vector<Primitive> empty_primitives = get_possible_primitives(
            {{2.0,2.0,2.0},{1.0,1.0,121.0},{1.0,1.0,1.0}},
            primitives);

        BOOST_CHECK(empty_primitives.empty());

        std::vector<Primitive> applicable_primitives2 = get_possible_primitives(
            {{2.0,2.0,2.0},{1.0,1.0,2.0},{2.0,1.0,1.0}},
            primitives);

        BOOST_CHECK_EQUAL(1, applicable_primitives2.size());

    }

    BOOST_AUTO_TEST_CASE(TestApplyPossiblePrimitives) {
        std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives = load_primitives(
          "Boost_test/primitives_test_files/output_list_3.json"
          );
        Node starting_node = Node({0.0,0.0,0.0}, {1.0,1.0,1.0},
            {2.0,2.0,2.0}, {3.0,3.0,3.0});

        std::vector<Primitive> applicable_primitives = get_possible_primitives(
            starting_node.data,
            primitives);

        std::vector<Node> nodes;

        for(auto prim : applicable_primitives) {
            //std::cout << prim << std::endl;

            nodes.push_back(prim.apply_primitive(starting_node));
        }
        BOOST_CHECK_EQUAL(applicable_primitives.size(), nodes.size());

        BOOST_CHECK_EQUAL(starting_node.data.position[0] + 4.0, nodes[0].data.position[0]);
        BOOST_CHECK_EQUAL(starting_node.data.position[1] + 4.0, nodes[0].data.position[1]);
        BOOST_CHECK_EQUAL(starting_node.data.position[2] + 4.0, nodes[0].data.position[2]);
        BOOST_CHECK_EQUAL(1.0, nodes[0].data.velocity[0]);
        BOOST_CHECK_EQUAL(1.0, nodes[0].data.velocity[1]);
        BOOST_CHECK_EQUAL(1.0, nodes[0].data.velocity[2]);
        BOOST_CHECK_EQUAL(1.0, nodes[0].data.acceleration[0]);
        BOOST_CHECK_EQUAL(1.0, nodes[0].data.acceleration[1]);
        BOOST_CHECK_EQUAL(1.0, nodes[0].data.acceleration[2]);
    }

    BOOST_AUTO_TEST_CASE(PrimDataHashTest) {

    }
BOOST_AUTO_TEST_SUITE_END()
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../include/map.h"


BOOST_AUTO_TEST_SUITE(MapTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
    std::vector<std::vector<int>> map;
    int rows, cols;

    boost::tie(map, rows, cols) = read_2d_map("data/maps_tests/sample_map_no_obstacles.json");
    BOOST_CHECK(!map.empty());
}

BOOST_AUTO_TEST_CASE(CheckCorrectTile)
{
    std::vector<std::vector<int>> map;
    int rows, cols;

    boost::tie(map, rows, cols) = read_2d_map("data/maps_tests/sample_map_one_obstacle.json");
    BOOST_CHECK_EQUAL(map[1][1], 1);
    BOOST_CHECK_EQUAL(map[1][2], 1);
    BOOST_CHECK_EQUAL(map[3][2], 1);
}


BOOST_AUTO_TEST_CASE(ConstructorWrong)
{
    std::vector<std::vector<int>> map;
    int rows, cols;

    boost::tie(map, rows, cols) = read_2d_map("/data/maps_tests/fake_map.json");
    BOOST_CHECK(map.empty());
}

BOOST_AUTO_TEST_SUITE_END()
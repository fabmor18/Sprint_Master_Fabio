#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../include/primitives.h"
#include "../include/map_objects.h"
#include "../include/setup.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

BOOST_AUTO_TEST_SUITE(PrimitiveTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
  auto a = Primitive({10.0,20.0,30.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,10.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,0.0},
                          {{0,0,0}},
                          0.0,
                          0);

  BOOST_CHECK_EQUAL(10, a.get_initial_condition().acceleration[2]);
}

BOOST_AUTO_TEST_CASE(DumpToFileSingle)
{
  auto a = Primitive({10.0,20.0,30.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,10.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,0.0},
                          {{0,0,0}},
                          0.0,
                          0);
  json b = a.to_json();

  std::ofstream outputFile("Boost_test/primitives_test_files/output.json");

  if (outputFile.is_open()) {
    // Write the JSON object to the file
    outputFile << std::setw(4) << b << std::endl;

    // Close the file
    outputFile.close();
  }

  BOOST_CHECK(boost::filesystem::exists("Boost_test/primitives_test_files/output.json"));

  // Optionally, check additional conditions or content of the file
  BOOST_CHECK(boost::filesystem::file_size("Boost_test/primitives_test_files/output.json") > 0);
}

BOOST_AUTO_TEST_CASE(DumpToFileMultiple)
{
  std::vector<json> primitives;
  primitives.reserve(5);
  for(int i = 0; i < 5; i++) {
      primitives.push_back(
      Primitive({1.0,1.0,1.0},
                  {1.0,1.0,1.0},
                  {1.0,1.0,1.0},
                  {1.0,1.0,1.0},
                  {1.0,1.0,1.0},
                  {1.0,1.0,1.0},
                  {{1,1,1}},
                  1.0 * i,
                  0).to_json()
        );
    };

  json data;
  data["primitives_tests"] = primitives;
  std::ofstream outputFile("Boost_test/primitives_test_files/output_list.json");

  if (outputFile.is_open()) {
    outputFile << data << std::endl;

    // Close the file
    outputFile.close();
  }

  BOOST_CHECK(boost::filesystem::exists("Boost_test/primitives_test_files/output_list.json"));

  // Optionally, check additional conditions or content of the file
  BOOST_CHECK(boost::filesystem::file_size("Boost_test/primitives_test_files/output_list.json") > 0);
}

BOOST_AUTO_TEST_CASE(FromFileSingle) {
    std::ifstream input_file("Boost_test/primitives_test_files/output.json");
    if (!input_file.is_open()) {
      std::cerr << "Error opening file" << std::endl;
      return;
    }
    json data_primitive;
    input_file >> data_primitive;
    input_file.close();

    auto a = Primitive(data_primitive, 0, TEST);

  BOOST_CHECK_EQUAL(10, a.get_initial_condition().acceleration[2]);
}

BOOST_AUTO_TEST_CASE(FromFileMultiple) {
  std::ifstream input_file("Boost_test/primitives_test_files/output_list.json");
  if (!input_file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }
  json data_primitive;
  input_file >> data_primitive;
  input_file.close();

  std::vector<Primitive> primitives;

  for(const auto& elem : data_primitive["primitives_tests"]) {
    primitives.emplace_back(elem, 0, TEST);
  }

  BOOST_CHECK_EQUAL(0, primitives[0].get_cost());
  BOOST_CHECK_EQUAL(1, primitives[1].get_cost());
  BOOST_CHECK_EQUAL(2, primitives[2].get_cost());
  BOOST_CHECK_EQUAL(3, primitives[3].get_cost());
  BOOST_CHECK_EQUAL(4, primitives[4].get_cost());
}


BOOST_AUTO_TEST_CASE(LoadPrimitivesIntoMap) {
  std::unordered_map<node_data, std::vector<Primitive>, PrimDataHash, PrimEqualNodes> primitives;

  std::ifstream input_file("Boost_test/primitives_test_files/output_list.json");
  if (!input_file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }
  json data_primitive;
  input_file >> data_primitive;
  input_file.close();

  for(const auto& elem : data_primitive["primitives_tests"]) {
    auto prim = Primitive(elem, 0, TEST);
    primitives[prim.get_initial_condition()].emplace_back(prim);
  }
  node_data a = {{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0}};
  node_data b = {{2.0,1.0,1.0},{1.0,1.0,1.0},{3.0,1.0,1.0}};

  BOOST_CHECK(!primitives.empty());
  BOOST_CHECK(!primitives[a].empty());
  BOOST_CHECK(primitives[b].empty());
}

BOOST_AUTO_TEST_CASE(ApplyPrimitiveTest) {

  auto start = Node(
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0},
      {1.0,1.0,1.0});

  const auto primitive = Primitive({10.0,20.0,30.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,0.0},
                          {1.0,2.0,3.0},
                          {0.0,0.0,0.0},
                          {0.0,0.0,0.0},
                          {{0,0,0}},
                          0.0,
                          0);

  Node end = primitive.apply_primitive(start);

  BOOST_CHECK_EQUAL(1.0, start.data.position[0]);
  BOOST_CHECK_EQUAL(1.0, start.data.position[1]);
  BOOST_CHECK_EQUAL(1.0, start.data.position[2]);
  BOOST_CHECK_EQUAL(1.0, start.data.velocity[0]);
  BOOST_CHECK_EQUAL(1.0, start.data.velocity[1]);
  BOOST_CHECK_EQUAL(1.0, start.data.velocity[2]);
  BOOST_CHECK_EQUAL(1.0, start.data.acceleration[0]);
  BOOST_CHECK_EQUAL(1.0, start.data.acceleration[1]);
  BOOST_CHECK_EQUAL(1.0, start.data.acceleration[2]);

  BOOST_CHECK_EQUAL(2.0, end.data.position[0]);
  BOOST_CHECK_EQUAL(3.0, end.data.position[1]);
  BOOST_CHECK_EQUAL(4.0, end.data.position[2]);
  BOOST_CHECK_EQUAL(0.0, end.data.velocity[0]);
  BOOST_CHECK_EQUAL(0.0, end.data.velocity[1]);
  BOOST_CHECK_EQUAL(0.0, end.data.velocity[2]);
  BOOST_CHECK_EQUAL(0.0, end.data.acceleration[0]);
  BOOST_CHECK_EQUAL(0.0, end.data.acceleration[1]);
  BOOST_CHECK_EQUAL(0.0, end.data.acceleration[2]);

  BOOST_CHECK_EQUAL(1.0, start.data.position[0]);
  BOOST_CHECK_EQUAL(1.0, start.data.position[1]);
  BOOST_CHECK_EQUAL(1.0, start.data.position[2]);
  BOOST_CHECK_EQUAL(1.0, start.data.velocity[0]);
  BOOST_CHECK_EQUAL(1.0, start.data.velocity[1]);
  BOOST_CHECK_EQUAL(1.0, start.data.velocity[2]);
  BOOST_CHECK_EQUAL(1.0, start.data.acceleration[0]);
  BOOST_CHECK_EQUAL(1.0, start.data.acceleration[1]);
  BOOST_CHECK_EQUAL(1.0, start.data.acceleration[2]);
}





BOOST_AUTO_TEST_SUITE_END()
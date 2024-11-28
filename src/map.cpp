#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../include/map.h"

using json = nlohmann::json;

//! File containing functions that manipulate the map
/*!
 * @file
 * This file contains the functions that perform manipulation over the map such as reading or modifying it.
 */

boost::tuple<std::vector<std::vector<int>>, int, int> read_2d_map(const std::string& map_file) {
    /*!
     * This function reads and returns a 2d map from a file.
     * @param map_file a string pointing to the location of the json file of the map.
     * @returns boost::tuple<std::vector<std::vector<int>>, int, int> three different values. A vector of vectors where each value
     * is a cell of the map, an int representing the number of rows and an int representing the number of columns.
     */
  std::ifstream file(map_file);

  if (!file.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return {};
  }

  json jsonData;
  file >> jsonData;

  file.close();

  const int rows = jsonData["info"]["size_x"];
  const int cols = jsonData["info"]["size_y"];

  json mapData = jsonData["map"];
  std::vector<std::vector<int>> twoDArray(rows, std::vector<int>(cols, 0));

  for (int i = 0; i < rows; ++i) {
    const json& currentRow = mapData[i];

    for (int j = 0; j < cols; ++j) {
      twoDArray[i][j] = currentRow[j];
    }
  }

  return boost::make_tuple(twoDArray, rows, cols);
}

#include <vector>
#include <tuple>
#include <cmath>
#include <memory>
#include <iostream>
#include <sstream>

#include "parameters.h"
#include "control_levels.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#ifndef SPRINT_INCLUDE_MAP_OBJECTS_H_
#define SPRINT_INCLUDE_MAP_OBJECTS_H_



/*!
 * @file
*/


typedef struct node_data{
    /*!
     * @struct node_data
     * Struct that defines the three values used to uniquely describe a Node
     *
     * @var node_data::position
     * array describing the three position value of a Node
     *
     * @var node_data::velocity
     * array describing the three velocity components of a Node
     *
     * @var node_data::acceleration
     * array describing the three acceleration components of a Node
     */
  std::array<float, 3> position;
  std::array<float, 3> velocity;
  std::array<float, 3> acceleration;

} node_data;


/*!
 * Class describing a Node, each one has a node_data struct containing the information about position, velocity and
 * acceleration and a fourth array for jerk information.
 */
class Node {
 public:
  Node(std::array<float, 3> position,
       std::array<float, 3> velocity,
       std::array<float, 3> acceleration,
       std::array<float, 3> jerk
  );
  Node();
  Node(const Node& input_node);
  node_data data{};
  std::array<float, 3> jerk{};
  bool compare_nodes(const Node& comparator, Controls control_level, bool goal);
  [[nodiscard]] float get_euclidean_dist(Node target) const;
  [[nodiscard]] json to_json() const;

  friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
    os << "Position: " << obj.data.position[0] << " " << obj.data.position[1] << " " << obj.data.position[2] << "\n";
    os << "Velocity: " << obj.data.velocity[0] << " " << obj.data.velocity[1] << " " << obj.data.velocity[2] << "\n";
    os << "Acceleration: " << obj.data.acceleration[0] << " " << obj.data.acceleration[1] << " " << obj.data.acceleration[2];
    return os;
  }
};


#endif //SPRINT_INCLUDE_MAP_OBJECTS_H_

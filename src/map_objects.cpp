#include "../include/map_objects.h"


Node::Node(std::array<float, 3> position,
           std::array<float, 3> velocity,
           std::array<float, 3> acceleration,
           std::array<float, 3> jerk) {
  this->data.position = position;
  this->data.velocity = velocity;
  this->data.acceleration = acceleration;
  this->jerk = jerk;
}

Node::Node() {
    this->data.position = std::array<float, 3>{-1.0,-1.0,-1.0};
    this->data.velocity = std::array<float, 3>{-1.0,-1.0,-1.0};
    this->data.acceleration = std::array<float, 3>{-1.0,-1.0,-1.0};
    this->jerk = std::array<float, 3>{-1.0,-1.0,-1.0};
}

Node::Node(const Node &input_node) {
    /*!
     * Node constructor that creates a copy of the input node.
     */
    this->data.position = std::array<float, 3>{0.0,0.0,0.0};

    this->data.position[0] += input_node.data.position[0];
    this->data.position[1] += input_node.data.position[1];
    this->data.position[2] += input_node.data.position[2];

    this->data.velocity = std::array<float, 3>{0.0,0.0,0.0};
    this->data.velocity[0] += input_node.data.velocity[0];
    this->data.velocity[1] += input_node.data.velocity[1];
    this->data.velocity[2] += input_node.data.velocity[2];

    this->data.acceleration = std::array<float, 3>{0.0,0.0,0.0};
    this->data.acceleration[0] += input_node.data.acceleration[0];
    this->data.acceleration[1] += input_node.data.acceleration[1];
    this->data.acceleration[2] += input_node.data.acceleration[2];

    this->jerk = std::array<float, 3>{0.0,0.0,0.0};
    this->jerk[0] += input_node.jerk[0];
    this->jerk[1] += input_node.jerk[1];
    this->jerk[2] += input_node.jerk[2];
}

bool Node::compare_nodes(const Node& comparator, Controls control_level, bool goal) {
    /*!
     * This method compares two nodes returning a boolean value based on the comparison. Takes a control level
     * as input since for different control levels the comparison considers different parameters.
     * @param comparator Node to compare the current with.
     * @param control_level the control level adopted for the comparison.
     * @returns bool value with the result of the comparison.
     */
     bool eq_position;

     if (goal) {
         eq_position = (
                         pow((this->data.position[0] - comparator.data.position[0]), 2) +
                         pow((this->data.position[1] - comparator.data.position[1]), 2) +
                         pow((this->data.position[2] - comparator.data.position[2]), 2))
                                 < pow(goal_accuracy, 2);

     } else {
         eq_position = fabs(this->data.position[0] - comparator.data.position[0]) < epsilon &&
                       fabs(this->data.position[1] - comparator.data.position[1]) < epsilon &&
                       fabs(this->data.position[2] - comparator.data.position[2]) < epsilon;
     }

    bool eq_vel = fabs(this->data.velocity[0] - comparator.data.velocity[0]) < epsilon &&
                  fabs(this->data.velocity[1] - comparator.data.velocity[1]) < epsilon &&
                  fabs(this->data.velocity[2] - comparator.data.velocity[2]) < epsilon;

    bool eq_acc = fabs(this->data.acceleration[0] - comparator.data.acceleration[0]) < epsilon &&
                  fabs(this->data.acceleration[1] - comparator.data.acceleration[1]) < epsilon &&
                  fabs(this->data.acceleration[2] - comparator.data.acceleration[2]) < epsilon;

    if (control_level == TEST) {
      return (
              eq_position && eq_vel && eq_acc
      );
    } else if (control_level == VEL) {
      return (
              eq_position && eq_vel
      );
    };

    return false;
}


json Node::to_json() const {
    /*!
     * Function that generates a json data from a Node. It is used to store nodes in a json file for easily
     * and human readable serialization.
     */
    json return_val = {
            {"position", this->data.position},
            {"velocity", this->data.velocity},
            {"acceleration", this->data.acceleration},
            {"jerk", this->jerk},

    };

    return return_val;
}

float Node::get_euclidean_dist(Node target) const {
    auto euclidean = static_cast<float>(
            sqrt(
                    pow(this->data.position[0] - target.data.position[0], 2) +
                    pow(this->data.position[1] - target.data.position[1], 2) +
                    pow(this->data.position[2] - target.data.position[2], 2)
            ));

    return euclidean;
}

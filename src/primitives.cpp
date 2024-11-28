#include "../include/primitives.h"

using json = nlohmann::json;

Primitive::Primitive(const std::array<float, 3> initial_position,
                     const std::array<float, 3> initial_velocity,
                     const std::array<float, 3> initial_acceleration,
                     const std::array<float, 3> final_position,
                     const std::array<float, 3> final_velocity,
                     const std::array<float, 3> final_acceleration,
                     const std::vector<std::array<int, 3>>& path_offsets,
                     const std::vector<std::array<float, 3>>& vel_traj, // AGGIUNTA
                     const float cost,
                     const int id) {

  this->initial_condition.position = initial_position;
  this->initial_condition.velocity = initial_velocity;
  this->initial_condition.acceleration = initial_acceleration;
  this->final_condition.position = final_position;
  this->final_condition.velocity = final_velocity;
  this->final_condition.acceleration = final_acceleration;
  this->path_offsets = path_offsets;
  this->vel_traj = vel_traj; // AGGIUNTA
  this->cost = cost;
  this->id = id;
}

Primitive::Primitive(const json& data, int id, Controls control_level) {
    /*!
     * Constructor for a primitive that takes a json data as input. Takes also a control level as input since
     * depending on it some values might be set to zero. (e.g., if control level is set to VEL then acceleration
     * has no meaning and is set to zero)
     */
  this->initial_condition.position = data["initial_pos"];
  this->initial_condition.velocity = data["initial_vel"];
  this->final_condition.position = data["final_pos"];
  this->final_condition.velocity = data["final_vel"];
  if (control_level == VEL) {
        this->initial_condition.acceleration = {0.0,0.0,0.0};
        this->final_condition.acceleration = {0.0,0.0,0.0};
  } else if (control_level == ACC || control_level == TEST) {
      this->initial_condition.acceleration = data["initial_acc"];
      this->final_condition.acceleration = data["final_acc"];
  }
  this->path_offsets = std::vector<std::array<int, 3>>();
  for (const auto& p: data["path"]) {
      this->path_offsets.emplace_back(p);
  }
  //this->path_offsets = data["path"];
  // this->vel_traj = std::vector<std::array<float, 3>>(); // AGGIUNTA
  // for (const auto& p: data["vel_traj"]) { // AGGIUNTA
  //     this->vel_traj.emplace_back(p); // AGGIUNTA
  // } // AGGIUNTA
  this->cost = data["cost"];
  this->id = id;
}

Primitive::Primitive() {
  this->initial_condition.position = {0.0,0.0,0.0};
  this->initial_condition.velocity = {0.0,0.0,0.0};
  this->initial_condition.acceleration = {0.0,0.0,0.0};
  this->final_condition.position = {0.0,0.0,0.0};
  this->final_condition.velocity = {0.0,0.0,0.0};
  this->final_condition.acceleration = {0.0,0.0,0.0};
  this->path_offsets = {};
  this->vel_traj = {}; // AGGIUNTA
  this->cost = 0.0;
  this->id = -1;
}



Node Primitive::apply_primitive(const Node& start) const {
    /*!
     * This function applies the current primitive to the given Node.
     * The new node position is equal to the old node position plus the values of the final_condition position
     * while velocity and acceleration are simply overwritten with the new values.
     * @param start The Node where the primitive is applied.
     * @returns The Node reached.
     */
    Node result = start;

    result.data.position[0] += this->final_condition.position[0];
    result.data.position[1] += this->final_condition.position[1];
    result.data.position[2] += this->final_condition.position[2];

    result.data.velocity[0] = this->final_condition.velocity[0];
    result.data.velocity[1] = this->final_condition.velocity[1];
    result.data.velocity[2] = this->final_condition.velocity[2];

    result.data.acceleration[0] = this->final_condition.acceleration[0];
    result.data.acceleration[1] = this->final_condition.acceleration[1];
    result.data.acceleration[2] = this->final_condition.acceleration[2];

    return result;
}


float Primitive::get_cost() const {
    /*!
     * Getter function for cost parameter.
     */
    return this->cost;
}

node_data Primitive::get_initial_condition() const {
    /*!
     * Getter function for initial_condition parameter.
     */
    return this->initial_condition;
}
node_data Primitive::get_final_condition() const {
    /*!
     * Getter function for final_condition parameter.
     */
    return this->final_condition;
}

std::vector<std::array<int, 3>> Primitive::get_path() const {
    /*!
     * Getter function for path_offsets parameter.
     */
    return this->path_offsets;
}

std::vector<std::array<float, 3>> Primitive::get_vel_traj() const { // AGGIUNTA
    /*!
     * Getter function for vel_traj parameter.
     */
    return this->vel_traj; // AGGIUNTA
}

int Primitive::get_id() const {
    /*!
     * Getter function for id parameter.
     */
    return this->id;
}

json Primitive::to_json() const {
    /*!
     * Function that generates a json data from a Primitive. It is used to store primitives in a json file for easily
     * and human readable serialization.
     */
      json return_val = {
          {"initial_pos", this->initial_condition.position},
          {"initial_vel", this->initial_condition.velocity},
          {"initial_acc", this->initial_condition.acceleration},
          {"final_pos", this->final_condition.position},
          {"final_vel", this->final_condition.velocity},
          {"final_acc", this->final_condition.acceleration},
          {"path", this->path_offsets},
          {"vel_traj", this->vel_traj}, // AGGIUNTA
          {"cost", this->cost}
      };

    return return_val;
}


#ifndef SPRINT_SRC_PRIMITIVES_H_
#define SPRINT_SRC_PRIMITIVES_H_

#include "map_objects.h"
#include <nlohmann/json.hpp>
#include <utility>
#include <string>


/*!
 * This class defines a motion primitive used by the algorithm. Each Primitive is identified by two node_data
 * structures, one defining the initial condition under which the primitive can be applied and one defining the
 * final condition reached after the application of the primitive.
 * Each primitive also contains a variable called path_offsets that is a vector of int arrays of size 3 where each
 * array represents a checkpoint for the collision checking stored as relative position difference with respect to
 * the starting node.
 * Each primitive also has a cost, expressed as a float and an int id.
 */

class Primitive {
public:
    explicit Primitive(
        std::array<float, 3> initial_position,
        std::array<float, 3> initial_velocity,
        std::array<float, 3> initial_acceleration,
        std::array<float, 3> final_position,
        std::array<float, 3> final_velocity,
        std::array<float, 3> final_acceleration,
        const std::vector<std::array<int, 3>>& path_offsets,
        const std::vector<std::array<float, 3>>& vel_traj, // AGGIUNTA
        float cost,
        int id
        );
    explicit Primitive(const nlohmann::json& data, int id, Controls control_level);
    explicit Primitive();
    [[nodiscard]] Node apply_primitive(const Node& start) const;
    [[nodiscard]] node_data get_initial_condition() const;
    [[nodiscard]] node_data get_final_condition() const;
    [[nodiscard]] std::vector<std::array<int, 3>> get_path() const;
    [[nodiscard]] std::vector<std::array<float, 3>> get_vel_traj() const; // AGGIUNTA
    [[nodiscard]] float get_cost() const;
    [[nodiscard]] [[maybe_unused]] int get_id() const;
    [[nodiscard]] nlohmann::json to_json() const;

    friend std::ostream& operator<<(std::ostream& os, const Primitive& obj) {
        os << "Initial Position " << obj.get_initial_condition().position[0] << " "
        << obj.get_initial_condition().position[1] << " " << obj.get_initial_condition().position[2] << "\n";
        os << "Initial Velocity " << obj.get_initial_condition().velocity[0] << " "
        << obj.get_initial_condition().velocity[1] << " " << obj.get_initial_condition().velocity[2] << "\n";
        os << "Initial Acceleration " << obj.get_initial_condition().acceleration[0] << " "
        << obj.get_initial_condition().acceleration[1] << " " << obj.get_initial_condition().acceleration[2] << "\n";
        os << "Final Position " << obj.get_final_condition().position[0] << " "
        << obj.get_final_condition().position[1] << " " << obj.get_final_condition().position[2] << "\n";
        os << "Final Velocity " << obj.get_final_condition().velocity[0] << " "
        << obj.get_final_condition().velocity[1] << " " << obj.get_final_condition().velocity[2] << "\n";
        os << "Final Acceleration " << obj.get_final_condition().acceleration[0] << " "
        << obj.get_final_condition().acceleration[1] << " " << obj.get_final_condition().acceleration[2] << "\n";
        os << "Cost " << obj.cost;
        return os;
    }

private:
    node_data initial_condition{};
    node_data final_condition{};
    std::vector<std::array<int, 3>> path_offsets;
    std::vector<std::array<float, 3>> vel_traj; // AGGIUNTA
    float cost;
    int id;
};



#endif //SPRINT_SRC_PRIMITIVES_H_

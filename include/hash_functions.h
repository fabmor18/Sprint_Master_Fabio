#ifndef SPRINT_HASH_FUNCTIONS_H
#define SPRINT_HASH_FUNCTIONS_H

#include "parameters.h"
#include "map_objects.h"

struct NodeDataHash
{
    std::size_t operator()(const node_data s) const noexcept
    {
        const int pos_int = static_cast<int>(
                s.position[0] * hash_epsilon +
                s.position[1] * hash_epsilon +
                s.position[2] * hash_epsilon
        );
        const int vel_int = static_cast<int>(
                s.velocity[0] * hash_epsilon +
                s.velocity[1] * hash_epsilon +
                s.velocity[2] * hash_epsilon
        );
        const int acc_int = static_cast<int>(
                s.acceleration[0] * hash_epsilon +
                s.acceleration[1] * hash_epsilon +
                s.acceleration[2] * hash_epsilon
        );

        int x = (pos_int + vel_int + acc_int);
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;

        return x;
    }

    std::size_t operator()(const Node& s) const noexcept
    {
        const int pos_int = static_cast<int>(
                s.data.position[0] * hash_epsilon +
                s.data.position[1] * hash_epsilon +
                s.data.position[2] * hash_epsilon
        );
        const int vel_int = static_cast<int>(
                s.data.velocity[0] * hash_epsilon +
                s.data.velocity[1] * hash_epsilon +
                s.data.velocity[2] * hash_epsilon
        );
        const int acc_int = static_cast<int>(
                s.data.acceleration[0] * hash_epsilon +
                s.data.acceleration[1] * hash_epsilon +
                s.data.acceleration[2] * hash_epsilon
        );

        int x = (pos_int + vel_int + acc_int);
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;

        return x;
    }
};

struct NodeDataEqual {
    bool operator()(const node_data& lhs, const node_data& rhs) const {
        return (
                fabs(lhs.position[0] - rhs.position[0]) < epsilon &&
                fabs(lhs.position[1] - rhs.position[1]) < epsilon &&
                fabs(lhs.position[2] - rhs.position[2]) < epsilon &&
                fabs(lhs.velocity[0] - rhs.velocity[0]) < epsilon &&
                fabs(lhs.velocity[1] - rhs.velocity[1]) < epsilon &&
                fabs(lhs.velocity[2] - rhs.velocity[2]) < epsilon &&
                fabs(lhs.acceleration[0] - rhs.acceleration[0]) < epsilon &&
                fabs(lhs.acceleration[1] - rhs.acceleration[1]) < epsilon &&
                fabs(lhs.acceleration[2] - rhs.acceleration[2]) < epsilon
        );
    };

    bool operator()(const Node& lhs, const Node& rhs) const {
        return (
                fabs(lhs.data.position[0] - rhs.data.position[0]) < epsilon &&
                fabs(lhs.data.position[1] - rhs.data.position[1]) < epsilon &&
                fabs(lhs.data.position[2] - rhs.data.position[2]) < epsilon &&
                fabs(lhs.data.velocity[0] - rhs.data.velocity[0]) < epsilon &&
                fabs(lhs.data.velocity[1] - rhs.data.velocity[1]) < epsilon &&
                fabs(lhs.data.velocity[2] - rhs.data.velocity[2]) < epsilon &&
                fabs(lhs.data.acceleration[0] - rhs.data.acceleration[0]) < epsilon &&
                fabs(lhs.data.acceleration[1] - rhs.data.acceleration[1]) < epsilon &&
                fabs(lhs.data.acceleration[2] - rhs.data.acceleration[2]) < epsilon
        );
    };
};


struct PrimDataHash
{
    std::size_t operator()(const node_data& s) const noexcept
    {
        const int vel_int = static_cast<int>(
                s.velocity[0] * hash_epsilon +
                s.velocity[1] * hash_epsilon +
                s.velocity[2] * hash_epsilon
        );
        const int acc_int = static_cast<int>(
                s.acceleration[0] * hash_epsilon +
                s.acceleration[1] * hash_epsilon +
                s.acceleration[2] * hash_epsilon
        );

        int x = (vel_int + acc_int);
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;

        return x;
    }

    std::size_t operator()(const Node& s) const noexcept
    {

        const int vel_int = static_cast<int>(
                s.data.velocity[0] * hash_epsilon +
                s.data.velocity[1] * hash_epsilon +
                s.data.velocity[2] * hash_epsilon
        );
        const int acc_int = static_cast<int>(
                s.data.acceleration[0] * hash_epsilon +
                s.data.acceleration[1] * hash_epsilon +
                s.data.acceleration[2] * hash_epsilon
        );

        int x = (vel_int + acc_int);
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;

        return x;
    }

};

struct PrimEqualNodes {
    bool operator()(const node_data& lhs, const node_data& rhs) const {
        return (
                fabs(lhs.velocity[0] - rhs.velocity[0]) < epsilon &&
                fabs(lhs.velocity[1] - rhs.velocity[1]) < epsilon &&
                fabs(lhs.velocity[2] - rhs.velocity[2]) < epsilon &&
                fabs(lhs.acceleration[0] - rhs.acceleration[0]) < epsilon &&
                fabs(lhs.acceleration[1] - rhs.acceleration[1]) < epsilon &&
                fabs(lhs.acceleration[2] - rhs.acceleration[2]) < epsilon
        );
    };

};
#endif //SPRINT_HASH_FUNCTIONS_H

#include "../include/heuristics.h"

//! Heuristic implementations file
/*!
 * @file
 * This file contains the implementations of the different heuristics used by the A* algorithm.
 */

float EuclideanHeuristic::calculateHeuristic(Node start, Node goal) const {
    /*!
     * Implementation of a simple euclidean distance.
     * @param Node start
     * @param Node goal
     * @returns float value of the euclidean distance between start and goal.
     */
    auto euclidean_distance = static_cast<float>(sqrt(
            pow((goal.data.position[0] - start.data.position[0]), 2) +
            pow((goal.data.position[1] - start.data.position[1]), 2) +
            pow((goal.data.position[2] - start.data.position[2]), 2)
    ));

    return euclidean_distance * resolution;//max_velocity; // / pow(max_velocity, 2);
}

float ManhattanHeuristic::calculateHeuristic(Node start, Node goal) const {
    /*!
     * Implementation of a simple manhattan distance.
     * @param Node start
     * @param Node goal
     * @returns float value of the manhattan distance between start and goal.
     */

    auto manhattan_distance = static_cast<float>(
            std::abs(start.data.position[0] - goal.data.position[0]) +
            std::abs(start.data.position[1] - goal.data.position[1])
            );

    return manhattan_distance;
}

float TestHeuristic::calculateHeuristic(Node start, Node goal) const {
    return 0;
}

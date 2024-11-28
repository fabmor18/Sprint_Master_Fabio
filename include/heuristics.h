#include "map.h"
#include <cmath>
#ifndef SPRINT_HEURISTICS_H
#define SPRINT_HEURISTICS_H

/*!
 * @file
 * Abstract Heuristic class that each different heuristic needs to inherit from. Exposes one function
 * called calculateHeuristic that returns a float value.
 */
class Heuristic {
public:
    [[nodiscard]] virtual float calculateHeuristic(Node start, Node goal) const = 0;
};

/*!
* Implementation of a simple euclidean distance.
* @param Node start
* @param Node goal
* @returns float value of the euclidean distance between start and goal.
*/
class EuclideanHeuristic : public Heuristic{
public:
    [[nodiscard]] float calculateHeuristic(Node start, Node goal) const override;
};



/*!
* Implementation of a simple manhattan distance.
* @param Node start
* @param Node goal
* @returns float value of the manhattan distance between start and goal.
*/
class ManhattanHeuristic : public Heuristic{
public:
    [[nodiscard]] float calculateHeuristic(Node start, Node goal) const override;
};


/*!
* Implementation of test heuristic.
* @param Node start
* @param Node goal
* @returns a test value.
*/
class TestHeuristic : public Heuristic{
public:
    [[nodiscard]] float calculateHeuristic(Node start, Node goal) const override;
};
#endif //SPRINT_HEURISTICS_H

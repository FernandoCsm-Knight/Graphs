#ifndef CYCLE_DETECTION_TYPE_HPP
#define CYCLE_DETECTION_TYPE_HPP

/**
 * @brief Represents the type of cycle detection algorithm.
 * 
 * - PERMUTATION: The cycle detection algorithm is based on permutations.
 * - WALK: The cycle detection algorithm is based on depth-first search.
 */
enum CycleDetectionType {
    PERMUTATION,
    WALK,
};

#endif
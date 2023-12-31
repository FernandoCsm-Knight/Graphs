/**
 * @file PriorityQueue.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of the priority queue data structure.
 *        It is used to store elements with associated priorities.
 *        The elements are popped in order of priority using a minimum
 *        heap data struct.
 * @version 1.0.0
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PRIORIY_QUEUE_HPP
#define PRIORIY_QUEUE_HPP

#include <iostream>
#include <stdexcept>

#include "MinHeap.hpp"

/**
 * @brief A template class implementing a priority queue data structure.
 * 
 * @tparam T The type of elements stored in the priority queue.
 */
template <class T> class PriorityQueue {
    private:
        MinHeap<T> heap; ///< The minimum heap used to store the elements.

    public:

        /**
         * @brief Add a new element to the priority queue.
         * 
         * @param element The element to be added to the priority queue.
         */
        void push(const T& element) {
            this->heap.add(element);
        }

        /**
         * @brief Remove the element with the highest priority from the priority queue.
         * 
         * @return T The removed element.
         */
        T poll() {
            return this->heap.pop();
        }

        /**
         * @brief Get the element with the highest priority from the priority queue.
         * 
         * @return T The element with the highest priority.
         */
        T peek() const {
            return this->heap.min();
        }

        /**
         * @brief Get the number of elements in the priority queue.
         * 
         * @return int The number of elements in the priority queue.
         */
        int size() const {
            return this->heap.size();
        }

        /**
         * @brief Check if the priority queue is empty.
         * 
         * @return True if the priority queue is empty, false otherwise.
         */
        bool isEmpty() const {
            return this->heap.isEmpty();
        }

        /**
         * @brief Print the priority queue to the output stream.
         * 
         * @param os The output stream.
         * @param queue The priority queue to be printed.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& queue) {
            os << queue.heap;
            return os;
        }

        /**
         * @brief Check if two priority queues are equal.
         * 
         * @param queue The priority queue to be compared.
         * @return True if the priority queues are equal, false otherwise. 
         */
        bool operator==(const PriorityQueue<T>& queue) const {
            return this->heap == queue.heap;
        }

        /**
         * @brief Check if two priority queues are different.
         * 
         * @param queue The priority queue to be compared.
         * @return True if the priority queues are different, false otherwise.
         */
        bool operator!=(const PriorityQueue<T>& queue) const {
            return this->heap != queue.heap;
        }
};


#endif
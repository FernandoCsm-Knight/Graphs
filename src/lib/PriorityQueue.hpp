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
        MinHeap<T> heap;

    public:

        void push(const T& element) {
            this->heap.add(element);
        }

        T pop() {
            return this->heap.pop();
        }

        T peek() const {
            return this->heap.min();
        }

        int size() const {
            return this->heap.size();
        }

        bool isEmpty() const {
            return this->heap.isEmpty();
        }

        friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& queue) {
            os << queue.heap;
            return os;
        }

        bool operator==(const PriorityQueue<T>& queue) const {
            return this->heap == queue.heap;
        }

        bool operator!=(const PriorityQueue<T>& queue) const {
            return this->heap != queue.heap;
        }
};


#endif
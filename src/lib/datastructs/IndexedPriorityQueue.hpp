/**
 * @file IndexedPriorityQueue.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmil.com)
 * @brief Made based on William Fiset implementation that can be 
 *        found at https://github.com/williamfiset/algorithms.
 * @version 1.0.0
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef INDEX_PRIORITY_QUEUE_HPP
#define INDEX_PRIORITY_QUEUE_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief A class that represents an Indexed Priority Queue.
 * 
 * This data structure allows for efficient priority queue operations
 * while maintaining an index on the elements.
 * 
 * @tparam T The type of elements in the priority queue.
 */
template <class T> class IndexedPriorityQueue {
    private:
        int length;          /**< The current number of elements in the queue */
        int cap;             /**< The capacity of the queue */
        int degree;          /**< The degree of the d-ary heap */
        int *child, *parent; /**< Arrays representing child and parent indices */
        int* positionMap;    /**< Array mapping element indices to their positions in the heap */
        int* inverseMap;     /**< Array mapping positions in the heap to element indices */
        T* array;            /**< Array holding the values of the elements */

        /**
         * @brief Restores the heap property by sinking an element down the tree.
         * 
         * @param i The index of the element to sink.
         */
        void sink(int i) {
            int j = this->minChild(i);
            while(j != -1) {
                this->swap(i, j);
                i = j;
                j = this->minChild(i);
            }
        }

        /**
         * @brief Restores the heap property by swimming an element up the tree.
         * 
         * @param i The index of the element to swim.
         */
        void swim(int i) {
            while(this->array[this->inverseMap[i]] < this->array[this->inverseMap[this->parent[i]]]) {
                this->swap(i, this->parent[i]);
                i = this->parent[i];
            }
        }

        /**
         * @brief Finds the minimum child of a given node.
         * 
         * @param i The index of the node.
         * @return int The index of the minimum child or -1 if no child exists.
         */
        int minChild(int i) {
            int idx = -1;
            int start = this->child[i];
            int end = std::min(this->length, start + this->degree);

            for(int j = start; j < end; j++) 
                if(this->array[this->inverseMap[j]] < this->array[this->inverseMap[i]]) 
                    idx = i = j;

            return idx;
        }

        /**
         * @brief Swaps two elements in the heap.
         * 
         * @param i The index of the first element.
         * @param j The index of the second element.
         */
        void swap(int i, int j) {
            this->positionMap[this->inverseMap[j]] = i;
            this->positionMap[this->inverseMap[i]] = j;

            int tmp = this->inverseMap[i];
            this->inverseMap[i] = this->inverseMap[j];
            this->inverseMap[j] = tmp;
        }

    public:

        /**
         * @brief Construct a new Indexed Priority Queue object.
         * 
         * @param capacity The capacity of the priority queue.
         * @param degree The degree of the d-ary heap.
         */
        IndexedPriorityQueue(int capacity = 3, int degree = 2) {
            if(degree < 2 || capacity < degree + 1) 
                throw std::invalid_argument("Invalid degree or capacity.");
    
            this->degree = degree;
            this->cap = capacity;
            this->length = 0;

            this->child = new int[this->cap];
            this->parent = new int[this->cap];
            this->positionMap = new int[this->cap];
            this->inverseMap = new int[this->cap];
            this->array = new T[this->cap];

            for(int i = 0; i < this->cap; ++i) {
                this->child[i] = i*this->degree + 1;
                this->parent[i] = (i - 1)/this->degree;
                this->positionMap[i] = -1;
                this->inverseMap[i] = -1;
            }
        }

        /**
         * @brief Construct a new Indexed Priority Queue object by copying another.
         * 
         * @param queue The IndexedPriorityQueue to copy from.
         */
        IndexedPriorityQueue(const IndexedPriorityQueue<T>& queue) {
            this->degree = queue.degree;
            this->cap = queue.cap;
            this->length = queue.length;
        }

        /**
         * @brief Destroy the Indexed Priority Queue object.
         */
        ~IndexedPriorityQueue() {
            delete[] this->child;
            delete[] this->parent;
            delete[] this->positionMap;
            delete[] this->inverseMap;
            delete[] this->array;
        }

        /**
         * @brief Assignment operator for IndexedPriorityQueue.
         * 
         * @param queue The IndexedPriorityQueue to assign from.
         * @return IndexedPriorityQueue& Reference to the assigned object.
         */
        IndexedPriorityQueue& operator=(const IndexedPriorityQueue<T>& queue) {
            if(this != &queue) {
                this->degree = queue.degree;
                this->cap = queue.cap;
                this->length = queue.length;
            }

            return *this;
        }

        /**
         * @brief Get the size of the priority queue.
         * 
         * @return int The number of elements in the queue.
         */
        inline int size() const { return this->length; }

        /**
         * @brief Check if the priority queue is empty.
         * 
         * @return true If the queue is empty.
         * @return false If the queue is not empty.
         */
        inline bool isEmpty() const { return this->length == 0; }

        /**
         * @brief Check if the priority queue is full.
         * 
         * @return true If the queue is full.
         * @return false If the queue is not full.
         */
        inline bool isFull() const { return this->length == this->cap; }

        /**
         * @brief Check if a given index is contained in the queue.
         * 
         * @param k The index to check.
         * @return true If the index is in the queue.
         * @return false If the index is not in the queue.
         * @throws std::invalid_argument If the index is out of bounds.
         */
        bool contains(int k) const {
            if(k < 0 || k >= this->cap)
                throw std::invalid_argument("Invalid index.");

            return this->positionMap[k] != -1;
        }

        /**
         * @brief Get the index of the element with the minimum key.
         * 
         * @return int The index of the minimum key.
         * @throws std::out_of_range If the queue is empty.
         */
        int minKey() {
            if(this->isEmpty())
                throw std::out_of_range("Queue is empty.");

            return this->inverseMap[0];
        }

        /**
         * @brief Remove and return the index of the element with the minimum key.
         * 
         * @return int The index of the removed element.
         */
        int pollKey() {
            int k = this->minKey();
            this->remove(k);
            return k;
        }

        /**
         * @brief Get the value of the element with the minimum key.
         * 
         * @return T The value of the element with the minimum key.
         * @throws std::out_of_range If the queue is empty.
         */
        T peek() {
            if(this->isEmpty())
                throw std::out_of_range("Queue is empty.");

            return this->array[this->inverseMap[0]];
        }

        /**
         * @brief Remove and return the value of the element with the minimum key.
         * 
         * @return T The value of the removed element.
         */
        T poll() {
            T value = this->peek();
            this->remove(this->minKey());
            return value;
        }

        /**
         * @brief Insert a new element into the priority queue.
         * 
         * @param k The index of the element.
         * @param value The value of the element.
         * @throws std::invalid_argument If the index is already in the queue.
         */
        void insert(int k, const T& value) {
            if(this->contains(k))
                throw std::invalid_argument("Index already exists.");
            
            this->positionMap[k] = this->length;
            this->inverseMap[this->length] = k;
            this->array[k] = value;

            this->swim(this->length++);
        }

        /**
         * @brief Get the value of an element by its index.
         * 
         * @param k The index of the element.
         * @return T The value of the element.
         * @throws std::invalid_argument If the index is not in the queue.
         */
        T valueOf(int k) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            return this->array[k];
        }

        /**
         * @brief Remove an element from the priority queue.
         * 
         * @param k The index of the element to remove.
         * @return T The value of the removed element.
         * @throws std::invalid_argument If the index is not in the queue.
         */
        T remove(int k) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            int idx = this->positionMap[k];
            this->swap(idx, --this->length);
            this->swim(idx);
            this->sink(idx);

            T value = this->array[k];
            this->positionMap[k] = -1;
            this->inverseMap[this->length] = -1;
            this->array[k] = T();

            return value;
        }

        /**
         * @brief Change the value of an element in the queue.
         * 
         * @param k The index of the element.
         * @param value The new value of the element.
         * @return T The old value of the element.
         * @throws std::invalid_argument If the index is not in the queue.
         */
        T change(int k, T value) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            T oldValue = this->array[k];

            this->array[k] = value;
            this->sink(this->positionMap[k]);
            this->swim(this->positionMap[k]);

            return oldValue;
        }

        /**
         * @brief Decrease the value of an element in the queue.
         * 
         * @param k The index of the element.
         * @param value The new value of the element.
         * @throws std::invalid_argument If the index is not in the queue.
         */
        void decrease(int k, T value) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            if(value < this->array[k]) {
                this->array[k] = value;
                this->swim(this->positionMap[k]);
            }
        }

        /**
         * @brief Increase the value of an element in the queue.
         * 
         * @param k The index of the element.
         * @param value The new value of the element.
         * @throws std::invalid_argument If the index is not in the queue.
         */
        void increase(int k, T value) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            if(this->array[k] < value) {
                this->array[k] = value;
                this->sink(this->positionMap[k]);
            }
        }

        /**
         * @brief Clear the priority queue.
         * 
         * Resets the priority queue, removing all elements.
         */
        void clear() {
            for(int i = 0; i < this->length; ++i) {
                this->positionMap[this->inverseMap[i]] = -1;
                this->inverseMap[i] = -1;
                this->array[i] = T();
            }

            this->length = 0;
        }
        
        /**
         * @brief Overloaded stream insertion operator for the IndexedPriorityQueue.
         * 
         * @param strm The output stream.
         * @param queue The priority queue to output.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& strm, const IndexedPriorityQueue<T>& queue) {
            strm << "[";
            for(int i = 0; i < queue.length; ++i) {
                strm << queue.array[queue.inverseMap[i]];
                if(i != queue.length - 1) strm << ", ";
            }
            return strm << "]";
        }
};

#endif
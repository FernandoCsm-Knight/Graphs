/**
 * @file MinHeap.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of the MinHeap data structure.
 * @version 1.0.0
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief A class that implements a Min Heap data structure.
 * 
 * The Min Heap is a binary tree-based data structure where the parent node 
 * is always less than or equal to its child nodes. This implementation supports 
 * dynamic resizing and several operations including insertion, removal, and access.
 * 
 * @tparam T The type of elements stored in the heap.
 */
template <class T> class MinHeap {
    private:
        T* array;         /**< The array to store heap elements */
        int length;       /**< The current number of elements in the heap */
        int cap;          /**< The capacity of the heap */
        bool isDynamic;   /**< Flag indicating if the heap is dynamically resizable */
        
        /**
         * @brief Get the index of the parent of a given node.
         * 
         * @param idx The index of the current node.
         * @return int The index of the parent node.
         */
        inline int parent(int idx) const { return (idx - 1) / 2; }

        /**
         * @brief Get the index of the left child of a given node.
         * 
         * @param idx The index of the current node.
         * @return int The index of the left child node.
         */
        inline int left(int idx) const { return idx * 2 + 1; } 

        /**
         * @brief Get the index of the right child of a given node.
         * 
         * @param idx The index of the current node.
         * @return int The index of the right child node.
         */
        inline int right(int idx) const { return idx * 2 + 2;}

        /**
         * @brief Resize the heap array to accommodate more elements.
         * 
         * This method doubles the current capacity of the heap.
         */
        void resize() {
            this->cap *= 2;
            T* temp = new T[this->cap];

            for(int i = 0; i < this->length; i++) 
                temp[i] = this->array[i];

            delete[] this->array;
            this->array = temp;
        }

        /**
         * @brief Sift up the element at the given index to restore the heap property.
         * 
         * @param idx The index of the element to sift up.
         */
        void siftUp(int idx) {
            int p = this->parent(idx);

            while(idx != 0 && this->array[p] > this->array[idx]) {
                this->swap(idx, p);
                idx = p;
                p = this->parent(idx);
            }
        }

        /**
         * @brief Sift down the element at the given index to restore the heap property.
         * 
         * @param idx The index of the element to sift down.
         */
        void siftDown(int idx) {
            int l = this->left(idx),
                r = this->right(idx),
                min = idx;

            while((l < this->length && this->array[l] < this->array[idx]) || 
                  (r < this->length && this->array[r] < this->array[idx])) {
                
                min = r >= this->length || this->array[l] < this->array[r] ? l : r;
                this->swap(idx, min);

                idx = min;
                l = this->left(idx);
                r = this->right(idx);
            }
        }


        /**
         * @brief Get the index of the given element in the heap.
         * 
         * @param element The element to find in the heap.
         * @return int The index of the element or -1 if not found.
         */
        int indexOf(const T& element) const {
            int idx = 0;

            while(idx < length) {
                if(array[idx] == element) 
                    return idx; 

                if(element < array[idx]) 
                    idx = left(idx);
                else 
                    idx = right(idx);
            }

            return -1;
        }

        /**
         * @brief Swap two elements in the heap array.
         * 
         * @param i The index of the first element.
         * @param j The index of the second element.
         */
        void swap(int i, int j) {
            T tmp = this->array[i];
            this->array[i] = this->array[j];
            this->array[j] = tmp;
        }

    public:

        /**
         * @brief Construct a new MinHeap object with a default capacity.
         * 
         * The default capacity is 10 and the heap is dynamically resizable.
         */
        MinHeap() {
            this->array = new T[10];
            this->isDynamic = true;
            this->length = 0;
            this->cap = 10;
        }

        /**
         * @brief Copy constructor for MinHeap.
         * 
         * @param heap The heap to copy.
         */
        MinHeap(const MinHeap<T>& heap) {
            this->array = new T[heap.capacity()];
            this->isDynamic = heap.isDynamic;
            this->length = heap.size();
            this->cap = heap.capacity();

            for(int i = 0; i < this->length; i++) 
                this->array[i] = heap.array[i];
        }

        /**
         * @brief Construct a new MinHeap object from an existing array.
         * 
         * The heap is built from the array and is not dynamically resizable.
         * 
         * @param arr The array to build the heap from.
         * @param capacity The size of the array.
         */
        MinHeap(const T* arr, int capacity) {
            this->array = new T[capacity];
            this->isDynamic = false;
            this->length = capacity;
            this->cap = capacity;

            for(int i = 0; i < this->length; i++) 
                this->array[i] = arr[i];

            for(int i = (this->length - 2) / 2; i >= 0; --i) 
                this->heapify(i);
        }

        /**
         * @brief Construct a new MinHeap object with a specific capacity.
         * 
         * The heap is not dynamically resizable.
         * 
         * @param capacity The capacity of the heap.
         */
        MinHeap(int capacity) {
            this->array = new T[capacity];
            this->isDynamic = false;
            this->length = 0;
            this->cap = capacity;
        }

        /**
         * @brief Destroy the MinHeap object.
         */
        ~MinHeap() {
            delete[] this->array;
        }

        /**
         * @brief Get the number of elements in the heap.
         * 
         * @return int The current size of the heap.
         */
        inline int size() const { return this->length; }

        /**
         * @brief Get the capacity of the heap.
         * 
         * @return int The capacity of the heap.
         */
        inline int capacity() const { return this->cap; }

        /**
         * @brief Check if the heap is full.
         * 
         * @return true If the heap is full and not resizable.
         * @return false Otherwise.
         */
        inline bool isFull() const { return !this->isDynamic && this->length == this->cap; }
        
        /**
         * @brief Check if the heap is empty.
         * 
         * @return true If the heap is empty.
         * @return false Otherwise.
         */
        inline bool isEmpty() const { return this->length == 0; }

        /**
         * @brief Add a new element to the heap.
         * 
         * @param element The element to add.
         */
        void add(const T& element) {
            if(this->isDynamic && this->length >= this->cap * 0.75)
                this->resize();

            this->array[this->length++] = element;
            this->siftUp(this->length - 1);
        }

        /**
         * @brief Replace an element at the given index with a new value.
         * 
         * @param idx The index of the element to replace.
         * @param element The new element.
         * @return T The old element that was replaced.
         * @throws std::out_of_range If the index is out of range.
         */
        T replace(int idx, const T& element) {
            if(idx < 0 || idx >= this->length)
                throw std::out_of_range("Index out of range");

            T res = this->array[idx];
            this->array[idx] = element;

            if(element < res)
                this->siftUp(idx);
            else
                this->siftDown(idx);

            return res;
        }

        /**
         * @brief Remove and return the minimum element from the heap.
         * 
         * @return T The minimum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T pop() {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            T element = this->array[0];
            this->array[0] = this->array[--this->length];
            this->siftDown(0);

            return element;
        }

        /**
         * @brief Get the minimum element in the heap without removing it.
         * 
         * @return T The minimum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T min() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            return this->array[0];
        }

        /**
         * @brief Get the maximum element in the heap.
         * 
         * @return T The maximum element in the heap.
         * @throws std::out_of_range If the heap is empty.
         */
        T max() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            int max = 0;

            for(int i = 1; i < this->length; i++)
                if(this->array[i] > this->array[max])
                    max = i;

            return this->array[max];
        }

        /**
         * @brief Check if the heap contains a specific element.
         * 
         * @param element The element to check for.
         * @return true If the element is in the heap.
         * @return false Otherwise.
         */
        bool contains(const T& element) const {
            return this->indexOf(element) != -1;
        }

        /**
         * @brief Clear all elements from the heap.
         * 
         * Resets the heap, removing all elements.
         */
        void clear() {
            this->length = 0;
        }

        /**
         * @brief Access an element in the heap by index.
         * 
         * @param idx The index of the element.
         * @return T& Reference to the element.
         * @throws std::out_of_range If the index is out of range.
         */
        T& operator[](int idx) {
            if(idx < 0 || idx >= this->length)
                throw std::out_of_range("Index out of range");

            return this->array[idx];
        }

        /**
         * @brief Assignment operator for MinHeap.
         * 
         * @param heap The heap to assign from.
         * @return MinHeap<T>& Reference to the assigned heap.
         */
        MinHeap<T>& operator=(const MinHeap<T>& heap) {
            if(this != &heap) {
                delete[] this->array;

                this->isDynamic = heap.isDynamic;
                this->length = heap.size();
                this->cap = heap.capacity();
                this->array = new T[heap.capacity()];

                for(int i = 0; i < this->length; i++) 
                    this->array[i] = heap.array[i];
            }

            return *this;
        }

        /**
         * @brief Output the elements of the heap to an output stream.
         * 
         * @param out The output stream.
         * @param heap The heap to output.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& out, const MinHeap<T>& heap) {
            for(int i = 0; i < heap.length; i++)
                out << heap.array[i] << " ";
            
            return out;
        }

        /**
         * @brief Compare two heaps for equality.
         * 
         * @param heap1 The first heap.
         * @param heap2 The second heap.
         * @return true If the heaps are equal.
         * @return false Otherwise.
         */
        friend bool operator==(const MinHeap<T>& heap1, const MinHeap<T>& heap2) {
            bool eq = heap1.length == heap2.length;

            for(int i = 0; eq && i < heap1.length; i++) 
                eq = heap1.array[i] == heap2.array[i];

            return eq;
        }

        /**
         * @brief Compare two heaps for inequality.
         * 
         * @param heap1 The first heap.
         * @param heap2 The second heap.
         * @return true If the heaps are not equal.
         * @return false If the heaps are equal.
         */
        inline friend bool operator!=(const MinHeap<T>& heap1, const MinHeap<T>& heap2) { return !(heap1 == heap2); }
};

#endif
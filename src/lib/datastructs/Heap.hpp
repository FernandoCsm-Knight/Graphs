/**
 * @file Heap.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a generic heap data structure.
 * 
 * This class provides a base implementation for a heap structure, supporting basic operations
 * like insertion, deletion, and access to elements. The specific behavior (MinHeap or MaxHeap)
 * is determined by derived classes that implement the `compare` method.
 * 
 * @version 1.0.0
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief A generic heap class.
 * 
 * This class implements a generic heap structure. It provides common functionality for both
 * MinHeap and MaxHeap. Specific behavior (e.g., MinHeap or MaxHeap) is determined by the derived
 * class through the `compare` function.
 * 
 * @tparam T The type of elements stored in the heap.
 */
template <class T> class Heap {
    protected:
        T* array;         /**< The array to store heap elements */
        int length;       /**< The current number of elements in the heap */
        int cap;          /**< The capacity of the heap */
        bool isDynamic;   /**< Flag indicating if the heap is dynamically resizable */

        /**
         * @brief Comparison function to maintain the heap property.
         * 
         * This is a pure virtual function that must be implemented by derived classes to 
         * specify whether this heap is a MinHeap or MaxHeap.
         * 
         * @param parent The value of the parent node.
         * @param child The value of the child node.
         * @return true If the heap property needs to be restored (depends on derived class).
         * @return false Otherwise.
         */
        virtual bool compare(const T& parent, const T& child) const = 0;

        /**
         * @brief Get the index of the parent node.
         * 
         * @param idx The index of the current node.
         * @return int The index of the parent node.
         */
        inline int parent(int idx) const { return (idx - 1) / 2; }

        /**
         * @brief Get the index of the left child node.
         * 
         * @param idx The index of the current node.
         * @return int The index of the left child node.
         */
        inline int left(int idx) const { return idx * 2 + 1; }

        /**
         * @brief Get the index of the right child node.
         * 
         * @param idx The index of the current node.
         * @return int The index of the right child node.
         */
        inline int right(int idx) const { return idx * 2 + 2; }

        /**
         * @brief Resize the heap array to accommodate more elements.
         * 
         * This method doubles the current capacity of the heap.
         */
        void resize() {
            this->cap *= 2;
            T* temp = new T[this->cap];

            for(int i = 0; i < this->length; ++i) 
                temp[i] = this->array[i];
            
            delete[] this->array;
            this->array = temp;
        }

        /**
         * @brief Restore the heap property by moving an element up.
         * 
         * Moves an element at the specified index up the heap to restore the heap property.
         * 
         * @param idx The index of the element to move up.
         */
        void siftUp(int idx) {
            int p = this->parent(idx);

            while(idx != 0 && this->compare(this->array[p], this->array[idx])) {
                this->swap(idx, p);
                idx = p;
                p = this->parent(idx);
            }
        }

        /**
         * @brief Restore the heap property by moving an element down.
         * 
         * Moves an element at the specified index down the heap to restore the heap property.
         * 
         * @param idx The index of the element to move down.
         */
        void siftDown(int idx) {
            int l = this->left(idx),
                r = this->right(idx),
                target = idx;

            while((l < this->length && this->compare(this->array[idx], this->array[l])) || 
                  (r < this->length && this->compare(this->array[idx], this->array[r]))) {
                
                target = r >= this->length || !this->compare(this->array[l], this->array[r]) ? l : r;
                this->swap(idx, target);

                idx = target;
                l = this->left(idx);
                r = this->right(idx);
            }
        }

        /**
         * @brief Get the index of an element in the heap.
         * 
         * Performs a search to find the index of the specified element in the heap.
         * 
         * @param element The element to search for.
         * @return int The index of the element, or -1 if not found.
         */
        int indexOf(const T& element) const {
            int idx = 0;

            while(idx < length) {
                if(array[idx] == element) 
                    return idx;

                if(this->compare(array[idx], element)) {
                    idx = left(idx);
                } else {
                    idx = right(idx);
                }
            }

            return -1;
        }

        /**
         * @brief Swap two elements in the heap.
         * 
         * Swaps the elements at the two specified indices.
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
         * @brief Default constructor for Heap.
         * 
         * Initializes an empty heap with a default capacity of 10.
         */
        Heap() : array(new T[10]), length(0), cap(10), isDynamic(true) {}
        
        /**
         * @brief Copy constructor for Heap.
         * 
         * Initializes a heap by copying another heap.
         * 
         * @param heap The heap to be copied.
         */
        Heap(const Heap<T>& heap) {
            array = new T[heap.capacity()]; 
            length = heap.size();
            cap = heap.capacity();
            isDynamic = heap.isDynamic;

            for(int i = 0; i < length; ++i)
                array[i] = heap.array[i];
        }

        /**
         * @brief Constructor for Heap with a specified capacity.
         * 
         * Initializes an empty heap with the specified capacity.
         * 
         * @param capacity The initial capacity of the heap.
         */
        Heap(int capacity) {
            array = new T[capacity];
            length = 0;
            cap = capacity;
            isDynamic = false; 
        }

        /**
         * @brief Construct a heap from an existing array.
         * 
         * Builds a heap from an array of elements. The heap is not dynamically resizable.
         * 
         * @param arr The array of elements.
         * @param capacity The size of the array.
         */
        Heap(const T* arr, int capacity) {
            array = new T[capacity];
            cap = capacity;
            isDynamic = false; 
            length = capacity;

            for(int i = 0; i < this->length; ++i)
                this->array[i] = arr[i];
            
            for(int i = (this->length - 2) / 2; i >= 0; --i)
                this->siftDown(i);
        }

        /**
         * @brief Destructor for Heap.
         * 
         * Frees the memory allocated for the heap array.
         */
        virtual ~Heap() { delete[] array; }

        /**
         * @brief Assignment operator for Heap.
         * 
         * Assigns one heap to another by copying its contents.
         * 
         * @param heap The heap to assign from.
         * @return Heap<T>& A reference to the assigned heap.
         */
        Heap<T>& operator=(const Heap<T>& heap) {
            if(this != &heap) {
                delete[] this->array;

                this->isDynamic = heap.isDynamic;
                this->length = heap.size();
                this->cap = heap.capacity();
                this->array = new T[heap.capacity()];

                for(int i = 0; i < this->length; ++i) 
                    this->array[i] = heap.array[i];
            }

            return *this;
        }

        /**
         * @brief Get the current size of the heap.
         * 
         * @return int The number of elements in the heap.
         */
        inline int size() const { return length; }

        /**
         * @brief Get the capacity of the heap.
         * 
         * @return int The total capacity of the heap.
         */
        inline int capacity() const { return cap; }

        /**
         * @brief Check if the heap is full.
         * 
         * @return true If the heap is full and not resizable.
         * @return false Otherwise.
         */
        inline bool isFull() const { return !isDynamic && length == cap; }
        
        /**
         * @brief Check if the heap is empty.
         * 
         * @return true If the heap is empty.
         * @return false Otherwise.
         */
        inline bool isEmpty() const { return length == 0; }

        /**
         * @brief Add a new element to the heap.
         * 
         * @param element The element to add.
         */
        void add(const T& element) {
            if(isDynamic && length >= cap * 0.75)
                resize();

            array[length++] = element;
            siftUp(length - 1);
        }

        /**
         * @brief Replace an element at a given index.
         * 
         * Replaces the element at the specified index with a new value and restores the heap property.
         * 
         * @param idx The index of the element to replace.
         * @param element The new element to replace the old one.
         * @return T The old element that was replaced.
         * @throws std::out_of_range If the index is out of bounds.
         */
        T replace(int idx, const T& element) {
            if(idx < 0 || idx >= length)
                throw std::out_of_range("Index out of range");

            T res = array[idx];
            array[idx] = element;

            if(compare(res, element))
                siftUp(idx);
            else
                siftDown(idx);

            return res;
        }

        /**
         * @brief Remove and return the root element from the heap.
         * 
         * Removes the element at the root (top of the heap) and restores the heap property.
         * 
         * @return T The root element (min or max depending on the heap type).
         * @throws std::out_of_range If the heap is empty.
         */
        T pop() {
            if(isEmpty())
                throw std::out_of_range("Heap is empty");

            T element = array[0];
            array[0] = array[--length];
            siftDown(0);

            return element;
        }

        /**
         * @brief Check if the heap contains a specific element.
         * 
         * @param element The element to check for.
         * @return true If the element is found in the heap.
         * @return false Otherwise.
         */
        bool contains(const T& element) const {
            return indexOf(element) != -1;
        }

        /**
         * @brief Clear all elements from the heap.
         * 
         * Resets the heap, removing all elements.
         */
        void clear() {
            length = 0;
        }

        /**
         * @brief Access an element by index.
         * 
         * @param idx The index of the element.
         * @return T& A reference to the element.
         * @throws std::out_of_range If the index is out of bounds.
         */
        T& operator[](int idx) {
            if(idx < 0 || idx >= length)
                throw std::out_of_range("Index out of range");
    
            return array[idx];
        }

        /**
         * @brief Output the elements of the heap to an output stream.
         * 
         * @param out The output stream.
         * @param heap The heap to output.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& out, const Heap<T>& heap) {
            for(int i = 0; i < heap.length; ++i)
                out << heap.array[i] << " ";
            
            return out;
        }

        /**
         * @brief Check if two heaps are equal.
         * 
         * Compares the elements of two heaps to see if they are the same.
         * 
         * @param heap1 The first heap.
         * @param heap2 The second heap.
         * @return true If the heaps are equal.
         * @return false Otherwise.
         */
        friend bool operator==(const Heap<T>& heap1, const Heap<T>& heap2) {
            bool eq = heap1.length == heap2.length;

            for(int i = 0; i < heap1.length && eq; ++i)
                eq = heap1.array[i] == heap2.array[i];

            return eq;
        }

        /**
         * @brief Check if two heaps are not equal.
         * 
         * @param heap1 The first heap.
         * @param heap2 The second heap.
         * @return true If the heaps are not equal.
         * @return false If the heaps are equal.
         */
        friend bool operator!=(const Heap<T>& heap1, const Heap<T>& heap2) {
            return !(heap1 == heap2);
        }
};

#endif
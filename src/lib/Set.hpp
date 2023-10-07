/**
 * @file Set.hpp
 * @author Ferando Campos Silva Dal Maria (fernando.csm123@gmail.com)
 * @brief A C++ implementatio of a Set class, a templated data structure representing a 
 *        set of unique elements. This class provides methods for adding, removing, and 
 *        manipulating elements in a sorted set. It supports various set operations like 
 *        union, difference, and Cartesian product.
 * @version 1.0.0
 * @date 2023-08-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <stdexcept>

#include "ArrayList.hpp"
#include "helpers/Pair.hpp"

/**
 * @brief A template class implementing a sorted set data structure.
 * 
 * @tparam T The type of elements stored in the set.
 */
template <class T> class Set {
    private:
        T* arr;              /**< Pointer to the dynamic array holding the elements. */
        int length;          /**< Number of elements currently in the set. */
        int capacity;        /**< Capacity of the dynamic array. */
        bool isDynamic;      /**< Flag indicating whether dynamic resizing is enabled. */

        // Private methods

        /**
         * @brief Resize the internal array by doubling its capacity.
         */
        void resize() {
            this->capacity *= 2;
            T* temp = new T[this->capacity];

            for(int i = 0; i < this->length; i++) 
                temp[i] = this->arr[i];

            delete[] this->arr;
            this->arr = temp;
        }

        /**
         * @brief Perform binary search to find the index of an element.
         * 
         * @param element The element to search for.
         * @return The index of the element if found, otherwise -1.
         */
        int search(const T& element) const {
            int l = 0, r = this->length - 1;

            while(l <= r) {
                int m = l + (r - l) / 2;

                if(this->arr[m] == element) 
                    return m;
                else if(this->arr[m] < element) 
                    l = m + 1;
                else 
                    r = m - 1;
            }

            return -1;
        }

    public:

        /**
         * @brief Constructor to create an instance of the Set class.
         * 
         * @param capacity Initial capacity of the set.
         * @param isDynamic Whether dynamic resizing is enabled.
         */
        Set(int capacity = 10, bool isDynamic = true): capacity(capacity), isDynamic(isDynamic) {
            this->arr = new T[this->capacity];
            this->length = 0;
        }

        /**
         * @brief Copy constructor to create a new Set instance as a copy of another set.
         * 
         * @param set The set to be copied.
         */
        Set(const Set<T>& set): capacity(set.capacity), isDynamic(set.isDynamic) {
            this->arr = new T[this->capacity];
            this->length = set.length;

            for(int i = 0; i < this->length; i++) 
                this->arr[i] = set.arr[i];
        }

        /**
         * @brief Destructor to free the memory allocated for the internal array.
         */
        ~Set() {
            delete[] this->arr;
        }

        // Public methods

        Set<T>& operator=(const Set<T>& set) {
            if(this != &set) {
                this->capacity = set.capacity;
                this->isDynamic = set.isDynamic;
                this->length = set.length;

                delete[] this->arr;
                this->arr = new T[this->capacity];

                for(int i = 0; i < this->length; i++) 
                    this->arr[i] = set.arr[i];
            }

            return *this;
        }

        /**
         * @brief Check if the set is full (reached its capacity).
         * 
         * @return True if the set is full, false otherwise.
         */
        bool isFull() const {
            return !isDynamic && this->length == this->capacity;
        }

        /**
         * @brief Check if the set is empty.
         * 
         * @return True if the set is empty, false otherwise.
         */
        bool isEmpty() const {
            return this->length == 0;
        }
    
        /**
         * @brief Get the current number of elements in the set.
         * 
         * @return The number of elements in the set.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Get the maximum capacity of the set.
         * 
         * @return The maximum capacity of the set.
         */
        int maxSize() const {
            return this->capacity;
        }

        /**
         * @brief Add an element to the set while maintaining sorted order.
         * 
         * @param value The element to be added to the set.
         */
        void add(const T& value) {
            if(this->length == this->capacity && this->isDynamic) 
                this->resize();

            if(this->length < this->capacity && !this->contains(value)) {
                int index = 0;

                while(this->arr[index] < value && index < this->length) 
                    index++;

                for(int i = this->length; i > index; i--) 
                    this->arr[i] = this->arr[i - 1];

                this->arr[index] = value;
                this->length++;
            } 
        }

        /**
         * @brief Remove an element from the set.
         * 
         * @param value The element to be removed.
         */
        void pop(const T& value) {
            if(this->isEmpty()) return;

            int index = this->search(value);

            if(index != -1) {
                for(int i = index; i < this->length - 1; i++) 
                    this->arr[i] = this->arr[i + 1];

                this->length--;
            }
        }

        /**
         * @brief Returns the set as a dynamic array.
         * 
         * @return ArrayList<T> The set as a dynamic array.
         */
        ArrayList<T> toArray() const {
            ArrayList<T> list = ArrayList<T>(this->length);

            for(int i = 0; i < this->length; i++) 
                list.add(this->arr[i]);

            return list;
        }

        /**
         * @brief Overloaded assignment operator to assign a set to another.
         * 
         * @param element The set to be assigned.
         * @return T& The set after assignment.
         */
        T& operator[](const T& element) {
            int index = this->search(element);

            if(index == -1) 
                throw std::out_of_range("Element not found");

            return this->arr[index];
        }

        /**
         * @brief Get the element at a given index.
         * 
         * @param idx The index of the element to be retrieved.
         * @return T& The element at the given index.
         */
        T& operator[](std::size_t idx) {
            if(((int)idx) >= this->length) 
                throw std::out_of_range("Index out of range");

            return this->arr[idx];
        }

        /**
         * @brief Check if the set contains a given element.
         * 
         * @param value The element to search for.
         * @return true if the set contains the element, false otherwise.
         */
        bool contains(const T& value) const {
            return this->search(value) != -1;
        }

        /**
         * @brief Clear the set by removing all elements.
         */
        void clear() {
            this->length = 0;
        }

        /**
         * @brief Get a string representation of the set.
         * 
         * @param out The output stream.
         * @param set The set to be printed.
         * @return std::ostream& The output stream after printing the set.
         */
        friend std::ostream& operator<<(std::ostream& out, const Set<T>& set) {
            out << "{";
            for(int i = 0; i < set.length; i++) {
                out << set.arr[i];
                if(i < set.length - 1) 
                    out << ", ";
            }
            out << "}";
            return out;
        }

        /**
         * @brief Overloaded equality operator to compare two sets for equality.
         * 
         * @param set1 the first set to compare.
         * @param set2 the second set to compare.
         * @return true if the sets are equal, false otherwise.
         */
        friend bool operator==(const Set<T>& set1, const Set<T>& set2) {
            bool eq = set1.length == set2.length;

            for(int i = 0; eq && i < set1.length; i++) 
                eq = set1.arr[i] == set2.arr[i];

            return eq;
        }

        /**
         * @brief Overloaded inequality operator to compare two sets for inequality.
         * 
         * @param set1 the first set to compare.
         * @param set2 the second set to compare.
         * @return true if the sets are not equal, false otherwise.
         */
        inline friend bool operator!=(const Set<T>& set1, const Set<T>& set2) { return !(set1 == set2); }

        /**
         * @brief Overloaded addition operator to compute the union of two sets.
         * 
         * @param set The set to compute the union with.
         * @return Set<T> The resulting set after computing the union.
         */
        Set<T> operator+(const Set<T>& set) const {
            Set<T> result = Set<T>(this->capacity + set.capacity, this->isDynamic || set.isDynamic);

            for(int i = 0; i < this->length; i++) 
                result.add(this->arr[i]);

            for(int i = 0; i < set.length; i++) 
                result.add(set.arr[i]);

            return result;
        }

        /**
         * @brief Overloaded subtraction operator to subtract two sets.
         * 
         * @param set The set to subtract from this set.
         * @return Set<T> The resulting set after subtraction.
         */
        Set<T> operator-(const Set<T>& set) const {
            Set<T> result = Set<T>(this->capacity, this->isDynamic);

            for(int i = 0; i < this->length; i++) 
                if(!set.contains(this->arr[i])) 
                    result.add(this->arr[i]);

            return result;
        }

        /**
         * @brief Overloaded cartesian product operator to compute the cartesian product of two sets.
         * 
         * @tparam U The type of elements in the second set.
         * @param set The second set to compute the cartesian product with.
         * @return Set<Pair<T, U>> The resulting set after computing the cartesian product.
         */
        template <class U> Set<Pair<T, U>> operator*(const Set<U>& set) const {
            Set<Pair<T, U>> result = Set<Pair<T, U>>(this->capacity * set.capacity, this->isDynamic || set.isDynamic);

            for(int i = 0; i < this->length; i++) 
                for(int j = 0; j < set.length; j++) 
                    result.add(Pair<T, U>(this->arr[i], set.arr[j], true));

            return result;
        }

};

#endif
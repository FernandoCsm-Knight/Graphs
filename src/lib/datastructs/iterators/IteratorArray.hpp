/**
 * @file IteratorArray.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ITERATOR_ARRAY_HPP
#define ITERATOR_ARRAY_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief A template class implementing an iterator for an array of elements.
 *
 * @tparam T The type of elements stored in the iterator.
 */
template <class T> class IteratorArray {
    private:
        T* ptr; ///< The pointer to the element.

    public:
        /**
         * @brief Constructor for the IteratorArray.
         *
         * @param ptr Pointer to the initial element.
         */
        IteratorArray(T* ptr): ptr(ptr) {}

        /**
         * @brief Copy constructor for the IteratorArray.
         *
         * @param other Another IteratorArray to copy from.
         */
        IteratorArray(const IteratorArray& other): ptr(other.ptr) {}

        /**
         * @brief Destructor for the IteratorArray.
         */
        ~IteratorArray() {}

        /**
         * @brief Assignment operator overload for the IteratorArray.
         *
         * @param other Another IteratorArray to assign from.
         * @return A reference to the current IteratorArray.
         */
        IteratorArray& operator=(const IteratorArray& other) {
            if(this != &other)
                ptr = other.ptr;

            return *this;
        }

        /**
         * @brief Pre-increment operator overload.
         *
         * @return A reference to the current IteratorArray after incrementing.
         */
        IteratorArray& operator++() {
            ++ptr;
            return *this;
        }

        /**
         * @brief Post-increment operator overload.
         *
         * @return A copy of the current IteratorArray before incrementing.
         */
        IteratorArray operator++(int) {
            IteratorArray it(*this);
            ++(*this);
            return it;
        }

        /**
         * @brief Pre-decrement operator overload.
         *
         * @return A reference to the current IteratorArray after decrementing.
         */
        IteratorArray& operator--() {
            --ptr;
            return *this;
        }

        /**
         * @brief Post-decrement operator overload.
         *
         * @return A copy of the current IteratorArray before decrementing.
         */
        IteratorArray operator--(int) {
            IteratorArray it(*this);
            --(*this);
            return it;
        }

        /**
         * @brief Subscript operator overload for accessing elements by index.
         *
         * @param idx Index of the element to access.
         * @return A reference to the element at the specified index.
         */
        T& operator[](int idx) {
            return *(ptr + idx);
        }

        /**
         * @brief Dereference operator overload for accessing the current element.
         *
         * @return A reference to the current element.
         */
        T& operator*() {
            return *ptr;
        }

        /**
         * @brief Member access operator overload for accessing the current element's properties.
         *
         * @return A pointer to the current element.
         */
        T* operator->() {
            return ptr;
        }

        /**
         * @brief Equality operator overload to compare two IteratorArray objects.
         *
         * @param other Another IteratorArray to compare with.
         * @return True if the two iterators are equal, otherwise false.
         */
        bool operator==(const IteratorArray& other) const {
            return ptr == other.ptr;
        }

        /**
         * @brief Inequality operator overload to compare two IteratorArray objects.
         *
         * @param other Another IteratorArray to compare with.
         * @return True if the two iterators are not equal, otherwise false.
         */
        bool operator!=(const IteratorArray& other) const {
            return ptr != other.ptr;
        }

        /**
         * @brief Less-than operator overload to compare two IteratorArray objects.
         *
         * @param other Another IteratorArray to compare with.
         * @return True if the current iterator is less than the other, otherwise false.
         */
        bool operator<(const IteratorArray& other) const {
            return ptr < other.ptr;
        }

        /**
         * @brief Greater-than operator overload to compare two IteratorArray objects.
         *
         * @param other Another IteratorArray to compare with.
         * @return True if the current iterator is greater than the other, otherwise false.
         */
        bool operator>(const IteratorArray& other) const {
            return ptr > other.ptr;
        }

        /**
         * @brief Less-than-or-equal operator overload to compare two IteratorArray objects.
         *
         * @param other Another IteratorArray to compare with.
         * @return True if the current iterator is less than or equal to the other, otherwise false.
         */
        bool operator<=(const IteratorArray& other) const {
            return ptr <= other.ptr;
        }

        /**
         * @brief Greater-than-or-equal operator overload to compare two IteratorArray objects.
         *
         * @param other Another IteratorArray to compare with.
         * @return True if the current iterator is greater than or equal to the other, otherwise false.
         */
        bool operator>=(const IteratorArray& other) const {
            return ptr >= other.ptr;
        }

        /**
         * @brief Addition-assignment operator overload to increment the iterator by an offset.
         *
         * @param offset The value by which the iterator should be incremented.
         * @return A reference to the current IteratorArray after incrementing.
         */
        IteratorArray& operator+=(int offset) {
            ptr += offset;
            return *this;
        }

        /**
         * @brief Subtraction-assignment operator overload to decrement the iterator by an offset.
         *
         * @param offset The value by which the iterator should be decremented.
         * @return A reference to the current IteratorArray after decrementing.
         */
        IteratorArray& operator-=(int offset) {
            ptr -= offset;
            return *this;
        }
};  

#endif
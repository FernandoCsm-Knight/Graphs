/**
 * @file ArrayList.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a dynamic array data structure known 
 *        as ArrayList. The ArrayList class provides efficient storage 
 *        and manipulation of elements with dynamic resizing to accommodate 
 *        varying data sizes. It offers constant time complexity for 
 *        element access, insertion, and removal at the end of the array. 
 *        The class supports various operations such as adding elements, 
 *        getting elements by index, removing elements, checking for element 
 *        existence, and converting the elements into linked lists. The 
 *        ArrayList is designed to be memory-efficient and easy to use, 
 *        making it suitable for applications requiring dynamic and 
 *        resizable data storage.
 * @version 1.0.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <stdexcept>
#include <functional>
#include <type_traits>

#include "iterators/ArrayIterator.hpp"

template<typename T, typename = void>
struct has_less_operator : std::false_type {};

template<typename T>
struct has_less_operator<T, std::is_void<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

template <class T> class ArrayList;
#include "Set.hpp"

/**
 * @brief Templated dynamic array list class.
 * 
 * This class provides an implementation of a dynamic array list with various methods
 * for manipulating the list, such as adding elements, removing elements, sorting, etc.
 * 
 * @tparam T The type of data that the array list will store.
 */
template <class T> class ArrayList {
    private:
        T* array; ///< Pointer to the dynamic array storing elements.
        int length; ///< The current number of elements in the array list.
        int maxLength; ///< The maximum capacity of the dynamic array.
        bool dynamic; ///< Flag indicating if the array can dynamically resize.
        std::function<int(const T& a, const T& b)> comparator; ///< The comparison function used for sorting.

        // Helper function for resizing the array when necessary.

        void resize() {
            if (this->dynamic && this->length == this->maxLength) {
                T* newArray = new T[this->maxLength * 2];

                for (int i = 0; i < this->length; ++i) 
                    newArray[i] = this->array[i];
                
                delete[] this->array;
                this->array = newArray;
                this->maxLength *= 2;
            }
        }

        // Helper function for serching using the binary search algorithm.

        int binarySearch(const T& element) const {
            int l = 0, r = this->length - 1, m = 0;

            if(comparator) {
                while(l <= r) {
                    m = l + (r - l) / 2;

                    if(comparator(this->array[m], element) == 0) 
                        return m;
                    else if(comparator(this->array[m], element) < 0)
                        l = m + 1;
                    else 
                        r = m - 1;
                }
            } else {
                while(l <= r) {
                    m = l + (r - l) / 2;

                    if(this->array[m] == element) 
                        return m;
                    else if(this->array[m] < element)
                        l = m + 1;
                    else 
                        r = m - 1;
                }
            }

            return -1;
        }

        // Helper functions for sorting using the quicksort algorithm.

        void quickSort(int first, int last) {
            if (first < last) {
                int pivot = this->partition(first, last);
                this->quickSort(pivot, last);
                this->quickSort(first, pivot - 1);
            }
        }

        int partition(int first, int last) {
            T pivot = this->array[(first + last) / 2];

            int i = first, j = last;

            while(i <= j) {
                if(comparator) {
                    while(comparator(this->array[i], pivot) < 0) ++i;
                    while(comparator(this->array[j], pivot) > 0) --j;
                } else if constexpr (std::is_same_v<T, std::string>) {
                    while(((std::string)this->array[i]).compare((std::string)pivot) < 0) ++i;
                    while(((std::string)this->array[j]).compare((std::string)pivot) > 0) --j;
                } else {
                    while(this->array[i] < pivot) ++i;
                    while(this->array[j] > pivot) --j;
                }

                if(i <= j) swap(i++, j--);
            }

            return i;
        }

        void swap(int i, int j) {
            T temp = this->array[i];
            this->array[i] = this->array[j];
            this->array[j] = temp;
        }

    public:

        /**
         * @brief Default constructor.
         * 
         * Creates an empty dynamic array list with a default maximum capacity of 2.
         */
        ArrayList(): length(0), maxLength(2), dynamic(true) {
            this->array = new T[this->maxLength];
            for(int i = 0; i < this->maxLength; ++i) 
                this->array[i] = T();
        }

        /**
         * @brief Constructor with initial capacity.
         * 
         * Creates an empty dynamic array list with the given initial capacity.
         * 
         * @param capacity The initial capacity of the array list.
         * @throw std::invalid_argument If the capacity is less than or equal to 1.
         */
        ArrayList(int capacity): length(0), maxLength(capacity), dynamic(false) {
            if (capacity <= 1) 
                throw std::invalid_argument("The capacity must be greater than 1");

            this->array = new T[capacity];
            for(int i = 0; i < capacity; ++i) 
                this->array[i] = T();
        }

        /**
         * @brief Construct a new Array List object from an array.
         * 
         * @param arr The array to be copied.
         */
        ArrayList(const T arr[], int length) {
            this->length = length;
            this->maxLength = this->length;
            this->array = new T[this->maxLength];
            
            for(int i = 0; i < this->length; ++i) 
                this->array[i] = arr[i];
        }

        /**
         * @brief Copy constructor.
         * 
         * Creates a new dynamic array list as a copy of an existing one.
         * 
         * @param arrayList The array list to be copied.
         */
        ArrayList(const ArrayList<T>& arrayList): length(arrayList.length), maxLength(arrayList.maxLength), dynamic(arrayList.dynamic) {
            this->array = new T[arrayList.maxLength];
            for(int i = 0; i < arrayList.length; ++i) 
                this->array[i] = arrayList.array[i];
        }

        /**
         * @brief Construct a new Array List object with a custom comparator.
         * 
         * @param comparator The comparison function to be used for sorting.
         */
        ArrayList(std::function<int(const T& a, const T& b)> comparator): length(0), maxLength(2), dynamic(true), comparator(comparator) {
            this->array = new T[this->maxLength];
            for(int i = 0; i < this->maxLength; ++i) 
                this->array[i] = T();
        }

        /**
         * @brief Destructor.
         * 
         * Frees the memory used by the dynamic array.
         */
        ~ArrayList() {
            delete[] this->array;
        }

        /**
         * @brief Overloaded assignment operator.
         * 
         * @param arrayList The array list to be copied.
         * @return ArrayList<T>& A reference to the new array list.
         */
        ArrayList<T>& operator=(const ArrayList<T>& arrayList) {
            if(this != &arrayList) {
                delete[] this->array;
                this->length = arrayList.length;
                this->maxLength = arrayList.maxLength;
                this->dynamic = arrayList.dynamic;
                this->array = new T[arrayList.maxLength];
                for(int i = 0; i < arrayList.length; ++i) 
                    this->array[i] = arrayList.array[i];
            }

            return *this;
        }

        /**
         * @brief Get the number of elements in the array list.
         * 
         * @return int The number of elements.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Get the maximum capacity of the array list.
         * 
         * @return int The maximum capacity, or -1 if the array list is dynamic.
         */
        int capacity() const {
            if(this->dynamic) return -1;
            return this->maxLength;
        }

        /**
         * @brief Add an element to the end of the array list.
         * 
         * @param element The element to be added.
         */
        void add(const T& element) {
            this->resize();
            this->array[this->length++] = element;
        }

        /**
         * @brief Add an element at the specified index in the array list.
         * 
         * @param index The index where the element will be inserted.
         * @param element The element to be added.
         * @throw std::out_of_range If the index is out of range.
         */
        void add(int index, const T& element) {
            if (index < 0 || index > this->length) 
                throw std::out_of_range("Index out of range");

            this->resize();
            for (int i = this->length; i > index; --i) 
                this->array[i] = this->array[i - 1];

            this->array[index] = element;
            this->length++;
        }

        /**
         * @brief Add an element to the array list in non-decreasing order.
         * 
         * @param element The element to be added.
         */
        void addInOrder(const T& element) {
            int index = 0;

            if(comparator) {
                while(index < this->length && comparator(this->array[index], element) < 0)
                    index++;
            } else {
                while(index < this->length && this->array[index] < element)
                    index++;
            }

            this->add(index, element);
        }

        /**
         * @brief Add an element at the beginning of the array list.
         * 
         * @param element The element to be added.
         */
        void unshift(const T& element) {
            this->add(0, element);
        }

        /**
         * @brief Remove and return the last element from the array list.
         * 
         * @return T The last element's value.
         * @throw std::out_of_range If the list is empty.
         */
        T pop() {
            if (this->length == 0) 
                throw std::out_of_range("Index out of range");

            T element = this->array[--this->length];
            this->array[this->length] = T();

            return element;
        }

        /**
         * @brief Remove and return the element at the specified index.
         * 
         * @param index The index of the element to be removed.
         * @return T The value of the removed element.
         * @throw std::out_of_range If the index is out of range.
         */
        T pop(int index) {
            if (index < 0 || index >= this->length) 
                throw std::out_of_range("Index out of range");

            T element = this->array[index];
            for(int i = index; i < this->length - 1; ++i) 
                this->array[i] = this->array[i + 1];

            this->array[--this->length] = T();
            return element;
        }

        /**
         * @brief Remove the first occurrence of the given element from the array list.
         * 
         * @param element The element to be removed.
         * @param check If true, search for the element from the beginning; otherwise, search from the end.
         * @throw std::invalid_argument If the element is not found in the list.
         */
        T pop(const T& element, bool check = true) {
            int index = -1;
            if(check)
                index = this->indexOf(element);
            else 
                index = this->lastIndexOf(element);

            if (index == -1) 
                throw std::invalid_argument("Element not found");

            return this->pop(index);
        }

        /**
         * @brief Remove and return the first element from the array list.
         * 
         * @return T The first element's value.
         * @throw std::out_of_range If the list is empty.
         */
        T shift() {
            return this->pop(0);
        }

        /**
         * @brief Get the element at the specified index without removing it.
         * 
         * @param index The index of the element to retrieve.
         * @return T The value of the element at the given index.
         */
        T get(int index) const {
            return this->array[index];
        }

        /**
         * @brief Overloaded subscript operator to access elements by index.
         * 
         * @param idx The index of the element to access.
         * @return T& Reference to the element's value at the given index.
         * @throw std::out_of_range If the index is out of range.
         */
        T& operator[](std::size_t idx) {
            if(idx >= (std::size_t)this->length) 
                throw std::out_of_range("Index out of range");
            return this->array[idx];
        }

        /**
         * @brief Update the element at the specified index with the given value.
         * 
         * @param index The index of the element to be updated.
         * @param element The new value for the element.
         * @throw std::out_of_range If the index is out of range.
         */
        void set(int index, const T& element) {
            if (index < 0 || index >= this->length)
                throw std::out_of_range("Index out of range");
                
            this->array[index] = element;
        }

        /**
         * @brief Resize the array list to the given capacity.
         * 
         * @param capacity The new capacity of the array list.
         */
        void resize(int capacity) {
            if (capacity <= this->length) 
                throw std::invalid_argument("The capacity must be greater than 1");

            T* newArray = new T[capacity];
            for(int i = 0; i < this->length; ++i) 
                newArray[i] = this->array[i];
            
            delete[] this->array;
            this->array = newArray;
            this->maxLength = capacity;
            this->dynamic = false;
        }

        /**
         * @brief Clear the array list, removing all elements.
         */
        void clear() {
            delete[] this->array;
            this->array = new T[this->maxLength];
            for (int i = 0; i < this->length; ++i) 
                this->array[i] = T();
            
            this->length = 0;
        }

        /**
         * @brief Check if the array list is empty.
         * 
         * @return bool True if the array list is empty; otherwise, false.
         */
        bool isEmpty() const {
            return this->length == 0;
        }

        /**
         * @brief Check if the array list contains the given element.
         * 
         * @param element The element to check for.
         * @param binary If true, use binary search; otherwise, use linear search.
         * @return bool True if the element exists in the array list; otherwise, false.
         */
        bool contains(const T& element, bool binary = false) const {
            return this->indexOf(element, binary) != -1;
        }

        /**
         * @brief Find the index of the first occurrence of the given element in the array list.
         * 
         * @param element The element to search for.
         * @param binary If true, use binary search; otherwise, use linear search.
         * @return int The index of the first occurrence of the element, or -1 if not found.
         */
        int indexOf(const T& element, bool binary = false) const {
            int idx = -1;
            
            if constexpr (has_less_operator<T>::value) {
                if(binary) {
                    idx = this->binarySearch(element);
                } else if(comparator) {
                    for (int i = 0; idx == -1 && i < this->length; ++i) 
                        if (comparator(this->array[i], element) == 0) 
                            idx = i;
                } else {
                    for (int i = 0; idx == -1 && i < this->length; ++i) 
                        if (this->array[i] == element) 
                            idx = i;
                }
            } else {
                for (int i = 0; idx == -1 && i < this->length; ++i) 
                    if (this->array[i] == element) 
                        idx = i;
            }
            
            return idx;
        }

        /**
         * @brief Find the index of the last occurrence of the given element in the array list.
         * 
         * @param element The element to search for.
         * @param binary If true, use binary search; otherwise, use linear search.
         * @return int The index of the last occurrence of the element, or -1 if not found.
         */
        int lastIndexOf(const T& element, bool binary = false) const {
            int idx = -1;

            if(binary) {
                idx = this->binarySearch(element);
            } else if(comparator) {
                for (int i = this->length - 1; idx == -1 && i >= 0; --i)
                    if (comparator(this->array[i], element) == 0) 
                        idx = i;
            } else {
                for (int i = this->length - 1; idx == -1 && i >= 0; --i)
                    if (this->array[i] == element) 
                        idx = i;
            }

            return idx;
        }

        /**
         * @brief Sort the array list in ascending order.
         */
        void sort() {
            this->quickSort(0, (long int)(this->length - 1));
        }

        /**
         * @brief Returns a copy of the array list as a built-in array.
         * 
         * @return T* A copy of the array list as a built-in array.
         */
        T* toVector() const {
            T* arr = new T[this->length];
            for(int i = 0; i < this->length; ++i) 
                arr[i] = this->array[i];
            
            return arr;
        }

        /**
         * @brief Returns a copy of the array list as a set.
         * 
         * @return Set<T> A copy of the array list as a set.
         */
        Set<T> toSet() const {
            Set<T> set;
            for(int i = 0; i < this->length; ++i) 
                set.add(this->array[i]);
            
            return set;
        }

        /**
         * @brief Returns a Iterator object pointing to the first element in the array list.
         * 
         * @return Iterator<T> An iterator pointing to the first element in the array list.
         */
        ArrayIterator<T> begin() const {
            return ArrayIterator<T>(this->array);
        }

        /**
         * @brief Returns a Iterator object pointing to the element after the last element in the array list.
         * 
         * @return Iterator<T> An iterator pointing to the element after the last element in the array list.
         */
        ArrayIterator<T> end() const {
            return ArrayIterator<T>(this->array + this->length);
        }

        // Friend functions for overloading stream insertion and equality operators.

        friend std::ostream& operator<<(std::ostream& strm, const ArrayList<T>& arrayList) {
            strm << "[";
            for (int i = 0; i < arrayList.length; ++i) {
                strm << arrayList.array[i];
                if (i != arrayList.length - 1) 
                    strm << ", ";
            }
            return strm << "]";
        }

        friend bool operator==(const ArrayList<T>& arrayList1, const ArrayList<T>& arrayList2) {
            bool eq = arrayList1.length == arrayList2.length;
    
            if(arrayList1.comparator) {
                for (int i = 0; i < arrayList1.length && eq; ++i) {
                    eq = arrayList1.comparator(arrayList1.array[i], arrayList2.array[i]) == 0;
                }
            } else if(arrayList2.comparator) {
                for (int i = 0; i < arrayList1.length && eq; ++i) {
                    eq = arrayList2.comparator(arrayList1.array[i], arrayList2.array[i]) == 0;
                }
            } else {
                for (int i = 0; i < arrayList1.length && eq; ++i) {
                    if constexpr (std::is_same_v<T, std::string>) {
                        eq = arrayList1.array[i].compare(arrayList2.array[i]) == 0;
                    } else {
                        eq = arrayList1.array[i] == arrayList2.array[i];
                    }
                }
            }

            return eq;
        }

        friend bool operator<(const ArrayList<T>& arrayList1, const ArrayList<T>& arrayList2) {
            bool lt = arrayList1.length < arrayList2.length;
    
            if(arrayList1.comparator) {
                for (int i = 0; i < arrayList1.length && lt; ++i) {
                    lt = arrayList1.comparator(arrayList1.array[i], arrayList2.array[i]) < 0;
                }
            } else if(arrayList2.comparator) {
                for (int i = 0; i < arrayList1.length && lt; ++i) {
                    lt = arrayList2.comparator(arrayList1.array[i], arrayList2.array[i]) < 0;
                }
            } else {
                for (int i = 0; i < arrayList1.length && lt; ++i) {
                    if constexpr (std::is_same_v<T, std::string>) {
                        lt = arrayList1.array[i].compare(arrayList2.array[i]) < 0;
                    } else {
                        lt = arrayList1.array[i] < arrayList2.array[i];
                    }
                }
            }
            
            return lt;
        }

        inline friend bool operator!=(const ArrayList<T>& arrayList1, const ArrayList<T>& arrayList2) { return !(arrayList1 == arrayList2); }
        inline friend bool operator>(const ArrayList<T>& arrayList1, const ArrayList<T>& arrayList2) { return arrayList2 < arrayList1; }
        inline friend bool operator<=(const ArrayList<T>& arrayList1, const ArrayList<T>& arrayList2) { return !(arrayList1 > arrayList2); }
        inline friend bool operator>=(const ArrayList<T>& arrayList1, const ArrayList<T>& arrayList2) { return !(arrayList1 < arrayList2); }
};

#endif
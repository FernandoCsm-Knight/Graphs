/**
 * @file LinkedList.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a doubly linked list data structure. 
 *        The LinkedList class provides efficient storage and manipulation 
 *        of elements in a linear order, allowing constant time insertion 
 *        and removal at both ends of the list. The class supports dynamic 
 *        resizing and various operations like adding elements, getting 
 *        elements by index, removing elements, reversing the list, and 
 *        sorting. It offers methods to check for element existence, 
 *        retrieve the size of the list, and convert the list elements into 
 *        arrays. The LinkedList is designed to be versatile and 
 *        memory-efficient, making it suitable for a wide range of 
 *        applications requiring flexible data storage and retrieval.
 * @version 1.0.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>

#include "../helpers/Node.hpp"
#include "iterators/LinkedListIterator.hpp"

/**
 * @brief Templated doubly-linked list class.
 * 
 * This class provides a doubly-linked list implementation with various methods
 * for manipulating the list such as adding elements, removing elements, sorting, reversing, etc.
 * 
 * @tparam T The type of data that the linked list will store.
 */
template <class T> class LinkedList {
    private:
        Node<T>* head;          ///< Pointer to the first node (head) of the linked list.
        Node<T>* tail;          ///< Pointer to the last node (tail) of the linked list.
        int length;    ///< The number of elements in the linked list.

        // Helper functions for sorting

        void quickSort(Node<T>* left, Node<T>* right) {
            if(right != nullptr && left != right && left != right->next) {
                Node<T>* pivot = this->partition(left, right);
                this->quickSort(left, pivot->prev);
                this->quickSort(pivot->next, right);
            }
        }

        Node<T>* partition(Node<T>* left, Node<T>* right) {
            bool isString = typeid(T) == typeid(std::string);

            T pivot = right->value;
            Node<T>* i = left->prev;

            for (Node<T>* j = left; j != right; j = j->next) {
                if(isString) {
                    if(((std::string)j->value).compare((std::string)pivot) <= 0) {
                        i = (i == nullptr) ? left : i->next;
                        swap(i, j);
                    }
                } else {
                    if(j->value <= pivot) {
                        i = (i == nullptr) ? left : i->next;
                        swap(i, j);
                    }
                }
            }

            i = (i == nullptr) ? left : i->next;
            swap(i, right);
            return i;
        }

        void swap(Node<T>* node1, Node<T>* node2) {
            T temp = node1->value;
            node1->value = node2->value;
            node2->value = temp;
        }

    public:

        /**
         * @brief Default constructor.
         * 
         * Creates an empty linked list.
         */
        LinkedList(): head(nullptr), tail(nullptr), length(0) {}

        /**
         * @brief Constructor with initial value.
         * 
         * Creates a linked list with a single element containing the given value.
         * 
         * @param value The value to be stored in the initial element.
         */
        LinkedList(T value): head(new Node<T>(value)), tail(this->head), length(1) {}

        /**
         * @brief Copy constructor.
         * 
         * Creates a new linked list as a copy of an existing one.
         * 
         * @param linkedList The linked list to be copied.
         */
        LinkedList(const LinkedList<T>& linkedList): head(nullptr), tail(nullptr), length(0) {
            Node<T>* node = linkedList.head;
            while(node != nullptr) {
                this->add(node->value);
                node = node->next;
            }
        }

        /**
         * @brief Destructor.
         * 
         * Frees the memory used by the linked list and its nodes.
         */
        ~LinkedList() {
            Node<T>* node = this->head;
            while(node != nullptr) {
                Node<T>* next = node->next;
                delete node;
                node = next;
            }
        }

        /**
         * @brief Overloaded assignment operator.
         * 
         * @param linkedList The linked list to be copied.
         * @return LinkedList<T>& A reference to the new linked list.
         */
        LinkedList<T>& operator=(const LinkedList<T>& linkedList) {
            if(this != &linkedList) {
                this->clear();

                Node<T>* node = linkedList.head;
                while(node != nullptr) {
                    this->add(node->value);
                    node = node->next;
                }
            }
            return *this;
        }

        /**
         * @brief Get the number of elements in the linked list.
         * 
         * @return int The number of elements.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Returns the first element in the linked list.
         * 
         * @return T& A reference to the first element's value.
         */
        T& front() const {
            return this->head->value;
        }

        /**
         * @brief Returns the last element in the linked list.
         * 
         * @return T& A reference to the last element's value.
         */
        T& back() const {
            return this->tail->value;
        }

        /**
         * @brief Add an element to the end of the linked list.
         * 
         * @param value The value to be added.
         */
        void add(const T& value) {
            Node<T>* node = new Node<T>(value);
            if(this->head == nullptr) {
                this->head = node;
                this->tail = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
                this->tail = node;
            }
            this->length++;
        }

        /**
         * @brief Add an element at the specified index in the linked list.
         * 
         * @param index The index where the value will be inserted.
         * @param value The value to be added.
         * @throw std::invalid_argument If the index is out of range.
         */
        void add(int index, const T& value) {
            if(index > this->length) 
                throw std::invalid_argument("The index must be greater than 0 and less than the length of the list");

            if (index == this->length) {
                this->add(value);
            } else if(index == 0) {
                this->unshift(value);
            } else {
                Node<T>* node = new Node<T>(value);

                Node<T>* prev = this->head;
                for(int i = 0; i < index - 1; ++i) 
                    prev = prev->next;
                
                node->next = prev->next;
                node->prev = prev;
                prev->next->prev = node;
                prev->next = node;

                this->length++;
            }
        }

        /**
         * @brief Add an element to the linked list in ascending order.
         * 
         * @param element The element to be added.
         */
        void addInOrder(const T& element) {
            Node<T>* node = new Node<T>(element);
            if(this->head == nullptr) {
                this->head = node;
                this->tail = node;
            } else {
                Node<T>* current = this->head;
                while(current != nullptr && current->value < element) {
                    current = current->next;
                }

                if(current == nullptr) {
                    this->tail->next = node;
                    node->prev = this->tail;
                    this->tail = node;
                } else if(current == this->head) {
                    this->head->prev = node;
                    node->next = this->head;
                    this->head = node;
                } else {
                    node->next = current;
                    node->prev = current->prev;
                    current->prev->next = node;
                    current->prev = node;
                }
            }
            this->length++;
        }

        /**
         * @brief Add an element at the beginning of the linked list.
         * 
         * @param value The value to be added.
         */
        void unshift(const T& value) {
            Node<T>* node = new Node<T>(value);
            if(this->head == nullptr) {
                this->head = node;
                this->tail = node;
            } else {
                this->head->prev = node;
                node->next = this->head;
                this->head = node;
            }
            this->length++;
        }

        /**
         * @brief Remove and return the last element from the linked list.
         * 
         * @return T The last element's value.
         * @throw std::out_of_range If the list is empty.
         */
        T pop() {
            if(this->length == 0) 
                throw std::out_of_range("Index out of range");

            T value = this->tail->value;
            Node<T>* node = this->tail;
            this->tail = this->tail->prev;
            this->tail->next = nullptr;
            delete node;
            this->length--;
            return value;
        }

        /**
         * @brief Remove and return the element at the specified index.
         * 
         * @param index The index of the element to be removed.
         * @return T The value of the removed element.
         * @throw std::out_of_range If the index is out of range.
         */
        T pop(int index) {
            if(index >= this->length) 
                throw std::out_of_range("Index out of range");

            if(index == this->length - 1) {
                return this->pop();
            } else if(index == 0) {
                return this->shift();
            } else {
                Node<T>* node = this->head;
                for(int i = 0; i < index; ++i) 
                    node = node->next;
                
                T value = node->value;
                node->prev->next = node->next;
                node->next->prev = node->prev;
                delete node;
                this->length--;
                return value;
            }
        }

        /**
         * @brief Remove the first occurrence of the given value from the linked list.
         * 
         * @param value The value to be removed.
         * @param check If true, search for the value from the beginning; otherwise, search from the end.
         * @throw std::invalid_argument If the value is not found in the list.
         */
        bool pop(const T& value, bool check) {
            int index = -1;
            if(check) 
                index = this->indexOf(value);
            else 
                index = this->lastIndexOf(value);

            if(index == -1)
                return false;
            
            return this->pop(index) == value;
        }

        /**
         * @brief Remove and return the first element from the linked list.
         * 
         * @return T The first element's value.
         * @throw std::out_of_range If the list is empty.
         */
        T shift() {
            if(this->length == 0) 
                throw std::out_of_range("Index out of range");

            T value = this->head->value;
            Node<T>* node = this->head;
            this->head = this->head->next;
            delete node;

            if(this->head == nullptr) 
                this->tail = nullptr;
            else 
                this->head->prev = nullptr;

            this->length--;
            return value;
        }

        /**
         * @brief Find the index of the first occurrence of the given value in the linked list.
         * 
         * @param value The value to search for.
         * @return int The index of the first occurrence of the value, or -1 if not found.
         */
        int indexOf(const T& value) const {
            Node<T>* node = this->head;

            for(int i = 0; node != nullptr; ++i) {
                if(node->value == value) 
                    return i;
                node = node->next;
            }

            return -1;
        }

        /**
         * @brief Find the index of the last occurrence of the given value in the linked list.
         * 
         * @param value The value to search for.
         * @return int The index of the last occurrence of the value, or -1 if not found.
         */
        int lastIndexOf(const T& value) const {
            Node<T>* node = this->tail;

            for(int i = this->length - 1; node != nullptr; --i) {
                if(node->value == value) 
                    return i;
                node = node->prev;
            }

            return -1;
        }

        /**
         * @brief Get the element at the specified index without removing it.
         * 
         * @param idx The index of the element to retrieve.
         * @return T The value of the element at the given index.
         * @throw std::out_of_range If the index is out of range.
         */
        T get(int idx) const {
            if(idx < 0 || idx >= this->length) 
                throw std::out_of_range("Index out of range");

            Node<T>* node;
            
            if(idx <= this->length / 2) {
                node = this->head;
                for(int i = 0; i < idx; ++i) 
                    node = node->next;
            } else {
                node = this->tail;
                for(int i = this->length - 1; i > idx; --i) 
                    node = node->prev;
            }
            
            return node->value;
        }

        /**
         * @brief Check if the linked list contains the given value.
         * 
         * @param value The value to check for.
         * @return bool True if the value exists in the linked list; otherwise, false.
         */
        bool contains(const T& value) const {
            return this->indexOf(value) != -1;
        }

        /**
         * @brief Overloaded subscript operator to access elements by index.
         * 
         * @param idx The index of the element to access.
         * @return T& Reference to the element's value at the given index.
         * @throw std::out_of_range If the index is out of range.
         */
        T& operator[](int idx) const {
            if(idx >= this->length) 
                throw std::out_of_range("Index out of range");

            Node<T>* node;

            if(idx <= this->length / 2) {
                node = this->head;
                for(int i = 0; i < idx; ++i) 
                    node = node->next;
            } else {
                node = this->tail;
                for(int i = this->length - 1; i > idx; --i) 
                    node = node->prev;
            }
            
            return node->value;
        }

        /**
         * @brief Update the element at the specified index with the given value.
         * 
         * @param index The index of the element to be updated.
         * @param value The new value for the element.
         * @throw std::out_of_range If the index is out of range.
         */
        void set(int index, const T& value) {
            if(index < 0 || index >= this->length) 
                throw std::out_of_range("Index out of range");

            Node<T>* node = this->head;
            for(int i = 0; i < index; ++i) 
                node = node->next;
            
            node->value = value;
        }

        /**
         * @brief Reverse the order of elements in the linked list.
         */
        void reverse() {
            Node<T>* node = this->head;
            while(node != nullptr) {
                Node<T>* next = node->next;
                node->next = node->prev;
                node->prev = next;
                node = next;
            }

            node = this->head;
            this->head = this->tail;
            this->tail = node;
        }

        /**
         * @brief Sort the linked list in ascending order using the quicksort algorithm.
         */
        void sort() {
            this->quickSort(this->head, this->tail);
        }

        /**
         * @brief Clear the linked list, removing all elements.
         */
        void clear() {
            Node<T>* node = this->head;
            while(node != nullptr) {
                Node<T>* next = node->next;
                delete node;
                node = next;
            }
            this->head = nullptr;
            this->tail = nullptr;
            this->length = 0;
        }

        /**
         * @brief Returns a iterator to the first element of the linked list.
         * 
         * @return LinkedListIterator<T> An iterator to the first element of the linked list.
         */
        LinkedListIterator<T> begin() {
            return LinkedListIterator<T>(head);
        }

        /**
         * @brief Returns a iterator to the element following the last element of the linked list.
         * 
         * @return LinkedListIterator<T> An iterator to the element following the last element of the linked list.
         */
        LinkedListIterator<T> end() {
            return LinkedListIterator<T>(nullptr);
        }

        // Friend functions for overloading stream insertion and equality operators.

        friend std::ostream& operator<<(std::ostream& strm, const LinkedList<T>& linkedList) {
            Node<T>* node = linkedList.head;
            strm << "[";
            while(node != nullptr) {
                strm << node->value;
                if (node->next != nullptr) 
                    strm << ", ";
                node = node->next;
            }
            strm << "]";
            return strm;
        }

        friend bool operator==(const LinkedList<T>& linkedList1, const LinkedList<T>& linkedList2) {
            bool eq = linkedList1.length == linkedList2.length;
            
            Node<T>* node1 = linkedList1.head;
            Node<T>* node2 = linkedList2.head;
            while(node1 != nullptr && eq) {
                eq = node1 == node2;
                node1 = node1->next;
                node2 = node2->next;
            }

            return eq;
        }

        friend bool operator<(const LinkedList<T>& linkedList1, const LinkedList<T>& linkedList2) {
            Node<T>* node1 = linkedList1.head;
            Node<T>* node2 = linkedList2.head;
            while(node1 != nullptr && node2 != nullptr) {
                if (node1->value < node2->value) 
                    return true;
                else if (node1->value > node2->value) 
                    return false;
                node1 = node1->next;
                node2 = node2->next;
            }

            return linkedList1.length < linkedList2.length;
        }

        inline friend bool operator!=(const LinkedList<T>& linkedList1, const LinkedList<T>& linkedList2) { return !(linkedList1 == linkedList2); }
        inline friend bool operator>(const LinkedList<T>& linkedList1, const LinkedList<T>& linkedList2) { return linkedList2 < linkedList1; }
        inline friend bool operator<=(const LinkedList<T>& linkedList1, const LinkedList<T>& linkedList2) { return !(linkedList1 > linkedList2); }
        inline friend bool operator>=(const LinkedList<T>& linkedList1, const LinkedList<T>& linkedList2) { return !(linkedList1 < linkedList2); }
};

#endif
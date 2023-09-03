/**
 * @file Queue.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a Queue class, a templated data structure
 *        representing a First-In-First-Out (FIFO) queue. he Queue class allows 
 *        elements to be added to the back and removed from the front, maintaining 
 *        their order of insertion. It also supports operations like sorting, 
 *        reversing, and checking for equality between different queue instances.
 * @version 1.0.0
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>

#include "helpers/Node.hpp"

/**
 * @brief A templated Queue class that represents a FIFO 
 *        (First-In-First-Out) data structure.
 * 
 * @tparam T The type of elements that the queue will hold.
 */
template <class T> class Queue {
    private:
        Node<T>* head; ///< Pointer to the first node in the queue.
        Node<T>* tail; ///< Pointer to the last node in the queue.
        unsigned int length; ///< Number of elements in the queue.

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

        /**
         * @brief Overloaded friend function for printing the queue elements.
         * 
         * @tparam U The type of elements in the queue.
         * @param strm The output stream.
         * @param queue The Queue object to print.
         * @return Reference to the output stream after printing.
         */
        template <class U> friend std::ostream& operator<<(std::ostream& strm, const Queue<U>& queue) {
            Node<U>* node = queue.head;
            strm << "[";
            while(node != nullptr) {
                strm << node->value;
                if(node->next != nullptr)
                    strm << ", ";
                node = node->next;
            }

            return strm << "]";
        }

        /**
         * @brief Overloaded friend function for comparing two queues for equality.
         * 
         * @tparam U The type of elements in the queues.
         * @param queue1 The first Queue object to compare.
         * @param queue2 The second Queue object to compare.
         * @return True if both queues are equal, otherwise false.
         */
        template <class U> friend bool operator==(const Queue<U>& queue1, const Queue<U>& queue2) {
            bool eq = queue1.length == queue2.length;
            
            Node<T>* node1 = queue1.head;
            Node<T>* node2 = queue2.head;
            while(node1 != NULL && eq) {
                eq = node1->value == node2->value;
                node1 = node1->next;
                node2 = node2->next;
            }

            return eq;
        }

    public:

        /**
         * @brief Default constructor for Queue class.
         */
        Queue(): head(nullptr), tail(nullptr), length(0) {}

        /**
         * @brief Copy constructor for Queue class.
         * 
         * @param queue The Queue object to copy from.
         */
        Queue(const Queue& queue): head(nullptr), tail(nullptr), length(0) {
            Node<T>* node = queue.head;
            while(node != nullptr) {
                this->push(node->value);
                node = node->next;
            }
        }

        /**
         * @brief Destructor for Queue class.
         */
        ~Queue() {
            Node<T>* node = this->head;
            while(node != nullptr) {
                Node<T>* next = node->next;
                delete node;
                node = next;
            }
        };

        /**
         * @brief Overloaded assignment operator for Queue class.
         * 
         * @param queue The Queue object to copy from.
         * @return Queue<T>& Reference to the Queue object after copying.
         */
        Queue<T>& operator=(const Queue<T>& queue) {
            if(this != &queue) {
                this->clear();

                Node<T>* node = queue.head;
                while(node != nullptr) {
                    this->push(node->value);
                    node = node->next;
                }
            }

            return *this;
        }

        /**
         * @brief Pushes an element to the back of the queue.
         * 
         * @param element The element to be added to the queue.
         */
        void push(const T& element) {
            Node<T>* node = new Node<T>(element);

            if(head == nullptr && tail == nullptr) {
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
         * @brief Removes and returns the front element of the queue.
         * 
         * @return The front element of the queue.
         * @throw std::out_of_range If the queue is empty.
         */
        T pop() {
            if(this->isEmpty()) 
                throw std::out_of_range("Index out of range");

            Node<T>* node = this->head->next;
            T value = this->head->value;
            delete this->head;
            this->head = node;

            if(this->head == nullptr)
                this->tail = nullptr;
            else
                this->head->prev = nullptr;

            this->length--;
            return value;
        }

        /**
         * @brief Returns the front element of the queue without removing it.
         * 
         * @return The front element of the queue.
         * @throw std::out_of_range If the queue is empty.
         */
        T pick() {
            if(this->isEmpty())
                throw std::out_of_range("Index out od range");

            return this->head->value;
        }

        /**
         * @brief Checks if the queue is empty.
         * 
         * @return True if the queue is empty, otherwise false.
         */
        bool isEmpty() const {
            return this->length == 0;
        }

        /**
         * @brief Returns the number of elements in the queue.
         * 
         * @return The number of elements in the queue.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Sorts the elements in the queue using quicksort algorithm.
         */
        void sort() {
            this->quickSort(this->head, this->tail);
        }

        /**
         * @brief Reverses the order of elements in the queue.
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
         * @brief Clears the queue by removing all elements.
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
};

#endif
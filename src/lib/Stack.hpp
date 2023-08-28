/**
 * @file Stack.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a Stack class, a templated data structure
 *        representing a Last-In-First-Out (LIFO) stack. The Stack class supports 
 *        various operations, such as adding elements to the top, removing elements 
 *        from the top, peeking at the top element, checking for emptiness, and 
 *        clearing the stack. Additionally, it provides an overloaded stream insertion 
 *        operator to print the stack elements.
 * @version 1.0.0
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <stdexcept>

#include "helpers/Node.hpp"

/**
 * @brief A templated Stack class that represents a Last-In-First-Out (LIFO) data structure.
 * 
 * @tparam T The type of elements that the stack will hold.
 */
template <class T> class Stack {
    private:
        Node<T>* top; ///< Pointer to the top node of the stack.
        int length; ///< Number of elements in the stack.

        /**
         * @brief Overloaded friend function for printing the stack elements.
         * 
         * @tparam T The type of elements in the stack.
         * @param os The output stream.
         * @param stack The Stack object to print.
         * @return Reference to the output stream after printing.
         */
        friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
            Node<T>* temp = stack.top;

            os << "[";
            while(temp != nullptr) {
                os << temp->value;
                if(temp->next != nullptr) {
                    os << ", ";
                }
                temp = temp->next;
            }
            os << "]";

            return os;
        }

    public:
        /**
         * @brief Default constructor for the Stack class.
         */
        Stack() {
            this->top = nullptr;
            this->length = 0;
        }

        /**
         * @brief Copy constructor for the Stack class.
         * 
         * @param stack The Stack object to be copied.
         */
        Stack(const Stack<T>& stack) {
            this->top = nullptr;
            this->length = 0;

            Node<T>* temp = stack.top;
            while(temp != nullptr) {
                this->push(temp->value);
                temp = temp->next;
            }
        }

        /**
         * @brief Destructor for the Stack class.
         * Clears all the elements in the stack and frees memory.
         */
        ~Stack() {
            Node<T>* temp = this->top;

            while(temp != nullptr) {
                Node<T>* next = temp->next;
                delete temp;
                temp = next;
            }
        }

        /**
         * @brief Overloaded copy constructor for the Stack class.
         * 
         * @param stack The Stack object to be copied.
         * @return Stack<T>& Reference to the Stack object after copying.
         */
        Stack<T>& operator=(const Stack<T>& stack) {
            if(this != &stack) {
                this->clear();

                Node<T>* temp = stack.top;
                while(temp != nullptr) {
                    this->push(temp->value);
                    temp = temp->next;
                }
            }

            return *this;
        }

        /**
         * @brief Pushes an element to the top of the stack.
         * 
         * @param value The element to be added to the stack.
         */
        void push(T value) {
            Node<T>* newNode = new Node<T>(value);

            if(this->top == nullptr) {
                this->top = newNode;
            } else {
                newNode->next = this->top;
                this->top = newNode;
            }

            this->length++;
        }

        /**
         * @brief Removes and returns the top element of the stack.
         * 
         * @return The top element of the stack.
         * @throw std::out_of_range If the stack is empty.
         */
        T pop() {
            if(this->top == nullptr) {
                throw std::out_of_range("Stack is empty");
            }

            Node<T>* temp = this->top;
            T value = temp->value;

            this->top = this->top->next;
            delete temp;

            this->length--;
            return value;
        }

        /**
         * @brief Returns the top element of the stack without removing it.
         * 
         * @return The top element of the stack.
         * @throw std::out_of_range If the stack is empty.
         */
        T peek() {
            if(this->top == nullptr) {
                throw std::out_of_range("Stack is empty");
            }

            return this->top->value;
        }

        /**
         * @brief Returns the number of elements in the stack.
         * 
         * @return The number of elements in the stack.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Checks if the stack is empty.
         * 
         * @return True if the stack is empty, otherwise false.
         */
        bool isEmpty() const {
            return this->length == 0;
        }

        /**
         * @brief Clears all the elements from the stack.
         * 
         * @note This function frees the memory for all the elements and resets the stack.
         */
        void clear() {
            Node<T>* temp = this->top;

            while(temp != nullptr) {
                Node<T>* next = temp->next;
                delete temp;
                temp = next;
            }

            this->top = nullptr;
            this->length = 0;
        }
};

#endif
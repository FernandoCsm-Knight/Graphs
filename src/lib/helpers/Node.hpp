/**
 * @file Node.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a template class, Node, that represents a node in a doubly linked list.
 *        Each node contains a value of a given type and has pointers to the next and previous nodes in the list.
 *        The class also includes overloaded operators for printing the node value, comparing nodes for equality
 *        and inequality, and assigning values between nodes.
 * @version 1.0.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef NODE_HPP
#define NODE_HPP

/**
 * @brief A template class representing a node in a linked list.
 * 
 * @tparam T The type of the value held by the node.
 */
template <class T> class Node {
    public:
        T value;            /**< The value held by the node. */
        Node<T>* next;      /**< Pointer to the next node in the linked list. */
        Node<T>* prev;      /**< Pointer to the previous node in the linked list. */

        /**
         * @brief Construct a new Node object with the given value and set next and prev pointers to NULL.
         * 
         * @param value The value to be held by the node.
         */
        Node(T value): value(value), next(nullptr), prev(nullptr) {}

        /**
         * @brief Construct a new Node object with the given value and set next and prev pointers accordingly.
         * 
         * @param value The value to be held by the node.
         * @param next Pointer to the next node.
         * @param prev Pointer to the previous node.
         */
        Node(T value, Node<T>* next, Node<T>* prev): value(value), next(next), prev(prev) {}

        /**
         * @brief Destructor for the Node object.
         */
        ~Node() {}

        /**
         * @brief Overloaded stream insertion operator for printing the value of the node.
         * 
         * @tparam U The type of the value of the node.
         * @param strm The output stream.
         * @param node The Node object to print.
         * @return std::ostream& The output stream after printing the value.
         */
        friend std::ostream& operator<<(std::ostream& strm, const Node<T>& node) {
            return strm << node.value;
        }

        /**
         * @brief Overloaded equality operator to compare two Node objects based on their values.
         * 
         * @tparam U The type of the value of the nodes.
         * @param node1 The first Node object to compare.
         * @param node2 The second Node object to compare.
         * @return true if the values of the nodes are equal, false otherwise.
         */
        friend bool operator==(const Node<T>& node1, const Node<T>& node2) {
            if constexpr (std::is_same_v<T, std::string>) {
                return node1.value.compare(node2.value) == 0;
            }

            return node1.value == node2.value;
        }

        /**
         * @brief Overloaded less than operator to compare two Node objects based on their values.
         * 
         * @tparam U The type of the value of the nodes.
         * @param node1 The first Node object to compare.
         * @param node2 The second Node object to compare.
         * @return true if the value of the first node is less than the value of the second node, false otherwise.
         */
        friend bool operator<(const Node<T>& node1, const Node<T>& node2) {
            if constexpr (std::is_same_v<T, std::string>) {
                return node1.value.compare(node2.value) < 0;
            }

            return node1.value < node2.value;
        }


        /**
         * @brief Overloaded assignment operator to assign the value of one Node to another.
         * 
         * @param other The Node object to assign.
         * @return T& Reference to the value of the assigned Node.
         */
        T& operator=(const T& other) {
            return this.value = other;
        }

        // Other comparison operator overloads (!=, <=, >, >=) follow the same pattern

        inline friend bool operator!=(const Node<T>& node1, const Node<T>& node2) { return !(node1.value == node2.value); }
        inline friend bool operator>(const Node<T>& node1, const Node<T>& node2) { return node2 < node1; }
        inline friend bool operator<=(const Node<T>& node1, const Node<T>& node2) { return !(node1 > node2); }
        inline friend bool operator>=(const Node<T>& node1, const Node<T>& node2) { return !(node1 < node2); }

};

#endif

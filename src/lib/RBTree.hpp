/**
 * @file RBTree.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a Red-Black Tree data structure. 
 *        The Red-Black Tree is a self-balancing binary search tree that 
 *        maintains the balance of the tree by satisfying certain color 
 *        properties. This data structure enables efficient insertion, 
 *        deletion, and search operations with guaranteed logarithmic 
 *        time complexity. The RBTree class provides methods to add 
 *        elements, remove elements, check element existence, and convert 
 *        the elements into linked lists or arrays. The class is designed 
 *        to handle various data types and ensures the tree remains 
 *        balanced to achieve optimal performance for common tree 
 *        operations.
 * @version 1.0.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <stdexcept>

#include "LinkedList.hpp"
#include "ArrayList.hpp"

/**
 * @brief A Red-Black Tree data structure implementation.
 * 
 * This class represents a Red-Black Tree data structure, which is a self-balancing binary search tree.
 * It maintains the balance of the tree by ensuring that the height of the two child subtrees of any node 
 * differs by at most one, and the coloring of the nodes is adjusted to satisfy certain properties known as 
 * "red" and "black" properties. This allows for efficient search, insert, and delete operations.
 * 
 * @tparam T The type of elements to be stored in the tree.
 */
template <class T> class RBTree {
    private:
        
        /**
         * @brief Node structure for the Red-Black Tree.
         */
        typedef struct Node {
            T element;           /**< The value stored in the node. */
            Node* left;          /**< Pointer to the left child node. */
            Node* right;         /**< Pointer to the right child node. */
            Node* parent;        /**< Pointer to the parent node. */
            bool isRed;          /**< Flag indicating whether the node is red or black. */
        } Node;

        Node* root;             /**< Pointer to the root node of the tree. */

        /**
         * @brief Performs a left rotation around the given node.
         * 
         * @param node The node around which the rotation is performed.
         */
        void rotateLeft(Node* node) {
            Node* right = node->right;
            node->right = right->left;
            if(right->left != nullptr)
                right->left->parent = node;

            right->parent = node->parent;
            if(node->parent == nullptr)
                this->root = right;
            else if(node == node->parent->left)
                node->parent->left = right;
            else
                node->parent->right = right;

            right->left = node;
            node->parent = right;
        }

        /**
         * @brief Performs a right rotation around the given node.
         * 
         * @param node The node around which the rotation is performed.
         */
        void rotateRight(Node* node) {
            Node* left = node->left;
            node->left = left->right;

            if(left->right != nullptr) 
                left->right->parent = node;

            left->parent = node->parent;
            if(node->parent == nullptr) 
                this->root = left;
            else if(node == node->parent->right) 
                node->parent->right = left;
            else 
                node->parent->left = left;

            left->right = node;
            node->parent = left;
        }

        /**
         * @brief Replaces one subtree as a child of its parent with another subtree.
         * 
         * @param u The node to be replaced.
         * @param v The node to replace u.
         */
        void transplant(Node* u, Node* v) {
            if(u->parent == nullptr)
                this->root = v;
            else if(u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;

            if(v != nullptr)
                v->parent = u->parent;
        }

        /**
         * @brief Checks if the node is red (or null) and returns the corresponding color.
         * 
         * @param node The node to check.
         * @return True if the node is red, false if it is black or null.
         */
        bool color(Node* node) {
            return node == nullptr ? false : node->isRed;
        }

        /**
         * @brief Restores the Red-Black Tree properties after insertion of a node.
         * 
         * @param node The node that was inserted and needs balancing.
         */
        void balanceInsertion(Node* node) {
            Node* uncle = nullptr;
            while(color(node->parent)) {
                if(node->parent == node->parent->parent->left) {
                    uncle = node->parent->parent->right;
                    if(color(uncle)) {
                        node->parent->isRed = false;
                        uncle->isRed = false;
                        node->parent->parent->isRed = true;
                        node = node->parent->parent;
                    } else {
                        if(node == node->parent->right) {
                            node = node->parent;
                            rotateLeft(node);
                        }

                        node->parent->isRed = false;
                        node->parent->parent->isRed = true;
                        rotateRight(node->parent->parent);
                    }
                } else {
                    uncle = node->parent->parent->left;
                    if(color(uncle)) {
                        node->parent->isRed = false;
                        uncle->isRed = false;
                        node->parent->parent->isRed = true;
                        node = node->parent->parent;
                    } else {
                        if(node == node->parent->left) {
                            node = node->parent;
                            rotateRight(node);
                        }

                        node->parent->isRed = false;
                        node->parent->parent->isRed = true;
                        rotateLeft(node->parent->parent);
                    }
                }
            }

            this->root->isRed = false;
        }

        /**
         * @brief Restores the Red-Black Tree properties after deletion of a node.
         * 
         * @param node The node that replaced the deleted node.
         * @param parent The parent node of the replacement node.
         */
        void balanceDeletion(Node* node, Node* parent) {
            Node* sibling = nullptr;
            while(node != this->root && !color(node)) {
                if(node == parent->left) {
                    sibling = parent->right;
                    if(color(sibling)) {
                        sibling->isRed = false;
                        parent->isRed = true;
                        rotateLeft(parent);
                        sibling = parent->right;
                    }

                    if(!color(sibling->left) && !color(sibling->right)) {
                        sibling->isRed = true;
                        node = parent;
                        parent = node->parent;
                    } else {
                        if(!color(sibling->right)) {
                            sibling->left->isRed = false;
                            sibling->isRed = true;
                            rotateRight(sibling);
                            sibling = parent->right;
                        }

                        sibling->isRed = parent->isRed;
                        parent->isRed = false;
                        sibling->right->isRed = false;
                        rotateLeft(parent);
                        node = this->root;
                    }
                } else {
                    sibling = parent->left;
                    if(color(sibling)) {
                        sibling->isRed = false;
                        parent->isRed = true;
                        rotateRight(parent);
                        sibling = parent->left;
                    }

                    if(!color(sibling->right) && !color(sibling->left)) {
                        sibling->isRed = true;
                        node = parent;
                        parent = node->parent;
                    } else {
                        if(!color(sibling->left)) {
                            sibling->right->isRed = false;
                            sibling->isRed = true;
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }

                        sibling->isRed = parent->isRed;
                        parent->isRed = false;
                        sibling->left->isRed = false;
                        rotateRight(parent);
                        node = this->root;
                    }
                }
            }

            if(node != nullptr) 
                node->isRed = false;
        }

        /**
         * @brief Finds the node with the minimum value in the given subtree.
         * 
         * @param node The root node of the subtree to search.
         * @return The node with the minimum value in the subtree.
         */
        Node* minimum(Node* node) {
            while(node->left != nullptr)
                node = node->left;
            return node;
        }

        /**
         * @brief Recursively clears the memory by deleting nodes.
         * 
         * @param node The current node being processed.
         */
        void clear(Node* node) {
            if(node != nullptr) {
                clear(node->left);
                clear(node->right);
                delete node;
            }
        }

        /**
         * @brief Converts the elements of the tree into a linked list in in-order traversal.
         * 
         * @param list The linked list to store the elements.
         * @param curr The current node being processed during traversal.
         */
        void toList(LinkedList<T>& list, Node* curr) const {
            if(curr != nullptr) {
                toList(list, curr->left);
                list.add(curr->element);
                toList(list, curr->right);
            }
        }

        /**
         * @brief Converts the elements of the tree into an array in in-order traversal.
         * 
         * @param array The array list to store the elements.
         * @param curr The current node being processed during traversal.
         */
        void toArray(ArrayList<T>& array, Node* curr) const {
            if(curr != nullptr) {
                toArray(array, curr->left);
                array.add(curr->element);
                toArray(array, curr->right);
            }
        }

        // Friend functions for overloading stream insertion and equality operators.

        friend std::ostream& operator<<(std::ostream& strm, const RBTree<T>& tree) {
            LinkedList<T> list = tree.toList();
            strm << list;
            return strm;
        }

    public:

        /**
         * @brief Constructor for RBTree class.
         */
        RBTree() {
            this->root = nullptr;
        }

        /**
         * @brief Copy constructor for RBTree class.
         * 
         * @param tree The tree to be copied.
         */
        RBTree(const RBTree& tree) {
            this->root = nullptr;
            ArrayList<T> list = tree.toArray();
            for(int i = 0; i < list.size(); i++)
                this->add(list[i]);
        }

        /**
         * @brief Destructor for RBTree class.
         */
        ~RBTree() {
            clear(this->root);
        }

        /**
         * @brief Overloaded assignment operator for RBTree class.
         * 
         * @param tree The tree to be copied.
         * @return A reference to the new tree.
         */
        RBTree& operator=(const RBTree& tree) {
            clear(this->root);
            this->root = nullptr;
            ArrayList<T> list = tree.toArray();
            for(int i = 0; i < list.size(); i++)
                this->add(list[i]);
            return *this;
        }

        /**
         * @brief Adds a new element to the tree.
         * 
         * @param element The element to be added to the tree.
         */
        void add(T element) {
            Node* parent = nullptr;
            Node* curr = this->root;

            while (curr != nullptr) {
                parent = curr;
                if (element < curr->element) 
                    curr = curr->left;
                else 
                    curr = curr->right;
            }

            Node* newNode = new Node;
            newNode->element = element;
            newNode->parent = parent;

            if (parent == nullptr)
                this->root = newNode;
            else if (element < parent->element)
                parent->left = newNode;
            else 
                parent->right = newNode;

            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->isRed = true;
            balanceInsertion(newNode);
        }

        /**
         * @brief Removes the first occurrence of the specified element from the tree.
         * 
         * @param element The element to be removed.
         */
        void pop(T element) {
            Node* curr = this->root;
            Node* node = nullptr;

            while(curr != nullptr) {
                if(curr->element == element) {
                    node = curr;
                    curr = nullptr;
                } else if(element < curr->element) {
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }

            if(node == nullptr)
                return;

            Node* x = nullptr;
            Node* y = node;
            bool isRed = y->isRed;

            if(node->left == nullptr) {
                x = node->right;
                transplant(node, node->right);
            } else if(node->right == nullptr) {
                x = node->left;
                transplant(node, node->left);
            } else {
                y = minimum(node->right);
                isRed = y->isRed;
                x = y->right;
                if(y->parent == node) {
                    if(x != nullptr)
                        x->parent = y;
                } else {
                    transplant(y, y->right);
                    y->right = node->right;
                    y->right->parent = y;
                }

                transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
                y->isRed = node->isRed;
            }

            if(!isRed)
                balanceDeletion(x, y->parent);
            
            delete node;
        }

        /**
         * @brief Checks if the tree contains the specified element.
         * 
         * @param element The element to be checked.
         * @return True if the element is present in the tree, false otherwise.
         */
        bool contains(T element) {
            Node* curr = this->root;
            while(curr != nullptr) {
                if(curr->element == element)
                    return true;
                else if(element < curr->element)
                    curr = curr->left;
                else
                    curr = curr->right;
            }

            return false;
        }

        /**
         * @brief Searchs an element in the tree.
         * @param element The element to be searched.
         * @return T& the element if found, nullptr otherwise.
         */
        T* search(T element) {
            Node* curr = this->root;
            while(curr != nullptr) {
                if(curr->element == element)
                    return &curr->element;
                else if(element < curr->element)
                    curr = curr->left;
                else
                    curr = curr->right;
            }

            return nullptr;
        }

        /**
         * @brief Converts the elements of the tree into a linked list in in-order traversal.
         * 
         * @return A linked list containing the elements of the tree in ascending order.
         */
        LinkedList<T> toList() const {
            LinkedList<T> list;
            toList(list, this->root);
            return list;
        }

        /**
         * @brief Converts the elements of the tree into an array in in-order traversal.
         * 
         * @return An array list containing the elements of the tree in ascending order.
         */
        ArrayList<T> toArray() const {
            ArrayList<T> array;
            toArray(array, this->root);
            return array;
        }

        /**
         * @brief Clears the tree and deallocates memory.
         */
        void clear() {
            clear(this->root);
        }

};

#endif
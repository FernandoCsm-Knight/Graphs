#ifndef LINKEDLISTITERATOR_HPP
#define LINKEDLISTITERATOR_HPP

#include "../../helpers/Node.hpp"

template <typename T> class LinkedListIterator {
    private:
        Node<T>* current;
    
    public:
        LinkedListIterator(Node<T>* start) : current(start) {}

        LinkedListIterator<T>& operator=(const LinkedListIterator<T>& other) {
            if (this != &other) 
                current = other.current;

            return *this;
        }

        T& operator*() {
            return current->value;
        }

        T* operator->() {
            return &(current->value);
        }

        LinkedListIterator<T>& operator++() {
            if (current != nullptr) 
                current = current->next;

            return *this;
        }

        LinkedListIterator<T> operator++(int) {
            LinkedListIterator<T> temp = *this;
            ++(*this);
            return temp;
        }

        LinkedListIterator<T>& operator--() {
            if (current != nullptr) 
                current = current->prev;

            return *this;
        }

        LinkedListIterator<T> operator--(int) {
            LinkedListIterator<T> temp = *this;
            --(*this);
            return temp;
        }

        bool operator!=(const LinkedListIterator<T>& other) const {
            return current != other.current;
        }

        bool operator==(const LinkedListIterator<T>& other) const {
            return current == other.current;
        }
};

#endif
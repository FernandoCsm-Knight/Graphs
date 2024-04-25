#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <iostream>
#include "ArrayList.hpp"
#include "LinkedList.hpp"

template <typename T> class HashSet {
    private:
        int length;
        int capacity;
        ArrayList<LinkedList<T>> table;

        size_t hash(const T& value) const {
            return std::hash<T>{}(value);
        }

    public:
        HashSet(int capacity = 100) {
            this->capacity = capacity;
            this->length = 0;
            table.resize(capacity);

            for(int i = 0; i < capacity; ++i) 
                table.add(LinkedList<T>());
        }

        HashSet(const HashSet& other) : capacity(other.capacity), table(other.table), length(other.length) {}

        ~HashSet() {}

        HashSet& operator=(const HashSet& other) {
            if(this != &other) {
                capacity = other.capacity;
                length = other.length;
                table = other.table;
            }

            return *this;
        }

        bool insert(const T& value) {
            int index = hash(value) % capacity;
            for(const T& element : table[index]) 
                if(element == value) 
                    return false;  

            length++;
            table[index].add(value);
            return true; 
        }

        bool remove(const T& value) {
            int index = hash(value) % capacity;
            bool done = table[index].pop(value);
            if(done) length--;
            return done;
        }

        T& operator[](const T& value) {
            int index = hash(value) % capacity;
            for(T& element : table[index]) 
                if(element == value) 
                    return element;

            length++;
            table[index].add(value);
            return table[index].back();
        }

        T get(const T& value) const {
            int index = hash(value) % capacity;
            for(const T& element : table[index]) 
                if(element == value) 
                    return element;

            return T();
        }

        bool contains(const T& value) const {
            int index = hash(value) % capacity;
            for(const T& element : table[index]) 
                if(element == value) 
                    return true;

            return false;
        }

        int size() const {
            return this->length;
        }

        bool isEmpty() const {
            return this->length == 0;
        }

        friend std::ostream& operator<<(std::ostream& os, const HashSet<T>& set) {
            os << "[";
            for(const LinkedList<T>& list : set.table) 
                os << list;
            os << "]";
            return os;
        }
};

#endif
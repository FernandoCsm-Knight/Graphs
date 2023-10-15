#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <iostream>

#include "ArrayList.hpp"

template <typename K, typename V> class HashMap {
    private:
        struct KeyValue {
            K key;
            V value;
            KeyValue* next;
            KeyValue(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
        };

        std::size_t length;
        std::size_t capacity;
        ArrayList<KeyValue*> table;

        std::size_t hash(const K& key) {
            return std::hash<K>{}(key) % capacity;
        }

    public:
        HashMap(std::size_t capacity = 16) {
            this->capacity = capacity;
            this->length = 0;
            table.resize(capacity);

            for(std::size_t i = 0; i < capacity; ++i) 
                table.add(nullptr);
        }

        ~HashMap() {
            clear();
        }

        void clear() {
            for (std::size_t i = 0; i < capacity; ++i) {
                KeyValue* current = table[i];
                while(current != nullptr) {
                    KeyValue* temp = current;
                    current = current->next;
                    delete temp;
                }

                table[i] = nullptr;
            }

            length = 0;
        }

        void insert(const K& key, const V& value) {
            std::size_t index = hash(key);
            KeyValue* current = table[index];

            while(current != nullptr && current->key != key) 
                current = current->next;

            if(current != nullptr) {
                current->value = value;
                return;
            }

            KeyValue* newKeyValue = new KeyValue(key, value);
            newKeyValue->next = table[index];
            table[index] = newKeyValue;
            length++;

            if(length >= capacity * 0.75)
                resize(capacity * 2);
        }

        V get(const K& key) {
            std::size_t index = hash(key);
            KeyValue* current = table[index];

            while(current != nullptr && current->key != key) 
                current = current->next;
            
            if(current != nullptr) 
                return current->value;

            return V();
        }

        V& operator[](const K& key) {
            std::size_t index = hash(key);
            KeyValue* current = table[index];

            while(current != nullptr && current->key != key) 
                current = current->next;

            if(current != nullptr)
                return current->value;

            KeyValue* newKeyValue = new KeyValue(key, V());
            newKeyValue->next = table[index];
            table[index] = newKeyValue;
            length++;

            if(length >= capacity * 0.75)
                resize(capacity * 2);

            return newKeyValue->value;
        }

        bool remove(const K& key) {
            size_t index = hash(key);
            KeyValue* current = table[index];
            KeyValue* prev = nullptr;

            while(current != nullptr && current->key != key) {
                prev = current;
                current = current->next;
            }

            if(current != nullptr) {
                if(prev != nullptr) prev->next = current->next;
                else table[index] = current->next;
                
                delete current;
                length--;
                return true;
            }

            return false;
        }

        bool contains(const K& key) {
            std::size_t index = hash(key);
            KeyValue* current = table[index];

            while(current != nullptr && current->key != key) 
                current = current->next;

            return current != nullptr;
        }

        void resize(std::size_t newCapacity) {
            ArrayList<KeyValue*> newTable;
            newTable.resize(newCapacity);

            for(std::size_t i = 0; i < newCapacity; ++i) 
                newTable.add(nullptr);

            for(std::size_t i = 0; i < capacity; ++i) {
                KeyValue* current = table[i];
                while(current != nullptr) {
                    KeyValue* temp = current;
                    current = current->next;

                    std::size_t index = std::hash<K>{}(temp->key) % newCapacity;
                    temp->next = newTable[index];
                    newTable[index] = temp;
                }
            }

            table.clear();
            table = newTable;
            capacity = newCapacity;
        }

        std::size_t size() const {
            return this->length;
        }

        bool isEmpty() const {
            return this->length == 0;
        }

        ArrayList<K> keys() const {
            ArrayList<K> keys;

            for(std::size_t i = 0; i < capacity; ++i) {
                KeyValue* current = table[i];
                while(current != nullptr) {
                    keys.add(current->key);
                    current = current->next;
                }
            }

            return keys;
        }

        ArrayList<V> values() const {
            ArrayList<V> values;

            for(std::size_t i = 0; i < capacity; ++i) {
                KeyValue* current = table[i];
                while(current != nullptr) {
                    values.add(current->value);
                    current = current->next;
                }
            }

            return values;
        }

        friend std::ostream& operator<<(std::ostream& os, const HashMap<K, V>& map) {
            os << "[ ";
            for(std::size_t i = 0; i < map.capacity; ++i) {
                int j = 0;
                KeyValue* current = map.table.get(i);
                if(current != nullptr) os << "[";

                while(current != nullptr) {
                    ++j;
                    os << "(" << current->key << ", " << current->value << ")";
                    current = current->next;
                    if(current != nullptr) os << ", ";
                }

                if(j > 0) {
                    os << "] ";
                    j = 0;
                }
            }

            return os << "]";
        }
};


#endif
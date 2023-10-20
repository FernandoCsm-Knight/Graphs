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

        int length;
        int capacity;
        ArrayList<KeyValue*> table;

        std::size_t hash(const K& key) const {
            return std::hash<K>{}(key) % capacity;
        }

    public:
        HashMap(int capacity = 16) {
            this->capacity = capacity;
            this->length = 0;
            table.resize(capacity);

            for(int i = 0; i < capacity; ++i) 
                table.add(nullptr);
        }

        HashMap(const HashMap<K, V>& other) : capacity(other.capacity), length(other.length) {
            table.resize(capacity);
            for(int i = 0; i < capacity; ++i) 
                table.add(nullptr);

            for (int i = 0; i < capacity; ++i) {
                if (other.table.get(i) != nullptr) {
                    KeyValue* current = other.table.get(i);
                    KeyValue* prev = nullptr;
                    while (current != nullptr) {
                        KeyValue* newKeyValue = new KeyValue(current->key, current->value);
                        if (prev == nullptr) {
                            table[i] = newKeyValue;
                        } else {
                            prev->next = newKeyValue;
                        }
                        prev = newKeyValue;
                        current = current->next;
                    }
                }
            }
        }

        ~HashMap() {
            clear();
        }

        HashMap<K, V>& operator=(const HashMap<K, V>& other) {
            if (this != &other) {
                clear();
                table.clear();
                capacity = other.capacity;
                length = other.length;
                table.resize(capacity);

                for(int i = 0; i < capacity; ++i) 
                    table.add(nullptr);

                for (int i = 0; i < capacity; ++i) {
                    if (other.table.get(i) != nullptr) {
                        KeyValue* current = other.table.get(i);
                        KeyValue* prev = nullptr;
                        while (current != nullptr) {
                            KeyValue* newKeyValue = new KeyValue(current->key, current->value);
                            if (prev == nullptr) {
                                table[i] = newKeyValue;
                            } else {
                                prev->next = newKeyValue;
                            }
                            prev = newKeyValue;
                            current = current->next;
                        }
                    }
                }
            }

            return *this;
        }

        void clear() {
            for(int i = 0; i < capacity; ++i) {
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

        void put(const K& key, const V& value) {
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

        V get(const K& key) const {
            std::size_t index = hash(key);
            KeyValue* current = table.get(index);

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
            std::size_t index = hash(key);
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

        bool contains(const K& key) const {
            std::size_t index = hash(key);
            KeyValue* current = table.get(index);

            while(current != nullptr && current->key != key) 
                current = current->next;

            return current != nullptr;
        }

        void resize(int newCapacity) {
            ArrayList<KeyValue*> newTable;
            newTable.resize(newCapacity);

            for(int i = 0; i < newCapacity; ++i) 
                newTable.add(nullptr);

            for(int i = 0; i < capacity; ++i) {
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

        int size() const {
            return this->length;
        }

        bool isEmpty() const {
            return this->length == 0;
        }

        ArrayList<K> keys() const {
            ArrayList<K> keys;

            for(int i = 0; i < capacity; ++i) {
                KeyValue* current = table.get(i);
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
            os << "{ " << std::endl;
            for(int i = 0; i < map.capacity; ++i) {
                KeyValue* current = map.table.get(i);
                int j = 0;

                while(current != nullptr) {
                    ++j;
                    os << "\t" << current->key << ": " << current->value;
                    current = current->next;
                    if(current != nullptr) os << ", ";
                }

                if(j != 0) {
                    os << std::endl;
                    j = 0;
                }
            }

            return os << "}";
        }
};


#endif
/**
 * @file Map.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a template class, which implements a key-value map.
 *        The class uses a red-black tree to store the key-value pairs, providing efficient access
 *        and insertion of elements. The class supports operations like adding key-value pairs,
 *        retrieving values by keys, removing pairs, checking for key existence, and obtaining lists
 *        of keys and values. It also includes overloaded operators for printing and comparing maps.
 * @version 1.0.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <stdexcept>

#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "RBTree.hpp"

#include "../helpers/Pair.hpp"

/**
 * @class Map
 * @brief A templated class representing a key-value map using a red-black tree.
 * @tparam K The type of the keys.
 * @tparam V The type of the values.
 */
template <class K, class V> class Map {
    private:
        int length; /**< The number of key-value pairs in the map. */
        RBTree<Pair<K, V>> tree; /**< The red-black tree used to store the key-value pairs. */

        // Friend functions for overloading stream insertion and equality operators.

        friend std::ostream& operator<<(std::ostream& strm, const Map<K, V>& map) {
            ArrayList<Pair<K, V>> list = map.tree.toArray();
            
            strm << "{" << std::endl;
            for(int i = 0; i < list.size(); ++i) {
                strm << "\t" << list[i].key << ": " << list[i].value;
                if(i < list.size() - 1)
                    strm << ",";
                strm << std::endl;
            }

            return strm << "}";
        }

        friend bool operator==(const Map<K, V>& map1, const Map<K, V>& map2) {
            bool eq = map1.length == map2.length;

            ArrayList<Pair<K, V>> list1 = map1.tree.toArray();
            ArrayList<Pair<K, V>> list2 = map2.tree.toArray();

            for(int i = 0; i < map1.length && eq; ++i) 
                eq = list1[i].key == list2[i].key;

            return eq;
        }

    public: 
        /**
         * @brief Default constructor for the Map class.
         */
        Map(): length(0) {}

        /**
         * @brief Copy constructor for the Map class.
         * @param map The Map object to copy.
         */
        Map(const Map<K, V>& map) {
            this->length = map.length;
            this->tree = map.tree;
        }

        /**
         * @brief Destructor for the Map class.
         */
        ~Map() {}

        /**
         * @brief Overloaded assignment operator for the Map class.
         * 
         * @param map The Map object to copy.
         * @return Map<K, V>& Reference to the Map object after copying.
         */
        Map<K, V>& operator=(const Map<K, V>& map) {
            if(this != &map) {
                this->length = map.length;
                this->tree = map.tree;
            }

            return *this;
        }

        /**
         * @brief Get the number of key-value pairs in the map.
         * @return int The number of key-value pairs in the map.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Add or update a key-value pair in the map.
         * @param key The key to be added or updated.
         * @param value The value to be associated with the key.
         */
        void put(K key, V value) {
            tree.add(Pair<K, V>(key, value));
            this->length++;
        }

        /**
         * @brief Get the value associated with the given key.
         * @param key The key to search for.
         * @return V The value associated with the given key.
         * @throw std::runtime_error if the key is not found in the map.
         */
        V get(K key) const {
            Pair<K, V> element = Pair<K, V>(key);
            V value = tree.search(element)->value;
            return value;
        }

        /**
         * @brief Get the value associated with the given key.
         * @param key The key to search for.
         * @return V& The value associated with the given key.
         */
        V& operator[](K key) {
            Pair<K, V> element = Pair<K, V>(key);
            Pair<K, V>* reached = tree.search(element);

            if(reached != nullptr) 
                return reached->value;
                    
            tree.add(element);
            reached = tree.search(element);
            this->length++;

            return reached->value;
        }

        /**
         * @brief Remove the key-value pair with the given key from the map.
         * @param key The key to remove.
         */
        bool remove(K key) {
            if(tree.contains(Pair<K, V>(key))) {
                tree.pop(Pair<K, V>(key));
                this->length--;
                return true;
            }

            return false;
        }

        /**
         * @brief Check if the map contains the given key.
         * @param key The key to check for existence.
         * @return bool true if the key exists in the map, false otherwise.
         */
        bool contains(K key) const {
            return tree.contains(Pair<K, V>(key));
        }

        /**
         * @brief Get a list of all keys in the map.
         * @return ArrayList<K> An ArrayList containing all keys in the map.
         */
        ArrayList<K> keys() const {
            ArrayList<Pair<K, V>> list = tree.toArray();
            ArrayList<K> keys = ArrayList<K>();

            for(int i = 0; i < list.size(); ++i) 
                keys.add(list[i].key);

            return keys;
        }

        /**
         * @brief Get a list of all values in the map.
         * @return ArrayList<V> An ArrayList containing all values in the map.
         */
        ArrayList<V> values() const {
            ArrayList<Pair<K, V>> list = tree.toArray();
            ArrayList<V> values = ArrayList<V>();

            for(int i = 0; i < list.size(); ++i) 
                values.add(list[i].value);

            return values;
        }

        /**
         * @brief Convert the map to a linked list of key-value pairs.
         * @return LinkedList<Pair<K, V>> A linked list containing all key-value pairs from the map.
         */
        LinkedList<Pair<K, V>> toList() const {
            return tree.toList();
        }

        /**
         * @brief Clear all key-value pairs from the map.
         */
        void clear() {
            tree.clear();
            this->length = 0;
        }

        /**
         * @brief Clear all values from the map.
         */
        void clearValues() {
            ArrayList<Pair<K, V>> list = tree.toArray();

            for(int i = 0; i < list.size(); ++i) 
                list[i].value = V();

            tree.clear();

            for(int i = 0; i < list.size(); ++i) 
                tree.add(list[i]);

            this->length = list.size();
        }
};

#endif
/**
 * @file Pair.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a `Pair` class, a templated container that represents a key-value pair.
 *        The class allows associating a key of type K with a corresponding value of type V. It provides multiple
 *        constructors for creating key-value pairs, including default, key-only, and key-value constructors.
 *        Additionally, the class overloads several comparison operators, such as equality, inequality, less than,
 *        less than or equal, greater than, and greater than or equal, to compare key-value pairs based on their keys.
 *        The class is designed to be used in data structures and algorithms that require storing and managing
 *        key-value associations efficiently.
 * @version 1.0.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PAIR_HPP
#define PAIR_HPP

template <class K, class V> class Pair {
    public:
        K key;          /**< The key of the key-value pair. */
        V value;        /**< The value associated with the key. */
        bool isTuple;   /**< Flag indicating whether the Pair is a tuple. */

        /**
         * @brief Default constructor for Pair.
         * Initializes the key and value with default values for their types.
         */
        Pair(): key(K()), value(V()), isTuple(false) {}

        /**
         * @brief Constructor for Pair with the given key.
         * @param key The key to set.
         */
        Pair(K key): key(key), value(V()), isTuple(false) {}

        /**
         * @brief Constructor for Pair with the given key and value.
         * @param key The key to set.
         * @param value The value to associate with the key.
         * @param tuple Flag indicating whether the Pair is a tuple.
         */
        Pair(K key, V value, bool tuple = false): key(key), value(value), isTuple(tuple) {}

        /**
         * @brief Copy constructor for Pair.
         * 
         * @param other The Pair to copy.
         */
        Pair(const Pair<K, V>& other): key(other.key), value(other.value), isTuple(other.isTuple) {}

        /**
         * @brief Destructor for Pair.
         */
        ~Pair() {}

        /**
         * @brief Overloaded assignment operator for Pair.
         * @param other The Pair to copy.
         * 
         * @return Pair& A reference to the Pair after copying.
         */
        Pair<K, V>& operator=(const Pair<K, V>& other) {
            if(this != &other) {
                this->key = other.key;
                this->value = other.value;
                this->isTuple = other.isTuple;
            }

            return *this;
        }

        /**
         * @brief getter for the key.
         */
        inline K& first() { return this->key; }

        /**
         * @brief getter for the value.
         */
        inline V& second() { return this->value; }

        /**
         * @brief Overloaded stream insertion operator to print the key-value pair.
         * @tparam U The type of the keys in the key-value pair.
         * @tparam W The type of the values in the key-value pair.
         * @param strm The output stream.
         * @param kv The Pair object to print.
         * @return std::ostream& The output stream after printing the key-value pair.
         */
        friend std::ostream& operator<<(std::ostream& strm, const Pair<K, V>& kv) {
            if(kv.value == V()) 
                return strm << kv.key;
            
            return strm << "(" << kv.key << ", " << kv.value << ")";
        }

        /**
         * @brief Overloaded equality operator to compare two key-value pairs based on their keys.
         * @tparam U The type of the keys in the key-value pairs.
         * @tparam W The type of the values in the key-value pairs.
         * @param kv1 The first Pair object to compare.
         * @param kv2 The second Pair object to compare.
         * @return true if the keys of the key-value pairs are equal, false otherwise.
         */
        friend bool operator==(const Pair<K, V>& kv1, const Pair<K, V>& kv2) {
            if(kv1.isTuple && kv2.isTuple) {
                bool keyEqual = false;
                bool valueEqual = false;

                if constexpr (std::is_same_v<K, std::string>) 
                    keyEqual = kv1.key.compare(kv2.key) == 0;
                else
                    keyEqual = kv1.key == kv2.key;

                if constexpr (std::is_same_v<V, std::string>) 
                    valueEqual = kv1.value.compare(kv2.value) == 0;
                else 
                    valueEqual = kv1.value == kv2.value;

                return keyEqual && valueEqual;
            } else {
                if constexpr (std::is_same_v<K, std::string>) {
                    return kv1.key.compare(kv2.key) == 0;
                } 
                    
                return kv1.key == kv2.key;
            }
        }

        /**
         * @brief Overloaded less than operator to compare two key-value pairs based on their keys.
         * 
         * @param kv1 The first Pair object to compare.
         * @param kv2 The second Pair object to compare.
         * @return true if the key of the first key-value pair is less than the key of 
         *         the second key-value pair, false otherwise.
         */
        friend bool operator<(const Pair<K, V>& kv1, const Pair<K, V>& kv2) { 
            if constexpr (std::is_same_v<K, V>) {
                if constexpr (std::is_same_v<K, std::string>) {
                    if(kv1.key.compare(kv2.key) == 0) 
                        return kv1.value.compare(kv2.value) < 0;
                    else 
                        return kv1.key.compare(kv2.key) < 0;
                } else {
                    if(kv1.key == kv2.key) 
                        return kv1.value < kv2.value;
                    else 
                        return kv1.key < kv2.key;
                }
            }

            if constexpr (std::is_same_v<K, std::string>) {
                return kv1.key.compare(kv2.key) < 0;
            }

            return kv1.key < kv2.key; 
        }

        // Other comparison operator overloads (!=, <=, >, >=) follow the same pattern

        inline friend bool operator!=(const Pair<K, V>& kv1, const Pair<K, V>& kv2) { return !(kv1 == kv2); }
        inline friend bool operator<=(const Pair<K, V>& kv1, const Pair<K, V>& kv2) { return !(kv2 < kv1); }
        inline friend bool operator>(const Pair<K, V>& kv1, const Pair<K, V>& kv2) { return kv2 < kv1; }
        inline friend bool operator>=(const Pair<K, V>& kv1, const Pair<K, V>& kv2) { return !(kv1 < kv2); }
};

#endif
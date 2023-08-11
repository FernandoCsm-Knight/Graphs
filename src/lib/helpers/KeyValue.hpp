/**
 * @file KeyValue.hpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a `KeyValue` class, a templated container that represents a key-value pair.
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

#ifndef KEYVALUE_HPP
#define KEYVALUE_HPP

template <class K, class V> class KeyValue {
    public:
        K key; /**< The key of the key-value pair. */
        V value; /**< The value associated with the key. */

        /**
         * @brief Default constructor for KeyValue.
         * Initializes the key and value with default values for their types.
         */
        KeyValue(): key(K()), value(V()) {}

        /**
         * @brief Constructor for KeyValue with the given key.
         * @param key The key to set.
         */
        KeyValue(K key): key(key), value(V()) {}
        
        /**
         * @brief Constructor for KeyValue with the given key and value.
         * @param key The key to set.
         * @param value The value to associate with the key.
         */
        KeyValue(K key, V value): key(key), value(value) {}

        /**
         * @brief Destructor for KeyValue.
         */
        ~KeyValue() {}

        /**
         * @brief Overloaded stream insertion operator to print the key-value pair.
         * @tparam U The type of the keys in the key-value pair.
         * @tparam W The type of the values in the key-value pair.
         * @param strm The output stream.
         * @param kv The KeyValue object to print.
         * @return std::ostream& The output stream after printing the key-value pair.
         */
        friend std::ostream& operator<<(std::ostream& strm, const KeyValue<K, V>& kv) {
            return strm << kv.key << ": " << kv.value;
        }

        /**
         * @brief Overloaded equality operator to compare two key-value pairs based on their keys.
         * @tparam U The type of the keys in the key-value pairs.
         * @tparam W The type of the values in the key-value pairs.
         * @param kv1 The first KeyValue object to compare.
         * @param kv2 The second KeyValue object to compare.
         * @return true if the keys of the key-value pairs are equal, false otherwise.
         */
        friend bool operator==(const KeyValue<K, V>& kv1, const KeyValue<K, V>& kv2) {            
            if constexpr (std::is_same_v<K, std::string>) {
                return kv1.key.compare(kv2.key) == 0;
            } else {
                return kv1.key == kv2.key;
            }
        }

        /**
         * @brief Overloaded less than operator to compare two key-value pairs based on their keys.
         * 
         * @param kv1 The first KeyValue object to compare.
         * @param kv2 The second KeyValue object to compare.
         * @return true if the key of the first key-value pair is less than the key of 
         *         the second key-value pair, false otherwise.
         */
        friend bool operator<(const KeyValue<K, V>& kv1, const KeyValue<K, V>& kv2) { 
            if constexpr (std::is_same_v<K, std::string>) {
                return kv1.key.compare(kv2.key) < 0;
            } else {
                return kv1.key < kv2.key;
            }
        }

        // Other comparison operator overloads (!=, <, <=, >, >=) follow the same pattern

        inline friend bool operator!=(const KeyValue<K, V>& kv1, const KeyValue<K, V>& kv2) { return !(kv1 == kv2); }
        inline friend bool operator<=(const KeyValue<K, V>& kv1, const KeyValue<K, V>& kv2) { return !(kv2 < kv1); }
        inline friend bool operator>(const KeyValue<K, V>& kv1, const KeyValue<K, V>& kv2) { return kv2 < kv1; }
        inline friend bool operator>=(const KeyValue<K, V>& kv1, const KeyValue<K, V>& kv2) { return !(kv1 < kv2); }
};

#endif
#ifndef NUMERIC_HPP
#define NUMERIC_HPP

#include <concepts>
#include <type_traits>

namespace art {
    /**
     * @brief A concept that checks if a type is a numeric type.
     * 
     * @tparam T the type to check.
     */
    template <typename T>
    concept Numeric = requires(T t) {
        std::is_same_v<T, int> ||
        std::is_same_v<T, long> ||
        std::is_same_v<T, float> ||
        std::is_same_v<T, double>;
    };
}

#endif
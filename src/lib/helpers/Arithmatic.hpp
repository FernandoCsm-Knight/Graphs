/**
 * @file Arithmatic.cpp
 * @author Fernando Campos Silva Dal Maria (fernandocsdm@gmail.com)
 * @brief A class that provides arithmetic operations for combinatorial problems.
 * @version 1.0.0
 * @date 2024-03-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <cmath>
#include <concepts>

#include "../datastructs/ArrayList.hpp"

class Arithmetic {
    public:
        /**
         * @brief Calculates the factorial of a number.
         * 
         * @param n the number to calculate the factorial.
         * @return unsigned long long the factorial of the number.
         */
        unsigned long long factorial(int n) const {
            int num = 1;
            for(int i = 1; i <= n; ++i) num *= i;
            return num;
        }
        
        /**
         * @brief Calculates the number of permutations of a set of n elements.
         * 
         * @param k the number of elements to permute.
         * @return unsigned long long the number of permutations.
         */
        unsigned long long permutations(int k) const {  
            return factorial(k);
        }
        
        /**
         * @brief Calculates the number of permutations of a set of n elements.
         * 
         * @param n the number of elements in the set.
         * @param k the number of elements to permute.
         * @return unsigned long long the number of permutations.
         */
        unsigned long long arrangements(int n, int k) const {
            return factorial(n) / factorial(n - k);
        }
        
        /**
         * @brief Calculates the number of combinations of a set of n elements.
         * 
         * @param n the number of Graph<int> graph(GraphTypes::COMPLETE, 9, false);

Stopwatch sw("Gelements in the set.
         * @param k the number of elements to combine.
         * @return unsigned long long the number of combinations.
         */
        unsigned long long combinations(int n, int k) const {
            return factorial(n) / (factorial(k) * factorial(n - k));
        }
};

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
    
    /**
     * @brief Calculates the sum of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the sum.
     * @return T the sum of the elements in the array.
     */
    template <Numeric T> 
    T sum(ArrayList<T> arr) {
        long sum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += arr[i];
        }
        
        return sum;
    }

    /**
     * @brief Calculates the product of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the product.
     * @return T the product of the elements in the array.
     */
    template <Numeric T>
    T product(ArrayList<T> arr) {
        long product = 1;
        
        for(int i = 0; i < arr.size(); ++i) {
            product *= arr[i];
        }

        return product;
    }

    /**
     * @brief Calculates the mean of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the mean.
     * @return T the mean of the elements in the array.
     */
    template <Numeric T>
    T mean(ArrayList<T> arr) {
        return sum(arr) / arr.size();
    }
    
    /**
     * @brief Calculates the median of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the median.
     * @return T the median of the elements in the array.
     */
    template <Numeric T>
    T median(ArrayList<T> arr) {
        int n = arr.size();
        arr.sort();
        
        if(n % 2 == 0) {
            return (arr[n / 2 - 1] + arr[n / 2]) / 2;
        } else {
            return arr[n / 2];
        }
    }

    /**
     * @brief Calculates the mode of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the mode.
     * @return T the mode of the elements in the array.
     */
    template <Numeric T>
    T mode(ArrayList<T> arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        
        int maxCount = 0;
        T mode = arr[0];
        int count = 1;
        T current = arr[0];
        
        for(int i = 1; i < n; ++i) {
            if(arr[i] == current) {
                count++;
            } else {
                if(count > maxCount) {
                    maxCount = count;
                    mode = current;
                }
                
                count = 1;
                current = arr[i];
            }
        }
        
        return mode;
    }

    /**
     * @brief Calculates the variance of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the variance.
     * @return T the variance of the elements in the array.
     */
    template <Numeric T>
    T variance(ArrayList<T> arr) {
        T mean = art::mean(arr);
        T variance = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            variance += (arr[i] - mean) * (arr[i] - mean);
        }
        
        return variance / arr.size();
    }

    /**
     * @brief Calculates the standard deviation of the elements in an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array to calculate the standard deviation.
     * @return T the standard deviation of the elements in the array.
     */
    template <Numeric T>
    T standardDeviation(ArrayList<T> arr) {
        return std::sqrt(variance(arr));
    }

    /**
     * @brief Calculates the covariance of two arrays.
     * 
     * @tparam T the type of the elements in the arrays.
     * @see Numeric
     * @param arr1 the first array.
     * @param arr2 the second array.
     * @return T the covariance of the two arrays.
     */
    template <Numeric T>
    T covariance(ArrayList<T> arr1, ArrayList<T> arr2) {
        T mean1 = mean(arr1);
        T mean2 = mean(arr2);
        T covariance = 0;
        
        for(int i = 0; i < arr1.size(); ++i) {
            covariance += (arr1[i] - mean1) * (arr2[i] - mean2);
        }
        
        return covariance / arr1.size();
    }

    /**
     * @brief Calculates the correlation of two arrays.
     * 
     * @tparam T the type of the elements in the arrays.
     * @see Numeric
     * @param arr1 the first array.
     * @param arr2 the second array.
     * @return T the correlation of the two arrays.
     */
    template <Numeric T>
    T correlation(ArrayList<T> arr1, ArrayList<T> arr2) {
        return covariance(arr1, arr2) / (standardDeviation(arr1) * standardDeviation(arr2));
    }

    /**
     * @brief Calculates the z-score of a value.
     * 
     * @tparam T the type of the value.
     * @see Numeric
     * @param x the value.
     * @param mean the mean of the values.
     * @param stdDev the standard deviation of the values.
     * @return T the z-score of the value.
     */
    template <Numeric T>
    T zScore(T x, T mean, T stdDev) {
        return (x - mean) / stdDev;
    }

    /**
     * @brief Calculates the z-scores of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return ArrayList<T> the z-scores of the elements in the array.
     */
    template <Numeric T>
    ArrayList<T> zScoreSet(ArrayList<T> arr) {
        T mean = art::mean(arr);
        T stdDev = art::standardDeviation(arr);
        ArrayList<T> zScores;

        for(int i = 0; i < arr.size(); ++i) {
            zScores.add(zScore(arr[i], mean, stdDev));
        }

        return zScores;
    }

    /**
     * @brief Calculates the percentile of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param p the percentile.
     * @return T the percentile of the array.
     */
    template <Numeric T>
    T percentile(ArrayList<T> arr, T p) {
        int n = arr.size();
        arr.sort();
        
        T rank = p * (n - 1);
        int k = (int) rank;
        T d = rank - k;
        
        if(k + 1 < n) {
            return arr[k] + d * (arr[k + 1] - arr[k]);
        } else {
            return arr[k];
        }
    }

    /**
     * @brief Calculates the quartile of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param q the quartile.
     * @return T the quartile of the array.
     */
    template <Numeric T>
    T quartile(ArrayList<T> arr, int q) {
        int n = arr.size();
        arr.sort();
        
        if(n % 2 == 0) {
            int k = n / 2;
            ArrayList<T> lowerHalf = arr.subList(0, k);
            ArrayList<T> upperHalf = arr.subList(k, n);
            
            if(q == 1) {
                return median(lowerHalf);
            } else {
                return median(upperHalf);
            }
        } else {
            int k = n / 2;
            ArrayList<T> lowerHalf = arr.subList(0, k);
            ArrayList<T> upperHalf = arr.subList(k + 1, n);
            
            if(q == 1) {
                return median(lowerHalf);
            } else {
                return median(upperHalf);
            }
        }
    }

    /**
     * @brief Calculates the interquartile range of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the interquartile range of the array.
     */
    template <Numeric T>
    T iqr(ArrayList<T> arr) {
        return quartile(arr, 3) - quartile(arr, 1);
    }

    /**
     * @brief Calculates the outlier of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the outlier of the array.
     */
    template <Numeric T>
    T outlier(ArrayList<T> arr) {
        T q1 = quartile(arr, 1);
        T q3 = quartile(arr, 3);
        T iqr = q3 - q1;
        
        T lowerBound = q1 - 1.5 * iqr;
        T upperBound = q3 + 1.5 * iqr;
        
        for(int i = 0; i < arr.size(); ++i) {
            if(arr[i] < lowerBound || arr[i] > upperBound) {
                return arr[i];
            }
        }
        
        return 0;
    }

    /**
     * @brief Calculates the range of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the range of the array.
     */
    template <Numeric T>
    T range(ArrayList<T> arr) {
        arr.sort();
        return arr[arr.size() - 1] - arr[0];
    }

    /**
     * @brief Calculates the midrange of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the midrange of the array.
     */
    template <Numeric T>
    T midRange(ArrayList<T> arr) {
        arr.sort();
        return (arr[0] + arr[arr.size() - 1]) / 2;
    }

    /**
     * @brief Calculates the harmonic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the harmonic mean of the array.
     */
    template <Numeric T>
    T harmonicMean(ArrayList<T> arr) {
        T sum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += 1 / arr[i];
        }
        
        return arr.size() / sum;
    }

    /**
     * @brief Calculates the geometric mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the geometric mean of the array.
     */
    template <Numeric T>
    T geometricMean(ArrayList<T> arr) {
        T product = 1;
        
        for(int i = 0; i < arr.size(); ++i) {
            product *= arr[i];
        }
        
        return std::pow(product, 1.0 / arr.size());
    }

    /**
     * @brief Calculates the root mean square of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the root mean square of the array.
     */
    template <Numeric T>
    T rootMeanSquare(ArrayList<T> arr) {
        T sum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += arr[i] * arr[i];
        }
        
        return std::sqrt(sum / arr.size());
    }

    /**
     * @brief Calculates the weighted mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted mean of the array.
     */
    template <Numeric T>
    T weightedMean(ArrayList<T> arr, ArrayList<T> weights) {
        T sum = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += arr[i] * weights[i];
            weightSum += weights[i];
        }
        
        return sum / weightSum;
    }

    /**
     * @brief Calculates the weighted geometric mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted geometric mean of the array.
     */
    template <Numeric T>
    T weightedGeometricMean(ArrayList<T> arr, ArrayList<T> weights) {
        T product = 1;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            product *= std::pow(arr[i], weights[i]);
            weightSum += weights[i];
        }
        
        return std::pow(product, 1.0 / weightSum);
    }

    /**
     * @brief Calculates the weighted harmonic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted harmonic mean of the array.
     */
    template <Numeric T>
    T weightedHarmonicMean(ArrayList<T> arr, ArrayList<T> weights) {
        T sum = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += weights[i] / arr[i];
            weightSum += weights[i];
        }
        
        return weightSum / sum;
    }

    /**
     * @brief Calculates the weighted root mean square of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted root mean square of the array.
     */
    template <Numeric T>
    T weightedRootMeanSquare(ArrayList<T> arr, ArrayList<T> weights) {
        T sum = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += weights[i] * arr[i] * arr[i];
            weightSum += weights[i];
        }
        
        return std::sqrt(sum / weightSum);
    }

    /**
     * @brief Calculates the weighted quadratic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted quadratic mean of the array.
     */
    template <Numeric T>
    T weightedVariance(ArrayList<T> arr, ArrayList<T> weights) {
        T mean = weightedMean(arr, weights);
        T variance = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            variance += weights[i] * (arr[i] - mean) * (arr[i] - mean);
            weightSum += weights[i];
        }
        
        return variance / weightSum;
    }

    /**
     * @brief Calculates the weighted standard deviation of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted standard deviation of the array.
     */
    template <Numeric T>
    T weightedStandardDeviation(ArrayList<T> arr, ArrayList<T> weights) {
        return std::sqrt(weightedVariance(arr, weights));
    }

    /**
     * @brief Calculates the weighted covariance of two arrays.
     * 
     * @tparam T the type of the elements in the arrays.
     * @see Numeric
     * @param arr1 the first array.
     * @param arr2 the second array.
     * @param weights the weights of the elements.
     * @return T the weighted covariance of the two arrays.
     */
    template <Numeric T>
    T weightedCovariance(ArrayList<T> arr1, ArrayList<T> arr2, ArrayList<T> weights) {
        T mean1 = weightedMean(arr1, weights);
        T mean2 = weightedMean(arr2, weights);
        T covariance = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr1.size(); ++i) {
            covariance += weights[i] * (arr1[i] - mean1) * (arr2[i] - mean2);
            weightSum += weights[i];
        }
        
        return covariance / weightSum;
    }

    /**
     * @brief Calculates the weighted correlation of two arrays.
     * 
     * @tparam T the type of the elements in the arrays.
     * @see Numeric
     * @param arr1 the first array.
     * @param arr2 the second array.
     * @param weights the weights of the elements.
     * @return T the weighted correlation of the two arrays.
     */
    template <Numeric T>
    T weightedCorrelation(ArrayList<T> arr1, ArrayList<T> arr2, ArrayList<T> weights) {
        return weightedCovariance(arr1, arr2, weights) / (weightedStandardDeviation(arr1, weights) * weightedStandardDeviation(arr2, weights));
    }

    /**
     * @brief Calculates the weighted z-score of a value.
     * 
     * @tparam T the type of the value.
     * @see Numeric
     * @param x the value.
     * @param mean the mean of the values.
     * @param stdDev the standard deviation of the values.
     * @return T the weighted z-score of the value.
     */
    template <Numeric T>
    T weightedZScore(T x, T mean, T stdDev) {
        return (x - mean) / stdDev;
    }

    /**
     * @brief Calculates the weighted z-scores of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return ArrayList<T> the weighted z-scores of the elements in the array.
     */
    template <Numeric T>
    ArrayList<T> weightedZScoreSet(ArrayList<T> arr, ArrayList<T> weights) {
        T mean = weightedMean(arr, weights);
        T stdDev = weightedStandardDeviation(arr, weights);
        ArrayList<T> zScores;

        for(int i = 0; i < arr.size(); ++i) {
            zScores.add(weightedZScore(arr[i], mean, stdDev));
        }

        return zScores;
    }

    /**
     * @brief Calculates the weighted percentile of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param p the percentile.
     * @param weights the weights of the elements.
     * @return T the weighted percentile of the array.
     */
    template <Numeric T>
    T weightedPercentile(ArrayList<T> arr, T p, ArrayList<T> weights) {
        int n = arr.size();
        arr.sort();
        
        T rank = p * (n - 1);
        int k = (int) rank;
        T d = rank - k;
        
        if(k + 1 < n) {
            return arr[k] + d * (arr[k + 1] - arr[k]);
        } else {
            return arr[k];
        }
    }

    /**
     * @brief Calculates the weighted quartile of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param q the quartile.
     * @param weights the weights of the elements.
     * @return T the weighted quartile of the array.
     */
    template <Numeric T>
    T weightedQuartile(ArrayList<T> arr, int q, ArrayList<T> weights) {
        int n = arr.size();
        arr.sort();
        
        if(n % 2 == 0) {
            int k = n / 2;
            ArrayList<T> lowerHalf = arr.subList(0, k);
            ArrayList<T> upperHalf = arr.subList(k, n);
            
            if(q == 1) {
                return median(lowerHalf);
            } else {
                return median(upperHalf);
            }
        } else {
            int k = n / 2;
            ArrayList<T> lowerHalf = arr.subList(0, k);
            ArrayList<T> upperHalf = arr.subList(k + 1, n);
            
            if(q == 1) {
                return median(lowerHalf);
            } else {
                return median(upperHalf);
            }
        }
    }

    /**
     * @brief Calculates the weighted interquartile range of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted interquartile range of the array.
     */
    template <Numeric T>
    T weightedIqr(ArrayList<T> arr, ArrayList<T> weights) {
        return weightedQuartile(arr, 3, weights) - weightedQuartile(arr, 1, weights);
    }

    /**
     * @brief Calculates the weighted outlier of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted outlier of the array.
     */
    template <Numeric T>
    T weightedOutlier(ArrayList<T> arr, ArrayList<T> weights) {
        T q1 = weightedQuartile(arr, 1, weights);
        T q3 = weightedQuartile(arr, 3, weights);
        T iqr = q3 - q1;
        
        T lowerBound = q1 - 1.5 * iqr;
        T upperBound = q3 + 1.5 * iqr;
        
        for(int i = 0; i < arr.size(); ++i) {
            if(arr[i] < lowerBound || arr[i] > upperBound) {
                return arr[i];
            }
        }
        
        return 0;
    }

    /**
     * @brief Calculates the weighted range of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted range of the array.
     */
    template <Numeric T>
    T weightedRange(ArrayList<T> arr, ArrayList<T> weights) {
        arr.sort();
        return arr[arr.size() - 1] - arr[0];
    }

    /**
     * @brief Calculates the weighted midrange of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted midrange of the array.
     */
    template <Numeric T>
    T weightedMidRange(ArrayList<T> arr, ArrayList<T> weights) {
        arr.sort();
        return (arr[0] + arr[arr.size() - 1]) / 2;
    }

    /**
     * @brief Calculates the weighted harmonic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the weighted harmonic mean of the array.
     */
    template <Numeric T>
    T quadraticMean(ArrayList<T> arr) {
        T sum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += arr[i] * arr[i];
        }
        
        return std::sqrt(sum / arr.size());
    }

    /**
     * @brief Calculates the weighted cubic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @return T the weighted cubic mean of the array.
     */
    template <Numeric T>
    T cubicMean(ArrayList<T> arr) {
        T sum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += arr[i] * arr[i] * arr[i];
        }
        
        return std::cbrt(sum / arr.size());
    }

    /**
     * @brief Calculates the weighted nth root mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param n the root.
     * @return T the weighted nth root mean of the array.
     */
    template <Numeric T>
    T nthRootMean(ArrayList<T> arr, int n) {
        T sum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += std::pow(arr[i], n);
        }
        
        return std::pow(sum / arr.size(), 1.0 / n);
    }

    /**
     * @brief Calculates the weighted quadratic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted quadratic mean of the array.
     */
    template <Numeric T>
    T weightedQuadraticMean(ArrayList<T> arr, ArrayList<T> weights) {
        T sum = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += weights[i] * arr[i] * arr[i];
            weightSum += weights[i];
        }
        
        return std::sqrt(sum / weightSum);
    }

    /**
     * @brief Calculates the weighted cubic mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param weights the weights of the elements.
     * @return T the weighted cubic mean of the array.
     */
    template <Numeric T>
    T weightedCubicMean(ArrayList<T> arr, ArrayList<T> weights) {
        T sum = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += weights[i] * arr[i] * arr[i] * arr[i];
            weightSum += weights[i];
        }
        
        return std::cbrt(sum / weightSum);
    }

    /**
     * @brief Calculates the weighted nth root mean of an array.
     * 
     * @tparam T the type of the elements in the array.
     * @see Numeric
     * @param arr the array.
     * @param n the root.
     * @param weights the weights of the elements.
     * @return T the weighted nth root mean of the array.
     */
    template <Numeric T>
    T weightedNthRootMean(ArrayList<T> arr, int n, ArrayList<T> weights) {
        T sum = 0;
        T weightSum = 0;
        
        for(int i = 0; i < arr.size(); ++i) {
            sum += weights[i] * std::pow(arr[i], n);
            weightSum += weights[i];
        }
        
        return std::pow(sum / weightSum, 1.0 / n);
    }
};

#endif
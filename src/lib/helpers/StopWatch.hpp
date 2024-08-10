/**
 * @file StopWatch.hpp
 * @author Fernando Campos Silva Dal' Maria (fernandocsdm@gmail.com)
 * @brief A C++ implementation of a simple stopwatch for timing events.
 * @version 1.0.0
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <iostream>
#include <chrono>
#include <string>

/**
 * @brief Enumeration for the different time periods.
 * 
 * This enum is used to specify the units of time that the Stopwatch should measure.
 */
enum Period {
    NANOSECONDS,
    MICROSECONDS,
    MILLISECONDS, 
    SECONDS,
    MINUTES,
    HOURS
};

/**
 * @brief A class that implements a simple stopwatch for timing events.
 * 
 * The Stopwatch class uses std::chrono to measure elapsed time with various time units.
 * It supports starting, stopping, and retrieving the elapsed time.
 */
class Stopwatch {
    private:
        std::chrono::steady_clock::time_point startTime; /**< The time point when the stopwatch was started */
        std::chrono::steady_clock::time_point endTime;   /**< The time point when the stopwatch was stopped */
        bool running;                                   /**< A flag indicating whether the stopwatch is currently running */
        std::string label;                              /**< A label for the stopwatch */
        Period period;                                  /**< The period (time unit) for the stopwatch */

        /**
         * @brief Calculate the elapsed time from the start time to a given end time.
         * 
         * @param end The time point representing the end time.
         * @return long long The elapsed time in the selected period.
         */
        long long elapsedTime(std::chrono::steady_clock::time_point end) const {
            switch(period) {
                case Period::NANOSECONDS: 
                    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - startTime).count();
                case Period::MICROSECONDS:
                    return std::chrono::duration_cast<std::chrono::microseconds>(end - startTime).count();
                case Period::MILLISECONDS:
                    return std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count();
                case Period::SECONDS:
                    return std::chrono::duration_cast<std::chrono::seconds>(end - startTime).count(); 
                case Period::MINUTES:
                    return std::chrono::duration_cast<std::chrono::minutes>(end - startTime).count();
                case Period::HOURS:
                    return std::chrono::duration_cast<std::chrono::hours>(end - startTime).count();
                default:
                    return 0;
            }
        }

    public:

        /**
         * @brief Construct a new Stopwatch object with a specified label and time period.
         * 
         * @param label The label for the stopwatch.
         * @param period The time period for measuring elapsed time (default is MILLISECONDS).
         */
        Stopwatch(const std::string& label, Period period = Period::MILLISECONDS) {
            this->label = label;
            this->running = false;
            this->period = period;
        }

        /**
         * @brief Start the stopwatch.
         * 
         * If the stopwatch is not already running, it records the current time as the start time.
         */
        void start() {
            if (!running) {
                startTime = std::chrono::steady_clock::now();
                running = true;
            }
        }

        /**
         * @brief Stop the stopwatch and return the elapsed time.
         * 
         * @return long long The elapsed time in the selected period.
         */
        long long stop() {
            if (running) {
                endTime = std::chrono::steady_clock::now();
                running = false;
                return elapsed();
            }

            return 0;
        }

        /**
         * @brief Get the elapsed time without stopping the stopwatch.
         * 
         * @return long long The elapsed time in the selected period.
         */
        long long elapsed() const {
            if (running) {
                auto tempEndTime = std::chrono::steady_clock::now();
                return elapsedTime(tempEndTime);
            } else {
                return elapsedTime(endTime);
            }
        }
        
        /**
         * @brief Set the time period for the stopwatch.
         * 
         * @param p The time period to set.
         */
        void setPeriod(Period p) {
            period = p;
        }

        /**
         * @brief Overloaded stream insertion operator to output the stopwatch's elapsed time.
         * 
         * @param os The output stream.
         * @param sw The Stopwatch object to output.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Stopwatch& sw) {
            os << sw.label << ": " << sw.elapsed() << " ";
            switch(sw.period) {
                case Period::NANOSECONDS:  os << "ns"; break;
                case Period::MICROSECONDS: os << "us"; break;
                case Period::MILLISECONDS: os << "ms"; break;
                case Period::SECONDS:      os << "s"; break;
                case Period::MINUTES:      os << "min"; break;
                case Period::HOURS:        os << "hr"; break;
            }
            return os;
        }
};

#endif
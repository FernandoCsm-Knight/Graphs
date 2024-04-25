#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <iostream>
#include <chrono>
#include <string>

enum class Period {
    NANOSECONDS,
    MICROSECONDS,
    MILLISECONDS, 
    SECONDS,
    MINUTES,
    HOURS
};

class Stopwatch {
    private:
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point endTime;
        bool running;
        std::string label;
        Period period;

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
        Stopwatch(const std::string& label, Period period = Period::MILLISECONDS) {
            this->label = label;
            this->running = false;
            this->period = period;
        }

        void start() {
            if (!running) {
                startTime = std::chrono::steady_clock::now();
                running = true;
            }
        }

        long long stop() {
            if (running) {
                endTime = std::chrono::steady_clock::now();
                running = false;
                return elapsed();
            }

            return 0;
        }

        long long elapsed() const {
            if (running) {
                auto tempEndTime = std::chrono::steady_clock::now();
                return elapsedTime(tempEndTime);
            } else {
                return elapsedTime(endTime);
            }
        }

        void setPeriod(Period p) {
            period = p;
        }

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
#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/stat.h>
#include "../../src/lib/Graph.hpp"
#include "../../src/lib/helpers/StopWatch.hpp"

#define STD_LOG_FOLDER "test/logs"
#define STD_LOG_FILE "test.log"

class Test {
    protected:
        std::string logFolder;
        std::ofstream logFile;

        virtual void onTestStart(const std::string& testName) = 0;
        virtual void onTestEnd(const std::string& testName, long long elapsed) = 0;
        virtual void customTest(const std::string& testName) = 0;

    public:
        Test(const std::string& logFolderName = "test/logs") : logFolder(logFolderName) {
            // Create the log folder if it doesn't exist
            struct stat st = {};
            if (stat(logFolder.c_str(), &st) == -1) {
                mkdir(logFolder.c_str(), 0700);
            }

            // Open the general log file
            std::string logFileName = logFolder + "/" + STD_LOG_FILE;
            logFile.open(logFileName, std::ios::app);
            if (!logFile.is_open()) {
                std::cerr << "Failed to open log file: " << logFileName << std::endl;
            }
        }

        virtual ~Test() {
            if (logFile.is_open()) {
                logFile.close();
            }
        }

        template <typename V>
        void testAlgorithm(const std::string& testName, const Graph<V>& graph, const std::function<void(const Graph<V>&)>& algorithm) {
            onTestStart(testName);

            Stopwatch stopwatch(testName);
            stopwatch.start();

            algorithm(graph);

            long long elapsed = stopwatch.stop();

            onTestEnd(testName, elapsed);

            // Log the test result
            std::string testLogFileName = logFolder + "/" + testName + ".log";
            std::ofstream testLogFile(testLogFileName);
            if (testLogFile.is_open()) {
                testLogFile << "Test Name: " << testName << std::endl;
                testLogFile << "Elapsed Time: " << elapsed << " ms" << std::endl;
                testLogFile.close();
            } else {
                std::cerr << "Failed to open test log file: " << testLogFileName << std::endl;
            }

            // Log the test result in the general log file
            if (logFile.is_open()) {
                logFile << "Test Name: " << testName << std::endl;
                logFile << "Elapsed Time: " << elapsed << " ms" << std::endl;
                logFile << "--------------------" << std::endl;
            }
        }

        void run(const std::string& testName) {
            onTestStart(testName);

            Stopwatch stopwatch(testName);
            stopwatch.start();

            customTest(testName);
            onTestEnd(testName, stopwatch.stop());
        }
};

#endif
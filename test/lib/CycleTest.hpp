#ifndef CYCLE_TEST_HPP
#define CYCLE_TEST_HPP

#include <iostream>
#include <fstream>

#include "Test.hpp"
#include "../../src/lib/Graph.hpp"
#include "../../src/lib/datastructs/ArrayList.hpp"

class CycleTest : public Test {
private:
    Graph<std::string> directedGraph;
    Graph<std::string> k5;
    Graph<std::string> proof;

protected:
    void onTestStart(const std::string& testName) override {
        std::cout << "Starting test: " << testName << std::endl;
    }

    void onTestEnd(const std::string& testName, long long elapsed) override {
        std::cout << "Finished test: " << testName << " in " << elapsed << " ms" << std::endl;
    }

    void customTest(const std::string& testName) override {
        if (testName == "Directed Cycles Walk Test") {
            directedCyclesWalkTest();
        } else if (testName == "Directed Cycles Permutation Test") {
            directedCyclesPermutationTest();
        } else if (testName == "Undirected Cycles Walk Test") {
            undirectedCyclesWalkTest();
        } else if (testName == "Undirected Cycles Permutation Test") {
            undirectedCyclesPermutationTest();
        }
    }

public:
    CycleTest(const std::string& logFolderName = "test/logs") : Test(logFolderName) {
        directedGraph = Graph<std::string>(true);

        directedGraph.addEdge("A", "B");
        directedGraph.addEdge("E", "A");
        directedGraph.addEdge("A", "D");
        directedGraph.addEdge("D", "B");
        directedGraph.addEdge("B", "E");
        directedGraph.addEdge("B", "C");
        directedGraph.addEdge("D", "C");
        directedGraph.addEdge("C", "E");
        directedGraph.addEdge("C", "F");
        directedGraph.addEdge("F", "E");
        directedGraph.addEdge("D", "F");

        k5.addEdge("A", "B");
        k5.addEdge("A", "C");
        k5.addEdge("A", "D");
        k5.addEdge("A", "E");
        k5.addEdge("B", "C");
        k5.addEdge("B", "D");
        k5.addEdge("B", "E");
        k5.addEdge("C", "D");
        k5.addEdge("C", "E");
        k5.addEdge("D", "E");

        proof.addEdge("A", "B");
        proof.addEdge("A", "D");
        proof.addEdge("B", "C");
        proof.addEdge("A", "E");
        proof.addEdge("B", "D");
        proof.addEdge("E", "B");
        proof.addEdge("C", "E");
        proof.addEdge("D", "C");
        proof.addEdge("D", "F");
        proof.addEdge("F", "C");
        proof.addEdge("F", "E");
    }

    void directedCyclesWalkTest() {
        bool passed = directedGraph.cycles().size() == 9;
        logResult("Cycles Walk Test (Digraph)", passed);
    }

    void directedCyclesPermutationTest() {
        bool passed = directedGraph.cycles(CycleDetectionType::PERMUTATION).size() == 9;
        logResult("Cycles Permutation Test (Digraph)", passed);
    }

    void undirectedCyclesWalkTest() {
        bool passed = k5.cycles().size() == 37 && proof.cycles().size() == 38;
        logResult("Cycles Walk Test (Graph)", passed);
    }

    void undirectedCyclesPermutationTest() {
        bool passed = k5.cycles(CycleDetectionType::PERMUTATION).size() == 37 && proof.cycles(CycleDetectionType::PERMUTATION).size() == 38;
        logResult("Cycles Permutation Test (Graph)", passed);
    }

private:
    void logResult(const std::string& testName, bool passed) {
        std::ofstream file(logFolder + "/" + STD_LOG_FILE, std::ios::app);
        file << "\t\t" << testName << ": " << (passed ? "Passed" : "Failed") << std::endl;
        file.close();
    }
};

#endif
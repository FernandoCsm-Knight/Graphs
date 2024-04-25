#ifndef DIGRAPH_TEST_HPP
#define DIGRAPH_TEST_HPP

#include <iostream>
#include <fstream>

#include "Test.hpp"
#include "../../src/lib/Graph.hpp"

class DigraphTest : public Test {
private:
    Graph<std::string> graph;

protected:
    void onTestStart(const std::string& testName) override {
        std::cout << "Starting test: " << testName << std::endl;
    }

    void onTestEnd(const std::string& testName, long long elapsed) override {
        std::cout << "Finished test: " << testName << " in " << elapsed << " ms" << std::endl;
    }

    void customTest(const std::string& testName) override {
        if (testName == "Weight Test") {
            weightTest();
        } else if (testName == "Vertices Test") {
            verticesTest();
        } else if (testName == "Edges Test") {
            edgesTest();
        } else if (testName == "Degree Test") {
            degreeTest();
        } else if (testName == "Neighbors Test") {
            neighborsTest();
        } else if (testName == "Add Vertex Test") {
            addVertexTest();
        } else if (testName == "Add Edge Test") {
            addEdgeTest();
        } else if (testName == "Remove Vertex Test") {
            removeVertexTest();
        } else if (testName == "Remove Edge Test") {
            removeEdgeTest();
        }
    }

public:
    DigraphTest(const std::string& logFolderName = "test/logs") : Test(logFolderName) {
        graph = Graph<std::string>(true);

        graph.addEdge("A", "B", 1);
        graph.addEdge("A", "E", 2);
        graph.addEdge("B", "F", 3);
        graph.addEdge("B", "G", 3);
        graph.addEdge("B", "C", 1);
        graph.addEdge("C", "D", 1);
        graph.addEdge("C", "G", 1);
        graph.addEdge("D", "C", 2);
        graph.addEdge("E", "I", 1);
        graph.addEdge("F", "A", 2);
        graph.addEdge("F", "J", 1);
        graph.addEdge("F", "G", 1);
        graph.addEdge("G", "K", 4);
        graph.addEdge("H", "G", 1);
        graph.addEdge("I", "J", 1);
        graph.addEdge("J", "E", 2);
        graph.addEdge("J", "K", 5);
        graph.addEdge("K", "L", 1);
        graph.addEdge("K", "H", 1);
        graph.addEdge("L", "H", 1);

        graph.addVertex("M");
    }

    void weightTest() {
        bool passed = graph.weight("J", "K") == 5;
        logResult("Weight Test", passed);
    }

    void verticesTest() {
        bool passed = graph.getVertices().size() == 13;
        logResult("Vertices Test", passed);
    }

    void edgesTest() {
        bool passed = graph.getEdges().size() == 20;
        logResult("Edges Test", passed);
    }

    void degreeTest() {
        bool passed = graph.degree("A").first() == 1 && graph.degree("A").second() == 2;
        logResult("Degree Test", passed);
    }

    void neighborsTest() {
        bool passed = graph.neighbors("A").size() == 2;
        logResult("Neighbors Test", passed);
    }

    void addVertexTest() {
        Graph<std::string> tmp(graph);
        tmp.addVertex("N");
        bool passed = tmp.contains("N");
        logResult("Add Vertex Test", passed);
    }

    void addEdgeTest() {
        Graph<std::string> tmp(graph);
        tmp.addEdge("A", "M", 1);
        bool passed = tmp.contains("A", "M");
        logResult("Add Edge Test", passed);
    }

    void removeVertexTest() {
        Graph<std::string> tmp(graph);
        tmp.removeVertex("M");
        bool passed = !tmp.contains("M");
        logResult("Remove Vertex Test", passed);
    }

    void removeEdgeTest() {
        Graph<std::string> tmp(graph);
        tmp.removeEdge("A", "B");
        bool passed = !tmp.contains("A", "B");
        logResult("Remove Edge Test", passed);
    }

private:
    void logResult(const std::string& testName, bool passed) {
        std::ofstream file(logFolder + "/" + STD_LOG_FILE, std::ios::app);
        file << "\t\t" << testName << ": " << (passed ? "Passed" : "Failed") << std::endl;
        file.close();
    }
};

#endif
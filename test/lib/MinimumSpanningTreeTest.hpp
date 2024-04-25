#ifndef MINIMUMSPANNINGTREETEST_HPP
#define MINIMUMSPANNINGTREETEST_HPP

#include <iostream>
#include <fstream>

#include "Test.hpp"
#include "../../src/lib/Graph.hpp"
#include "../../src/lib/helpers/Path.hpp"
#include "../../src/lib/helpers/Edge.hpp"

class MinimumSpanningTreeTest : public Test {
private:
    Graph<std::string> graph;
    Graph<std::string> digraph;
    Path<Edge<std::string>> p;

protected:
    void onTestStart(const std::string& testName) override {
        std::cout << "Starting test: " << testName << std::endl;
    }

    void onTestEnd(const std::string& testName, long long elapsed) override {
        std::cout << "Finished test: " << testName << " in " << elapsed << " ms" << std::endl;
    }

    void customTest(const std::string& testName) override {
        if (testName == "Minimum Spanning Tree Test (Graph)") {
            GraphMSTTest();
        } else if (testName == "Minimum Spanning Tree Test (Digraph)") {
            DigraphMSTTest();
        }
    }

public:
    MinimumSpanningTreeTest(const std::string& logFolderName = "test/logs") : Test(logFolderName) {
        graph = Graph<std::string>(false);

        graph.addEdge("A", "B", 1.0);
        graph.addEdge("A", "E", 3.0);
        graph.addEdge("A", "G", 2.0);
        graph.addEdge("G", "E", 8.0);
        graph.addEdge("B", "C", 4.0);
        graph.addEdge("C", "D", 1.0);
        graph.addEdge("E", "D", 2.0);
        graph.addEdge("E", "F", 9.0);
        graph.addEdge("D", "F", 7.0);
        graph.addEdge("D", "H", 2.0);
        graph.addEdge("F", "H", 1.0);

        digraph = Graph<std::string>(true);

        digraph.addEdge("A", "B", 1.0);
        digraph.addEdge("A", "E", 3.0);
        digraph.addEdge("A", "G", 2.0);
        digraph.addEdge("G", "E", 8.0);
        digraph.addEdge("B", "C", 4.0);
        digraph.addEdge("C", "D", 1.0);
        digraph.addEdge("E", "D", 2.0);
        digraph.addEdge("E", "F", 9.0);
        digraph.addEdge("F", "D", 7.0);
        digraph.addEdge("D", "H", 2.0);
        digraph.addEdge("H", "F", 1.0);
    }

    void GraphMSTTest() {
        p = Path<Edge<std::string>>();

        p.add(Edge<std::string>("A", "A", false));
        p.add(Edge<std::string>("A", "B", false, 1.0));
        p.add(Edge<std::string>("A", "G", false, 2.0));
        p.add(Edge<std::string>("A", "E", false, 3.0));
        p.add(Edge<std::string>("E", "D", false, 2.0));
        p.add(Edge<std::string>("D", "C", false, 1.0));
        p.add(Edge<std::string>("D", "H", false, 2.0));
        p.add(Edge<std::string>("H", "F", false, 1.0));

        p.setWeight(12.0);
        bool passed = graph.minimumSpanningTree() == p;
        logResult("Minimum Spanning Tree Test (Graph)", passed);
    }

    void DigraphMSTTest() {
        p = Path<Edge<std::string>>();

        p.add(Edge<std::string>("A", "A", true));
        p.add(Edge<std::string>("A", "B", true, 1.0));
        p.add(Edge<std::string>("A", "G", true, 2.0));
        p.add(Edge<std::string>("A", "E", true, 3.0));
        p.add(Edge<std::string>("E", "D", true, 2.0));
        p.add(Edge<std::string>("D", "H", true, 2.0));
        p.add(Edge<std::string>("H", "F", true, 1.0));
        p.add(Edge<std::string>("B", "C", true, 4.0));

        p.setWeight(15.0);
        bool passed = digraph.minimumSpanningTree() == p;
        logResult("Minimum Spanning Tree Test (Digraph)", passed);
    }

private:
    void logResult(const std::string& testName, bool passed) {
        std::ofstream file(logFolder + "/" + STD_LOG_FILE, std::ios::app);
        file << "\t\t" << testName << ": " << (passed ? "Passed" : "Failed") << std::endl;
        file.close();
    }
};

#endif
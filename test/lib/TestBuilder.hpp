#ifndef TESTBUILDER_HPP
#define TESTBUILDER_HPP

#include <iostream>
#include <fstream>

#include "../../src/lib/datastructs/ArrayList.hpp"

#include "GraphDijkstraTest.hpp"
#include "GraphTest.hpp"
#include "DigraphTest.hpp"
#include "MinimumSpanningTreeTest.hpp"
#include "CycleTest.hpp"

enum TestType {
    graph_t,
    digraph_t,
    dijkstra_t,
    mst_t,
    cycles_t,
};

class TestBuilder {
private:
    struct Entry {
        TestType type;
        std::string name;
    };

    ArrayList<Entry> tests;
    std::string logFolderName;

public:
    TestBuilder(const std::string& logFolderName = "test/logs") : logFolderName(logFolderName) {}

    ~TestBuilder() {}

    void addTest(TestType type, const std::string& name) {
        tests.add({type, name});
    }

    bool removeTest(const std::string& name) {
        int idx = -1;
        for (int i = 0; i < tests.size() && idx == -1; ++i) {
            if (tests[i].name == name) {
                idx = i;
            }
        }

        if (idx != -1) {
            tests.pop(idx);
        }
        return idx != -1;
    }

    bool run() {
        for (const Entry& entry : tests) {
            switch (entry.type) {
                case TestType::graph_t: {
                    GraphTest graphTest(logFolderName);
                    graphTest.run(entry.name);
                    break;
                }
                case TestType::digraph_t: {
                    DigraphTest digraphTest(logFolderName);
                    digraphTest.run(entry.name);
                    break;
                }
                case TestType::dijkstra_t: {
                    GraphDijkstraTest dijkstraTest(logFolderName);
                    dijkstraTest.run(entry.name);
                    break;
                }
                case TestType::mst_t: {
                    MinimumSpanningTreeTest mstTest(logFolderName);
                    mstTest.run(entry.name);
                    break;
                }
                case TestType::cycles_t: {
                    CycleTest cycleTest(logFolderName);
                    cycleTest.run(entry.name);
                    break;
                }
            }
        }
        return true;
    }
};

#endif
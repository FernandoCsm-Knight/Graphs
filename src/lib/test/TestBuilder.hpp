#ifndef TESTBUILDER_HPP
#define TESTBUILDER_HPP

#include <iostream>
#include <fstream>

#include "../datastructs/ArrayList.hpp"

#include "GraphDijkstraTest.hpp"
#include "GraphTest.hpp"
#include "DigraphTest.hpp"
#include "MinimunSpanningTreeTest.hpp"

enum TestType {
    graph_t,
    digraph_t,
    dijkstra_t,
    mst_t,
};

class TestBuilder {
    private:
        struct Entry {
            TestType type;
            std::string name;
            std::string description;
        };

        ArrayList<Entry> tests;

        std::string path;
        std::string fileName;

    public:
        TestBuilder(std::string fileName = "test") : fileName(fileName) {
            this->fileName = fileName;
            this->path = "src/log/" + fileName + ".log";
            std::ofstream file;
            file.open(path, std::ios::out | std::ios::trunc);
            file.close();
        }

        ~TestBuilder() {}

        void addTest(TestType type, const std::string& name = "", const std::string& description = "") {
            tests.add({type, name, description});
        }

        bool removeTest(const std::string& name) {
            int idx = -1;
            for(int i = 0; i < tests.size() && idx == -1; ++i) 
                if(tests[i].name == name) idx = i;

            if(idx != -1) tests.pop(idx);
            return idx != -1;
        }

        bool run() {
            for(const Entry& entry : tests) {
                if(entry.type == TestType::graph_t) {
                    GraphTest graphTest(path, entry.name, entry.description);
                    graphTest.run();
                } else if(entry.type == TestType::digraph_t) {
                    DigraphTest digraphTest(path, entry.name, entry.description);
                    digraphTest.run();
                } else if(entry.type == TestType::dijkstra_t) {
                    GraphDijkstraTest dijkstraTest(path, entry.name, entry.description);
                    dijkstraTest.run();
                } else if(entry.type == TestType::mst_t) {
                    MinimumSpanningTreeTest mstTest(path, entry.name, entry.description);
                    mstTest.run();
                }
            }
            return true;
        }
};

#endif
#include <iostream>
#include <cstdlib> 

#include "lib/TestBuilder.hpp"

int main() {
    TestBuilder testBuilder;

    // Graph tests
    testBuilder.addTest(TestType::graph_t, "Weight Test");
    testBuilder.addTest(TestType::graph_t, "Vertices Test");
    testBuilder.addTest(TestType::graph_t, "Edges Test");
    testBuilder.addTest(TestType::graph_t, "Degree Test");
    testBuilder.addTest(TestType::graph_t, "Neighbors Test");
    testBuilder.addTest(TestType::graph_t, "Add Vertex Test");
    testBuilder.addTest(TestType::graph_t, "Add Edge Test");
    testBuilder.addTest(TestType::graph_t, "Remove Vertex Test");
    testBuilder.addTest(TestType::graph_t, "Remove Edge Test");

    // Digraph tests
    testBuilder.addTest(TestType::digraph_t, "Weight Test");
    testBuilder.addTest(TestType::digraph_t, "Vertices Test");
    testBuilder.addTest(TestType::digraph_t, "Edges Test");
    testBuilder.addTest(TestType::digraph_t, "Degree Test");
    testBuilder.addTest(TestType::digraph_t, "Neighbors Test");
    testBuilder.addTest(TestType::digraph_t, "Add Vertex Test");
    testBuilder.addTest(TestType::digraph_t, "Add Edge Test");
    testBuilder.addTest(TestType::digraph_t, "Remove Vertex Test");
    testBuilder.addTest(TestType::digraph_t, "Remove Edge Test");

    // Dijkstra tests
    testBuilder.addTest(TestType::dijkstra_t, "Shortest Path Test (Digraph)");
    testBuilder.addTest(TestType::dijkstra_t, "Shortest Path Test (Graph)");
    testBuilder.addTest(TestType::dijkstra_t, "Distance Test (Digraph)");
    testBuilder.addTest(TestType::dijkstra_t, "Distance Test (Graph)");

    // Minimum Spanning Tree tests
    testBuilder.addTest(TestType::mst_t, "Minimum Spanning Tree Test (Graph)");
    testBuilder.addTest(TestType::mst_t, "Minimum Spanning Tree Test (Digraph)");

    // Cycle tests
    testBuilder.addTest(TestType::cycles_t, "Directed Cycles Walk Test");
    testBuilder.addTest(TestType::cycles_t, "Directed Cycles Permutation Test");
    testBuilder.addTest(TestType::cycles_t, "Undirected Cycles Walk Test");
    testBuilder.addTest(TestType::cycles_t, "Undirected Cycles Permutation Test");

    testBuilder.run();

    return 0;
}

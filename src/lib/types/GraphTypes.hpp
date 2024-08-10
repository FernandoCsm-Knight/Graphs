#ifndef GRAPH_TYPES_HPP
#define GRAPH_TYPES_HPP

/**
 * @brief A list of graph types that can be used to generate a graph.
 * 
 * - REGULAR: A regular graph.
 * - COMPLETE: A complete graph.
 * - BIPARTITE: A bipartite graph.
 * - COMPLETE_BIPARTITE: A complete bipartite graph.
 * - EULERIAN: An Eulerian graph.
 * - TREE: A tree.
 * - FOREST: A forest.
 * - CYCLIC: A cyclic graph.
 */
enum GraphTypes {
    REGULAR,
    COMPLETE,
    BIPARTITE,
    COMPLETE_BIPARTITE,
    EULERIAN,
    TREE,
    FOREST,
    CYCLIC,
};

#endif
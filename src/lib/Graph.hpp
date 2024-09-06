/**
 * @file Graph.hpp
 * @author Fernando Campos Silva Dal Maria (fernando.csm123@gmail.com)
 * @brief A C++ implementation of a Graph class, a templated container that represents a graph data structure.
 *        The class allows associating a vertex label of type V with a corresponding list of adjacent vertices.
 *        It provides multiple constructors for creating graphs, including default and directed constructors.
 *        Additionally, the class overloads the stream insertion operator to print the graph's information.
 *        The class is designed to be used in data structures and algorithms that require storing and managing
 *        graphs efficiently.
 * @version 1.0.0
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <limits>
#include <string>

#include "algorithms/CycleDetection.hpp"
#include "algorithms/StronglyConnectedComponents.hpp"
#include "algorithms/ShortestPath.hpp"
#include "algorithms/MinimumSpanningTree.hpp"
#include "algorithms/DepthFirstSearch.hpp"
#include "algorithms/BreathFirstSearch.hpp"

#include "datastructs/ArrayList.hpp"
#include "datastructs/Map.hpp"
#include "datastructs/Queue.hpp"
#include "datastructs/Stack.hpp"
#include "datastructs/Queue.hpp"
#include "datastructs/Set.hpp"
#include "datastructs/PriorityQueue.hpp"
#include "datastructs/IndexedPriorityQueue.hpp"
#include "datastructs/UnionFind.hpp"

#include "helpers/Edge.hpp"
#include "helpers/Pair.hpp"
#include "helpers/Path.hpp"
#include "helpers/Storage.hpp"
#include "helpers/Arithmatic.hpp"
#include "helpers/GraphGenerator.hpp"
#include "helpers/GraphDescriber.hpp"

#include "types/GraphTypes.hpp"
#include "types/CycleDetectionType.hpp"
#include "types/MinimumSpanningTreeType.hpp"

/**
 * @brief Represents a graph data structure.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class Graph {
    private:
        Map<V, Set<V>> adj; ///< The adjacency list of the graph.
        Set<Edge<V>> edges; ///< The edge list of the graph.
        bool directed = false; ///< Indicates whether the graph is directed.

    public:
        // Constructors & Destructor

        Graph(bool isDirected = false): directed(isDirected) {}

        Graph(const GraphTypes type, const int n = 5, const bool isDirected = false) {
            GraphGenerator<V> generator;
            *this = generator.create(type, n, isDirected);
        }

        Graph(const Edge<V> edges[], const int size, const bool isDirected = false) {
            for (int i = 0; i < size; ++i) 
                this->addEdge(edges[i]);

            directed = isDirected;
        }

        Graph(const Graph<V>& other): adj(other.adj), edges(other.edges), directed(other.directed) {}

        ~Graph() {}

        // Operators

        Graph<V>& operator=(const Graph<V>& other) {
            if (this != &other) {
                adj = other.adj;
                edges = other.edges;
                directed = other.directed;
            }

            return *this;
        }

        // Inline Methods

        inline bool contains(const V& vertex) const { return adj.contains(vertex); }
        inline bool contains(const Edge<V>& edge) const { return edges.contains(edge); }
        inline bool contains(const V& src, const V& dest) const { return edges.contains(Edge<V>(src, dest, directed)); }

        inline bool isEmpty() const { return adj.size() == 0; }
        inline bool isDigraph() const { return directed; }
        inline int size() const { return adj.size(); }
        inline int sizeEdges() const { return edges.size(); }

        inline ArrayList<V> vertices() const { return adj.keys(); }
        inline Set<V> setOfVertices() const { return adj.keys().toSet(); }
        inline Set<V> setOfNeighbors(const V& vertex) const { return adj.get(vertex); }
        inline Set<Edge<V>> setOfEdges() const { return edges; }
        inline Map<V, Set<V>> adjacencyList() const { return adj; }

        // State Methods

        inline Map<V, Set<V>>& adjacency() { return adj; }
        inline Set<Edge<V>>& edgeList() { return edges; }
        inline Set<V>& neighbors(const V& vertex) { return adj[vertex]; }

        // Other Methods

        bool isRegular() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isRegular();
            delete gd;
            return value;
        }

        bool isComplete() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isComplete();
            delete gd;
            return value;
        }

        bool isBipartite() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isBipartite();
            delete gd;
            return value;
        }

        bool isTree() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isTree();
            delete gd;
            return value;
        }

        bool isForest() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isForest();
            delete gd;
            return value;
        }

        bool isCyclic() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isCyclic();
            delete gd;
            return value;
        }

        bool isEulerian() const {
            GraphDescriber<V> *gd = new GraphDescriber<V>(*this);
            bool value = gd->isEulerian();
            delete gd;
            return value;
        }

        Pair<int, int> degree(const V& vertex) const {
            if(!directed) return Pair<int, int>(adj.get(vertex).size());

            int in = 0, out = 0;
            for(int i = 0; i < edges.size(); ++i) {
                if(edges.get(i).getDestination() == vertex) ++in;
                if(edges.get(i).getSource() == vertex) ++out;
            }

            return Pair<int, int>(in, out);
        }

        ArrayList<Pair<int, int>> degreeList() const {
            ArrayList<V> vertices = adj.keys();
            ArrayList<Pair<int, int>> list;

            for(const V& vertex : vertices) 
                list.add(this->degree(vertex));

            return list;
        }

        int connectedComponents() const {
            int cc = -1;

            if(!directed) {
                ArrayList<V> vertices = adj.keys();
                UnionFind<V> uf(vertices);

                for(Edge<V> e : edges) 
                    uf.unify(e.getSource(), e.getDestination());
                
                cc = uf.numberOfComponents();
            } else {
                cc = stronglyConnectedComponents().size();
            }

            return cc;
        }

        ArrayList<ArrayList<V>> stronglyConnectedComponents() const {
            StronglyConnectedComponents<V> *sc = new StronglyConnectedComponents<V>(*this);
            ArrayList<ArrayList<V>> arr = sc->stronglyConnectedComponents();
            delete sc;
            return arr;
        }

        void transpose() {
            if(directed) {
                Map<V, Set<V>> tmp(adj);
                ArrayList<V> vertices = adj.keys();
                for(int i = 0; i < vertices.size(); i++) {
                    V u = vertices[i];
                    Set<V> set = tmp.get(u);
                    
                    for(V v : set) {
                        this->removeEdge(u, v);
                        this->addEdge(v, u);
                    }
                }
            }
        }

        void addVertex(const V& vertex) {
            if(!adj.contains(vertex)) 
                adj.put(vertex, Set<V>());
        }

        void removeVertex(const V& vertex) {
            if(adj.contains(vertex)) {
                Set<V> vertices = adj[vertex];
                adj.remove(vertex);

                if(!directed) {
                    for(int i = 0; i < vertices.size(); ++i) 
                        adj[vertices[i]].pop(vertex);
                } else {
                    ArrayList<V> keys = adj.keys();

                    for(int i = 0; i < keys.size(); ++i) 
                        adj[keys[i]].pop(vertex);
                }
            }
        }

        bool changeWeight(const V& src, const V& dest, double weight) {
            return this->changeWeight(Edge<V>(src, dest, directed, weight));
        }

        bool changeWeight(const Edge<V>& edge) {
            int idx = edges.search(edge);
            if(idx != -1 && edges[idx].getWeight() != edge.getWeight()) 
                    edges[idx] = edge;
            
            return idx != -1;
        }

        void addEdge(const V& src, const V& dest, double weight = 0.0) {
            this->addEdge(Edge<V>(src, dest, directed, weight));
        }

        void addEdge(const Edge<V>& edge) {
            this->addVertex(edge.getSource());
            this->addVertex(edge.getDestination());

            adj[edge.getSource()].add(edge.getDestination());
            edges.add(edge);

            if(!directed) adj[edge.getDestination()].add(edge.getSource());
        }

        void removeEdge(const V& src, const V& dest) {
            this->removeEdge(Edge<V>(src, dest, directed));
        }

        void removeEdge(const Edge<V>& edge) {
            if(edges.contains(edge)) {
                adj[edge.getSource()].pop(edge.getDestination());
                edges.pop(edge);

                if(!directed) adj[edge.getDestination()].pop(edge.getSource());
            }
        }

        ArrayList<ArrayList<V>> cycles(const CycleDetectionType type = CycleDetectionType::WALK, const bool isomorphic = true) const {
            ArrayList<ArrayList<V>> arr;
            CycleDetection<V> *cd = new CycleDetection(*this);

            if(type == CycleDetectionType::WALK) arr = cd->permutationCycles(isomorphic);
            else if(type == CycleDetectionType::PERMUTATION) arr = cd->walkCycles(isomorphic);

            delete cd;
            return arr;
        }

        ArrayList<ArrayList<V>> permutations() const {
            return art::permutations<V>(adj.keys(), true);
        }

        ArrayList<ArrayList<V>> arrangements(int k) const {
            return art::arrangements<V>(adj.keys(), k);
        }

        ArrayList<ArrayList<V>> combinations(int k) const {
            return art::combinations<V>(adj.keys(), k);
        }

        Path<V> depthFirstSearch(const V& vertex) const {
            DepthFirstSearch<V> *dfs = new DepthFirstSearch<V>(*this);
            Path<V> path = dfs->dfs(vertex);
            delete dfs;
            return path;
        }

        Path<V> breathFirstSearch(const V& vertex) const {
            BreathFirstSearch<V> *bfs = new BreathFirstSearch<V>(*this);
            Path<V> path = bfs->bfs(vertex);
            delete bfs;
            return path;
        }

        int distance(const V& src, const V& dest) const {
            ShortestPath<V> *sp = new ShortestPath<V>(*this);
            int dist = sp->distance(src, dest);
            delete sp;
            return dist;
        }

        Map<V, Path<V>> shortestPath(const V& vertex) const {
            ShortestPath<V> *sp = new ShortestPath<V>(*this);
            Map<V, Path<V>> map = sp->shortestPath(vertex);
            delete sp;
            return map;
        }

        Path<V> shortestPath(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            return this->shortestPath(src)[dest];
        }

        Map<V, Map<V, double>> allDistances() const {
            ShortestPath<V> *sp = new ShortestPath<V>(*this);
            Map<V, Map<V, double>> map = sp->floydWarshal();
            delete sp;
            return map;
        }

        double weight(const V& src, const V& dest) const {
            int idx = edges.search(Edge<V>(src, dest, directed));
            
            if(idx == -1 && !directed) 
                idx = edges.search(Edge<V>(dest, src, directed));

            if(idx == -1) {
                if(src == dest) return 0.0;
                else throw std::invalid_argument("The given edge does not exist in the graph.");
            } 

            return edges.get(idx).getWeight();
        }

        Path<Edge<V>> minimumSpanningTree(const MinimumSpanningTreeType type = MinimumSpanningTreeType::PRIM) const {
            Path<Edge<V>> path;
            MinimumSpanningTree<V> *mst = new MinimumSpanningTree<V>(*this);

            if(type == MinimumSpanningTreeType::PRIM) path = mst->prim();
            else if(type == MinimumSpanningTreeType::KRUSKAL) path = mst->kruskal();

            delete mst;
            return path;
        }

        ArrayList<V> base() const {
            ArrayList<V> base;
            ArrayList<V> vertices = adj.keys();

            if(directed) {
                ArrayList<ArrayList<V>> sccs = this->stronglyConnectedComponents();
                
                Graph<int> hyperGraph(true);
                Map<V, int> vertexToHypervertex;
                
                for (int i = 0; i < sccs.size(); ++i) {
                    for (const V& v : sccs[i]) {
                        vertexToHypervertex[v] = i;
                    }
                }
                
                for (const Edge<V>& edge : edges) {
                    int srcHyper = vertexToHypervertex[edge.getSource()];
                    int destHyper = vertexToHypervertex[edge.getDestination()];
                    if (srcHyper != destHyper) {
                        hyperGraph.addEdge(srcHyper, destHyper);
                    }
                }
                
                for (int i = 0; i < sccs.size(); ++i) {
                    if (hyperGraph.degree(i).first() == 0) {
                        base.add(sccs[i][0]);
                    }
                }
            } else {
                Set<V> verticesSet = vertices.toSet();
                for(const V& v : vertices) {
                    if(adj.get(v).size() == 0) {
                        verticesSet.pop(v);
                        base.add(v);
                    }
                }

                if(!verticesSet.isEmpty()) base.add(verticesSet.get(0));
            }

            return base;
        }

        ArrayList<V> clasp(const V& vertex, const char& type = '+') const {
            if(!adj.contains(vertex))
                throw std::invalid_argument("The given vertex does not exist in the graph.");

            if(type != '+' && type != '-') 
                throw std::invalid_argument("The given type is not valid.");

            ArrayList<V> clp;
            if(type == '+') {
                Stack<V> stack;
                stack.push(vertex);

                Set<V> visited;
                ArrayList<V> vertices = adj.keys();
                while(!stack.isEmpty()) {
                    V u = stack.pop();
                    visited.add(u);
                    clp.add(u);

                    for(V v : adj.get(u)) 
                        if(!visited.contains(v)) 
                            stack.push(v);
                }
            } else {
                Graph<V> tmp(*this);
                tmp.transpose();
                clp = tmp.clasp(vertex);
            }

            return clp;
        }

        Map<V, Pair<int, int>> times(const V& vertex) const {
            ArrayList<V> vertices = adj.keys();
            Map<V, Pair<int, int>> map;
            Set<V> visited;

            Stack<V> stack;
            stack.push(vertex);
            visited.add(vertex);

            int time = 0;
            while(!stack.isEmpty()) {
                V v = stack.peek();
                
                if(!map.contains(v))
                    map.put(v, Pair<int, int>(++time));

                bool done = true;
                for(V u : adj.get(v)) {
                    if(!visited.contains(u)) {
                        stack.push(u);
                        visited.add(u);
                        done = false;
                    }
                }

                if(done) {
                    stack.pop();
                    map[v].second() = ++time;
                }
            }

            return map;
        }

        void clear() {
            adj.clear();
            edges.clear();
        }

        // Output Methods

        std::string describe() const {
            std::string s = "";

            s.append((directed ? "Directed" : "Undirected"));
            s.append((connectedComponents() == 1 ? " Connected" : " Disconnected"));
            s.append((isRegular() ? " Regular" : ""));
            s.append((isComplete() ? " Complete" : ""));
            s.append((isBipartite() ? " Bipartite" : ""));
            s.append((isEulerian() ? " Eulerian" : ""));
            s.append((isTree() ? " Tree" : ""));
            s.append((isForest() ? " Forest" : ""));
            s.append((isCyclic() ? " Cyclic" : ""));

            s.append(" Graph");
            return s;
        }

        void import(const std::string& fileName, bool customPath = false) {
            storage::import(*this, fileName, customPath);
        }

        void exportJSON(const std::string& fileName, bool customPath = false) {
            storage::exportJSON(*this, fileName, customPath);
        }

        void plot(std::string pngFileName = "", bool showInAWindow = false) {
            storage::plot(*this, pngFileName, showInAWindow);
        }

        void draw() {
            storage::draw(*this);
        }

        friend std::ostream& operator<<(std::ostream& strm, const Graph<V>& graph) {
            strm << graph.edges << std::endl;
            return strm << graph.adj << std::endl;
        }

        Set<V> operator[](const V& vertex) const {
            return adj.get(vertex);
        }

        bool operator==(const Graph<V>& other) const {
            return adj == other.adj && edges == other.edges && directed == other.directed;
        }

        bool operator!=(const Graph<V>& other) const {
            return !(*this == other);
        }
};

#endif
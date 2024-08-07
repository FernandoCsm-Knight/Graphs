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
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <limits>
#include <string>
#include <nlohmann/json.hpp>

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
#include "helpers/Vertex.hpp"
#include "helpers/Arithmatic.hpp"
#include "helpers/GraphGenerator.hpp"

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
            switch(type) {
                case GraphTypes::REGULAR:
                    *this = generator.regular(n, 2, isDirected);
                    break;
                case GraphTypes::COMPLETE:
                    *this = generator.complete(n, isDirected);
                    break;
                case GraphTypes::BIPARTITE:
                    if(n % 2 == 0) {
                        *this = generator.bipartite((int)(n/2), (int)(n/2), isDirected);
                    } else {
                        *this = generator.bipartite((int)(n/2), (int)(n/2 - 1), isDirected);
                    }

                    break;
                case GraphTypes::COMPLETE_BIPARTITE:
                    *this = generator.completeBipartite(n, isDirected);
                    break;
                case GraphTypes::EULERIAN:
                    *this = generator.eulerian(n, isDirected);
                    break;
                case GraphTypes::TREE:
                    *this = generator.tree(n, isDirected);
                    break;
                case GraphTypes::FOREST:
                    *this = generator.forest(n, isDirected);
                    break;
                case GraphTypes::CYCLIC:
                    *this = generator.cyclic(n, isDirected);
                    break;
                default:
                    throw std::invalid_argument("Invalid graph type.");
            }
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

        inline Set<V> getVertices() const { return adj.keys().toSet(); }
        inline Set<V> neighbors(const V& vertex) const { return adj.get(vertex); }
        inline Set<Edge<V>> getEdges() const { return edges; }
        inline Map<V, Set<V>> adjacencyList() const { return adj; }

        // Other Methods

        bool isRegular() const {
            ArrayList<Pair<int, int>> list = this->degreeList();

            bool value = true;
            if(!directed) {
                for(int i = 0; i < list.size() && value; ++i) 
                    value = list[i].first() == list[0].first();
            } else {
                for(int i = 0; i < list.size() && value; ++i)
                    value = list[i].first() == list[0].first() && list[i].second() == list[0].second();
            }
            
            return value;
        }

        bool isComplete() const {
            ArrayList<Pair<int, int>> list = this->degreeList();

            bool value = true;
            if(!directed) {
                for(int i = 0; i < list.size() && value; ++i) 
                    value = list[i].first() == list.size() - 1;
            } else {
                for(int i = 0; i < list.size() && value; ++i)
                    value = list[i].first() == list.size() - 1 && list[i].second() == list.size() - 1;
            }

            return value;
        }

        bool isBipartite() const {
            Map<V, bool> color;
            Map<V, bool> visited;
            bool value = true;

            ArrayList<V> vertices = adj.keys();
            for(const V& vertex : vertices) {
                color[vertex] = false;
                visited[vertex] = false;
            }

            Stack<V> stack;
            for(int i = 0; i < this->size() && value; ++i) {
                if(!visited[i]) {

                    stack.push(vertices[i]);
                    while(!stack.isEmpty() && value) {
                        V u = stack.pop();

                        visited[u] = true;
                        for(V v : adj.get(u)) {
                            if(!visited[v]) {
                                color[v] = !color[u];
                                stack.push(v);
                            } else if(color[v] == color[u]) {
                                value = false;
                            }
                        }
                    }
                } 
            }
            
            return value;
        }

        bool isTree() const {
            ArrayList<V> vertices = adj.keys();
            UnionFind<V> uf(vertices);

            for(Edge<V> e : edges) 
                uf.unify(e.getSource(), e.getDestination());

            return uf.numberOfComponents() == 1 && edges.size() == this->size() - 1;
        }

        bool isForest() const {
            ArrayList<V> vertices = adj.keys();
            UnionFind<V> uf(vertices);

            for(Edge<V> e : edges) 
                uf.unify(e.getSource(), e.getDestination());

            return edges.size() == this->size() - uf.numberOfComponents();
        }

        bool isCyclic() const {
            ArrayList<V> vertices = adj.keys();
            Map<V, V> parent;
            Map<V, char> visited;
            for(const V& vertex : vertices) visited[vertex] = 'w';
            
            Stack<V> stack;
            for(const V& vertex : vertices) {
                if(visited[vertex] == 'w') {
                    stack.push(vertex);
                    parent[vertex] = vertex;
                }

                while(!stack.isEmpty()) {
                    bool done = true;
                    V v = stack.peek();
                    if(visited[v] == 'w') visited[v] = 'g';

                    for(V u : adj.get(v)) {
                        if(u != parent[v]) {
                            if(visited[u] == 'w') {
                                stack.push(u);
                                parent[u] = v;
                                done = false;
                                break;
                            } else if(visited[u] == 'g') {
                                return true;
                            } 
                        }
                    }

                    if(done) visited[stack.pop()] = 'b';
                }
            }

            return false;
        }

        bool isEulerian() const {
            ArrayList<Pair<int, int>> list = degreeList();

            if(directed) {
                bool value = true;
                int j = 0, k = 0;
                for(int i = 0; i < list.size() && value; ++i) {
                    value = list[i].first() - list[i].second() <= 1 || list[i].second() - list[i].first() <= 1;
                    
                    if(value) {
                        if(list[i].first() - list[i].second() == 1) ++j;
                        if(list[i].second() - list[i].first() == 1) ++k;
                    }
                }

                return value && ((j == 1 && k == 1) || (j == 0 && k == 0));
            }

            int j = 0;
            for(int i = 0; i < list.size(); ++i) 
                if(list[i].first() % 2 != 0) ++j;

            return j == 2 || j == 0;
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

            Stack<V> stack;
            stack.push(vertex);

            int time = 0;
            while(!stack.isEmpty()) {
                V v = stack.peek();
                
                if(!map.contains(v))
                    map.put(v, Pair<int, int>(++time));

                bool done = true;
                for(V u : adj.get(v)) {
                    if(!map.contains(u)) {
                        stack.push(u);
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
            std::ifstream file(customPath ? fileName : ("data/" + fileName));
            if (!file.is_open()) 
                throw std::invalid_argument("Failed to open file: " + fileName);

            std::string jsonString;
            std::string line;
            while (std::getline(file, line)) 
                jsonString += line;

            nlohmann::json data = nlohmann::json::parse(jsonString);

            adj.clear();
            edges.clear();
            directed = data["directed"];

            for (const auto& link : data["edges"]) {
                V source = link["source"].get<V>();
                V target = link["target"].get<V>();
                double weight = link["weight"].get<double>();
                addEdge(source, target, weight);
            }
        }

        void exportJSON(const std::string& fileName, bool customPath = false) const {
            nlohmann::json data;
            data["directed"] = directed;
            data["multigraph"] = false;

            nlohmann::json links = nlohmann::json::array();
            for (const Edge<V>& edge : edges) {
                nlohmann::json link;
                link["source"] = edge.getSource();
                link["target"] = edge.getDestination();
                link["weight"] = edge.getWeight();
                links.push_back(link);
            }

            data["edges"] = links;
            std::string json =  data.dump(4); 

            std::ofstream file(customPath ? fileName : ("data/" + fileName));
            if (!file.is_open()) {
                std::cout << "Failed to open file: " << fileName << std::endl;
            } else {
                file << json;
                file.close();
            }
        }

        void plot(std::string pngFileName = "", bool showInAWindow = false) const {
            if (!pngFileName.empty() && !pngFileName.ends_with(".png")) {
                pngFileName = pngFileName.substr(0, pngFileName.find_last_of('.')) + ".png";
            }
            
            std::string filename = "tmp/toPlot.json";
            exportJSON(filename, true);
            std::cout << "Graph exported to " << filename << std::endl;

            std::string command = "python src/scripts/graph_visualizer.py ";
            command += filename;
            command += (showInAWindow ? " true " : " false ");
            command += pngFileName;
            int result = std::system(command.c_str());
            if (result == 0) {
                std::cout << "Graph image generated successfully." << std::endl;
            } else {
                std::cout << "Failed to generate graph image." << std::endl;
            }

            std::remove(filename.c_str());
        }

        void draw() {
            std::string command = "python src/scripts/graph_drawer.py";
            int result = std::system(command.c_str());
            if (result == 0) {
                std::cout << "Graph drawer executed successfully." << std::endl;
            } else {
                std::cout << "Failed to execute drawer." << std::endl;
            }
        
            try {
                import("tmp/importable.json");
                std::cout << "Graph imported successfully!" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "No graph to import!" << std::endl;
            }

            std::remove("tmp/importable.json");
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
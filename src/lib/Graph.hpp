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
#include <stdexcept>
#include <cmath>

#include "datastructs/ArrayList.hpp"
#include "datastructs/Map.hpp"
#include "datastructs/Queue.hpp"
#include "datastructs/Stack.hpp"
#include "datastructs/Set.hpp"
#include "datastructs/PriorityQueue.hpp"
#include "datastructs/IndexedPriorityQueue.hpp"
#include "datastructs/UnionFind.hpp"

#include "helpers/Edge.hpp"
#include "helpers/Pair.hpp"
#include "helpers/Path.hpp"
#include "helpers/Vertex.hpp"

/**
 * @brief Represents a graph data structure.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class Graph {
    private:
        Map<V, Set<V>> adj; ///< The adjacency list of the graph.
        Set<Edge<V>> edges; ///< The edge list of the graph.
        bool isDig = false; ///< Indicates whether the graph is directed.

        Path<V> parentsToPath(V* parents, double* distances, V dest) const {
            ArrayList<V> vertices = adj.keys();
            int indexDest = vertices.indexOf(dest, true);
            if(distances[indexDest] == std::numeric_limits<double>::infinity()) 
                return Path<V>(distances[indexDest]);

            Path<V> path;
            int index = indexDest;
            V tmp = parents[index];
            while(vertices[index] != tmp) {
                path.addParent(vertices[index]);
                index = vertices.indexOf(tmp, true);
                tmp = parents[index];
            }

            path.addParent(vertices[index]);
            path.setWeight(distances[indexDest]);
            return path;
        }

    public:

        // Constructors & Destructor

        Graph() {}

        Graph(bool isDirected): isDig(isDirected) {}

        Graph(Edge<V> edges[], int size, bool isDirected = false) {
            for (int i = 0; i < size; i++) 
                this->addEdge(edges[i]);

            isDig = isDirected;
        }

        Graph(const Graph<V>& other): adj(other.adj), edges(other.edges), isDig(other.isDig) {}

        ~Graph() {}

        // Operators

        Graph<V>& operator=(const Graph<V>& other) {
            if (this != &other) {
                adj = other.adj;
                edges = other.edges;
                isDig = other.isDig;
            }

            return *this;
        }

        // Inline Methods

        inline bool contains(const V& vertex) const { return adj.contains(vertex); }
        inline bool contains(const Edge<V>& edge) const { return edges.contains(edge); }
        inline bool contains(const V& src, const V& dest) const { return edges.contains(Edge<V>(src, dest, isDig)); }

        inline bool isEmpty() const { return adj.isEmpty(); }
        inline bool isDigraph() const { return isDig; }
        inline int size() const { return adj.size(); }
        inline int sizeEdges() const { return edges.size(); }

        inline Set<V> getVertices() const { return adj.keys().toSet(); }
        inline Set<V> getNeighbors(const V& vertex) const { return adj.get(vertex); }
        inline Set<Edge<V>> getEdges() const { return edges; }
        inline Map<V, Set<V>> adjacencyList() const { return adj; }

        // Other Methods

        bool isRegular() const {
            ArrayList<Pair<int, int>> list = this->degreeList();

            bool value = true;
            if(!isDig) {
                for(int i = 0; i < list.size() && value; i++) 
                    value = list[i].first() == list[0].first();
            } else {
                for(int i = 0; i < list.size() && value; i++)
                    value = list[i].first() == list[0].first() && list[i].second() == list[0].second();
            }
            
            return value;
        }

        bool isComplete() const {
            ArrayList<Pair<int, int>> list = this->degreeList();

            bool value = true;
            if(!isDig) {
                for(int i = 0; i < list.size() && value; i++) 
                    value = list[i].first() == list.size() - 1;
            } else {
                for(int i = 0; i < list.size() && value; i++)
                    value = list[i].first() == list.size() - 1 && list[i].second() == list.size() - 1;
            }

            return value;
        }

        bool isBipartite() const {
            bool color[this->size()];
            bool visited[this->size()];
            bool value = true;

            for(int i = 0; i < this->size(); i++) {
                color[i] = false;
                visited[i] = false;
            }

            Stack<V> stack;
            ArrayList<V> vertices = adj.keys();

            for(int i = 0; i < this->size() && value; i++) {
                if(!visited[i]) {
                    stack.push(vertices[i]);

                    while(!stack.isEmpty() && value) {
                        V u = stack.pop();
                        int indexU = vertices.indexOf(u, true);

                        visited[indexU] = true;
                        for(V v : adj.get(u)) {
                            int indexV = vertices.indexOf(v, true);

                            if(!visited[indexV]) {
                                color[indexV] = !color[indexU];
                                stack.push(v);
                            } else if(color[indexV] == color[indexU]) {
                                value = false;
                            }
                        }
                    }
                } 
            }
            
            return value;
        }

        bool isTree() const {
            UnionFind uf(this->size());
            ArrayList<V> vertices = adj.keys();

            for(Edge<V> e : edges) 
                uf.unify(vertices.indexOf(e.getSource(), true), vertices.indexOf(e.getDestination(), true));

            return uf.numberOfComponents() == 1 && edges.size() == this->size() - 1;
        }

        bool isForest() const {
            UnionFind uf(this->size());
            ArrayList<V> vertices = adj.keys();

            for(Edge<V> e : edges) 
                uf.unify(vertices.indexOf(e.getSource(), true), vertices.indexOf(e.getDestination(), true));

            return edges.size() == this->size() - uf.numberOfComponents();
        }

        bool isEulerian() const {
            ArrayList<Pair<int, int>> list = degreeList();

            if(isDig) {
                bool value = true;
                int j = 0, k = 0;
                for(int i = 0; i < list.size() && value; i++) {
                    value = list[i].first() - list[i].second() <= 1 || list[i].second() - list[i].first() <= 1;
                    
                    if(value) {
                        if(list[i].first() - list[i].second() == 1) j++;
                        if(list[i].second() - list[i].first() == 1) k++;
                    }
                }

                return value && ((j == 1 && k == 1) || (j == 0 && k == 0));
            }

            int j = 0;
            for(int i = 0; i < list.size(); i++) 
                if(list[i].first() % 2 != 0) j++;

            return j == 2 || j == 0;
        }

        Pair<int, int> degree(const V& vertex) const {
            if(!isDig) return Pair<int, int>(adj.get(vertex).size());

            int in = 0, out = 0;
            for(int i = 0; i < edges.size(); i++) {
                if(edges.get(i).getDestination() == vertex) in++;
                if(edges.get(i).getSource() == vertex) out++;
            }

            return Pair<int, int>(in, out);
        }

        ArrayList<Pair<int, int>> degreeList() const {
            ArrayList<V> vertices = adj.keys();
            ArrayList<Pair<int, int>> list;

            for(int i = 0; i < vertices.size(); i++) 
                list.add(this->degree(vertices[i]));

            return list;
        }

        int connectedComponents() const {
            if(!isDig) {
                UnionFind uf(this->size());
                ArrayList<V> vertices = adj.keys();

                for(Edge<V> e : edges) 
                    uf.unify(vertices.indexOf(e.getSource(), true), vertices.indexOf(e.getDestination(), true));
                
                return uf.numberOfComponents();
            }

            return -1;
        }

        ArrayList<ArrayList<V>> stronglyConnectedComponents() const {
            if(!isDig) throw std::invalid_argument("The graph hasn't strongly connected components because is not directed.");

            ArrayList<V> vertices = adj.keys();
        
            int id = 0;
            int ids[vertices.size()];
            int lowLink[vertices.size()];
            bool onStack[vertices.size()];
            Stack<V> stack;
            Stack<V> dfsStack;
            ArrayList<ArrayList<V>> components;

            for(int i = 0; i < vertices.size(); i++) {
                ids[i] = -1;
                lowLink[i] = -1;
                onStack[i] = false;
            }

            for(int i = 0; i < vertices.size(); i++) {
                if(ids[i] == -1) {
                    dfsStack.push(vertices[i]);
                    stack.push(vertices[i]);
                    ids[i] = id;
                    lowLink[i] = id;
                    onStack[i] = true;
                    id++;

                    while(!dfsStack.isEmpty()) {
                        V u = dfsStack.peek();
                        int indexU = vertices.indexOf(u, true);
                        bool done = true;

                        for(V w : adj.get(u)) {
                            int indexW = vertices.indexOf(w, true);

                            if(ids[indexW] == -1) {
                                dfsStack.push(w);
                                stack.push(w);
                                ids[indexW] = id;
                                lowLink[indexW] = id;
                                onStack[indexW] = true;
                                id++;
                                done = false;
                                break;
                            } else if(onStack[indexW]) {
                                lowLink[indexU] = std::min(lowLink[indexW], lowLink[indexU]);
                            }
                        }

                        if(done) {
                            dfsStack.pop();
                            if(lowLink[indexU] == ids[indexU]) {
                                ArrayList<V> list;
                                V w;
                                do {
                                    w = stack.pop();
                                    onStack[vertices.indexOf(w, true)] = false;
                                    list.add(w);
                                } while(w != u);
                                components.add(list);
                            }
                        }
                    }
                }
            }

            return components;
        }

        void transpose() {
            if(isDig) {
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

                if(!isDig) {
                    for(int i = 0; i < vertices.size(); i++) 
                        adj[vertices[i]].pop(vertex);
                } else {
                    ArrayList<V> keys = adj.keys();

                    for(int i = 0; i < keys.size(); i++) 
                        adj[keys[i]].pop(vertex);
                }
            }
        }

        void addEdge(const V& src, const V& dest, double weight = 0.0) {
            this->addEdge(Edge<V>(src, dest, isDig, weight));
        }

        void addEdge(const Edge<V>& edge) {
            this->addVertex(edge.getSource());
            this->addVertex(edge.getDestination());

            adj[edge.getSource()].add(edge.getDestination());
            edges.add(edge);

            if(!isDig) adj[edge.getDestination()].add(edge.getSource());
        }

        void removeEdge(const V& src, const V& dest) {
            this->removeEdge(Edge<V>(src, dest, isDig));
        }

        void removeEdge(const Edge<V>& edge) {
            if(edges.contains(edge)) {
                adj[edge.getSource()].pop(edge.getDestination());
                edges.pop(edge);

                if(!isDig) adj[edge.getDestination()].pop(edge.getSource());
            }
        }

        int distance(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            if(src == dest) return 0;

            ArrayList<V> vertices = adj.keys();
            PriorityQueue<Pair<int, V>> queue;
            bool visited[this->size()];

            for(int i = 0; i < this->size(); i++) 
                visited[i] = false;

            Pair<int, V> pair(0, src);
            queue.push(pair);
            while(!queue.isEmpty() && pair.second() != dest) {
                pair = queue.poll();
                visited[vertices.indexOf(pair.second(), true)] = true;
                
                for(V u : adj.get(pair.second())) {
                    if(!visited[vertices.indexOf(u, true)]) 
                        queue.push(Pair<int, V>(pair.first() + 1, u));
                }
            }

            return (pair.second() == dest) ? pair.first() : -1;
        }

        Map<V, Path<V>> shortestPath(const V& vertex) const {
            if(!adj.contains(vertex)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            bool hasNegativeWeight = false;
            for(int i = 0; i < edges.size() && !hasNegativeWeight; i++) 
                hasNegativeWeight = edges.get(i).getWeight() < 0;

            ArrayList<V> vertices = adj.keys();
            double distances[this->size()];
            V parents[this->size()];

            for(int i = 0; i < this->size(); i++) {
                distances[i] = std::numeric_limits<double>::infinity();
                parents[i] = vertices[i];
            }

            distances[vertices.indexOf(vertex, true)] = 0;

            if(hasNegativeWeight) {
                for(int i = 0; i < this->size() - 1; i++) {
                    for(Edge<V> edge : edges) {
                        int indexSrc = vertices.indexOf(edge.getSource(), true);
                        int indexDest = vertices.indexOf(edge.getDestination(), true);

                        if(distances[indexSrc] + edge.getWeight() < distances[indexDest]) {
                            distances[indexDest] = distances[indexSrc] + edge.getWeight();
                            parents[indexDest] = edge.getSource();
                        }
                    }
                }

                for(int i = 0; i < this->size() - 1; i++) {
                    for(Edge<V> edge : edges) {
                        int indexSrc = vertices.indexOf(edge.getSource(), true);
                        int indexDest = vertices.indexOf(edge.getDestination(), true);

                        if(distances[indexSrc] + edge.getWeight() < distances[indexDest]) {
                            distances[indexDest] = -std::numeric_limits<double>::infinity();
                            parents[indexDest] = edge.getSource();
                        }
                    }
                }
            } else {
                PriorityQueue<Pair<double, V>> queue;
                bool visited[this->size()];

                for(int i = 0; i < this->size(); i++) 
                    visited[i] = false;

                queue.push(Pair<double, V>(0.0, vertex));
                while(!queue.isEmpty()) {
                    V w = queue.poll().second();
                    int indexW = vertices.indexOf(w, true);

                    visited[indexW] = true;
                    for(V u : adj.get(w)) {
                        int indexU = vertices.indexOf(u, true);

                        if(!visited[indexU]) {
                            if(distances[indexU] < distances[indexW] + weight(w, u)) {
                                distances[indexU] = distances[indexU];
                            } else {
                                distances[indexU] = distances[indexW] + weight(w, u);
                                parents[indexU] = w;
                            }

                            queue.push(Pair<double, V>(distances[indexU], u));
                        }
                    }
                }
            }

            Map<V, Path<V>> map;
            for(int i = 0; i < vertices.size(); i++) 
                map.put(vertices[i], parentsToPath(parents, distances, vertices[i]));
            
            return map;
        }

        Path<V> shortestPath(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            return this->shortestPath(src)[dest];
        }

        double weight(const V& src, const V& dest) const {
            int idx = edges.search(Edge<V>(src, dest, isDig));
            
            if(idx == -1 && !isDig) 
                idx = edges.search(Edge<V>(dest, src, isDig));

            if(idx == -1) {
                if(src == dest) return 0.0;
                else throw std::invalid_argument("The given edge does not exist in the graph.");
            } 

            return edges.get(idx).getWeight();
        }

        Path<Edge<V>> minimumSpanningTree() const {
            IndexedPriorityQueue<Pair<double, Edge<V>>> queue(this->size());
            ArrayList<V> vertices = adj.keys();
            bool visited[this->size()];
            Path<Edge<V>> path;

            for(int i = 0; i < this->size(); i++) 
                visited[i] = false;

            queue.insert(0, Pair<double, Edge<V>>(0.0, Edge<V>(vertices[0], vertices[0], isDig)));

            while(!queue.isEmpty()) {
                visited[queue.minKey()] = true;
                Pair<double, Edge<V>> pair = queue.poll();
                path.add(pair.second(), pair.first());

                V u = pair.second().getDestination();
                for(V w : adj.get(u)) {
                    int indexW = vertices.indexOf(w, true);
                
                    if(!visited[indexW]) {
                        double weight = this->weight(u, w);

                        if(queue.contains(indexW)) 
                            queue.decrease(indexW, Pair<double, Edge<V>>(weight, Edge<V>(u, w, isDig, weight)));
                        else 
                            queue.insert(indexW, Pair<double, Edge<V>>(weight, Edge<V>(u, w, isDig, weight)));
                    }
                }
            }

            return path;
        }

        ArrayList<V> clasp(const V& vertex, const char& type = '+') {
            if(!adj.contains(vertex))
                throw std::invalid_argument("The given vertex does not exist in the graph.");

            if(type != '+' && type != '-') 
                throw std::invalid_argument("The given type is not valid.");

            ArrayList<V> clp;

            if(type == '+') {
                Stack<V> stack;
                stack.push(vertex);

                ArrayList<V> vertices = adj.keys();
                bool visited[this->size()];

                for(int i = 0; i < this->size(); i++) 
                    visited[i] = false;

                while(!stack.isEmpty()) {
                    V u = stack.pop();
                    clp.add(u);

                    visited[vertices.indexOf(u, true)] = true;
                    for(V v : adj.get(u)) {
                        if(!visited[vertices.indexOf(v, true)]) 
                            stack.push(v);
                    }
                }
            } else {
                Graph<V> tmp(*this);
                tmp.transpose();
                clp = tmp.clasp(vertex);
            }

            return clp;
        }



        void clear() {
            adj.clear();
            edges.clear();
        }

        // Output Methods

        std::string describe() const {
            std::string s = "";

            s.append((isDig ? "Directed" : "Undirected"));
            s.append((connectedComponents() == 1 ? " Connected" : " Disconnected"));
            s.append((isRegular() ? " Regular" : ""));
            s.append((isComplete() ? " Complete" : ""));
            s.append((isBipartite() ? " Bipartite" : ""));
            s.append((isEulerian() ? " Eulerian" : ""));
            s.append((isTree() ? " Tree" : ""));
            s.append((isForest() ? " Forest" : ""));

            s.append(" Graph");
            return s;
        }

        void toJsonFile() const {
            std::ofstream file;
            file.open("graph.json");

            if(file.is_open()) {
                file << "[" << std::endl;
                file << "{" << std::endl << "\"Graph\": {" << std::endl;
                file << "\t\"isDirected\": " << (isDig ? "true" : "false") << "," << std::endl;
                file << "\t\"Adjacency List\": {" << std::endl;

                ArrayList<V> vertices = adj.keys();

                for(int i = 0; i < vertices.size(); i++) {
                    Set<V> set = adj.get(vertices[i]);
                    V* list = set.toVector();

                    file << "\t\t\"" << vertices[i] << "\": [";
                    
                    for(int i = 0; i < set.size(); i++) 
                        file << "\"" << list[i] << "\"" << ((i < set.size() - 1) ? ", " : "");

                    file << "]" << ((i < vertices.size() - 1) ? "," : "") << std::endl;
                }

                file << "\t}," << std::endl << "\t\"Edges\": {" << std::endl;

                Edge<V>* list = edges.toVector();
                for(int i = 0; i < edges.size(); i++) 
                    file << "\t\t\"" << list[i].getSource() << " -> " << list[i].getDestination() << "\": " << list[i].getWeight() << ((i < edges.size() - 1) ? "," : "") << std::endl;
                
                file << "\t}" << std::endl << "}" << std::endl << "}" << std::endl << "]" << std::endl;
            }

            file.close();
        }

        friend std::ostream& operator<<(std::ostream& strm, const Graph<V>& graph) {
            strm << graph.edges << std::endl;
            return strm << graph.adj << std::endl;
        }
};

#endif
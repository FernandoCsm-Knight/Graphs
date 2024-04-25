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
#include "helpers/GraphGenerator.hpp"

/**
 * @brief Represents the type of cycle detection algorithm.
 * 
 * - PERMUTATION: The cycle detection algorithm is based on permutations.
 * - WALK: The cycle detection algorithm is based on depth-first search.
 */
enum CycleDetectionType {
    PERMUTATION,
    WALK,
};

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

        Path<V> parentsToPath(V* parents, double* const distances, const V& dest) const {
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

        void walkRecurse(const V& v, const V& parent, Map<V, V>& visited, Set<V>& counting, ArrayList<ArrayList<V>>& cycles, bool isomorphic) const {
            visited[v] = parent;
            counting.add(v);

            for(V u : adj.get(v)) {
                if(u != parent) {
                    if(!visited.contains(u)) {
                        walkRecurse(u, v, visited, counting, cycles, isomorphic);
                    } else {
                        ArrayList<V> cycle;
                        V current = v;

                        cycle.add(u);
                        while(current != u) {
                            cycle.add(current);
                            current = visited[current];
                        }

                        if(cycle.size() >= 3) addIfUnique(cycles, cycle, isomorphic);
                    }
                }
            }

            visited.remove(v);
        }

        ArrayList<ArrayList<V>> walkCycles(bool isomorphic) const {
            ArrayList<ArrayList<V>> cycles;
            Map<V, V> visited;
            Set<V> counting;

            ArrayList<V> vertices = adj.keys();
            for(const V& start : vertices) {
                if(!counting.contains(start)) {
                    walkRecurse(start, start, visited, counting, cycles, isomorphic);
                }
            }

            return cycles;
        }

        bool areCyclesIsomorphic(const ArrayList<V>& cycle1, const ArrayList<V>& cycle2) const {
            bool isomorphic = false;

            if (cycle1.size() == cycle2.size()) {
                int size = cycle1.size();
                for (int i = 0; i < size && !isomorphic; ++i) {
                    bool match = true;
                    for (int j = 0; j < size && match; ++j) 
                        if (cycle1.get(j) != cycle2.get((i + j) % size)) 
                            match = false;

                    isomorphic = match;
                }

                if(!isomorphic) {
                    ArrayList<V> reversedCycle2 = cycle2;
                    std::reverse(reversedCycle2.begin(), reversedCycle2.end());
                    for (int i = 0; i < size && !isomorphic; ++i) {
                        bool match = true;
                        for (int j = 0; j < size && match; ++j) 
                            if (cycle1.get(j) != reversedCycle2[(i + j) % size]) 
                                match = false;

                        isomorphic = match;
                    }
                }
            }
            
            return isomorphic; 
        }

        void addIfUnique(ArrayList<ArrayList<V>>& uniqueCycles, const ArrayList<V>& cycle, bool isomorphic) const {
            bool unique = true;

            for(int j = 0; j < uniqueCycles.size() && unique; ++j) {
                bool found = uniqueCycles[j].size() == cycle.size();
                for(int k = 0; k < cycle.size() && found; ++k) 
                    found = uniqueCycles[j].contains(cycle.get(k));

                if(found && isomorphic) found = areCyclesIsomorphic(uniqueCycles[j], cycle);
                unique = !found;
            }

            if(unique) uniqueCycles.add(cycle);
        }

        ArrayList<ArrayList<V>> permutationCycles(bool isomorphic) const {
            ArrayList<ArrayList<V>> uniqueCycles;
            
            for(int i = 3; i <= this->size(); ++i) {
                ArrayList<ArrayList<V>> perms = arrangements(i);

                for(ArrayList<V> perm : perms) {
                    bool found = true;
                    for(int j = 0; j < perm.size() && found; ++j) 
                        found = adj.get(perm[j]).contains(perm[(j + 1) % perm.size()]);

                    if(found) {
                        addIfUnique(uniqueCycles, perm, isomorphic);
                    }
                }
            }

            return uniqueCycles;
        }

    public:

        // Constructors & Destructor

        Graph(bool isDirected = false): directed(isDirected) {}

        Graph(GraphTypes type, int n = 5, bool isDirected = false) {
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

        Graph(Edge<V> edges[], int size, bool isDirected = false) {
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
            if(!directed) throw std::invalid_argument("The graph hasn't strongly connected components because is not directed.");

            int id = 0;
            Map<V, int> ids;
            Map<V, int> lowLink;
            Map<V, bool> onStack;

            Stack<V> stack;
            Stack<V> dfsStack;
            ArrayList<V> vertices = adj.keys();
            ArrayList<ArrayList<V>> components;
            for(const V& vertex : vertices) {
                ids[vertex] = -1;
                lowLink[vertex] = -1;
                onStack[vertex] = false;
            }

            for(const V& vertex : vertices) {
                if(ids[vertex] == -1) {
                    dfsStack.push(vertex);
                    stack.push(vertex);
                    ids[vertex] = id;
                    lowLink[vertex] = id;
                    onStack[vertex] = true;
                    ++id;

                    while(!dfsStack.isEmpty()) {
                        V u = dfsStack.peek();
                        bool done = true;

                        for(V w : adj.get(u)) {
                            if(ids[w] == -1) {
                                dfsStack.push(w);
                                stack.push(w);
                                ids[w] = id;
                                lowLink[w] = id;
                                onStack[w] = true;
                                id++;
                                done = false;
                                break;
                            } else if(onStack[w]) {
                                lowLink[u] = std::min(lowLink[w], lowLink[u]);
                            }
                        }

                        if(done) {
                            dfsStack.pop();
                            if(lowLink[u] == ids[u]) {
                                ArrayList<V> list;
                                V w;
                                do {
                                    w = stack.pop();
                                    onStack[w] = false;
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

        ArrayList<ArrayList<V>> cycles(CycleDetectionType type = CycleDetectionType::WALK, bool isomorphic = true) const {
            if(CycleDetectionType::PERMUTATION == type) return permutationCycles(isomorphic);
            else return walkCycles(isomorphic);
        }

        ArrayList<ArrayList<V>> permutations() const {
            ArrayList<ArrayList<V>> allPermutations;
            ArrayList<V> vertices = adj.keys();

            do {
                allPermutations.add(vertices);
            } while(std::next_permutation(vertices.begin(), vertices.end()));
            
            return allPermutations;
        }

        ArrayList<ArrayList<V>> arrangements(int k) const {
            ArrayList<ArrayList<V>> comb = combinations(k);
            ArrayList<ArrayList<V>> allArrangements;

            for(ArrayList<V> c : comb) {
                do {
                    allArrangements.add(c);
                } while(std::next_permutation(c.begin(), c.end()));
            }

            return allArrangements; 
        }

        ArrayList<ArrayList<V>> combinations(int k) const {
            ArrayList<V> vertices = adj.keys();
            ArrayList<ArrayList<V>> allCombinations;

            std::string bitmask(k, 1); 
            bitmask.resize(vertices.size(), 0);

            do {
                ArrayList<V> curr;

                for(int i = 0; i < vertices.size(); ++i) {
                    if(bitmask[i]) curr.add(vertices[i]);
                }

                allCombinations.add(curr);
            } while(std::prev_permutation(bitmask.begin(), bitmask.end()));

            return allCombinations;
        }


        Path<V> depthFirstSearch(const V& vertex) const {
            if(!adj.contains(vertex)) 
                throw std::invalid_argument("The given vertex doesn't belongs to the current graph.");

            Set<V> visited;
            ArrayList<V> vertices = adj.keys();

            Path<V> path;
            Stack<V> stack;
            stack.push(vertex);
            while(!stack.isEmpty()) {
                V v = stack.pop();
                visited.add(v);
                path.add(v);

                for(V u : adj.get(v)) if(!visited.contains(u)) stack.push(u);
            }

            return path;
        }

        Path<V> breathFirstSearch(const V& vertex) const {
            if(!adj.contains(vertex))
                throw std::invalid_argument("The given vertex doesn't belongs to the current graph.");

            ArrayList<V> vertices = adj.keys();
            Set<V> visited;

            Path<V> path;
            Queue<V> queue;
            queue.push(vertex);
            while(!queue.isEmpty()) {
                V v = queue.pop();
                visited.add(v);
                path.add(v);

                for(V u : adj.get(v)) if(!visited.contains(u)) queue.push(u);
            }
            
            return path;
        }

        int distance(const V& src, const V& dest) const {
            if(!adj.contains(src) || !adj.contains(dest)) 
                throw std::invalid_argument("The given vertices do not exist in the graph.");

            if(src == dest) return 0;

            ArrayList<V> vertices = adj.keys();
            PriorityQueue<Pair<int, V>> queue;
            Set<V> visited;

            Pair<int, V> pair(0, src);
            queue.push(pair);
            while(!queue.isEmpty() && pair.second() != dest) {
                pair = queue.poll();
                visited.add(pair.second());
                
                for(V u : adj.get(pair.second())) 
                    if(!visited.contains(u)) 
                        queue.push(Pair<int, V>(pair.first() + 1, u));
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
            int idx = edges.search(Edge<V>(src, dest, directed));
            
            if(idx == -1 && !directed) 
                idx = edges.search(Edge<V>(dest, src, directed));

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

            queue.insert(0, Pair<double, Edge<V>>(0.0, Edge<V>(vertices[0], vertices[0], directed)));

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
                            queue.decrease(indexW, Pair<double, Edge<V>>(weight, Edge<V>(u, w, directed, weight)));
                        else 
                            queue.insert(indexW, Pair<double, Edge<V>>(weight, Edge<V>(u, w, directed, weight)));
                    }
                }
            }

            return path;
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

        void import(const std::string& jsonFile) {
            std::ifstream file(jsonFile);
            if (!file.is_open()) {
                throw std::invalid_argument("Failed to open file: " + jsonFile);
            }

            std::string jsonString;
            std::string line;
            while (std::getline(file, line)) {
                jsonString += line;
            }

            nlohmann::json data = nlohmann::json::parse(jsonString);

            adj.clear();
            edges.clear();

            directed = data["directed"];

            for (const auto& link : data["links"]) {
                V source = link["source"].get<V>();
                V target = link["target"].get<V>();
                addEdge(source, target);
            }
        }

        void exportJSON(const std::string& fileName) const {
            nlohmann::json data;
            data["directed"] = directed;
            data["multigraph"] = false;
            data["graph"] = nlohmann::json::object();

            nlohmann::json nodes = nlohmann::json::array();
            ArrayList<V> vertices = adj.keys();
            for (int i = 0; i < vertices.size(); ++i) {
                nlohmann::json node;
                node["pos"] = nlohmann::json::array({0, 0});
                node["id"] = i;
                nodes.push_back(node);
            }
            data["nodes"] = nodes;

            nlohmann::json links = nlohmann::json::array();
            for (const Edge<V>& edge : edges) {
                nlohmann::json link;
                link["source"] = vertices.indexOf(edge.getSource(), true);
                link["target"] = vertices.indexOf(edge.getDestination(), true);
                links.push_back(link);
            }

            data["links"] = links;
            std::string json =  data.dump(4); 

            std::ofstream file("data/" + fileName);
            if (!file.is_open()) {
                std::cout << "Failed to open file: " << fileName << std::endl;
                return;
            }

            file << json;
            file.close();
        }


        void exportDOT() const {
            std::string filename = "toPlot.dot";
            std::ofstream file("tmp/" + filename);
            file << (directed ? "digraph" : "graph") << " G {\n";
            
            for(const V& v : adj.keys()) {
                file << "  \"" << v << "\";\n";
            }
            
            for(const Edge<V>& e : edges) {
                file << "  \"" << e.getSource() << "\" " 
                    << (directed ? "->" : "--") << " \"" 
                    << e.getDestination() << "\";\n";
            }
            
            file << "}\n";
            file.close();
        }

        void plot(std::string pngFileName = "graph_visualization.png", bool showInAWindow = false) const {
            if (!pngFileName.ends_with(".png")) {
                pngFileName = pngFileName.substr(0, pngFileName.find_last_of('.')) + ".png";
            }

            std::string filename = "tmp/toPlot.json";
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cout << "Failed to open file: " << filename << std::endl;
                return;
            }

            file << "{\n";
            file << "  \"directed\": " << (directed ? "true" : "false") << ",\n";
            file << "  \"nodes\": [\n";

            ArrayList<V> vertices = adj.keys();
            for (int i = 0; i < vertices.size(); ++i) {
                file << "    { \"id\": \"" << vertices[i] << "\" }";
                if (i < vertices.size() - 1) {
                    file << ",";
                }
                file << "\n";
            }

            file << "  ],\n";
            file << "  \"edges\": [\n";

            int edgeCount = 0;
            for (const Edge<V>& edge : edges) {
                file << "    { \"source\": \"" << edge.getSource() << "\", \"target\": \"" << edge.getDestination() << "\" }";
                if (edgeCount < edges.size() - 1) {
                    file << ",";
                }
                file << "\n";
                ++edgeCount;
            }

            file << "  ]\n";
            file << "}\n";

            file.close();
            std::cout << "Graph exported to " << filename << std::endl;

            std::string command = "python src/scripts/graph_visualizer.py ";
            command += filename;
            command += " " + pngFileName + " ";
            command += (showInAWindow ? "true" : "false");
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
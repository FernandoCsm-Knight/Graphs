/**
 * @file MatrixGraph.hpp
 * @author Fernando Campos Silva Dal Maria (fernando.csm123@gmail.com)
 * @brief A C++ implementation of a MatrixGraph class, a templated container 
 *        that represents a graph data structure using an adjacency matrix.
 *        The class allows associating a vertex label of type V with a corresponding
 *        adjacency matrix of type char**. It provides multiple constructors for
 *        creating graphs, including default and directedness constructors.
 * 
 * @version 1.0.0
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

template <class V> class MatrixGraph;

#include <iostream>
#include <stdexcept>

#include "datastructs/ArrayList.hpp"
#include "datastructs/PriorityQueue.hpp"
#include "datastructs/Map.hpp"
#include "datastructs/Queue.hpp"
#include "datastructs/Stack.hpp"

#include "DepthFirstOrder.hpp"
#include "Tarjan.hpp"

#include "helpers/Edge.hpp"
#include "helpers/Vertex.hpp"
#include "helpers/Pair.hpp"

/**
 * @brief A template class implementing a graph data structure using an adjacency matrix.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class MatrixGraph {
    private:
        char** matrix;                      ///< The adjacency matrix.
        ArrayList<Vertex<V>> vertices;      ///< The vertices of the graph.
        int length;                         ///< The number of vertices in the graph.
        bool isDir;                         ///< Indicates whether the graph is directed.

        /**
         * @brief Deallocates the memory used by the adjacency matrix.
         */
        void deallocate() {
            for(int i = 0; i < this->length; i++)
                delete[] this->matrix[i];
            
            delete[] this->matrix;
        }

        /**
         * @brief Returns a bool array containing the vertices
         * 
         * @param vertex The vertex to start the search.
         * @return True if the graph contains the given vertex, false otherwise.
         */
        bool* depthFirstSearch(const Vertex<V>& vertex) const {
            Stack<Vertex<V>> stk;
            
            bool* arr = new bool[this->length];
            for(int i = 0; i < this->length; i++) 
                arr[i] = false;

            stk.push(vertex);
            arr[this->vertices.indexOf(vertex, true)] = true;
            while(!stk.isEmpty()) {
                Vertex<V> tmp = stk.pop();

                int idx = this->vertices.indexOf(tmp, true);
                for(int i = 0; i < this->length; i++) {
                    if(this->matrix[idx][i] == 1 && !arr[i]) {
                        stk.push(this->vertices.get(i));
                        arr[i] = true;
                    }
                } 
            }

            return arr;
        }

    public:

        /**
         * @brief Construct a new Matrix Graph object.
         */
        MatrixGraph(): matrix(nullptr), length(0), isDir(false) {}

        /**
         * @brief Construct a new Matrix Graph object
         *        with the specified directedness.
         * 
         * @param isDir Indicates whether the graph is directed.
         */
        MatrixGraph(bool isDir): matrix(nullptr), length(0), isDir(isDir) {}

        /**
         * @brief Construct a new Matrix Graph object
         * 
         * @param graph The graph to be copied.
         */
        MatrixGraph(const MatrixGraph<V>& graph) {
            this->vertices = graph.vertices;
            this->length = graph.length;
            this->isDir = graph.isDir;

            this->matrix = new char*[this->length];
            for(int i = 0; i < this->length; i++) {
                this->matrix[i] = new char[this->length];
                for(int j = 0; j < this->length; j++) 
                    this->matrix[i][j] = graph.matrix[i][j];
            }
        }

        /**
         * @brief Destroy the Matrix Graph object.
         */
        ~MatrixGraph() { this->deallocate(); }

        /**
         * @brief Indicates whether the graph is empty.
         * 
         * @return True if the graph is empty, false otherwise.
         */
        bool isEmpty() const {
            return this->length == 0;
        }

        /**
         * @brief Indicates whether the graph is directed.
         * 
         * @return True if the graph is directed, false otherwise.
         */
        bool isDigraph() const {
            return this->isDir;
        }

        /**
         * @brief Returns the number of vertices in the graph.
         * 
         * @return int The number of vertices in the graph.
         */
        int size() const {
            return this->length;
        }

        /**
         * @brief Overloaded assignment operator to copy the given graph.
         * 
         * @param graph The graph to be copied. 
         * @return MatrixGraph<V>& The copied graph.
         */
        MatrixGraph<V>& operator=(const MatrixGraph<V>& graph) {
            if(this != &graph) {
                this->vertices = graph.vertices;
                this->length = graph.length;
                this->isDir = graph.isDir;

                this->matrix = new char*[this->length];
                for(int i = 0; i < this->length; i++) {
                    this->matrix[i] = new char[this->length];
                    for(int j = 0; j < this->length; j++) 
                        this->matrix[i][j] = graph.matrix[i][j];
                }
            }

            return *this;
        }

        /**
         * @brief Returns the given vertex's line in the adjacency matrix.
         * 
         * @param vertex The vertex to get its line.
         * @return char* The vertex's line in the adjacency matrix.
         */
        char* operator[](const Vertex<V>& vertex) const {
            int index = this->vertices.indexOf(vertex, true);

            if(index == -1)
                throw std::invalid_argument("Vertex not found.");

            return this->matrix[index];
        }

        /**
         * @brief Returns the given vertex's line in the adjacency matrix.
         * 
         * @param idx The index of the vertex to get its line.
         * @return char* The vertex's line in the adjacency matrix.
         */
        char* operator[](std::size_t idx) const {
            if(idx >= (std::size_t)this->length)
                throw std::out_of_range("Index out of range.");

            return this->matrix[idx];
        }

        /**
         * @brief Indicates whether the graph contains the given vertex.
         * 
         * @param label 
         * @return True if the graph contains the given vertex, false otherwise.
         */
        bool contains(const V& label) const {
            return this->vertices.contains(Vertex<V>(label), true);
        }

        /**
         * @brief Indicates whether the graph contains the given vertex.
         * 
         * @param vertex The vertex to be checked.
         * @return True if the graph contains the given vertex, false otherwise. 
         */
        bool contains(const Vertex<V>& vertex) const {
            return this->vertices.contains(vertex, true);
        }

        /**
         * @brief Indicates whether the graph contains the given edge.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         * @return True if the graph contains the given edge, false otherwise.
         */
        bool contains(const V& src, const V& dest) const {
            int srcIndex = this->vertices.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertices.indexOf(Vertex<V>(dest), true);

            if(srcIndex != -1 && destIndex != -1) 
                return this->matrix[srcIndex][destIndex] != 0;

            return false;
        }

        /**
         * @brief Indicates whether the graph contains the given edge.
         * 
         * @param edge The edge to be checked.
         * @return True if the graph contains the given edge, false otherwise. 
         */
        bool contains(const Edge<V>& edge) const {
            return this->contains(edge.getSource(), edge.getDestination());
        }

        /**
         * @brief Indicates whether there is a path from the source vertex to the destination vertex.
         * 
         * @param src The source vertex.
         * @param dest The destination vertex.
         * @return True if there is a path from the source vertex to the destination vertex, false otherwise. 
         */
        bool hasPath(const V& src, const V& dest) const {
            if(!this->contains(src) || !this->contains(dest))
                return false;

            int srcIndex = this->vertices.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertices.indexOf(Vertex<V>(dest), true);

            if(this->matrix[srcIndex][destIndex] == 1)
                return true;

            bool* arr = this->depthFirstSearch(Vertex<V>(src));
            bool res = arr[destIndex];
            delete[] arr;

            return res;
        }

        /**
         * @brief Adds a vertex to the graph.
         * 
         * @param label The label of the vertex to be added.
         */
        void addVertex(const V& label) {
            if(this->contains(label))
                return;

            this->vertices.addInOrder(Vertex<V>(label));

            if(this->length == 0) {
                this->matrix = new char*[1];
                this->matrix[0] = new char[1];
                this->matrix[0][0] = 0;
            } else {
                char** tmp = new char*[this->length + 1];
                for(int i = 0; i < this->length; i++) {
                    tmp[i] = new char[this->length + 1];
                    for(int j = 0; j < this->length; j++) 
                        tmp[i][j] = this->matrix[i][j];
                }

                this->deallocate();

                this->matrix = tmp;
                this->matrix[this->length] = new char[this->length + 1];
                for(int i = 0; i < this->length; i++) 
                    this->matrix[this->length][i] = this->matrix[i][this->length] = 0;

                this->matrix[this->length][this->length] = 0;
            }

            this->length++;
        }

        /**
         * @brief Adds a vertex to the graph.
         * 
         * @param vertex The vertex to be added.
         */
        void addVertex(const Vertex<V>& vertex) {
            this->addVertex(vertex.getLabel());
        }

        /**
         * @brief Removes a vertex from the graph.
         * 
         * @param label The label of the vertex to be removed.
         */
        void removeVertex(const V& label) {
            int index = this->vertices.indexOf(Vertex<V>(label), true);

            if(index == -1)
                return;

            this->vertices.pop(index);

            int** tmp = new int*[this->length - 1];
            for(int i = 0, j = 0; i < this->length; i++) {
                if(i != index) {
                    tmp[j] = new int[this->length - 1];
                    for(int k = 0, w = 0; k < this->length; k++) {
                        if(k != index) {
                            tmp[j][w] = this->matrix[i][k];
                            w++;
                        }
                    }
                    j++;
                }
            }

            this->deallocate();

            this->matrix = tmp;
            this->length--;
        }

        /**
         * @brief Adds an edge to the graph. if the 
         *        graph doesn't contain the given vertices,
         *        they will be added.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         */
        void addEdge(const V& src, const V& dest) {
            this->addVertex(src);
            this->addVertex(dest);

            int srcIndex = this->vertices.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertices.indexOf(Vertex<V>(dest), true);

            this->matrix[srcIndex][destIndex] = 1;

            if(!this->isDir)
                this->matrix[destIndex][srcIndex] = 1;
        }

        /**
         * @brief Adds an edge to the graph. if the 
         *        graph doesn't contain the given vertices,
         *        they will be added.
         * 
         * @param edge The edge to be added.
         */
        void addEdge(const Edge<V>& edge) {
            this->addEdge(edge.getSource(), edge.getDestination());
        }

        /**
         * @brief Adds an edge to the graph. if the
         *        graph doesn't contain the given vertices,
         *        they will be added.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         */
        void addEdge(const Vertex<V>& src, const Vertex<V>& dest) {
            this->addEdge(src.getLabel(), dest.getLabel());
        }

        /**
         * @brief Removes an edge from the graph.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         */
        void removeEdge(const V& src, const V& dest) {
            if(!this->contains(src, dest))
                return;

            int srcIndex = this->vertices.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertices.indexOf(Vertex<V>(dest), true);

            this->matrix[srcIndex][destIndex] = 0;

            if(!this->isDir)
                this->matrix[destIndex][srcIndex] = 0;
        }

        /**
         * @brief Returns the degree of the given vertex.
         * 
         * @param ver The vertex to get its degree.
         * @return Pair<int, int> The degree of the given vertex.
         */
        Pair<int, int> degree(const V& ver) const {
            if(!this->contains(ver))
                return Pair<int, int>(-1);

            int index = this->vertices.indexOf(Vertex<V>(ver), true);

            if(this->isDir) {
                int in = 0, out = 0;

                for(int i = 0; i < this->length; i++) {
                    if(this->matrix[index][i] == 1) out++;
                    if(this->matrix[i][index] == 1) in++;
                }

                return Pair<int, int>(in, out);
            } else {
                int degree = 0;
                for(int i = 0; i < this->length; i++) 
                    if(this->matrix[index][i] == 1) 
                        degree++;

                return Pair<int, int>(degree);
            }
        }

        /**
         * @brief Returns the degree list of the graph.
         * 
         * @return ArrayList<Pair<int, int>> The degree list of the graph.
         */
        ArrayList<Pair<int, int>> degreeList() const {
            ArrayList<Pair<int, int>> list;

            for(int i = 0; i < this->length; i++) 
                list.add(this->degree(this->vertices.get(i).getLabel()));

            return list;
        }

        /**
         * @brief Return the vertices list of the graph.
         * 
         * @return ArrayList<Vertex<V>> The vertices list of the graph.
         */
        ArrayList<Vertex<V>> getVertices() const {
            return this->vertices;
        }

        /**
         * @brief Returns the list of edges of the given vertex.
         * 
         * @param ver The vertex to get its edges.
         * @return ArrayList<Edge<V>> The list of edges of the given vertex.
         */
        ArrayList<Edge<V>> getEdges(const V& ver) const {
            if(!this->contains(ver))
                throw std::invalid_argument("Vertex not found.");

            ArrayList<Edge<V>> list;

            int idx = this->vertices.indexOf(Vertex<V>(ver), true);
            for(int i = 0; i < this->length; i++) {
                if(this->matrix[idx][i] == 1) {
                    Edge<V> edge(ver, this->vertices.get(i).getLabel());
                    edge.setDirect(this->isDir);
                    list.addInOrder(edge);
                }
            } 

            return list;
        }

        /**
         * @brief Return a map containing the edges for all
         *        vertices in the graph.
         * 
         * @return Map<Vertex<V>, ArrayList<Edge<V>>> A map containing the edges for all
         *                                            vertices in the graph.
         */
        Map<Vertex<V>, ArrayList<Edge<V>>> getEdges() const {
            Map<Vertex<V>, ArrayList<Edge<V>>> map;

            for(int i = 0; i < this->length; i++) 
                map.put(this->vertices.get(i), this->getEdges(this->vertices.get(i)));

            return map;
        }

        /**
         * @brief Returns the adjacent list of the graph.
         * 
         * @return Map<Vertex<V>, ArrayList<Vertex<V>>> The adjacent list of the graph.
         */
        Map<Vertex<V>, ArrayList<Vertex<V>>> adjacentList() const {
            Map<Vertex<V>, ArrayList<Vertex<V>>> adj;

            for(int i = 0; i < this->length; i++) {
                ArrayList<Vertex<V>> list;
                for(int j = 0; j < this->length; j++)
                    if(this->matrix[i][j] == 1)
                        list.addInOrder(this->vertices.get(j));

                adj.put(this->vertices.get(i), list);                
            }

            return adj;
        }

        /**
         * @brief Clears the graph by removing all vertices and edges.
         */
        void clear() {
            this->vertices.clear();
            this->deallocate();
            this->length = 0;
        }

        /**
         * @brief Clears all edges in the graph.
         */
        void clearEdges() {
            for(int i = 0; i < this->length; i++) 
                for(int j = 0; j < this->length; j++) 
                    this->matrix[i][j] = 0;
        }

        /**
         * @brief Overloaded stream insertion operator to print the graph.
         * 
         * @param strm The output stream.
         * @param graph The graph to be printed.
         * @return std::ostream& The output stream after printing the graph.
         */
        friend std::ostream& operator<<(std::ostream& strm, const MatrixGraph<V>& graph) {
            strm << "  ";
            for(int i = 0; i < graph.length; i++) 
                strm << graph.vertices.get(i) << " ";
            strm << std::endl;

            for(int i = 0; i < graph.length; i++) {
                strm << graph.vertices.get(i) << " ";
                for(int j = 0; j < graph.length; j++) 
                    strm << (int)graph.matrix[i][j] << " ";
                strm << std::endl;
            }

            return strm;
        }

        /**
         * @brief Returns a new graph there is a walk from the given vertex.
         * 
         * @param label The vertex to start walking.
         * @return MatrixGraph<V> A new graph there is a walk from the given vertex.
         */
        MatrixGraph<V> walk(const V& label) const {
            int line = this->vertices.indexOf(Vertex<V>(label), true);

            Map<Vertex<V>, bool> map;
            MatrixGraph<V> graph;
            Stack<Vertex<V>> stk;

            for(int i = 0; i < this->length; i++) {
                if(this->matrix[line][i] == 1) {
                    stk.push(this->vertices.get(i));
                    graph.addEdge(this->vertices.get(line), this->vertices.get(i));
                }
            }

            while(!stk.isEmpty()) {
                Vertex<V> ver = stk.pop();

                if(!map.contains(ver)) {
                    char* arr = this->matrix[this->vertices.indexOf(ver, true)];
                    for(int i = 0; i < this->length; i++) {
                        if(arr[i] == 1) {
                            stk.push(this->vertices.get(i));
                            graph.addEdge(ver, this->vertices.get(i));
                        }
                    }
                }

                map[ver] = true;
            }

            return graph;
        }

        /**
         * @brief Transpose a digraph.
         */
        void transpose() {
            if(this->isDir) {
                for(int i = 0; i < this->length; i++) {
                    for(int j = 0; j < this->length - i; j++) {
                        char tmp = this->matrix[i + j][i];
                        this->matrix[i + j][i] = this->matrix[i][i + j];
                        this->matrix[i][i + j] = tmp;
                    }
                }
            }
        }

        /**
         * @brief Returns a new graph that is the transpose of the given graph.
         * 
         * @return MatrixGraph<V> A new graph that is the transpose of the given graph.
         */
        MatrixGraph<V> getTranspose() const {
            MatrixGraph<V> graph = *this;
            graph.transpose();
            return graph;
        }

        /**
         * @brief Returns a ArrayList containing all the conex components of the graph.
         * 
         * @return ArrayList<MatrixGraph<V>> A list containing all the conex components of the graph.
         */
        ArrayList<MatrixGraph<V>> getConexComponents() {
            ArrayList<MatrixGraph<V>> list;

            for(int i = 0; i < this->length; i++) {
                MatrixGraph<V> graph = this->walk(this->vertices.get(i).getLabel());
                i += graph.size() - 1;
                list.add(graph);
            }

            return list;
        }

        /**
         * @brief Returns the number of conex components of the graph.
         * 
         * @return int The number of conex components of the graph.
         */
        int numberOfComponents() {
            int num = 0;

            for(int i = 0; i < this->length; i++) {
                MatrixGraph<V> graph = this->walk(this->vertices.get(i).getLabel());
                i += graph.size() - 1;
                num++;
            }

            return num;
        }
        
        /**
         * @brief Returns the clasp of the given vertex. The (+) clasp of a vertex v is the set of all vertices
         *        that are reachable from v in the graph. Also, the (-) clasp of a vertex v is the set of all
         *        vertices from which v is reachable in the graph.
         * 
         * @param label The label of the vertex to get its clasp.
         * @param type The type of the clasp. (+) for direct clasp and (-) for inverse clasp.
         * @return ArrayList<Vertex<V>> The clasp of the given vertex.
         */
        ArrayList<Vertex<V>> clasp(const V& label, const char& type = '+') const {
            if(!this->contains(label))
                throw std::invalid_argument("Vertex not found.");

            if(type != '+' && type != '-') 
                throw std::invalid_argument("Invalid type.");

            bool* arr = nullptr;
            ArrayList<Vertex<V>> list;
            if(type == '+') {
                arr = this->depthFirstSearch(Vertex<V>(label));
                for(int i = 0; i < this->length; i++) 
                    if(arr[i]) list.add(this->vertices.get(i));
            } else {
                MatrixGraph<V> graph = this->getTranspose();
                arr = graph.depthFirstSearch(Vertex<V>(label));
                for(int i = 0; i < graph.length; i++) 
                    if(arr[i]) list.add(graph.vertices.get(i));
            }

            delete[] arr;
            return list;
        }

        /**
         * @brief Returns the start and end times of the given vertex.
         * 
         * @param label The label of the vertex to get its times.
         * @return Map<Vertex<V>, Pair<int, int>> The start and end times of the given vertex.
         */
        Map<Vertex<V>, Pair<int, int>> times(const V& label) const {
            return this->times(Vertex<V>(label));
        }

        /**
         * @brief Returns the start and end times of the given vertex.
         * 
         * @param vertex The vertex to get its times.
         * @return Map<Vertex<V>, Pair<int, int>> The start and end times of the given vertex.
         */
        Map<Vertex<V>, Pair<int, int>> times(const Vertex<V>& vertex) const {
            ArrayList<Vertex<V>> list;
            Stack<Vertex<V>> aux;
            Map<Vertex<V>, Pair<int, int>> map;

            bool* arr = new bool[this->length];
            for(int i = 0; i < this->length; i++) 
                arr[i] = false;

            int time = 0;

            list.addInOrder(vertex);
            map[vertex] = Pair<int, int>(++time);
            arr[this->vertices.indexOf(vertex, true)] = true;
            while(!list.isEmpty()) {
                Vertex<V> tmp = list.shift();
                int idx = this->vertices.indexOf(tmp, true);

                aux.push(tmp);
                for(int i = 0; i < this->length; i++) {
                    if(this->matrix[idx][i] == 1 && !arr[i]) {
                        list.addInOrder(this->vertices.get(i));
                        map[this->vertices.get(i)] = Pair<int, int>(++time);
                        arr[i] = true;
                    } 
                }
            }

            while(!aux.isEmpty())
                map[aux.pop()].value = ++time;

            delete[] arr;
            return map;
        }

        /**
         * @brief Returns the strongly connected components of the graph.
         * 
         * @return ArrayList<MatrixGraph<V>> The strongly connected components of the graph.
         */
        ArrayList<MatrixGraph<V>> tarjan() const {
            Tarjan<V> tarjan(*this);
            return tarjan.getScc();
        }

        /**
         * @brief Returns the DepthFirstOrder of the graph.
         * 
         * @return DepthFirstOrder<V> The topological order of the graph.
         */
        DepthFirstOrder<V> depthFirstOrder() const {
            return DepthFirstOrder<V>(*this);
        }

        int dist(const V& src, const V& dest) {
            if(!this->contains(src) || !this->contains(dest))
                throw std::invalid_argument("Vertex not found.");

            return this->dist(Vertex<V>(src), Vertex<V>(dest));
        }

        int dist(const Vertex<V>& src, const Vertex<V>& dest) {
            if(!this->contains(src) || !this->contains(dest))
                throw std::invalid_argument("Vertex not found.");

            PriorityQueue<Pair<int, Vertex<V>>> queue;

            bool* arr = new bool[this->length];
            for(int i = 0; i < this->length; i++)
                arr[i] = false;
            
            queue.push(Pair<int, Vertex<V>>(0, src, true));
            arr[this->vertices.indexOf(src, true)] = true;

            Pair<int, Vertex<V>> tmp = Pair<int, Vertex<V>>(0, src, true);
            while(!queue.isEmpty() && tmp.value != dest) {
                tmp = queue.pop();

                int idx = this->vertices.indexOf(tmp.value, true);
                for(int i = 0; i < this->length; i++) {
                    if(this->matrix[idx][i] == 1 && !arr[i]) {
                        queue.push(Pair<int, Vertex<V>>(tmp.key + 1, this->vertices.get(i), true));
                        arr[i] = true;
                    }
                }
            }

            delete[] arr;
            return queue.isEmpty() && tmp.value != dest ? -1 : tmp.key;
        }
};

/**
 * @brief Checks if the given graph is complete.
 * 
 * @tparam V The type of the vertex label.
 * @param graph The graph to check.
 * @return True if the graph is complete, false otherwise.
 */
template <class V> bool isComplete(const MatrixGraph<V>& graph) {
    ArrayList<Pair<int, int>> list = graph.degreeList();

    bool eq = !list.isEmpty();
    int expectedEdges = graph.size() - 1;
    for(int i = 0; eq && i < list.size(); i++) {
        if(graph.isDigraph()) 
            eq = list[i].first() + list[i].second() == expectedEdges;
        else 
            eq = list[i].first() == expectedEdges;
    }

    return eq;
}

/**
 * @brief Checks if the given graph is regular.
 * 
 * @tparam V The type of the vertex label.
 * @param graph The graph to check.
 * @return True if the graph is regular, false otherwise.
 */
template <class V> bool isRegular(const MatrixGraph<V>& graph) {
    ArrayList<Pair<int, int>> list = graph.degreeList();

    bool eq = !list.isEmpty();
    for(int i = 0; eq && i < list.size(); i++)
        eq = list[0] == list[i];

    return eq;
}

/**
 * @brief Checks if the given graph is bipartite.
 * 
 * @tparam V The type of the vertex label.
 * @param graph The graph to check.
 * @return True if the graph is bipartite, false otherwise.
 */
template <class V> bool isBipartite(const MatrixGraph<V>& graph) {
    ArrayList<Vertex<V>> vertices = graph.getVertices();
    Map<Vertex<V>, bool> colors;

    for(int i = 0; i < vertices.size(); i++) {
        if(!colors.contains(vertices[i])) {
            colors[vertices[i]] = true;
            Queue<Vertex<V>> queue;
            queue.push(vertices[i]);

            while(!queue.isEmpty()) {
                Vertex<V> vertex = queue.pop();

                for(int j = 0; j < graph.size(); j++) {
                    if(graph[vertex][j] == 1) {
                        if(!colors.contains(vertices[j])) {
                            colors[vertices[j]] = !colors[vertex];
                            queue.push(vertices[j]);
                        } else if(colors[vertices[j]] == colors[vertex]) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

#endif
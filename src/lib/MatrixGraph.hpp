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

#include <iostream>
#include <stdexcept>

#include "ArrayList.hpp"
#include "Map.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

#include "helpers/Edge.hpp"
#include "helpers/Vertex.hpp"

/**
 * @brief A template class implementing a graph data structure using an adjacency matrix.
 * 
 * @tparam V The type of the vertex label.
 */
template <class V> class MatrixGraph {
    private:
        char** matrix;                      ///< The adjacency matrix.
        ArrayList<Vertex<V>> vertexes;      ///< The vertexes of the graph.
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
         * @brief Returns the given vertex's line in the adjacency matrix.
         * 
         * @param vertex The vertex to get its line.
         * @return char* The vertex's line in the adjacency matrix.
         */
        char* operator[](const Vertex<V>& vertex) const {
            int index = this->vertexes.indexOf(vertex, true);

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
            return this->vertexes.contains(Vertex<V>(label), true);
        }

        /**
         * @brief Indicates whether the graph contains the given edge.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         * @return True if the graph contains the given edge, false otherwise.
         */
        bool contains(const V& src, const V& dest) const {
            int srcIndex = this->vertexes.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertexes.indexOf(Vertex<V>(dest), true);

            if(srcIndex != -1 && destIndex != -1) 
                return this->matrix[srcIndex][destIndex] != 0;

            return false;
        }

        /**
         * @brief Adds a vertex to the graph.
         * 
         * @param label The label of the vertex to be added.
         */
        void addVertex(const V& label) {
            if(this->contains(label))
                return;

            this->vertexes.addInOrder(Vertex<V>(label));

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
         * @brief Removes a vertex from the graph.
         * 
         * @param label The label of the vertex to be removed.
         */
        void removeVertex(const V& label) {
            int index = this->vertexes.indexOf(Vertex<V>(label), true);

            if(index == -1)
                return;

            this->vertexes.pop(index);

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
         *        graph doesn't contain the given vertexes,
         *        they will be added.
         * 
         * @param src The source vertex of the edge.
         * @param dest The destination vertex of the edge.
         */
        void addEdge(const V& src, const V& dest) {
            this->addVertex(src);
            this->addVertex(dest);

            int srcIndex = this->vertexes.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertexes.indexOf(Vertex<V>(dest), true);

            this->matrix[srcIndex][destIndex] = 1;

            if(!this->isDir)
                this->matrix[destIndex][srcIndex] = 1;
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

            int srcIndex = this->vertexes.indexOf(Vertex<V>(src), true), 
                destIndex = this->vertexes.indexOf(Vertex<V>(dest), true);

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
                return -1;

            int index = this->vertexes.indexOf(Vertex<V>(ver));

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
                    if(this->matrix[index][i] != 0) 
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
                list.add(this->degree(this->vertexes.get(i).getLabel()));

            return list;
        }

        /**
         * @brief Return the vertexes list of the graph.
         * 
         * @return ArrayList<Vertex<V>> The vertexes list of the graph.
         */
        ArrayList<Vertex<V>> getVertexes() const {
            return this->vertexes;
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

            int idx = this->vertexes.indexOf(Vertex<V>(ver), true);
            for(int i = 0; i < this->length; i++) 
                if(this->matrix[idx][i] == 1) 
                    list.addInOrder(Edge<V>(Vertex<V>(ver), this->vertexes.get(i)));

            return list;
        }

        /**
         * @brief Return a map containing the edges for all
         *        vertexes in the graph.
         * 
         * @return Map<Vertex<V>, ArrayList<Edge<V>>> A map containing the edges for all
         *                                            vertexes in the graph.
         */
        Map<Vertex<V>, ArrayList<Edge<V>>> getEdges() const {
            Map<Vertex<V>, ArrayList<Edge<V>>> map;

            for(int i = 0; i < this->length; i++) 
                map.put(this->vertexes.get(i), this->getEdges(this->vertexes.get(i)));

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
                        list.addInOrder(this->vertexes.get(j));

                adj.put(this->vertexes.get(i), list);                
            }

            return adj;
        }

        /**
         * @brief Clears the graph by removing all vertexes and edges.
         */
        void clear() {
            this->vertexes.clear();
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
                strm << graph.vertexes.get(i) << " ";
            strm << std::endl;

            for(int i = 0; i < graph.length; i++) {
                strm << graph.vertexes.get(i) << " ";
                for(int j = 0; j < graph.length; j++) 
                    strm << (int)graph.matrix[i][j] << " ";
                strm << std::endl;
            }

            return strm;
        }

        int countComp() {

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
    ArrayList<Vertex<V>> vertexes = graph.getVertexes();
    Map<Vertex<V>, bool> colors;

    for(int i = 0; i < vertexes.size(); i++) {
        if(!colors.contains(vertexes[i])) {
            colors[vertexes[i]] = true;
            Queue<Vertex<V>> queue;
            queue.push(vertexes[i]);

            while(!queue.isEmpty()) {
                Vertex<V> vertex = queue.pop();

                for(int j = 0; j < graph.size(); j++) {
                    if(graph[vertex][j] == 1) {
                        if(!colors.contains(vertexes[j])) {
                            colors[vertexes[j]] = !colors[vertex];
                            queue.push(vertexes[j]);
                        } else if(colors[vertexes[j]] == colors[vertex]) {
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
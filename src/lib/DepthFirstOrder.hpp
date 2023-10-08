#ifndef DEPTH_FIRST_ORDER_HPP
#define DEPTH_FIRST_ORDER_HPP

#include <iostream>
#include <stdexcept>

#include "ArrayList.hpp"
#include "Graph.hpp"
#include "MatrixGraph.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

#include "helpers/Vertex.hpp"
#include "helpers/Edge.hpp"

template <class V> class DepthFirstOrder {
    private:
        Queue<Vertex<V>> pre;           ///< Queue of vertices in preorder.
        Queue<Vertex<V>> post;          ///< Queue of vertices in postorder.
        Stack<Vertex<V>> reversePost;   ///< Stack of vertices in reverse postorder.

        ArrayList<Vertex<V>> vertices;  ///< List of vertices in the graph.
        bool* visited;                  ///< Array of booleans indicating whether a vertex has been visited.

        void dfs(const MatrixGraph<V>& graph, const Vertex<V>& vertex) {
            pre.push(vertex);
            
            this->visited[this->vertices.indexOf(vertex, true)] = true;
            char* arr = graph[vertex];

            for(int i = 0; i < graph.size(); i++)
                if(arr[i] != 0 && !this->visited[i])
                    this->dfs(graph, this->vertices.get(i));

            post.push(vertex);
            reversePost.push(vertex);
        }

        void dfs(const Graph<V>& graph, const Vertex<V>& vertex) {
            pre.push(vertex);

            this->visited[this->vertices.indexOf(vertex, true)] = true;
            ArrayList<Edge<V>> list = graph.getEdges(vertex);
            for(int i = 0; i < list.size(); i++)
                if(!this->visited[this->vertices.indexOf(list[i].getDestination(), true)])
                    this->dfs(graph, list[i].getDestination());

            post.push(vertex);
            reversePost.push(vertex);
        }

    public:
        DepthFirstOrder(const MatrixGraph<V>& graph) {
            this->vertices = graph.getVertices();
            this->visited = new bool[this->vertices.size()];

            for(int i = 0; i < this->vertices.size(); i++) 
                this->visited[i] = false;

            for(int i = 0; i < this->vertices.size(); i++) 
                if(!this->visited[i]) 
                    this->dfs(graph, this->vertices.get(i));
        }

        DepthFirstOrder(const Graph<V>& graph) {
            this->vertices = graph.getVertices();
            this->visited = new bool[this->vertices.size()];

            for(int i = 0; i < this->vertices.size(); i++) 
                this->visited[i] = false;

            for(int i = 0; i < this->vertices.size(); i++) 
                if(!this->visited[i]) 
                    this->dfs(graph, this->vertices.get(i));
        }

        ~DepthFirstOrder() { 
            delete[] this->visited; 
        }

        Queue<Vertex<V>> getPre() const { 
            return this->pre; 
        }
        
        Queue<Vertex<V>> getPost() const { 
            return this->post; 
        }
        
        Stack<Vertex<V>> getReversePost() const { 
            return this->reversePost; 
        }
};

#endif
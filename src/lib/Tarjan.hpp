#ifndef TARJAN_HPP
#define TARJAN_HPP

#include "helpers/Edge.hpp"
#include "helpers/Vertex.hpp"

#include "datastructs/ArrayList.hpp"
#include "MatrixGraph.hpp"

template <class V> class Tarjan {
    private:
        int* ids;
        int* lowLink;
        bool* onStack;
        
        MatrixGraph<V> graph;
        ArrayList<Vertex<V>> vertices;
        Stack<int> stk;

        int time = 0;
        int scc = 0;

        void dfs(int i) {
            stk.push(i);
            onStack[i] = true;
            ids[i] = lowLink[i] = time++;

            for(int j = 0; j < graph.size(); j++) {
                if(graph[i][j] == 1) {
                    if(ids[j] == -1) 
                        dfs(j);
                    if(onStack[j]) 
                        lowLink[i] = lowLink[i] < lowLink[j] ? lowLink[i] : lowLink[j];
                } 
            }

            if(ids[i] == lowLink[i]) {
                int v;
                do {
                    v = stk.pop();
                    onStack[v] = false;
                    lowLink[v] = ids[i];
                } while(v != i);
                scc++;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Tarjan<V>& tarjan) {
            os << "Tarjan's algorithm" << std::endl;
            os << "Strongly connected components: " << tarjan.scc << std::endl;
            os << "Low link: ";
            for(int i = 0; i < tarjan.vertices.size(); i++) 
                os << tarjan.lowLink[i] << " ";
            os << std::endl;
            os << "Ids: ";
            for(int i = 0; i < tarjan.vertices.size(); i++) 
                os << tarjan.ids[i] << " ";
            os << std::endl;
            return os;
        }

    public:

        Tarjan(const MatrixGraph<V>& graph) {
            this->graph = graph;
            this->vertices = graph.getVertices();
            this->ids = new int[graph.size()];
            this->lowLink = new int[graph.size()];
            this->onStack = new bool[graph.size()];

            for(int i = 0; i < graph.size(); i++) {
                this->ids[i] = -1;
                this->lowLink[i] = 0;
                this->onStack[i] = false;
            }

            for(int i = 0; i < graph.size(); i++) 
                if(this->ids[i] == -1) 
                    this->dfs(i);
        }

        ~Tarjan() {
            delete[] ids;
            delete[] lowLink;
            delete[] onStack;
        }

        int* getLowLink() {
            return this->lowLink;
        }

        int* getIds() {
            return this->ids;
        }

        int getScc() const {
            return this->scc;
        }

        ArrayList<MatrixGraph<V>> getScc() {
            ArrayList<MatrixGraph<V>> components;

            for(int i = 0; i < this->scc; i++) {
                MatrixGraph<V> component(true);
                for(int j = 0; j < this->vertices.size(); j++) {
                    if(this->lowLink[j] == i) {
                        component.addVertex(this->vertices[j]);

                        for(int k = 0; k < this->vertices.size(); k++) 
                            if(this->lowLink[k] == i && this->graph[j][k] == 1) 
                                component.addEdge(this->vertices[j], this->vertices[k]);

                    }
                }

                components.add(component);
            }

            return components;
        }
};

#endif
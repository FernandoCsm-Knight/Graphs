#ifndef STRONGLY_CONNECTED_COMPONENTS_HPP
#define STRONGLY_CONNECTED_COMPONENTS_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/Stack.hpp"
#include "../helpers/Arithmatic.hpp"

template <class V> class Graph;

template <class V> class StronglyConnectedComponents {
    private:
        const Graph<V>& graph;

    public:
        explicit StronglyConnectedComponents(const Graph<V>& graph) : graph(graph) {}

        ArrayList<ArrayList<V>> stronglyConnectedComponents() const {
            if(!graph.isDigraph()) throw std::invalid_argument("The graph hasn't strongly connected components because is not directed.");

            int id = 0;
            Map<V, int> ids;
            Map<V, int> lowLink;
            Map<V, bool> onStack;

            Stack<V> stack;
            Stack<V> dfsStack;
            ArrayList<V> vertices = graph.vertices();
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

                        for(const V& w : graph[u]) {
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
};

#endif
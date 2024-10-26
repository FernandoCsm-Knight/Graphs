#ifndef DEPTH_FIRST_SEARCH_HPP
#define DEPTH_FIRST_SEARCH_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../datastructs/Stack.hpp"

#include "../helpers/Pair.hpp"
#include "../helpers/Path.hpp"

template <class V> class Graph;

template <class V> class DepthFirstSearch {
    private:
        const Graph<V>& graph;
        Map<V, Pair<int, int>> map;
        ArrayList<V> clp;

    public:
        explicit DepthFirstSearch(const Graph<V>& graph): graph(graph) {}

        inline ArrayList<V> clasp() const { return this->clp; }
        inline Map<V, Pair<int, int>> times() const { return this->map; }

        void calculate(const V& vertex) {
            Set<V> visited;
            map.clear();
            clp.clear();

            Stack<V> stack;
            stack.push(vertex);
            visited.add(vertex);

            int time = 0;
            while(!stack.isEmpty()) {
                V v = stack.peek();
                clp.add(v);
                
                if(!map.contains(v))
                    map.put(v, Pair<int, int>(++time));

                bool done = true;
                for(const V& u : graph[v]) {
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
        }
};

#endif
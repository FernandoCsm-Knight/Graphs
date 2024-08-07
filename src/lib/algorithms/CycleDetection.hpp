#ifndef CYCLE_DETECTION_HPP
#define CYCLE_DETECTION_HPP

#include "../datastructs/Map.hpp"
#include "../datastructs/Set.hpp"
#include "../types/CycleDetectionType.hpp"
#include "../helpers/Arithmatic.hpp"

template <class V> class Graph;

template <class V> class CycleDetection {
    private:
        const Map<V, Set<V>> adj;

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

        

    public:
        explicit CycleDetection(const Graph<V> &graph) : adj(graph.adjacencyList()) {}
        
        ArrayList<ArrayList<V>> permutationCycles(bool isomorphic) const {
            ArrayList<ArrayList<V>> uniqueCycles;
            
            for(int i = 3; i <= adj.size(); ++i) {
                ArrayList<ArrayList<V>> perms = art::arrangements<V>(adj.keys(), i);

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
};

#endif
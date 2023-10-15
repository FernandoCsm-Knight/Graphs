#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/ArrayList.hpp"
#include "lib/helpers/Pair.hpp"
#include "lib/datastructs/LinkedList.hpp"
#include "lib/datastructs/Map.hpp"
#include "lib/datastructs/RBTree.hpp"
#include "lib/helpers/Edge.hpp"
#include "lib/helpers/Vertex.hpp"
#include "lib/MatrixGraph.hpp"
#include "lib/datastructs/Set.hpp"
#include "lib/Tarjan.hpp"
#include "lib/datastructs/MinHeap.hpp"
#include "lib/datastructs/PriorityQueue.hpp"
#include "lib/datastructs/HashSet.hpp"
#include "lib/datastructs/HashMap.hpp"

using std::string;

int main() {
    HashMap<string, int> map;

    map.insert("a", 1);
    map.insert("b", 2);
    map.insert("c", 3);
    map.insert("d", 4);
    map.insert("e", 5);
    map.insert("f", 6);
    map.insert("g", 7);
    map.insert("h", 8);
    map.insert("i", 9);
    map.insert("j", 10);
    map.insert("k", 11);
    map.insert("l", 12);

    std::cout << map << std::endl;
}

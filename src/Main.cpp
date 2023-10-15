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

using std::string;

int main() {
    HashSet<int> hash;

    for(int i = 0; i < 100; i++) 
        hash.insert(i);

    std::cout << hash << std::endl;
}

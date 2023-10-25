# Graph Theory and Computability

### Author: Fernando Campos Silva Dal Maria

## Description

This repository contains the implementation of some graph algorithms and data structures. The main purpose of this project is to learn about graph theory and its applications. You will find the following directory structure:

```bash
.
│
├── graph.json
├── LICENSE
├── makefile
├── README.md
├── bin
│   └── main
├── obj
│   └── Main.o
└── src
    ├── lib
    │   ├── datastructs
    │   │   ├── ArrayList.hpp
    │   │   ├── HashMap.hpp
    │   │   ├── HashSet.hpp
    │   │   ├── IndexedPriorityQueue.hpp
    │   │   ├── iterators
    │   │   │   ├── ArrayIterator.hpp
    │   │   │   └── LinkedListIterator.hpp
    │   │   ├── LinkedList.hpp
    │   │   ├── Map.hpp
    │   │   ├── MinHeap.hpp
    │   │   ├── PriorityQueue.hpp
    │   │   ├── Queue.hpp
    │   │   ├── RBTree.hpp
    │   │   ├── Set.hpp
    │   │   ├── Stack.hpp
    │   │   └── UnionFind.hpp
    │   ├── DepthFirstOrder.hpp
    │   ├── Graph.hpp
    │   ├── helpers
    │   │   ├── Edge.hpp
    │   │   ├── Node.hpp
    │   │   ├── Pair.hpp
    │   │   ├── Path.hpp
    │   │   └── Vertex.hpp
    │   ├── MatrixGraph.hpp
    │   ├── Tarjan.hpp
    │   └── test
    │       ├── DigraphTest.hpp
    │       ├── GraphDijkstraTest.hpp
    │       ├── GraphTest.hpp
    │       ├── MinimunSpanningTreeTest.hpp
    │       ├── TestBuilder.hpp
    │       └── Test.hpp
    ├── log
    │   └── test.log
    └── Main.cpp
```

the `src` directory contains the source code of the project, the `lib` directory contains the implementation of the data structures and algorithms, and the `test` directory contains the unit tests. The `bin` directory contains the executable file and the `obj` directory contains the object files. Furthermore, the `graph.json` file contains the graph that is used in the unit tests and the `log` directory contains the log file of the unit tests. Finally, the `makefile` contains the instructions to compile the project.

## Usage

To compile the project, you need to run the following command:

```bash
make
```

To run the unit tests, you need to run the following command:

```bash
make run
```

To clean the project, you need to run the following command:

```bash
make clean
```

To rebuild the project, you need to run the following command:

```bash
make rerun
```

To run the valgrind tool, you need to run the following command:

```bash
make valgrind
```

## Data Structures

The following data structures are implemented:

- [ArrayList](src/lib/datastructs/ArrayList.hpp)
- [HashMap](src/lib/datastructs/HashMap.hpp)
- [HashSet](src/lib/datastructs/HashSet.hpp)
- [IndexedPriorityQueue](src/lib/datastructs/IndexedPriorityQueue.hpp)
- [LinkedList](src/lib/datastructs/LinkedList.hpp)
- [Map](src/lib/datastructs/Map.hpp)
- [MinHeap](src/lib/datastructs/MinHeap.hpp)
- [PriorityQueue](src/lib/datastructs/PriorityQueue.hpp)
- [Queue](src/lib/datastructs/Queue.hpp)
- [RBTree](src/lib/datastructs/RBTree.hpp)
- [Set](src/lib/datastructs/Set.hpp)
- [Stack](src/lib/datastructs/Stack.hpp)
- [UnionFind](src/lib/datastructs/UnionFind.hpp)

## Algorithms

The following algorithms are implemented:

- [Depth First Order](src/lib/DepthFirstOrder.hpp)
- [Cycle Detection](src/lib/Graph.hpp)
- [Breadth First Search](src/lib/Graph.hpp)
- [Depth First Search](src/lib/Graph.hpp)
- [Dijkstra](src/lib/Graph.hpp)
- [Prim - MST](src/lib/Graph.hpp)
- [Tarjan - Strongly Connected Components](src/lib/Tarjan.hpp)

## References

- [Algorithms, 4th Edition](https://algs4.cs.princeton.edu/home/)
- [Introduction to Algorithms, 4th Edition](https://mitpress.ublish.com/book/introduction-to-algorithms-4)
- [Algorithm Design](https://www.cs.princeton.edu/~wayne/kleinberg-tardos/)
- [Introduction to Graph Theory](https://www.pearson.com/en-us/subject-catalog/p/introduction-to-graph-theory/P200000005756/9780273728894)
- [Grokking Algorithms](https://www.oreilly.com/library/view/grokking-algorithms/9781617292231/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

# Graph Theory and Computability

### Author: Fernando Campos Silva Dal Maria

![Eulerian Graph Image](/src/scripts/assets/graph_visualization.png)

## Description

This repository contains the implementation of some graph algorithms and data structures. The main purpose of this project is to learn about graph theory and its applications. You will find the following directory structure:

```bash
.
├── lib
│   ├── algorithms
│   │   ├── BreathFirstSearch.hpp
│   │   ├── CycleDetection.hpp
│   │   ├── DepthFirstSearch.hpp
│   │   ├── MinimumSpanningTree.hpp
│   │   ├── ShortestPath.hpp
│   │   └── StronglyConnectedComponents.hpp
│   ├── datastructs
│   │   ├── ArrayList.hpp
│   │   ├── HashMap.hpp
│   │   ├── HashSet.hpp
│   │   ├── IndexedPriorityQueue.hpp
│   │   ├── iterators
│   │   │   ├── ArrayIterator.hpp
│   │   │   └── LinkedListIterator.hpp
│   │   ├── LinkedList.hpp
│   │   ├── Map.hpp
│   │   ├── MinHeap.hpp
│   │   ├── PriorityQueue.hpp
│   │   ├── Queue.hpp
│   │   ├── RBTree.hpp
│   │   ├── Set.hpp
│   │   ├── Stack.hpp
│   │   └── UnionFind.hpp
│   ├── Graph.hpp
│   ├── helpers
│   │   ├── Arithmatic.hpp
│   │   ├── Edge.hpp
│   │   ├── GraphGenerator.hpp
│   │   ├── Node.hpp
│   │   ├── Pair.hpp
│   │   ├── Path.hpp
│   │   ├── StopWatch.hpp
│   │   └── Vertex.hpp
│   └── types
│       ├── CycleDetectionType.hpp
│       ├── GraphTypes.hpp
│       ├── MinimumSpanningTreeType.hpp
│       └── Numeric.hpp
├── Main.cpp
└── scripts
    ├── assets
    │   ├── graph_drawer_logo.png
    │   └── graph_visualization.png
    ├── graph_drawer.py
    └── graph_visualizer.py
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

- [Cycle Detection](src/lib/algorithms/CycleDetection.hpp)
- [Breadth First Search](src/lib/algorithms/BreathFirstSearch.hpp)
- [Depth First Search](src/lib/algorithms/DepthFirstSearch.hpp)
- [Union Find Connected Components](src/lib/Graph.hpp)
- [Floyd Warshall](src/lib/algorithms/ShortestPath.hpp)
- [Dijkstra](src/lib/algorithms/ShortestPath.hpp)
- [Bellman Ford](src/lib/algorithms/ShortestPath.hpp)
- [Prim - MST](src/lib/algorithms/MinimumSpanningTree.hpp)
- [Kruskal - MST](src/lib/algorithms/MinimumSpanningTree.hpp)
- [Tarjan - Strongly Connected Components](src/lib/algorithms/StronglyConnectedComponents.hpp)
- [Topological Sort](src/lib/Graph.hpp)
- [Visitation Time](src/lib/Graph.hpp)

## Dependencies

This project depends on the nlohmann/json library for JSON parsing. You can find the library on GitHub: [nlohmann/json](https://github.com/nlohmann/json).

### Installing the nlohmann/json library

To install the nlohmann/json library, you need to run the following commands:

#### Linux

At ubuntu, you can install the library using the following command:

```bash
sudo apt install nlohmann-json3-dev
```
At Fedora, you can install the library using the following command:

```bash
sudo dnf install nlohmann-json-devel
```

At Arch Linux, you can install the library using the following command:

```bash
sudo pacman -S nlohmann-json
```

#### macOS

At macOS, you can install the library using the following command:

```bash
brew install nlohmann-json
```

#### Windows

At Windows, you can install the library using the following command:

```bash
vcpkg install nlohmann-json
```

This project also include some python scripts to enable visualization and some facilities.

### Installing Python Libraries

The following Python libraries are used in the project:

- [networkx](https://networkx.org/)
- [matplotlib](https://matplotlib.org/)
- [numpy](https://numpy.org/)
- [pygame](https://www.pygame.org/)

To install the libraries, you need to run the following command:

```bash
pip install networkx matplotlib numpy pygame
```

If you are using the `conda` package manager, you can install the libraries using the following command:

```bash
conda install networkx matplotlib numpy pygame
```

## Graph Visualization

The project contains a Python script that generates a graph visualization using the `networkx` and `matplotlib` libraries. The script reads a JSON file containing the graph and generates a visualization of the graph. The script is located in the `src/scripts` directory. You can plot the graph using the `plot()` method at a Graph object.

The Graph class contains a method that generates a JSON file containing the graph. The method is called `toJSON` and is located in the `Graph.hpp` file. 

## Graph Drawer

Another python script allows you to draw a graph and import it to the program. To use this script, you need to run the `draw()` method at a graph object that will automatically import the drawn graph when you close the window.

### How to use the Graph Drawer

- **Create vertex:** Left click on the screen to create a vertex.
- **Create edge:** Right click on a source vertex and right click on a target vertex to create an edge.
- **Delete vertex or edge:** Click the middle button on a vertex or edge to delete it.
- **Move vertex:** Click and drag a vertex to move it.
- **Change vertex label:** Press 'e' on a vertex to change its label.
- **Change edge weight:** Press 'e' on an edge to change its weight.

## References

- [Algorithms, 4th Edition](https://algs4.cs.princeton.edu/home/)
- [Introduction to Algorithms, 4th Edition](https://mitpress.ublish.com/book/introduction-to-algorithms-4)
- [Algorithm Design](https://www.cs.princeton.edu/~wayne/kleinberg-tardos/)
- [Introduction to Graph Theory](https://www.pearson.com/en-us/subject-catalog/p/introduction-to-graph-theory/P200000005756/9780273728894)
- [Grokking Algorithms](https://www.oreilly.com/library/view/grokking-algorithms/9781617292231/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

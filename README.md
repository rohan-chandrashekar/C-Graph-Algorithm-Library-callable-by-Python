# Generic Graph Library in C++ with Python Integration

Welcome to the **Generic Graph Library**, a high-performance, flexible C++ library for graph data structures and algorithms, now fully integrated with Python! This library empowers you to build and manipulate complex graphs with ease, leveraging the speed of C++ and the versatility of Python. Whether you are working on academic research, solving complex network problems, or just exploring graph theory, this library has you covered.

## 🚀 Features at a Glance

### 🧩 **1. Versatile Graph Structures**
- **Directed & Undirected Graphs**: Effortlessly switch between directed and undirected graphs to suit your problem requirements.
- **Generic Node & Edge Types**: Define your own types for nodes and edges, making the library adaptable to a wide range of applications.

### 🧠 **2. Powerful Graph Algorithms**
- **Node & Edge Coloring**: Easily solve graph coloring problems with our efficient algorithms.
- **Cycle Detection**: Detect cycles in your graphs, helping in applications like dependency resolution.
- **Connected Components**: Identify all connected components within your graph—essential for network analysis.
- **Katz Centrality**: Measure the influence of nodes in your network using Katz centrality, a key metric in social network analysis.
- **Minimum Spanning Tree**:
  - **Prim’s Algorithm**: Find the minimum spanning tree using Prim’s greedy approach.
  - **Kruskal’s Algorithm**: Alternatively, use Kruskal’s algorithm for edge-centric MST computation.
- **Graph Traversal**:
  - **Iterative Depth-First Search (DFS)**: Traverse graphs iteratively without risking stack overflow.
  - **Uniform Cost Search (UCS)**: Find the least-cost path between nodes.
  - **A* Search**: Implement heuristic-based search for optimal pathfinding in weighted graphs.

### 🛠️ **3. Seamless Python Integration**
- **Python Bindings via Pybind11**: Call C++ functions directly from Python, combining the performance of C++ with the flexibility of Python.
- **Comprehensive API**: Create, manipulate, and analyze graphs in Python using an intuitive API.

## 🛠️ Installation

### Prerequisites

- **C++11 (or later)**: A C++ compiler that supports C++11 or later.
- **Python 3.x**: Ensure Python is installed on your system.
- **Pybind11**: Install the necessary Python bindings with:
  \`\`\`bash
  pip install pybind11
  \`\`\`

### Build Instructions

1. **Clone the Repository**:
   \`\`\`bash
   git clone https://github.com/rohan-chandrashekar/generic-graph-library.git
   cd generic-graph-library
   \`\`\`

2. **Compile the Library**:
   \`\`\`bash
   mkdir build
   cd build
   cmake ..
   make
   \`\`\`

3. **Run Python Test Scripts**:
   \`\`\`bash
   python ../test_1.py
   python ../test_2.py
   # Continue with other test scripts
   \`\`\`

## 🎯 Usage Examples

### C++ Example

Here’s a simple example to get started with the library in C++:

\`\`\`cpp
#include "graph.h"

int main() {
    Graph<std::string, int> g(false); // Create an undirected graph
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 1);
    g.addEdge("B", "C", 2);

    auto mst = g.primMST();
    for (const auto& edge : mst) {
        std::cout << edge.getSource() << " - " << edge.getDestination() << " : " << edge.getWeight() << std::endl;
    }

    return 0;
}
\`\`\`

### Python Example

Here’s how you can use the library from Python:

\`\`\`python
import graphlib

# Create an undirected graph
g = graphlib.Graph(False)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")

# Add edges
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 2)

# Run algorithms
connected_components = g.connectedComponents()
katz_centrality = g.katzCentrality(0.1, 1)
prim_mst = g.primMST()

# Print results
print("Connected Components:", connected_components)
print("Katz Centrality:", katz_centrality)
print("Prim's MST:", [(e.getSource(), e.getDestination(), e.getWeight()) for e in prim_mst])
\`\`\`

## 📂 Repository Structure

- **\`src/\`**: Contains the C++ source code for the core graph library.
- **\`include/\`**: Header files for the graph library.
- **\`tests/\`**: Python test scripts to demonstrate and validate the library's functionality.
- **\`CMakeLists.txt\`**: Configuration for building the project with CMake.
- **\`README.md\`**: The documentation you are currently reading.


## 🌟 Acknowledgments

- **Pybind11**: For enabling seamless C++ and Python integration.
- **C++ Standard Library**: Providing robust and efficient data structures and algorithms.

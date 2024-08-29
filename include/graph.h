#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdexcept>
#include <queue>
#include <stack>

template <typename T, typename W>
class Edge {
public:
    Edge(const T& src, const T& dest, const W& weight);
    T getSource() const;
    T getDestination() const;
    W getWeight() const;
    bool operator<(const Edge<T, W>& other) const;
    bool operator==(const Edge& other) const {
    return this->source == other.source && this->destination == other.destination && this->weight == other.weight;
}


private:
    T source;
    T destination;
    W weight;
};

template <typename T, typename W>
struct EdgeHash {
    std::size_t operator()(const Edge<T, W>& edge) const {
        std::hash<T> hashFn;
        return hashFn(edge.getSource()) ^ hashFn(edge.getDestination());
    }
};

template <typename T, typename W>
class Graph {
public:
    Graph(bool directed);
    void addNode(const T& data);
    void addEdge(const T& src, const T& dest, const W& weight = W());
    bool hasCycle() const;
    std::vector<Edge<T, W>> primMST() const;
    std::vector<Edge<T, W>> kruskalMST() const;
    T find(const T& x, std::unordered_map<T, T>& parent) const;
    void unionByRank(const T& x, const T& y, std::unordered_map<T, int>& rank, std::unordered_map<T, T>& parent) const;
    std::vector<int> nodeColoring() const;
    std::vector<int> edgeColoring() const;
    std::vector<std::vector<T>> connectedComponents() const;
    std::vector<double> katzCentrality(double alpha, double beta) const;

private:
    bool directed;
    std::unordered_map<T, std::vector<Edge<T, W>>> adjList;
    bool hasCycleDFS(const T& node, std::unordered_map<T, T>& parent) const;
    std::unordered_map<T, Edge<T, W>> minEdge;
    std::unordered_map<T, bool> inTree;
    std::vector<Edge<T, W>> MST;
    int findSet(std::unordered_map<T, int>& nodeSet, T node) const {
        if (nodeSet[node] != findSet(nodeSet, node)) {
            nodeSet[node] = findSet(nodeSet, nodeSet[node]);
        }
        return nodeSet[node];
    }
    void strongConnect(const T& node, int& index, std::unordered_map<T, int>& indices, std::unordered_map<T, int>& lowlinks, std::vector<T>& stack, std::unordered_set<T>& onStack, std::vector<std::vector<T>>& components) const;
};

// Implementations for Edge class

template <typename T, typename W>
Edge<T, W>::Edge(const T& src, const T& dest, const W& weight) : source(src), destination(dest), weight(weight) {}

template <typename T, typename W>
T Edge<T, W>::getSource() const {
    return source;
}

template <typename T, typename W>
T Edge<T, W>::getDestination() const {
    return destination;
}

template <typename T, typename W>
W Edge<T, W>::getWeight() const {
    return weight;
}

template <typename T, typename W>
bool Edge<T, W>::operator<(const Edge<T, W>& other) const {
    return weight < other.weight;
}

template <typename T, typename W>
bool operator>(const Edge<T, W>& e1, const Edge<T, W>& e2) {
    return e2.getWeight() < e1.getWeight();
}

// Implementations for Graph class

template <typename T, typename W>
Graph<T, W>::Graph(bool directed) : directed(directed) {}

template <typename T, typename W>
void Graph<T, W>::addNode(const T& data) {
    if (adjList.find(data) == adjList.end()) {
        adjList[data] = std::vector<Edge<T, W>>{};
    }
}

template <typename T, typename W>
void Graph<T, W>::addEdge(const T& src, const T& dest, const W& weight) {
    if (adjList.find(src) == adjList.end() || adjList.find(dest) == adjList.end()) {
        throw std::invalid_argument("Source or destination node not found");
    }

    adjList[src].push_back(Edge<T, W>(src, dest, weight));
    if (!directed) {
        adjList[dest].push_back(Edge<T, W>(dest, src, weight));
    }
}

template <typename T, typename W>
bool Graph<T, W>::hasCycle() const {
    if (directed) return false; // This method is for undirected graphs only
    std::unordered_map<T, T> parent;
    for (const auto& pair : adjList) {
        if (parent.find(pair.first) == parent.end()) {
            parent[pair.first] = pair.first;
            if (hasCycleDFS(pair.first, parent)) {
                return true;
            }
        }
    }
    return false;
}

template <typename T, typename W>
bool Graph<T, W>::hasCycleDFS(const T& node, std::unordered_map<T, T>& parent) const {
    for (const Edge<T, W>& edge : adjList.at(node)) {
        T dest = edge.getDestination();
        if (parent.find(dest) == parent.end()) {
            parent[dest] = node;
            if (hasCycleDFS(dest, parent)) {
                return true;
            }
        } else if (parent[node] != dest) {
            return true;
        }
    }
    return false;
}

template <typename T, typename W>
std::vector<Edge<T, W>> Graph<T, W>::primMST() const {
    if (adjList.empty()) {
        throw std::invalid_argument("Graph is empty");
    }

    std::vector<Edge<T, W>> mst;
    std::unordered_map<T, bool> visited;
    std::priority_queue<Edge<T, W>, std::vector<Edge<T, W>>, std::greater<Edge<T, W>>> pq;

    // Add first node to the priority queue
    const T& firstNode = adjList.begin()->first;
    visited[firstNode] = true;
    for (const Edge<T, W>& edge : adjList.at(firstNode)) {
        pq.push(edge);
    }

    // Construct the MST
    while (!pq.empty()) {
        Edge<T, W> currEdge = pq.top();
        pq.pop();

        T currNode = currEdge.getDestination();
        if (visited.find(currNode) != visited.end()) {
            continue;
        }

        visited[currNode] = true;
        mst.push_back(currEdge);
        for (const Edge<T, W>& edge : adjList.at(currNode)) {
            if (visited.find(edge.getDestination()) == visited.end()) {
                pq.push(edge);
            }
        }
    }

    return mst;
}

template <typename T, typename W>
std::vector<Edge<T, W>> Graph<T, W>::kruskalMST() const {
    // Initialize the result MST
    std::vector<Edge<T, W>> mst;

    // Create a vector of all edges
    std::vector<Edge<T, W>> edges;
    for (const auto& pair : adjList) {
        for (const Edge<T, W>& edge : pair.second) {
            if (!directed || edge.getSource() < edge.getDestination()) {
                edges.push_back(edge);
            }
        }
    }

    // Sort the edges by weight
    std::sort(edges.begin(), edges.end());

    // Initialize the disjoint-set data structure
    std::unordered_map<T, int> rank;
    std::unordered_map<T, T> parent;
    for (const auto& pair : adjList) {
        rank[pair.first] = 0;
        parent[pair.first] = pair.first;
    }

    // Add edges to the MST as long as they don't create a cycle
    for (const Edge<T, W>& edge : edges) {
        T srcRoot = find(edge.getSource(), parent);
        T destRoot = find(edge.getDestination(), parent);

        if (srcRoot != destRoot) {
            mst.push_back(edge);
            unionByRank(srcRoot, destRoot, rank, parent);
        }
    }

    return mst;
}

template <typename T, typename W>
T Graph<T, W>::find(const T& x, std::unordered_map<T, T>& parent) const {
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}

template <typename T, typename W>
void Graph<T, W>::unionByRank(const T& x, const T& y, std::unordered_map<T, int>& rank, std::unordered_map<T, T>& parent) const {
    T rootX = find(x, parent);
    T rootY = find(y, parent);

    if (rootX == rootY) {
        return;
    }

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

template <typename T, typename W>
std::vector<int> Graph<T, W>::nodeColoring() const {
    std::unordered_map<T, int> colors;
    for (const auto& node : adjList) {
        std::unordered_set<int> used_colors;
        for (const Edge<T, W>& edge : adjList.at(node.first)) {
            if (colors.find(edge.getDestination()) != colors.end()) {
                used_colors.insert(colors[edge.getDestination()]);
            }
        }
        int color = 1;
        while (used_colors.find(color) != used_colors.end()) {
            ++color;
        }
        colors[node.first] = color;
    }

    std::vector<int> result;
    result.reserve(colors.size());
    for (const auto& node_color : colors) {
        result.push_back(node_color.second);
    }

    return result;
}

template <typename T, typename W>
std::vector<int> Graph<T, W>::edgeColoring() const {
    // Map to store the color of each edge
    std::unordered_map<Edge<T, W>, int, EdgeHash<T, W>> edgeColors;

    // Custom hash function for the Edge class
    for (const auto& nodeEdges : adjList) {
        for (const Edge<T, W>& edge : nodeEdges.second) {
            // Check if the edge has already been colored
            if (edgeColors.find(edge) != edgeColors.end()) {
                continue;
            }

            // Find the colors used by adjacent edges
            std::unordered_set<int> usedColors;
            for (const Edge<T, W>& adjacentEdge : adjList.at(edge.getSource())) {
                if (edgeColors.find(adjacentEdge) != edgeColors.end()) {
                    usedColors.insert(edgeColors[adjacentEdge]);
                }
            }
            for (const Edge<T, W>& adjacentEdge : adjList.at(edge.getDestination())) {
                if (edgeColors.find(adjacentEdge) != edgeColors.end()) {
                    usedColors.insert(edgeColors[adjacentEdge]);
                }
            }

            // Assign the smallest available color to the current edge
            int color = 1;
            while (usedColors.find(color) != usedColors.end()) {
                ++color;
            }
            edgeColors[edge] = color;
        }
    }

    // Convert the edge-color map to a vector of colors
    std::vector<int> result;
    result.reserve(edgeColors.size());
    for (const auto& edgeColor : edgeColors) {
        result.push_back(edgeColor.second);
    }

    return result;
}

template <typename T, typename W>
std::vector<std::vector<T>> Graph<T, W>::connectedComponents() const {
    if (directed) {
        std::unordered_map<T, int> indices;
        std::unordered_map<T, int> lowlinks;
        std::vector<T> stack;
        std::unordered_set<T> onStack;
        std::vector<std::vector<T>> components;
        int index = 0;

        for (const auto& pair : adjList) {
            if (indices.find(pair.first) == indices.end()) {
                strongConnect(pair.first, index, indices, lowlinks, stack, onStack, components);
            }
        }

        return components;
    } else {
        throw std::logic_error("This method is for directed graphs only");
    }
}

template <typename T, typename W>
void Graph<T, W>::strongConnect(const T& node, int& index, std::unordered_map<T, int>& indices, std::unordered_map<T, int>& lowlinks, std::vector<T>& stack, std::unordered_set<T>& onStack, std::vector<std::vector<T>>& components) const {
    indices[node] = index;
    lowlinks[node] = index;
    index++;
    stack.push_back(node);
    onStack.insert(node);

    for (const Edge<T, W>& edge : adjList.at(node)) {
        T dest = edge.getDestination();
        if (indices.find(dest) == indices.end()) {
            strongConnect(dest, index, indices, lowlinks, stack, onStack, components);
            lowlinks[node] = std::min(lowlinks[node], lowlinks[dest]);
        } else if (onStack.find(dest) != onStack.end()) {
            lowlinks[node] = std::min(lowlinks[node], indices[dest]);
        }
    }

    if (lowlinks[node] == indices[node]) {
        std::vector<T> component;
        T w;
        do {
            w = stack.back();
            stack.pop_back();
            onStack.erase(w);
            component.push_back(w);
        } while (w != node);
        components.push_back(component);
    }
}

template <typename T, typename W>
std::vector<double> Graph<T, W>::katzCentrality(double alpha, double beta) const {
    int n = adjList.size();
    std::vector<double> centrality(n, beta);

    std::unordered_map<T, int> node_to_index;
    int index = 0;
    for (const auto& entry : adjList) {
        node_to_index[entry.first] = index++;
    }

    bool converged = false;
    while (!converged) {
        converged = true;
        std::vector<double> new_centrality(n, 0.0);

        for (const auto& entry : adjList) {
            int node_index = node_to_index.at(entry.first);
            double sum = 0.0;

            for (const auto& edge : entry.second) {
                int neighbor_index = node_to_index.at(edge.getDestination());
                sum += centrality[neighbor_index];
            }

            new_centrality[node_index] = beta + alpha * sum;

            if (std::abs(new_centrality[node_index] - centrality[node_index]) > 1e-9) {
                converged = false;
            }
        }

        centrality = new_centrality;
    }

    return centrality;
}
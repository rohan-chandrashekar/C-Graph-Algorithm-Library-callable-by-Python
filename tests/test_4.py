import graphlib

# Create a weighted undirected graph
g = graphlib.Graph(False)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")
g.addNode("D")
g.addNode("E")

# Add edges with weights
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 1)
g.addEdge("C", "D", 1)
g.addEdge("D", "E", 1)
g.addEdge("A", "C", 1)
g.addEdge("B", "D", 1)

node_coloring = g.nodeColoring()

print("Node coloring:", node_coloring)
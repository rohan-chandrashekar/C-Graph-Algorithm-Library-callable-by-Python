import graphlib

# Create a weighted undirected graph
g = graphlib.Graph(False)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")
g.addNode("D")

# Add edges with weights
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 1)
g.addEdge("C", "D", 1)
g.addEdge("D", "A", 1)

edge_coloring = g.edgeColoring()

print("Edge coloring:", edge_coloring)
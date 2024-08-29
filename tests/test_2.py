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
g.addEdge("B", "C", 2)
g.addEdge("C", "D", 3)
g.addEdge("D", "A", 4)
g.addEdge("A", "C", 5)

# Run Prim's algorithm
prim_mst = g.primMST()

# Print results
print("Prim's MST:", [(e.getSource(), e.getDestination(), e.getWeight()) for e in prim_mst])
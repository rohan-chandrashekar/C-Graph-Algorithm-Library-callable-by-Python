import graphlib

# Create a weighted undirected graph
g = graphlib.Graph(True)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")
g.addNode("D")
g.addNode("E")
g.addNode("F")

# Add edges with weights
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 2)
g.addEdge("C", "D", 3)
g.addEdge("D", "A", 4)
g.addEdge("A", "C", 5)
g.addEdge("D", "E", 2)
g.addEdge("E", "F", 6)

connected_components = g.connectedComponents()

print("Connected components:", [[node for node in component] for component in connected_components])
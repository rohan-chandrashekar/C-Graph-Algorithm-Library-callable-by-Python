import graphlib

# Create a weighted undirected graph
g = graphlib.Graph(False)

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
g.addEdge("E", "F", 6)

katz_centrality = g.katzCentrality(0.1, 1)

print("Katz Centrality:", katz_centrality)
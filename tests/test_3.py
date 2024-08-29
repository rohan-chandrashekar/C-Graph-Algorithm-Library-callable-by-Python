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
g.addEdge("D", "E", 2)
g.addEdge("E", "F", 6)

kruskal_mst = g.kruskalMST()

print("Kruskal's MST:", [(e.getSource(), e.getDestination(), e.getWeight()) for e in kruskal_mst])
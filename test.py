import graphlib

# Create a weighted directed graph
g = graphlib.Graph(True)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")
g.addNode("D")
g.addNode("E")

# Add edges with weights
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 2)
g.addEdge("C", "A", 3)
g.addEdge("D", "C", 4)
g.addEdge("E", "D", 5)

# Run algorithms
has_cycle = g.hasCycle()
prim_mst = g.primMST()
kruskal_mst = g.kruskalMST()
node_coloring = g.nodeColoring()
edge_coloring = g.edgeColoring()
connected_components = g.connectedComponents()
katz_centrality = g.katzCentrality(0.1, 1)

# Print results
print("Has cycle:", has_cycle)
print("Prim's MST:", [(e.getSource(), e.getDestination(), e.getWeight()) for e in prim_mst])
print("Kruskal's MST:", [(e.getSource(), e.getDestination(), e.getWeight()) for e in kruskal_mst])
print("Node coloring:", node_coloring)
print("Edge coloring:", edge_coloring)
print("Connected components:", [[node for node in component] for component in connected_components])
print("Katz Centrality:", katz_centrality)
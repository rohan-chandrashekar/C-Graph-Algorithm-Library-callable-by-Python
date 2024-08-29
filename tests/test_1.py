import graphlib

# Create a directed graph
g = graphlib.Graph(False)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")
g.addNode("D")
g.addNode("E")

# Add edges
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 2)
g.addEdge("C", "D", 3)
g.addEdge("D", "E", 4)
#g.addEdge("E", "A", 5)

# Check for cycles
has_cycle = g.hasCycle()

# Print result
if has_cycle:
    print("The graph has a cycle.")
else:
    print("The graph does not have a cycle.")
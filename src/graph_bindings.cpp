#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "graph.h"

namespace py = pybind11;

PYBIND11_MODULE(graphlib, m) {
    py::class_<Edge<std::string, int>>(m, "Edge")
        .def(py::init<const std::string&, const std::string&, const int&>())
        .def("getSource", &Edge<std::string, int>::getSource)
        .def("getDestination", &Edge<std::string, int>::getDestination)
        .def("getWeight", &Edge<std::string, int>::getWeight);

    py::class_<Graph<std::string, int>>(m, "Graph")
        .def(py::init<bool>())
        .def("addNode", &Graph<std::string, int>::addNode)
        .def("addEdge", &Graph<std::string, int>::addEdge)
        .def("hasCycle", &Graph<std::string, int>::hasCycle)
        .def("primMST", &Graph<std::string, int>::primMST)
        .def("kruskalMST", &Graph<std::string, int>::kruskalMST)
        .def("nodeColoring", &Graph<std::string, int>::nodeColoring)
        .def("edgeColoring", &Graph<std::string, int>::edgeColoring)
        .def("connectedComponents", &Graph<std::string, int>::connectedComponents)
        .def("katzCentrality", &Graph<std::string, int>::katzCentrality);
}
#ifndef GRAPH_HPP
#define GRAPH_HPP

class Graph {
public:
    explicit Graph(int n);
    ~Graph();

    void inputGraph();
    void printGraph();
    void addNode();
    void removeNode();
    void addEdge();
    void removeEdge();
    void findEdges();
    bool isLinked();
    bool hasNegativeEdges();
    int getNodeCount() const;
    void runDijkstra(int start);
    void runWaveAlgorithm(int start, int end);
    int runGetTreeDiameter();
    void clearGraph();

private:
    int** graph;
    int n;
};

#endif

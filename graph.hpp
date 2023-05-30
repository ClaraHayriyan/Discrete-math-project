#ifndef DISCRETE_MATH_PROJECT_GRAPH_HPP
#define DISCRETE_MATH_PROJECT_GRAPH_HPP

#include <string>
#include <vector>

class Graph {
public:
    Graph(const std::string& fileName);
    void printAdjLists();
    void findCycles(int lenght);

private:
    void addVertex(const std::string& line);
    std::vector<int> stringToVector(std::string);
    bool adj(int vertex1, int vertex2);
    void printCycle(int currentVertex, int startVertex);
    void detectCycle(int startVertex, int currentVertex, int length);

private:
    struct Vertex {
    std::vector<int> adj;
    int parent {-1};
    bool isVisited {false};
    };

    std::vector<Vertex> vertices;
    size_t numOfVertices;
};

#endif // DISCRETE_MATH_PROJECT_GRAPH_HPP
#include "graph.hpp"

#include <algorithm> // std::copy
#include <fstream>
#include <iostream>
#include <iterator> // std::back_inserter, std::ostream_iterator
#include <stdexcept> // std::runtime_error

Graph::Graph(const std::string& fileName) {
    std::ifstream file(fileName);
    if(!file.is_open())
        throw std::runtime_error("failed to open file");
    std::string line;

    std::getline(file, line);
    try {
    numOfVertices = std::stoi(line);
    } catch(std::invalid_argument) {
        throw std::runtime_error("wrong representation of the graph");
    }
    vertices.reserve(numOfVertices);

    while(std::getline(file, line)) {
        if(!line.empty()) {
            addVertex(line);
        }
    }
}

void Graph::addVertex(const std::string& line) {
    std::vector<int> vec = stringToVector(line);
    if(vec.empty())
        throw std::runtime_error("wrong representation of the graph");
    std::copy(std::next(vec.begin()), vec.end(), std::back_inserter(vertices[vec[0]].adj));
}

std::vector<int> Graph::stringToVector(std::string line)
{
    std::vector<int> vec;

    int i = 0;
    while(line[i] != '\0')
    {
        while(line[i] != '\0' && !isdigit(line[i]))
            ++i;
        if(line[i] != '\0') {
            int index = atoi(&line[i]);
            if(index < 0 || index >= numOfVertices)
                throw std::runtime_error("wrong representation of the graph");
            vec.push_back(index);
        }
        while(line[i] != '\0' && isdigit(line[i]))
            ++i;
    }
    return vec;
}

bool Graph::adj(int vertex1, int vertex2) {
    for(int v : vertices[vertex1].adj)
        if(v == vertex2)
            return true;
    return false;
}

void Graph::printAdjLists() {
    int i {0};
    for(int v = 0; v < numOfVertices; ++v) {
        auto vec = vertices[v].adj;
        std::cout << i++ << " -> ";
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
        std::cout << std::endl;
    }
}

void Graph::printCycle(int currentVertex, int startVertex) {
    std::cout << startVertex << " -> " << currentVertex;
    while(vertices[currentVertex].parent != currentVertex) {
        std::cout << " -> " << vertices[currentVertex].parent;
        currentVertex = vertices[currentVertex].parent;
    }
    std::cout << std::endl;
}

void Graph::detectCycle(int startVertex, int currentVertex, int length) {
    if(length == 0) {
        if(adj(currentVertex, startVertex))
            printCycle(currentVertex, startVertex);
        return;
    }
    vertices[currentVertex].isVisited = true;
    for(auto& v : vertices[currentVertex].adj)
        if(!vertices[v].isVisited) {
            vertices[v].parent = currentVertex;
            detectCycle(startVertex, v, length - 1);
        }

    vertices[currentVertex].isVisited = false;
}

void Graph::findCycles(int length) {
    if(length < 3 || length > numOfVertices) {
        return;
    }
    for(int v = 0; v < vertices.size(); ++v)
        vertices[v].isVisited = false;

    for(auto i = 0; i < numOfVertices - length + 1; ++i) {
        vertices[i].parent = i;
        detectCycle(i, i, length - 1);
        vertices[i].isVisited = true;
    }
}
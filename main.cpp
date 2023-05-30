#include "graph.hpp"

#include <iostream>

int inputLengthOfCycle() {
    int length;
    std::cout << "\nInput the lenght of cycles (>=3): ";
    std::cin >> length;
    std::cout << std::endl;
    return length;
}

int main(int argc, char* argv[]) {
    try {
        Graph graph(argv[1]);
        graph.printAdjLists();
        int length = inputLengthOfCycle();
        graph.findCycles(length);
    }
    catch(std::runtime_error err) {
        std::cout << err.what() << std::endl;
    }
}
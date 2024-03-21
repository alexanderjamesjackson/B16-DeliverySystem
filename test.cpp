//File to test modular functionality 

#include "maps.hpp"
#include <iostream>
#include <limits>
#include <vector>



void PrintGraph(const Graph& g, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            float value = g.getValue(i, j);
            if (value == std::numeric_limits<float>::infinity()) {
                std::cout << "inf ";
            } else {
                std::cout << value << " ";
            }
        }
        std::cout << "\n";
    }
}

int main(){

    Graph g(5);

    g.storeHouseInitialisation();
    // g.changeEdge(1.5, 0, 1, false); 
    // g.changeEdge(2.5, 2, 3, true);  


    PrintGraph(g, 5);

    return 0;
};
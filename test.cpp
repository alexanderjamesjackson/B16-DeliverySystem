//File to test modular functionality 

#include "maps.hpp"
#include <iostream>
#include <limits>
#include <vector>





int main(){

    Graph g(5);
    srand(time(0));
    g.storeHouseInitialisation();
    g.ringRoadInitialisation();
    g.crossRoadInitialisation(0.4);
    Graph walk = g.randomWalk();
    // g.changeEdge(1.5, 0, 1, false); 
    // g.changeEdge(2.5, 2, 3, true);  


    walk.print();

    return 0;
};
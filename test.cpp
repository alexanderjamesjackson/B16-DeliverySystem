//File to test modular functionality 

#include "maps.hpp"


using namespace std;



int main(){
    int numNodes = 5;
    Graph g(numNodes);
    srand(time(0));
    g.storeHouseInitialisation();
    g.ringRoadInitialisation();
    g.crossRoadInitialisation(0.4);
    Graph walk = g.randomWalk();
    // g.changeEdge(1.5, 0, 1, false); 
    // g.changeEdge(2.5, 2, 3, true);  
    Pipeline p(numNodes, 0, 2);
    p.createOrders();
    p.printOrders();
    walk.print();

    return 0;
};
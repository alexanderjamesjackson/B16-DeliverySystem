//File to test modular functionality 

#include "maps.hpp"


using namespace std;

void printPaths(const vector< pair<vector<int>, float> > paths){
    for(int i = 0 ; i < paths.size() ; i++){
        cout << "Distance: " << paths[i].second << " Path: ";
        for(int j = 0 ; j < paths[i].first.size() ; j++){
            cout << paths[i].first[j] << " ";
        }
        cout<<endl;
    }
};

int main(){
    int numNodes = 20;
    Graph g(numNodes);
    srand(time(0));
    g.storeHouseInitialisation();
    g.ringRoadInitialisation();
    //g.crossRoadInitialisation(0.4);
    Graph walk = g.randomWalk();
    const vector< pair<vector<int>, float> > shortestPaths = g.dijkstraWithPath(0);
    printPaths(shortestPaths);
    // g.changeEdge(1.5, 0, 1, false); 
    // g.changeEdge(2.5, 2, 3, true);  
    // Pipeline p(numNodes, 0, 2);
    // p.createOrders();
    // p.printOrders();
    // walk.print();

    return 0;
};
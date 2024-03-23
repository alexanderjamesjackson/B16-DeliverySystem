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
    int numNodes = 8;
    Graph g(numNodes);
    srand(time(0));
    g.storeHouseInitialisation();
    g.ringRoadInitialisation();
    g.crossRoadInitialisation(1);
    Graph walk = g.randomWalk();
    cout << "    " << endl;
    walk.print();
    cout << "    " << endl;
    const vector< pair<vector<int>, float> > shortestPaths = walk.dijkstraWithPath(0);
    printPaths(shortestPaths);
    cout << "    " << endl;
    Pipeline p(numNodes, 0, 2);
    p.createOrders();
    p.printOrders();
    // g.changeEdge(1.5, 0, 1, false); 
    // g.changeEdge(2.5, 2, 3, true);  
    
    // walk.print();

    return 0;
};
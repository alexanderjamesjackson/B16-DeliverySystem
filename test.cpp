//File to test modular functionality 

#include "maps.hpp"


using namespace std;

//Function to print paths from the path container
void printPaths(const vector< pair<vector<int>, float> > paths){
    for(int i = 0 ; i < paths.size() ; i++){
        cout << "Distance: " << paths[i].second << " Path: ";
        for(int j = 0 ; j < paths[i].first.size() ; j++){
            cout << paths[i].first[j] << " ";
        }
        cout<<endl;
    }
};

//Function to print data from the allData container
void printAllData(const vector < pair<vector<int> , vector<int > > > & allData){
    for(int i = 0 ; i< allData.size() ; i++){
        cout<< "Delivered " << allData[i].first[0] << " baskets to house " << allData[i].first[1] << " along path: ";

        for(int j = 0 ; j < allData[i].second.size() ; j++){
            cout << allData[i].second[j] << " ";
        }
        cout << endl;
    }
};

int main(){

    int numNodes = 8;

    //Initialising a graph with connections to the store and a ring road and cross roads between houses
    Graph g(numNodes);

    srand(time(0));

    g.storeHouseInitialisation();
        
    g.ringRoadInitialisation();
    
    g.crossRoadInitialisation(0.5);

    //Takes a random walk through previous graph to create truly random network
    Graph walk = g.randomWalk();
    cout << "    " << endl;
    walk.print();
    cout << "    " << endl;

    //find shortest paths
    vector< pair<vector<int>, float> > shortestPaths = walk.dijkstraWithPath(0);
    printPaths(shortestPaths);
    cout << "    " << endl;

    //create pipeline of orders
    Pipeline p(numNodes, 0, 2);


    p.createOrders();
    p.printOrders();

    //Create a delivery planner and create and print a plan
    DeliveryPlanner dp(walk, p, shortestPaths);

    vector < pair<vector<int> , vector<int > > > allData = dp.generatePlan();

    printAllData(allData);
    return 0;
};
#include "maps.hpp"

using namespace std;

Graph::Graph(int N):n(N), graph(std::vector<std::vector<float> > (N, std::vector<float> (N, numeric_limits<float>::infinity() ))){
    for(int i = 0 ; i < n ; i++){
        graph[i][i] =0;
        int j;
    }
};


void Graph::changeEdge(float w, int i, int j, bool twoWay){
    graph[i][j] = w;

    if (twoWay == true){
        graph[j][i] = w;
    }
};

float Graph::getValue(int i, int j) const{
    return graph[i][j];
};

void Graph::storeHouseInitialisation(){
    //Define how many houses connect to store
    int storeConnections = n/2;
    if(storeConnections > 5){
        storeConnections = 5;
    }

    for(int i = 0 ; i < storeConnections; i++){
        
        int min = 1;
        int max = n-1;
        int randEdge = min + rand() % (max - min + 1);

        float randWeight = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        //Ensure that the same edge is not changed

        if(graph[0][randEdge] > 100){
            changeEdge(randWeight, 0, randEdge, true);
        }

        //Reselect edge if invalid
        else{
            i = i -1;
        }
    }
}


void Graph::ringRoadInitialisation(){
    
    
    //loop n-2 times to connect node 1 -> 2, 2 -> 3, .......
    for( int i = 1 ; i < n - 1 ; i++){
        float randWeight = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        changeEdge(randWeight, i, i + 1, true);
    }

    //close loop i.e node n-1 -> 1 
    float randWeight = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    changeEdge(randWeight, 1 , n - 1, true);
};

void Graph::crossRoadInitialisation(float k){
    int min = 1;
    int max = n - 1;
    int nCross = k * n;

    for(int i = 0; i< nCross ; i++){
        float randWeight = static_cast<float>(rand()) /static_cast<float>(RAND_MAX);

        int randEdge1 = min + rand() % (max - min + 1);
        int randEdge2 = min + rand() % (max - min + 1);

        //Ensure that we are adding between two different houses that do not have a road between them
        if(randEdge1 != randEdge2 && getValue(randEdge1, randEdge2) > 100){
            changeEdge(randWeight, randEdge1, randEdge2, true);
        }
        else{
            i = i - 1;
        }
    }
};
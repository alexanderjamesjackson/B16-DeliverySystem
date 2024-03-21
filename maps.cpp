#include "maps.hpp"

using namespace std;

Graph::Graph(int N):n(N), graph(std::vector<std::vector<float> > (N, std::vector<float> (N, numeric_limits<float>::infinity() ))){
    for(int i = 0 ; i < n ; i++){
        graph[i][i] =0;
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

    srand(time(0));


    for(int i = 0 ; i < storeConnections; i++){
        
        int min = 1;
        int max = n-1;
        int randEdge = min + rand() % (max - min + 1);

        float randWeight = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

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

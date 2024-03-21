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


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

int Graph::getSize()const {return n;}

void Graph::print()const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            float value = getValue(i, j);
            if (value == std::numeric_limits<float>::infinity()) {
                std::cout << "inf ";
            } else {
                std::cout << value << " ";
            }
        }
        std::cout << "\n";
    }
}

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



Graph Graph::randomWalk(){
    bool visitedAll = false;
    int currentNode = 0;
    Graph walkGraph(n);

    vector<bool> nodeVisited;

    //termination vector initialised to all false terminates when all true
    for(int i = 0 ; i < n ; i++){
        nodeVisited.push_back(false);
    }
    nodeVisited[0] = true;

    int min = 0;
    int max = n-1;

    while(visitedAll == false){



        bool validChoice = false;


        while(validChoice == false){
            int newNode = min + rand() % (max - min + 1);
            //retrieve the distance between current node and new proposed node to visit
            float currentWeight = getValue(currentNode, newNode);
            //retrieve the distance stored in our walk (should be inf if not visited)
            float newWeight = walkGraph.getValue(currentNode,newNode);
            //Check for the road existing
            if(currentWeight < 100){
 
                    //Check for it being a new edge
                    if(newWeight > 100){
                        //Update the new node to be visited in termination vector (may already be true but no issue in doing it again)
                        nodeVisited[newNode] = true;
                    }

                    walkGraph.changeEdge(currentWeight,currentNode,newNode, true);
                    validChoice = true;
                    currentNode = newNode;
                    
                    //Checks if all entries of termination vector are true

                    visitedAll = all_of(nodeVisited.begin(), nodeVisited.end(), [](bool val) { return val; });
                    
            }
        }

    }
    return walkGraph;
};

Pipeline::Pipeline(int nNodes, int min, int max): nNodes(nNodes),minBaskets(min), maxBaskets(max){};

void Pipeline::createOrders(){
    for(int i = 1 ; i < nNodes ; i++){
        int nBaskets = minBaskets + rand() % (maxBaskets - minBaskets + 1);
        if (nBaskets != 0){
            orders.push_back(vector<int> {i , nBaskets});
        }
    }
    nOrders = orders.size();
};

vector<int> Pipeline::getOrder(int orderNum)const{
    return orders[orderNum - 1];
};

vector<vector<int> > Pipeline::getAllOrders() const{
    return orders;
};

void Pipeline::printOrders() const{
    for(int i = 0 ; i < nOrders ; i++){
        cout<< "House " << orders[i][0] << " ordered " << orders[i][1] << " baskets." << endl;
    }
};

int Pipeline::getNumberOrders() const{return nOrders;};

int Pipeline::getMaxBaskets() const{return maxBaskets;};

int Pipeline::getMinBaskets() const{return minBaskets;};
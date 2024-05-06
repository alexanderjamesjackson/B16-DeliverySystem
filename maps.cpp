#include "maps.hpp"

using namespace std;

Graph::Graph(int N):n(N), graph(vector<vector<float> > (N, vector<float> (N, numeric_limits<float>::infinity() ))){
    for(int i = 0 ; i < n ; i++){
        graph[i][i] =0;
    }
};

vector<vector<float> >Graph::getAdjMatrix() const{
    return graph;
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
            if (value == numeric_limits<float>::infinity()) {
                cout << "inf ";
            } else {
                cout << value << " ";
            }
        }
        cout << "\n";
    }
}

void Graph::storeHouseInitialisation(){
    //Define how many houses connect to store
    int storeConnections = n/2;
    if(storeConnections > 3){
        storeConnections = 3;
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
//
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


//takes a random walk through the previous graph in order to create a truly random graph network where all houses are accessible from the store but not directly
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
//Find shortest paths to source node
vector<pair<vector<int> , float> > Graph::dijkstraWithPath(int source) const{
    //Keep tracks of distances
    vector<float> dist(n, numeric_limits<float>::infinity());
    //Keep track of previously visited
    vector<int> prev(n , -1);
    //Keep track of whether node is visited
    vector<bool> visited(n, false);

    //Queue of nodes to visit prioritised by tentative distance from source smallest first
    priority_queue< pair<float, int> , vector<pair<float, int> > , greater<> > pq;

    dist[source] = 0.0;
    pq.push({0.0, source});

    while(pq.empty() == false){
        int u = pq.top().second;
        pq.pop();

        if(visited[u] == true){
            continue;
        }
        visited[u] = true;

        for(int v = 0 ; v < n ; v++){
            float weight = getValue(u,v);
            if(visited[v] == false && weight < 100 && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v] , v});
            }
        }
    };

    //Reconstruct Paths

    vector<pair<vector<int>, float> > paths(n);
    for(int i = 0 ; i < n ; i++){
        vector<int> path;
        //start at target node, check that there is a predecessor and then work backwards each iteration
        for(int at = i ; at != -1; at = prev[at]){
            path.insert(path.begin(),at); //Insert at start
        }
        paths[i] = {path, dist[i]};

    }

    return paths;
};




Pipeline::Pipeline(int nNodes, int min, int max): nNodes(nNodes),minBaskets(min), maxBaskets(max){};
//Create random orders
void Pipeline::createOrders(){
    for(int i = 1 ; i < nNodes ; i++){
        int nBaskets = minBaskets + rand() % (maxBaskets - minBaskets + 1);
        if (nBaskets != 0){
            orders.push_back(vector<int> {i , nBaskets});
        }
    }
    nOrders = orders.size();
};

//retrieve how many baskets a certain house ordered
int Pipeline::getOrder(int houseNum)const{
    for(int i = 0 ; i < orders.size() ; i++){
        if(orders[i][0] == houseNum){
            return orders[i][1];
        }
    }
    //magic no to signify no order found
    return -1;

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
//Remove an order to house from pipeline
void Pipeline::removeOrder(int house){

    for(int i = 0 ; i < orders.size() ; i++){
        if(orders[i][0] == house){
            orders.erase(orders.begin() + i);
            break;
        }
    }
};
//Reduce an order to house from pipeline by 1

void Pipeline::reduceOrder(int house){
    for(int i = 0 ; i < orders.size() ; i++){
        if(orders[i][0] == house){
            orders[i][1] =orders[i][1] - 1;
            break;
        }
    }
}


DeliveryPlanner::DeliveryPlanner(Graph & g, Pipeline & p, vector<pair<vector<int>, float> > & shortestPaths): graph(g),pipeline(p), shortestPaths(shortestPaths){};


/* Function to generate a delivery plan. Algorithm works by:
-identifying the house "targetHouse"for which the shortest path to it contains the most houses that need delivering to
-Completing delivery to targetHouse by removing its order from teh pipeline and adjusting the orders onboard accordingly
-Work backwards along the path to targetHouse completing orders until empty or reached store
-Repeat*/
vector < pair<vector<int> , vector<int > > > DeliveryPlanner::generatePlan(){

    vector<vector<int> > orders = pipeline.getAllOrders();

    vector < pair<vector<int> , vector<int > > > allData;
    //Loop until no more orders
    while(pipeline.getAllOrders().empty() == false){


        int basketsOnboard = 3;

        //Find furthest house to visit

        int targetHouse = findTargetHouse();

        vector<int> targetPath = shortestPaths[targetHouse].first;

        int basketsDelivered = pipeline.getOrder(targetHouse);
        //log info about delivery
        pair< vector<int> , vector<int> > data;
        data.first.push_back(basketsDelivered);
        data.first.push_back(targetHouse);
        data.second = targetPath;
        allData.push_back(data);
        //adjust current orders on robot
        basketsOnboard = basketsOnboard - basketsDelivered;

        //remove order from pipeline as it is completed
        pipeline.removeOrder(targetHouse);


        //Backtrack along path completing deliveries until empty 

        vector<int> newPath;

        newPath.push_back(targetHouse);

        for(int i = targetPath.size() - 2  ; i > 0 ; i--){

            //construct new path to be logged for next delivery
            newPath.push_back(targetPath[i]);
            int basketsOrdered = pipeline.getOrder(targetPath[i]);

            //Check for a valid order(magic number of -1 represents no order found)

            if(basketsOrdered != -1){
                //If equal then log delivery and empty the robot and start again from store
                if(basketsOrdered == basketsOnboard){
                    data.first[0] = basketsOrdered;
                    data.first[1] = targetPath[i];
                    data.second = newPath;
                    allData.push_back(data);
                    pipeline.removeOrder(targetPath[i]);
                    break;
                }
                //If there are still baskets on robot then repeat until empty logging each delivery
                else if(basketsOrdered < basketsOnboard){
                    data.first[0] = basketsOrdered;
                    data.first[1] = targetPath[i];
                    data.second = newPath;
                    allData.push_back(data);
                    pipeline.removeOrder(targetPath[i]);
                    newPath = {targetPath[i]};
                    basketsOnboard = basketsOnboard - basketsOrdered;
                }
                //If the order exceeds what we have then reduce the order by giving what we have left and return to store
                else if(basketsOrdered > basketsOnboard){
                    data.first[0] = basketsOnboard;
                    data.first[1] = targetPath[i];
                    data.second = newPath;
                    allData.push_back(data);
                    pipeline.reduceOrder(targetPath[i]);
                    break;
                }

                
                
            }
            //Check for not carrying anything
            if(basketsOnboard == 0){
                break;
            }
            if(basketsOnboard < 0){
                cout << "Error cannot have negative baskets" << endl;

            }
        }

        

    } 

    return allData;
    
    
};

int DeliveryPlanner::findTargetHouse(){
    vector<vector<int> > orders = pipeline.getAllOrders();

    //find longest no of houses path that is in order list

    int maxOrdersOnPath = 0;
    int targetHouse = 0;
    //Construct set of houses with orders for easy lookup
    set<int> housesThatOrdered;

    for(int i = 0 ; i< orders.size() ; i++){
        housesThatOrdered.insert(orders[i][0]);
    }

    //Find best house to target by most matches with orders
    for(int i = 0 ; i < orders.size(); i++){
        int currentHouse = orders[i][0];

        vector<int> pathToCurrent = shortestPaths[currentHouse].first;

        int houseCommon = 0;

        for(int house : pathToCurrent){
            if(housesThatOrdered.find(house) != housesThatOrdered.end()){
                houseCommon++;
            }
        }
        
        if(houseCommon > maxOrdersOnPath){
            maxOrdersOnPath = houseCommon;
            targetHouse = currentHouse;
        }

        
    }
    return targetHouse;
};




#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

class Graph{
    private:
        std::vector < std::vector<float> > graph;
        int n;

    public:
        //Construct a adjacency matrix of size N initialised to infinite weights
        Graph(int N);

        //Modify an edge value from i -> j with value w, option to change j-> at same time by setting twoWay to true
        void changeEdge(float w, int i, int j, bool twoWay);

        //Read weight from i ->j
        float getValue(int i, int j) const;

        //Initialise n/2 randomly weighted edge connections between store and random houses
        void storeHouseInitialisation();
};







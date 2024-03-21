#ifndef MAPS_HPP
#define MAPS_HPP


#include <vector>
#include <iostream>
#include <limits>

class Graph{
    private:
        std::vector < std::vector<float> > graph;
        int n;

    public:
        Graph(int N);
        void changeEdge(float w, int i, int j, bool twoWay);
        float getValue(int i, int j) const;
};






#endif 
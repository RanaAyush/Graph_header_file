#ifndef MYHEADER_H
#define MYDEADER_H
#include <vector>
#include <unordered_map>
#include<list>
using namespace std;

class Graph
{
    vector<pair<int, int>> edges;
    vector<vector<int>> wtdEdges;
    unordered_map<int, vector<int>> adjLst;
    unordered_map<int,list<pair<int,int>>> wtdAdjlst;
public:
    Graph();
    Graph(vector<pair<int, int>> edges);
    Graph(vector<vector<int>> edges);
    void createAdjList();
    void createWtdAdjList();
    void print_adjLst();

    //Traversal algorithms
    vector<int> bfs(int src);
    vector<int> dfs(int src);

    // Shortest path algorithms 
    // Dijkstra algo
    vector<int> dijkstraDist(int src, vector<vector<int>> edges,int vertices);//shortest distance array
    int dijkstraDist(int src,int dest, vector<vector<int>> edges,int vertices);//shortest distance

    //Bellmanford Algo
    vector<int> bellmanFordDist(int src, vector<vector<int>> edges,int vertices);//shortest distance array

    //floyd-Warshall algo for shortest distance between each edge
    vector<vector<int>> floydWarshallDist(vector<vector<int>> edgeMatrix);
    
    //shortest path
    vector<int> spath(int src,int dest, vector<pair<int,int>> edges,int vertices);//unweighted graph
    vector<int> spath(int src,int dest, vector<vector<int>> edges,int vertices);//weighted graph

};

#endif
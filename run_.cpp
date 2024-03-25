#include "my_header.h"
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int main(){
    // vector<pair<int,int>> edges = {{0,1},{1,2},{1,3},{2,4},{3,4},{4,5},{4,6},{3,7}};
    // vector<vector<int>> edges = {{0,1,5},{1,2,-1},{1,3,2},{2,4,2},{3,4,1},{4,5,5},{4,6,3},{3,7,10},{4,7,1}};
    vector<vector<int>> edges = {{0,1,5},{1,2,-6},{2,0,-2}};



    Graph g(edges);
    // int dest;
    // cin>>dest;
    // int ans = g.dijkstraDist(0,7,edges,8);
    vector<int> path = g.bellmanFordDist(0,edges,8);

    for(auto x : path) cout<<x<<"->";
    // cout<<ans<<endl;
    return 0;
}
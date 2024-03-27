#include "my_header.h"
#include <queue>
#include <iostream>
#include <vector>
#include <unordered_map>
#include<set>
#include<list>
#include<algorithm>
using namespace std;

void run_bfs(queue<int> &q, unordered_map<int, bool> &visited, vector<int> &traversal, unordered_map<int, vector<int>> adjLst)
{
    while (!q.empty())
    {
        int src = q.front();
        q.pop();
        traversal.push_back(src);

        for (auto x : adjLst[src])
        {
            if (!visited[x])
            {
                q.push(x);
                visited[x] = true;
            }
        }
    }
}

void run_dfs(int src, unordered_map<int, bool> &visited, vector<int> &traversal, unordered_map<int, vector<int>> adjLst)
{
    visited[src] = true;
    traversal.push_back(src);
    for (auto x : adjLst[src])
    {
        if (!visited[x])
        {
            run_dfs(x, visited, traversal, adjLst);
        }
    }
}

Graph::Graph(){}
Graph::Graph(vector<pair<int, int>> edges) : edges(edges){}
Graph::Graph(vector<vector<int>> edges) : wtdEdges(edges){}



void Graph::createAdjList()
{
    for (auto x : edges)
    {
        adjLst[x.first].push_back(x.second);
        adjLst[x.second].push_back(x.first);
    }
}

void Graph::createWtdAdjList()
{
    for (auto x : wtdEdges)
    {
        wtdAdjlst[x[0]].push_back({x[1],x[2]});
        wtdAdjlst[x[1]].push_back({x[0],x[2]});
    }
}

void Graph::print_adjLst()
{
    for (auto x : adjLst)
    {
        cout << x.first << "-> ";
        for (auto y : x.second)
        {
            cout << y << ", ";
        }
        cout << endl;
    }
}

vector<int> Graph::bfs(int src)
{
    vector<int> traversal;
    queue<int> q;
    unordered_map<int, bool> visited;
    visited[src] = true;
    createAdjList();
    q.push(src);
    run_bfs(q, visited, traversal, adjLst);
    return traversal;
}

vector<int> Graph::dfs(int src)
{
    vector<int> traversal;
    unordered_map<int, bool> visited;
    createAdjList();
    run_dfs(src, visited, traversal, adjLst);
    return traversal;
}

vector<int> Graph::dijkstraDist(int src,vector<vector<int>> edges,int vertices){
    createWtdAdjList();
    vector<int> distance(vertices,INT_MAX);
    distance[src]=0;
    set<pair<int,int>> st;
    st.insert({0,src});

    while(!st.empty()){
        auto topele = *(st.begin());
        st.erase(st.begin());

        int currDist = topele.first;
        int currNode = topele.second;

        for(auto x : wtdAdjlst[currNode]){
            if(currDist + x.second < distance[x.first]){
                if(st.find({distance[x.first],x.first})!=st.end()){
                    st.erase({distance[x.first],x.first});
                }

                distance[x.first] = currDist+x.second;
                st.insert({currDist+x.second,x.first});
            }
        }
    }
    return distance;
}
int Graph::dijkstraDist(int src,int dest, vector<vector<int>> edges,int vertices){
    vector<int> dist = dijkstraDist(src,edges,vertices);
    return dist[dest];
}

vector<int> Graph::sPath(int src,int dest, vector<pair<int,int>> edges,int vertices){
    vector<int> path;
    createAdjList();
    queue<int> q;
    unordered_map<int,bool> visitetd;
    vector<int> parent(vertices);
    q.push(src);
    visitetd[src]=1;
    while(!q.empty()){
        int t=q.front();
        q.pop();
        for(auto x : adjLst[t]){
            if(!visitetd[x]){
                visitetd[x]=1;
                parent[x]=t;
                q.push(x);
            }
        }
    }
    path.push_back(dest);
    while(dest!=src){
        dest = parent[dest];
        path.push_back(dest);
    }
    reverse(path.begin(),path.end());
    return path;
}
vector<int> Graph::sPath(int src,int dest, vector<vector<int>> edges,int vertices){
    createWtdAdjList();
    vector<int> distance(vertices,INT_MAX);
    vector<int> parent(vertices);
    vector<int> path;
    distance[src]=0;
    set<pair<int,int>> st;
    st.insert({0,src});

    while(!st.empty()){
        auto topele = *(st.begin());
        st.erase(st.begin());

        int currDist = topele.first;
        int currNode = topele.second;

        for(auto x : wtdAdjlst[currNode]){
            if(currDist + x.second < distance[x.first]){
                if(st.find({distance[x.first],x.first})!=st.end()){
                    st.erase({distance[x.first],x.first});
                }
                parent[x.first] = currNode;
                distance[x.first] = currDist+x.second;
                st.insert({currDist+x.second,x.first});
            }
        }
    }
    path.push_back(dest);
    while(src!=dest){
        dest = parent[dest];
        path.push_back(dest);
    }
    reverse(path.begin(),path.end());
    return path;
}

vector<int> Graph::bellmanFordDist(int src, vector<vector<int>> edges,int vertices){
    vector<int> distance(vertices,INT_MAX);
    distance[src] =0;

    for(int i=0;i<vertices-1;i++){
        for(auto x : edges){
            int u=x[0];
            int v=x[1];
            int w=x[2];
            if(distance[u] != INT_MAX && distance[u]+w<distance[v])
                distance[v] = distance[u]+w;
        }
    }
    //for negative cycle 
    for(auto x : edges){
        int u=x[0];
            int v=x[1];
            int w=x[2];
            if(distance[u] != INT_MAX && distance[u]+w<distance[v]){
                cout<<"Negative cycle is present"<<endl;
                return {};
            }
    }
    return distance;   
}

vector<vector<int>> Graph::floydWarshallDist(vector<vector<int>> edgeMatrix){
    vector<vector<int>> distance = edgeMatrix;
    int inf = INT_MAX;
    int n = edgeMatrix.size();

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=k && j!=k && distance[i][k]!=inf && distance[k][j]!=inf && distance[i][j]>distance[i][k]+distance[k][j])
                        distance[i][j] = distance[i][k]+distance[k][j];
            }
        }
    }
    return distance;
}
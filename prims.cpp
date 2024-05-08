#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

struct Edge{
    int dest,weight;
};
class Graph{
private:
    int V;
    vector<vector<Edge>> adj;
public:
    Graph(int v): V(v),adj(v){}

    void addEdge(int src, int dest, int weight){
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight});
    }

    void PrimMST(){
        vector<int> key(V,INT_MAX);
        vector<int> parent(V,-1);
        vector<bool> inMST(V,false);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0,0});
        key[0] = 0;

        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true;

            for(auto& edge:adj[u]){
                int v = edge.dest;
                int weight = edge.weight;

                if(!inMST[v] && weight < key[v]){
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }

        for(int i=1;i<V;i++){
            cout << parent[i] << "-" << i << ": " << key[i] << endl;
        }
    }
    
};

int main(){
     Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1,2,34);
    g.addEdge(0,2,22);

    // Find Minimum Spanning Tree
    g.PrimMST();
    
    return 0;
}
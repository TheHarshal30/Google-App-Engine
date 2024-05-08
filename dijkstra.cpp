#include<iostream>
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
    Graph(int v): V(v),adj(v) {}

    void addEdge(int src, int dest, int weight){
        adj[src].push_back({dest,weight});
    }

    void Dijkstra(int src){
        vector<int> dist(V,INT_MAX);
        vector<bool> visited(V,false);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push({0,src});
        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            if(visited[u]) continue;
            visited[u] = true;

            for(const auto& edge: adj[u]){
                int v = edge.dest;
                int weight = edge.weight;
                if(!visited[v] && dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v],v});
                }
            }

        }

        cout << "Shortest path: " << endl;
        for(int i=0;i<V;i++){
            cout << "Vertex: " << i << ": ";
            if(dist[i] == INT_MAX) cout << "INF" << endl;
            else cout << dist[i] << endl;
        }

    }
};

int main(){
     Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 10);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 20);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 15);
    g.addEdge(3, 4, 11);
    g.addEdge(4, 5, 6);
    g.Dijkstra(0);
    return 0;
}
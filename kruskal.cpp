#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;

struct Edge{
    int src,dest,weight;
};

struct Subset{
    int parent,rank;
};

class Graph{
private:
    int V;
    vector<Edge> edges;
public:
    Graph(int v): V(v){};

    void addEdge(int src, int dest, int weight){
        edges.push_back({src,dest,weight});
    }

    int find(vector<Subset> subsets, int i){
        if(subsets[i].parent != i){
            subsets[i].parent = find(subsets, subsets[i].parent);
        }
        return subsets[i].parent;
    }

    void Union(vector<Subset> subsets, int x, int y){
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if(subsets[xroot].rank < subsets[yroot].rank){
            subsets[xroot].parent = yroot;
        }
        else if(subsets[yroot].rank < subsets[xroot].rank){
            subsets[yroot].parent = xroot;
        }
        else{
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
    }

    void KruskalMST(){
        vector<Edge> results;
        sort(edges.begin(), edges.end(), [](Edge a, Edge b){
            return a.weight<b.weight; 
        });
        vector<Subset> subsets(V);  
        for(int v=0;v<V;v++){
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }

        int e =0;
        int i = 0;

        while( e < V-1 & i < edges.size()){
            Edge nextEdge = edges[i++];
            int x = find(subsets, nextEdge.src);
            int y = find(subsets, nextEdge.dest);

            if(x!=y){
                Union(subsets,x,y);
                results.push_back(nextEdge);
                ++e;
            }
        }

        for (auto& it: results){
            cout << it.src << "-" << it.dest << ": " << it.weight << endl;
        }

    }

};

int main(){
      Graph g(4);
        
    // Find Minimum Spanning Tree
    g.KruskalMST();
    return 0;
}
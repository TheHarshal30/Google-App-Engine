#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
using namespace std;
struct Node{
    int x,y;
    int g,h;
    Node* parent;

    Node(int x1,int y1, int g1, int h1, Node* p) {
        x = x1;
        y = y1;
        g = g1;
        h = h1;
        parent = p;
    }
    int f(){
        return h+g;
    }

    bool operator>(Node& other) {
        return f() > other.f();
    }
};

int calMan(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}


vector<pair<int,int>> astar(vector<vector<int>> grid, pair<int,int> start, pair<int,int> goal){
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<Node*, vector<Node*>, greater<Node*>> open;
    unordered_map<int,unordered_map<int,int>> g_vals;

    Node* startNode = new Node(start.first, start.second, 0, calMan(start.first, start.second, goal.first, goal.second), nullptr);
    open.push(startNode);
    g_vals[start.first][start.second] = 0;  

    while(!open.empty()){
        Node* curr = open.top();
        open.pop();

        if(curr->x == goal.first && curr->y == goal.second){
            vector<pair<int,int>> path;
            while(curr != nullptr){
                path.push_back({curr->x, curr->y});
                curr = curr->parent;
            }

            reverse(path.begin(), path.end());
            return path;
        }

        vector<pair<int,int>> succ = {
            {curr->x-1, curr->y},
            {curr->x+1, curr->y},
            {curr->x, curr->y-1},
            {curr->x, curr->y+1}
        };

        for(auto s: succ){
            int x = s.first;
            int y = s.second;
            if(x>=0 && x <rows && y>=0 && y< cols && grid[x][y] == 0){
                int new_g = curr->g+1;

                if(g_vals.find(x) != g_vals.end() && g_vals[x].find(y) != g_vals[x].end() && new_g >= g_vals[x][y]) continue;

                Node* succNode = new Node(x,y, new_g, calMan(x,y,goal.first,goal.second), curr);
                open.push(succNode);
                g_vals[x][y] = new_g;
            }
        }
    }
    return {};
}

int main(){
    vector<vector<int>> grid = {
        {0, 0, 0, 1},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    pair<int,int> start = {0,0};
    pair<int,int> goal = {2,3};

    vector<pair<int,int>> path = astar(grid, start,goal);

    if(!path.empty()) {
        cout << "path found: " << endl;
        for(auto it: path){
            cout << "( "<< it.first << ", " <<it.second << " )";
        }
        cout << endl;
    }
    else{
        cout << "Path not found" << endl;
    }
    return 0;


}
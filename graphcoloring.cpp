#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if it's safe to color a vertex with a given color
bool isSafe(int vertex, int color, const vector<vector<int>>& graph, const vector<int>& colorAssigned) {
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex][i] && colorAssigned[i] == color) {
            return false;
        }
    }
    return true;
}

// Function to perform backtracking with branch and bound for graph coloring
bool graphColoringUtil(int vertex, int m, vector<int>& colorAssigned, const vector<vector<int>>& graph) {
    if (vertex == graph.size()) {
        return true; // All vertices colored
    }

    // Try assigning different colors to the vertex
    for (int c = 1; c <= m; ++c) {
        if (isSafe(vertex, c, graph, colorAssigned)) {
            colorAssigned[vertex] = c;

            // Recur for the next vertex
            if (graphColoringUtil(vertex + 1, m, colorAssigned, graph)) {
                return true; // If coloring is successful
            }

            // Backtrack if coloring is not possible
            colorAssigned[vertex] = 0;
        }
    }

    return false; // If no color can be assigned to the vertex
}

// Function to perform graph coloring using backtracking with branch and bound
void graphColoring(const vector<vector<int>>& graph, int m) {
    int V = graph.size();
    vector<int> colorAssigned(V, 0);

    if (!graphColoringUtil(0, m, colorAssigned, graph)) {
        cout << "No solution exists." << endl;
        return;
    }

    // Print the solution
    cout << "The colors assigned to vertices are:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": Color " << colorAssigned[i] << endl;
    }
}

int main() {
    // Example graph represented as an adjacency matrix
    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3; // Number of colors available

    // Perform graph coloring
    graphColoring(graph, m);

    return 0;
}

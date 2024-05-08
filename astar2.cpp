#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include<functional>

using namespace std;

// Define a structure for each cell in the grid
struct Cell {
    int x, y; // Coordinates of the cell
    int g, h, f; // Cost variables for A* algorithm
    Cell* parent; // Parent cell

    Cell(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}

    // Function to calculate the heuristic (Manhattan distance)
    void calculateH(Cell* goal) {
        h = abs(x - goal->x) + abs(y - goal->y);
    }

    // Function to calculate the total cost
    void calculateF() {
        f = g + h;
    }
};

// A* algorithm function
vector<Cell*> aStar(vector<vector<int>>& grid, Cell* start, Cell* goal) {
    // Create priority queue for open cells
    priority_queue<Cell*, vector<Cell*>, function<bool(Cell*, Cell*)>> open(
        [](Cell* a, Cell* b) {
            return a->f > b->f;
        });

    // Create closed list
    vector<vector<bool>> closed(grid.size(), vector<bool>(grid[0].size(), false));

    // Add the start cell to open list
    open.push(start);

    // Loop until open list is empty
    while (!open.empty()) {
        // Get the cell with the lowest F score
        Cell* current = open.top();
        open.pop();

        // Check if we reached the goal
        if (current == goal) {
            vector<Cell*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Mark current cell as closed
        closed[current->x][current->y] = true;

        // Generate successors
        vector<pair<int, int>> successors = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (const auto& dir : successors) {
            int newX = current->x + dir.first;
            int newY = current->y + dir.second;

            // Check if the new position is within bounds and not blocked
            if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] == 0 && !closed[newX][newY]) {
                Cell* successor = new Cell(newX, newY);
                successor->parent = current;
                successor->g = current->g + 1; // Assuming each step cost is 1
                successor->calculateH(goal);
                successor->calculateF();

                open.push(successor);
            }
        }
    }

    // If no path found, return empty vector
    return {};
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    Cell start(0, 0);
    Cell goal(0, 1);

    // Find the path
    vector<Cell*> path = aStar(grid, &start, &goal);

    // Print the path
    if (path.empty()) {
        cout << "No path found!" << endl;
    } else {
        cout << "Path found: ";
        for (const auto& cell : path) {
            cout << "(" << cell->x << "," << cell->y << ") ";
        }
        cout << endl;
    }

    // Free memory
    for (auto cell : path) {
        delete cell;
    }

    return 0;
}

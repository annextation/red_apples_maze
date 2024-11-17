#include <iostream>
#include <vector>
#include <chrono>
#include "Maze_from_Astrahankina.h"
#include "Maze_from_Vivcharik.h"

using namespace std;

class DFS {
public:
    
    bool findShortestPathDFS(int startX, int startY, int endX, int endY,
        vector<pair<int, int>>& path,
        vector<vector<char>>& maze) {
        int size = maze.size(); 
        auto start = chrono::high_resolution_clock::now(); 

        vector<vector<bool>> visited(size, vector<bool>(size, false));
        bool found = dfs(startX, startY, endX, endY, path, visited, maze);

        auto end = chrono::high_resolution_clock::now(); 
        chrono::duration<double> duration = end - start; 
        cout << "DFS time: " << duration.count() * 1000 << " ms." << endl;
        cout << "Steps: " << path.size() << endl;

        return found;
    }

private:
    
    bool dfs(int x, int y, int endX, int endY,
        vector<pair<int, int>>& path,
        vector<vector<bool>>& visited,
        vector<vector<char>>& maze) {
        int size = maze.size();

        
        if (x < 0 || y < 0 || x >= size || y >= size || maze[y][x] == '#' || visited[y][x]) {
            return false;
        }

        visited[y][x] = true;
        path.push_back({ x, y });

        
        if (x == endX && y == endY) {
            return true;
        }

        
        const int dx[] = { 0, 1, 0, -1 };
        const int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (dfs(newX, newY, endX, endY, path, visited, maze)) {
                return true;
            }
        }

        path.pop_back(); 
        return false;
    }
};
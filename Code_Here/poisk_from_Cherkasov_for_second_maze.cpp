#include "Maze_from_Astrahankina.h" 
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <stack>
#include <chrono>
#include <climits>

using namespace std;


bool findShortestPathDFS(Maze1& maze, int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {

    vector<vector<bool>> visited(maze.size, vector<bool>(maze.size, false));
    bool found = dfs(maze, startX, startY, endX, endY, path, visited);

    auto end = chrono::high_resolution_clock::now();
    return found;
}


bool dfs(Maze1& maze, int x, int y, int endX, int endY, vector<pair<int, int>>& path, vector<vector<bool>>& visited) {
    if (!inBounds(maze, x, y) || maze.grid[y][x] == Wall || visited[y][x]) {
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

        if (dfs(maze, newX, newY, endX, endY, path, visited)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}


void printMazeWithPath(const Maze1& maze, const vector<pair<int, int>>& path) {
    vector<vector<char>> mazeWithPath(maze.size, vector<char>(maze.size));
  
    for (int y = 0; y < maze.size; ++y) {
        for (int x = 0; x < maze.size; ++x) {
            mazeWithPath[y][x] = (maze.grid[y][x] == Wall) ? '#' : ' ';
        }
    }

    
    for (const auto& p : path) {
        int x = p.first;
        int y = p.second;
        mazeWithPath[y][x] = '.';
    }

    
    mazeWithPath[path.front().second][path.front().first] = 'S';  // Start
    mazeWithPath[path.back().second][path.back().first] = 'E';   // End

    for (int y = 0; y < maze.size; ++y) {
        for (int x = 0; x < maze.size; ++x) {
            cout << mazeWithPath[y][x];
        }
        cout << endl;
    }
}

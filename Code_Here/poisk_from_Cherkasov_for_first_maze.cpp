#include "Maze_from_Vivcharic.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;

bool findShortestPathDFS(Maze& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path) {
    std::vector<std::vector<bool>> visited(maze.size, std::vector<bool>(maze.size, false));
    bool found =  dfs(maze, startX, startY, endX, endY, visited, path);
    return found;
}

bool dfs(Maze& maze, int x, int y, int endX, int endY, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& path) {
    if (x < 0 || x >= maze.size || y < 0 || y >= maze.size || maze.labyrinth[x][y] == Stena || visited[x][y]) {
        return false;
    }

    visited[x][y] = true;
    path.push_back({ x, y });

    if (x == endX && y == endY) {
        return true;
    }

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };
    for (int i = 0; i < 4; i++) {
        if (dfs(maze, x + dx[i], y + dy[i], endX, endY, visited, path)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

int calculatePathLength(const std::vector<std::pair<int, int>>& path) {
    return path.size();
}

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

// Реализация поиска в глубину (DFS)
bool Maze1::findShortestPathDFS(int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {
    auto start = chrono::high_resolution_clock::now();

    vector<vector<bool>> visited(size, vector<bool>(size, false));
    bool found = dfs(startX, startY, endX, endY, path, visited);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "DFS: " << duration.count() * 1000 << " ms." << endl;
    cout << "Steps: " << path.size() << endl;
    return found;
}

bool Maze1::dfs(int x, int y, int endX, int endY, vector<pair<int, int>>& path, vector<vector<bool>>& visited) {
    if (!inBounds(x, y) || maze[y][x] == Wall || visited[y][x]) {
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

        if (dfs(newX, newY, endX, endY, path, visited)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

void Maze1::printMazeWithPath(const vector<pair<int, int>>& path) {
    vector<vector<char>> mazeWithPath(size, vector<char>(size));

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            mazeWithPath[y][x] = (maze[y][x] == Wall) ? '#' : ' ';
        }
    }

    for (const auto& p : path) {
        int x = p.first;
        int y = p.second;
        if (mazeWithPath[y][x] != 'S' && mazeWithPath[y][x] != 'E')
            mazeWithPath[y][x] = '.';
    }

    // Обозначаем старт и финиш
    mazeWithPath[path.front().second][path.front().first] = 'S';
    mazeWithPath[path.back().second][path.back().first] = 'E';

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            cout << mazeWithPath[y][x];
        }
        cout << endl;
    }
}

#include "Maze_from_Astrahankina.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

// ??????????? ????????? Node ??? ????????? ????????
struct Node {
    int x, y, dist;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

// ?????????? ????????? ????????
bool findShortestPathDijkstra(Maze1& maze, int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {

    vector<vector<int>> dist(maze.size, vector<int>(maze.size, INT_MAX));
    dist[startY][startX] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ startX, startY, 0 });

    vector<vector<pair<int, int>>> parent(maze.size, vector<pair<int, int>>(maze.size, { -1, -1 }));

    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;

        if (x == endX && y == endY) {
            // ??????????????? ????
            while (x != startX || y != startY) {
                path.push_back({ x, y });
                int px = parent[y][x].first;
                int py = parent[y][x].second;
                x = px;
                y = py;
            }
            path.push_back({ startX, startY });
            reverse(path.begin(), path.end());
            return true;
        }

        // ????????? ???????
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (inBounds(maze, newX, newY) && maze.grid[newY][newX] != Wall) {
                int newDist = dist[y][x] + 1;

                if (newDist < dist[newY][newX]) {
                    dist[newY][newX] = newDist;
                    parent[newY][newX] = { x, y };
                    pq.push({ newX, newY, newDist });
                }
            }
        }
    }

    return false; // ???? ?? ??????
}

// ?????????? ?????? ? ??????? (DFS)
bool findShortestPathDijkstra1(Maze1& maze, int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {

    vector<vector<bool>> visited(maze.size, vector<bool>(maze.size, false));
    bool found = Dijkstra1(maze, startX, startY, endX, endY, path, visited);
    return found;
}

// ?????????? ?????? DFS ??????
bool Dijkstra1(Maze1& maze, int x, int y, int endX, int endY, vector<pair<int, int>>& path, vector<vector<bool>>& visited) {
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

        if (Dijkstra1(maze, newX, newY, endX, endY, path, visited)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}



// ?????????? ???????
void printMazeWithPath1(const Maze1& maze, const std::vector<std::pair<int, int>>& path) {
    vector<vector<char>> mazeWithPath(maze.size, vector<char>(maze.size));

    // ?????????? ????????? ? ????
    for (int y = 0; y < maze.size; ++y) {
        for (int x = 0; x < maze.size; ++x) {
            mazeWithPath[y][x] = (maze.grid[y][x] == Wall) ? '#' : ' ';
        }
    }

    // ??????? ???? ???????
    for (const auto& p : path) {
        int x = p.first;
        int y = p.second;
        mazeWithPath[y][x] = '.';
    }

    // ?????????? ????? ? ?????
    mazeWithPath[path.front().second][path.front().first] = 'S';  // Start
    mazeWithPath[path.back().second][path.back().first] = 'E';   // End

    // ?????? ????????? ? ????
    for (int y = 0; y < maze.size; ++y) {
        for (int x = 0; x < maze.size; ++x) {
            cout << mazeWithPath[y][x];
        }
        cout << endl;
    }
}

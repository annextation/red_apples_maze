LLP#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <chrono>
#include "Maze_from_Astrahankina.h"
#include "Maze_from_Vivcharik.h"
using namespace std;

struct Node {
    int x, y, dist;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};


bool inBounds(int x, int y, int size) {
    return x >= 0 && y >= 0 && x < size && y < size;
}

bool findShortestPathDijkstra(const vector<vector<int>>& maze, int size, int wallValue,
    int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {
    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> dist(size, vector<int>(size, INT_MAX));
    dist[startX][startY] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ startX, startY, 0 });

    vector<vector<pair<int, int>>> parent(size, vector<pair<int, int>>(size, { -1, -1 }));

    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { 1, 0, -1, 0 };

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x, y = current.y;

        if (x == endX && y == endY) {
           
            while (x != startX || y != startY) {
                path.push_back({ x, y });
                tie(x, y) = parent[x][y];
            }
            path.push_back({ startX, startY });
            reverse(path.begin(), path.end());

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            cout << "Dijkstra: " << duration.count() * 1000 << " ms." << endl;

            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (inBounds(newX, newY, size) && maze[newX][newY] != wallValue) {
                int newDist = dist[x][y] + 1;

                if (newDist < dist[newX][newY]) {
                    dist[newX][newY] = newDist;
                    parent[newX][newY] = { x, y };
                    pq.push({ newX, newY, newDist });
                }
            }
        }
    }

    return false;

int calculatePathLength(const vector<pair<int, int>>& path) {
    return path.size() - 1;
}

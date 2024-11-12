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


// Определение структуры Node для алгоритма Дейкстры
struct Node {
    int x, y, dist;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

// Реализация алгоритма Дейкстры
bool Maze1::findShortestPathDijkstra(int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {
    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> dist(size, vector<int>(size, INT_MAX));
    dist[startY][startX] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ startX, startY, 0 });

    vector<vector<pair<int, int>>> parent(size, vector<pair<int, int>>(size, { -1, -1 }));

    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;

        if (x == endX && y == endY) {
            // Восстанавливаем путь
            while (x != startX || y != startY) {
                path.push_back({ x, y });
                int px = parent[y][x].first;
                int py = parent[y][x].second;
                x = px;
                y = py;
            }
            path.push_back({ startX, startY });
            reverse(path.begin(), path.end());

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            cout << "Dijkstra: " << duration.count() * 1000 << " ms." << endl;
            cout << "Steps: " << path.size() << endl;
            return true;
        }

        // Исследуем соседей
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (inBounds(newX, newY) && maze[newY][newX] != Wall) {
                int newDist = dist[y][x] + 1;

                if (newDist < dist[newY][newX]) {
                    dist[newY][newX] = newDist;
                    parent[newY][newX] = { x, y };
                    pq.push({ newX, newY, newDist });
                }
            }
        }
    }

    return false; // Путь не найден
}

#include "Maze_from_Vivcharic.h"
#include <chrono>
#include <climits>


using namespace std;

bool findShortestPathDijkstra(Maze& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path) {

    std::vector<std::vector<int>> dist(maze.size, std::vector<int>(maze.size, INT_MAX));
    std::vector<std::vector<std::pair<int, int>>> parent(maze.size, std::vector<std::pair<int, int>>(maze.size, { -1, -1 }));
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<>> pq;

    dist[startX][startY] = 0;
    pq.push({ 0, startX, startY });

    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (x == endX && y == endY) {
            // ?????????????? ????
            while (x != -1 && y != -1) {
                path.push_back({ x, y });
                auto [px, py] = parent[x][y];
                x = px;
                y = py;
            }
            std::reverse(path.begin(), path.end());
            return true;
        }

        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { 1, 0, -1, 0 };

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < maze.size && ny >= 0 && ny < maze.size && maze.labyrinth[nx][ny] == Put) {
                int newDist = d + 1;
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    parent[nx][ny] = { x, y };
                    pq.push({ newDist, nx, ny });
                }
            }
        }
    }

    return false;
}

int calculatePathDijkstraLength(const std::vector<std::pair<int, int>>& path) {
    return path.size();
}

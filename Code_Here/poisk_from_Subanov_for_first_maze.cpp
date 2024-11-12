#include "Maze_from_Vivcharic.h"


using namespace std;

struct Node {
    int x, y, dist;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

// Функция для поиска кратчайшего пути с использованием алгоритма Дейкстры
bool Maze::findShortestPathDijkstra(int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {
    auto start = std::chrono::high_resolution_clock::now();  // Начало замера времени

    // Массив расстояний для всех точек
    vector<vector<int>> dist(size, vector<int>(size, INT_MAX));
    dist[startX][startY] = 0;

    // Очередь с приоритетом для обработки клеток (минимальное расстояние)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ startX, startY, 0 });

    // Массив предков для восстановления пути
    vector<vector<pair<int, int>>> parent(size, vector<pair<int, int>>(size, { -1, -1 }));

    // Направления движения (вправо, вниз, влево, вверх)
    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { 1, 0, -1, 0 };

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x, y = current.y;

        // Если мы достигли выхода, восстанавливаем путь
        if (x == endX && y == endY) {
            while (x != startX || y != startY) {
                path.push_back({ x, y });
                tie(x, y) = parent[x][y];
            }
            path.push_back({ startX, startY });
            reverse(path.begin(), path.end());

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            std::cout << "Dijkstra: " << duration.count() * 1000 << " ms." << std::endl;

            return true; // Путь найден, алгоритм завершен
        }


        // Проверяем соседей
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (inBounds(newX, newY) && labyrinth[newX][newY] != Stena) {
                int newDist = dist[x][y] + 1; // Расстояние от стартовой точки до соседа

                // Если найден более короткий путь, обновляем расстояние и предка
                if (newDist < dist[newX][newY]) {
                    dist[newX][newY] = newDist;
                    parent[newX][newY] = { x, y };
                    pq.push({ newX, newY, newDist });
                }
            }
        }
    }

    /*auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Vremya poiska (Dijkstra): " << duration.count() << " sekund." << std::endl;*/

    return false; // Если выход не найден
}

int Maze::calculatePathDijkstraLength1(const std::vector<std::pair<int, int>>& path) {
    return (path.size() - 1 - 1) / 2; // Длина пути (размер пути минус один)
}


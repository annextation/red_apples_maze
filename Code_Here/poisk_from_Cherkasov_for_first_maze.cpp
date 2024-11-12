#include "Maze_from_Vivcharic.h"
#include "Maze_from_Astrahankina.h"


using namespace std;

// Функция для поиска кратчайшего пути с использованием DFS
bool Maze::findShortestPathDFS1(int startX, int startY, int endX, int endY, vector<pair<int, int>>& path) {
    auto start = std::chrono::high_resolution_clock::now();  // Начало замера времени

    vector<vector<bool>> visited(size, vector<bool>(size, false));
    vector<pair<int, int>> currentPath;
    bool found = dfs1(startX, startY, endX, endY, currentPath, visited);

    auto end = std::chrono::high_resolution_clock::now();  // Конец замера времени
    std::chrono::duration<double> duration = end - start;  // Вычисляем длительность
    std::cout << "DFS: " << duration.count() * 1000 << " ms." << std::endl;

    if (found) {
        path = currentPath;
        return true;
    }
    return false;
}




// Вспомогательная функция DFS для поиска пути
bool Maze::dfs1(int x, int y, int endX, int endY, vector<pair<int, int>>& path, vector<vector<bool>>& visited) {
    // Если достигли конца, сохраняем путь
    if (x == endX && y == endY) {
        path.push_back({ x, y });
        return true;
    }

    // Проверяем границы и проходимость клетки
    if (!inBounds(x, y) || labyrinth[x][y] == Stena || visited[x][y]) {
        return false;
    }

    visited[x][y] = true;
    path.push_back({ x, y });

    // Вспомогательные массивы для направления движения
    const int dx[] = { 0, 1, 0, -1 };  // Вправо, вниз, влево, вверх
    const int dy[] = { 1, 0, -1, 0 };

    // Рекурсивный поиск в каждом направлении
    for (int i = 0; i < 4; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (dfs1(newX, newY, endX, endY, path, visited)) {
            return true;
        }
    }

    path.pop_back(); // Удаляем из пути, если не удалось пройти
    visited[x][y] = false; // Отмечаем как непосещенную для других путей
    return false;
}


// Функция для вычисления длины пути
int Maze::calculatePathLength1(const vector<pair<int, int>>& path) {
    return path.size() - 1;  // Длина пути в шагах (размер пути минус один)
}

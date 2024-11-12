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

Maze1::Maze1(int size) : size(size) {
    // Инициализируем лабиринт стенами
    maze.resize(size, vector<int>(size, Wall));
}

bool Maze1::inBounds(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size;
}

void Maze1::generateMazePrim() {
    srand(static_cast<unsigned int>(time(0)));

    // Список стен
    vector<pair<int, int>> walls;

    // Начальная клетка
    int x = rand() % size;
    int y = rand() % size;

    if (x % 2 == 0) x += 1;
    if (y % 2 == 0) y += 1;
    if (x >= size) x -= 2;
    if (y >= size) y -= 2;

    maze[y][x] = Path;

    // Добавляем соседние стены в список
    vector<pair<int, int>> neighbours = getNeighbours(x, y);
    for (auto& n : neighbours) {
        walls.push_back(n);
    }

    while (!walls.empty()) {
        // Выбираем случайную стену из списка
        int randIndex = rand() % walls.size();
        int wx = walls[randIndex].first;
        int wy = walls[randIndex].second;

        // Удаляем стену из списка
        walls.erase(walls.begin() + randIndex);

        // Проверяем, разделяет ли стена две клетки
        int dx = 0, dy = 0;

        if (wx % 2 == 1 && wy % 2 == 0) {
            dy = 1;
        }
        else if (wx % 2 == 0 && wy % 2 == 1) {
            dx = 1;
        }
        else {
            continue;
        }

        int nx = wx + dx;
        int ny = wy + dy;
        int nx2 = wx - dx;
        int ny2 = wy - dy;

        if (inBounds(nx, ny) && inBounds(nx2, ny2)) {
            if (maze[ny][nx] != maze[ny2][nx2]) {
                maze[wy][wx] = Path;

                if (maze[ny][nx] == Wall) {
                    maze[ny][nx] = Path;
                    vector<pair<int, int>> neighbours = getNeighbours(nx, ny);
                    for (auto& n : neighbours) {
                        if (maze[n.second][n.first] == Wall)
                            walls.push_back(n);
                    }
                }
                if (maze[ny2][nx2] == Wall) {
                    maze[ny2][nx2] = Path;
                    vector<pair<int, int>> neighbours = getNeighbours(nx2, ny2);
                    for (auto& n : neighbours) {
                        if (maze[n.second][n.first] == Wall)
                            walls.push_back(n);
                    }
                }
            }
        }
    }
}

vector<pair<int, int>> Maze1::getNeighbours(int x, int y) {
    vector<pair<int, int>> neighbours;

    // Рассматриваем 4 направления
    const int dx[] = { 0, 2, 0, -2 };
    const int dy[] = { -2, 0, 2, 0 };

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        int wx = x + dx[i] / 2;
        int wy = y + dy[i] / 2;

        if (inBounds(nx, ny)) {
            if (maze[ny][nx] == Wall) {
                neighbours.push_back({ wx, wy });
            }
        }
    }
    return neighbours;
}

void Maze1::printMaze() {
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            cout << (maze[y][x] == Wall ? "#" : " ");
        }
        cout << endl;
    }
}

const vector<vector<int>>& Maze1::getMaze() const {
    return maze;
}


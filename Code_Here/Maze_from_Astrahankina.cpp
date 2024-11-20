#include "Maze_from_Astrahankina.h"
#include <vector>
#include <cstdlib>
#include <ctime>

Maze1 createMaze(int size) {
    Maze1 maze;
    maze.size = size;
    maze.grid.resize(size, std::vector<int>(size, Wall));
    return maze;
}

bool inBounds(const Maze1& maze, int x, int y) {
    return x >= 0 && x < maze.size && y >= 0 && y < maze.size;
}

std::vector<std::pair<int, int>> getNeighbours(const Maze1& maze, int x, int y) {
    std::vector<std::pair<int, int>> neighbours;

    // ????????????? 4 ???????????
    const int dx[] = { 0, 2, 0, -2 };
    const int dy[] = { -2, 0, 2, 0 };

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int wx = x + dx[i] / 2;
        int wy = y + dy[i] / 2;

        if (inBounds(maze, nx, ny) && maze.grid[ny][nx] == Wall) {
            neighbours.emplace_back(wx, wy);
        }
    }
    return neighbours;
}

void generateMazePrim(Maze1& maze) {
    srand(static_cast<unsigned int>(time(0)));

    // ?????? ????
    std::vector<std::pair<int, int>> walls;

    maze.grid[0][1] = Path;
    maze.grid[maze.size - 1][maze.size - 2] = Path;

    // ????????? ?????
    int x = rand() % maze.size;
    int y = rand() % maze.size;

    // ?????????? ????????? ? ???????? ?????????
    x = x % 2 == 0 ? x + 1 : x;
    y = y % 2 == 0 ? y + 1 : y;

    maze.grid[y][x] = Path;

    // ????????? ???????? ?????
    for (const auto& neighbour : getNeighbours(maze, x, y)) {
        walls.push_back(neighbour);
    }

    while (!walls.empty()) {
        // ???????? ????????? ?????
        int index = rand() % walls.size();
        int wx = walls[index].first;
        int wy = walls[index].second;
        walls.erase(walls.begin() + index);

        // ?????????, ????? ?? ??????? ?????? ????? ??? ?????
        int dx = 0, dy = 0;

        if (wx % 2 == 1 && wy % 2 == 0) dy = 1;  // ???????????? ?????
        else if (wx % 2 == 0 && wy % 2 == 1) dx = 1; // ?????????????? ?????
        else continue;

        int nx = wx + dx;
        int ny = wy + dy;
        int nx2 = wx - dx;
        int ny2 = wy - dy;

        if (inBounds(maze, nx, ny) && inBounds(maze, nx2, ny2) && maze.grid[ny][nx] != maze.grid[ny2][nx2]) {
            maze.grid[wy][wx] = Path; // ??????? ?????

            if (maze.grid[ny][nx] == Wall) {
                maze.grid[ny][nx] = Path;
                for (const auto& neighbour : getNeighbours(maze, nx, ny)) {
                    if (maze.grid[neighbour.second][neighbour.first] == Wall) {
                        walls.push_back(neighbour);
                    }
                }
            }

            if (maze.grid[ny2][nx2] == Wall) {
                maze.grid[ny2][nx2] = Path;
                for (const auto& neighbour : getNeighbours(maze, nx2, ny2)) {
                    if (maze.grid[neighbour.second][neighbour.first] == Wall) {
                        walls.push_back(neighbour);
                    }
                }
            }
        }
    }
}

void printMaze(const Maze1& maze) {
    for (const auto& row : maze.grid) {
        for (int cell : row) {
            std::cout << (cell == Wall ? "#" : " ");
        }
        std::cout << '\n';
    }
}

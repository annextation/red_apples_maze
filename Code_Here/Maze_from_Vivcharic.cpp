#include "Maze_from_Vivcharic.h"

const int dx[] = { 2, 0, -2, 0 };
const int dy[] = { 0, 2, 0, -2 };

void generateMaze(Maze& maze) {
    maze.labyrinth.assign(maze.size, std::vector<char>(maze.size, Stena));
    createPath(maze, 1, 1);
    maze.labyrinth[0][1] = Put;  
    maze.labyrinth[maze.size - 1][maze.size - 2] = Put;  
}

void createPath(Maze& maze, int x, int y) {
    maze.labyrinth[x][y] = Put;
    std::vector<int> directions = { 0, 1, 2, 3 };

   
    for (int i = directions.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(directions[i], directions[j]);
    }

    for (int dir : directions) {
        int newX = x + dx[dir];
        int newY = y + dy[dir];
        if (inBounds(maze, newX, newY) && maze.labyrinth[newX][newY] == Stena) {
            maze.labyrinth[x + dx[dir] / 2][y + dy[dir] / 2] = Put;
            createPath(maze, newX, newY);
        }
    }
}

bool inBounds(const Maze& maze, int x, int y) {
    return x >= 0 && x < maze.size && y >= 0 && y < maze.size;
}

void displayMaze(const Maze& maze) {
    for (const auto& row : maze.labyrinth) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

void saveMazeToFile(const Maze& maze, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& row : maze.labyrinth) {
            for (char cell : row) {
                outFile << cell;
            }
            outFile << std::endl;
        }
        outFile.close();
        std::cout << "Labirint sohraneny v fail: " << filename << std::endl;
    }
    else {
        std::cerr << "Ne udalos' otkryt' fail dlya zapisi." << std::endl;
    }
}

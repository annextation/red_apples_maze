#pragma once
#include <vector>
#include <utility>

enum CellType {
    Wall = 1,
    Path = 0
};

class Maze1 {
public:
    Maze1(int size);
    void generateMazePrim();
    void printMaze();

    // Accessor for the maze grid
    const std::vector<std::vector<int>>& getMaze() const;

    // Pathfinding functions
    bool findShortestPathDijkstra(int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
    bool findShortestPathDFS(int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
    void printMazeWithPath(const std::vector<std::pair<int, int>>& path);

private:
    int size;
    std::vector<std::vector<int>> maze;

    // Utility functions
    bool inBounds(int x, int y);
    std::vector<std::pair<int, int>> getNeighbours(int x, int y);

    // For DFS
    bool dfs(int x, int y, int endX, int endY, std::vector<std::pair<int, int>>& path, std::vector<std::vector<bool>>& visited);
};


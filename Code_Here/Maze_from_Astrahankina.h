#pragma once
#include <vector>
#include <utility>
#include <iostream>

enum CellType {
    Wall = 1,
    Path = 0
};


struct Maze1 {
    int size;
    std::vector<std::vector<int>> grid;
};


Maze1 createMaze(int size);
void generateMazePrim(Maze1& maze);
void printMaze(const Maze1& maze);

bool inBounds(const Maze1& maze, int x, int y);
std::vector<std::pair<int, int>> getNeighbours(const Maze1& maze, int x, int y);
bool findShortestPathDijkstra(Maze1& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
bool findShortestPathDFS(Maze1& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
void printMazeWithPath(const Maze1& maze, const std::vector<std::pair<int, int>>& path);
bool dfs(Maze1& maze, int x, int y, int endX, int endY, std::vector<std::pair<int, int>>& path, std::vector<std::vector<bool>>& visited);
bool findShortestPathDijkstra1(Maze1& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
void printMazeWithPath1(const Maze1& maze, const std::vector<std::pair<int, int>>& path);
bool Dijkstra1(Maze1& maze, int x, int y, int endX, int endY, std::vector<std::pair<int, int>>& path, std::vector<std::vector<bool>>& visited);

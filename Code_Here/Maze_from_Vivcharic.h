#pragma once
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <fstream>

const char Stena = '#';
const char Put = ' ';


struct Maze {
    int size;
    std::vector<std::vector<char>> labyrinth;
};


void generateMaze(Maze& maze);
bool inBounds(const Maze& maze, int x, int y);
void displayMaze(const Maze& maze);
void saveMazeToFile(const Maze& maze, const std::string& filename);
bool dfs(Maze& maze, int x, int y, int endX, int endY, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& path);
void createPath(Maze& maze, int x, int y);
bool findShortestPathDFS(Maze& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
int calculatePathLength(const std::vector<std::pair<int, int>>& path);
bool findShortestPathDijkstra(Maze& maze, int startX, int startY, int endX, int endY, std::vector<std::pair<int, int>>& path);
int calculatePathDijkstraLength(const std::vector<std::pair<int, int>>& path);

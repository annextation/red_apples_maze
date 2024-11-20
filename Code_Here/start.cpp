#include "start.h"
#include "Maze_from_Vivcharic.h"
#include "Maze_from_Astrahankina.h"
#include "time.h"
#include <iostream>
#include <vector>

using namespace std;



void start_search_labirint_1() {
    cout << "Input size: ";
    int size = GetCorrectNumber<int>(5, 73);

    Maze maze = { size };
    cout << "The maze was created for " << time_generation(maze, generateMaze) * 1000 << " ms." << endl;
    displayMaze(maze);

    vector<pair<int, int>> pathDijkstra;
    auto start = std::chrono::high_resolution_clock::now();
    bool foundDijkstra = findShortestPathDijkstra(maze, 0, 1, maze.size - 1, maze.size - 2, pathDijkstra);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    if (foundDijkstra) {
        cout << "Dijkstra: " << endl << duration.count() * 1000 << " ms." << endl;
        cout << "Steps Dijkstra: " << calculatePathDijkstraLength(pathDijkstra) << endl;
    }
    else {
        cout << "No path found." << endl;
    }

    vector<pair<int, int>> path;
    auto start1 = std::chrono::high_resolution_clock::now();
    bool foundDFS = findShortestPathDFS(maze, 0, 1, maze.size - 1, maze.size - 2, path);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    if (foundDFS) {
        cout << "DFS: " << endl << duration1.count() * 1000 << " ms." << endl;
        cout << "Steps DFS: " << calculatePathLength(path) << endl;
    }
    else {
        cout << "No path found." << endl;
    }
}

void start_search_labirint_2() {
    cout << "Input size: ";
    int size = GetCorrectNumber<int>(5, 73);

    Maze1 maze = createMaze(size);
    cout << "The maze was created for " << time_generation(maze, generateMazePrim) * 1000 << " ms." << endl;
    printMaze(maze);

    int startX = 1, startY = 1;
    int endX = size - 2, endY = size - 2;

    vector<pair<int, int>> pathDijkstra;
    auto start = std::chrono::high_resolution_clock::now();
    bool foundDijkstra = findShortestPathDijkstra(maze, startX, startY, endX, endY, pathDijkstra);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    if (foundDijkstra) {
        
        cout << "Dijkstra: " << endl << duration.count() * 1000 << " ms." << endl;
        cout << "Steps Dijkstra: " << calculatePathLength(pathDijkstra) << endl;

    }
    else {
        std::cout << "No path found." << endl;
    }

    
    std::vector<std::pair<int, int>> pathDFS;
    auto start1 = std::chrono::high_resolution_clock::now();
    bool foundDFS = findShortestPathDFS(maze, startX, startY, endX, endY, pathDFS);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    if (foundDFS) {
        
        cout << "DFS: " << endl << duration1.count() * 1000 << " ms." << endl;
        cout << "Steps DFS: " << calculatePathLength(pathDFS) << endl;
    }
    else {
        std::cout << "No path found ." << endl;
    }

}

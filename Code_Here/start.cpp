#include "start.h"
#include "Maze_from_Vivcharic.h"
#include "Maze_from_Astrahankina.h"
#include "verification.h"
#include "time.h"
#include <iostream>
#include <vector>

using namespace std;

void start_search_labirint_1(){
    int size;
    cout << "Size: ";
    while (1) {
        cin >> size;
        if (size >= 73 || size < 3 || size % 2 == 0) {
            cout << "Incorect input, try again" << endl << "> ";
        }
        else {
            break;
        }
    }
    

    Maze maze(size);
    double time_maze1 = time_generate_maze_from_Vivcharic(maze);
    maze.display();
    cout << "The maze was created for " << time_maze1 * 1000 << " ms." << endl;
    verifyMazeSaving;
    // Определяем начальную и конечную точки
    int startX = 0, startY = 1;
    int endX = size - 1, endY = size - 2;
    
    // Поиск кратчайшего пути
    vector<pair<int, int>> path;
    if (maze.findShortestPathDFS1(startX, startY, endX, endY, path)) {
        //        for (const auto& p : path) {
        //            cout << "(" << p.first << ", " << p.second << ") ";
        //        }

                // Вычисление длины пути
        int pathLength = maze.calculatePathLength1(path);
        cout << "Steps: " << pathLength << endl;
    }
    else {
        cout << "Error.";
    }
    cout << endl;

    // Поиск кратчайшего пути методом Дейкстры
    if (maze.findShortestPathDijkstra(startX, startY, endX, endY, path)) {
        //      for (const auto& p : path) {
        //             cout << "(" << p.first << ", " << p.second << ") ";
        //        }

                // Вычисление длины пути
        int pathLength = maze.calculatePathDijkstraLength1(path);
        cout << "Steps: " << pathLength << endl;
    }
    else {
        cout << "Error" << endl;
    }
    cout << endl;

}

void start_search_labirint_2(){
        int size;
        cout << "Size: ";
        while (1) {
            cin >> size;
            if (size >= 73 || size < 3 || size % 2 == 0) {
                cout << "Incorect input, try again" << endl << "> ";
            }
            else {
                break;
            }
        }


        Maze1 maze(size);
        double time_maze2 = time_generate_maze_from_Astrahankina(maze);
        maze.printMaze();
        cout << "The maze was created for " << time_maze2 * 1000 << " ms." << endl;

        int startX = 1, startY = 1;
        int endX = size - 2, endY = size - 2;

        std::vector<std::pair<int, int>> pathDijkstra;
        if (maze.findShortestPathDijkstra(startX, startY, endX, endY, pathDijkstra)) {
            //std::cout << "\nPath found using Dijkstra's Algorithm:\n";
            //maze.printMazeWithPath(pathDijkstra);
        }
        else {
            std::cout << "No path found using Dijkstra's Algorithm.\n";
        }

        std::vector<std::pair<int, int>> pathDFS;
        if (maze.findShortestPathDFS(startX, startY, endX, endY, pathDFS)) {
            //std::cout << "\nPath found using Depth-First Search:\n";
            //maze.printMazeWithPath(pathDFS);
        }
        else {
            std::cout << "No path found using Depth-First Search.\n";
        }


}

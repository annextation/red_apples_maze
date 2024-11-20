#pragma once
#include "Maze_from_Vivcharic.h"
#include "Maze_from_Astrahankina.h"
#include "time.h"
#include <chrono>

template <typename MazeType, typename GenerateMazeFunc>
double time_generation(MazeType& maze, GenerateMazeFunc generateFunc) {
    auto start = std::chrono::high_resolution_clock::now();
    generateFunc(maze);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

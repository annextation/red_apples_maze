#include "Maze_from_Vivcharic.h"
#include "Maze_from_Astrahankina.h"
#include "time.h"
#include <chrono>


double time_generate_maze_from_Vivcharic(Maze& maze) {
	auto start = std::chrono::high_resolution_clock::now();
    maze.generate();
    auto end = std::chrono::high_resolution_clock::now();  
    std::chrono::duration<double> duration = end - start;  
    return duration.count();
}

double time_generate_maze_from_Astrahankina(Maze1& maze) {
    auto start = std::chrono::high_resolution_clock::now();
    maze.generateMazePrim();;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

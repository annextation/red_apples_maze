#include "Maze_from_Vivcharic.h"
#include "verification.h"

void verifyMazeGeneration(int size) {
    Maze maze(size);
    maze.generate();
    //std::cout << "Generated maze of size " << size << ":\n";
    maze.display();
}

void verifyMazeSaving(int size, const std::string& filename) {
    Maze maze(size);
    maze.generate();
    maze.saveToFile(filename);
    //std::cout << "Maze saved to " << filename << std::endl;
}


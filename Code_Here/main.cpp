#include "Maze_from_Vivcharic.h"
#include "Maze_from_Astrahankina.h"
#include "start.h"
#include <format>

using namespace std;
void print_menu() {
    cout << "--------------------" << endl;
    cout << "Methods: " << endl;
    cout << "1. Random wandering" << endl;
    cout << "2. Prima" << endl;
    cout << "0. Exit" << endl;
    cout << "> ";
}

template <typename Type>
Type GetCorrectNumber(Type min, Type max) {
    Type x;
    while ((std::cin >> x).fail()
        || std::cin.peek() != '\n'
        || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Enter a number of the type " << typeid(Type).name() << " in the range from " << min << " to " << max << ": ";
    }
    //std::cerr << x << std::endl;
    return x;
}

int main() {
    int input;
    do {
        print_menu();
        input = GetCorrectNumber<int>(0, 2);
        switch (input)
        {
        case 1:
            start_search_labirint_1();
            break;
        case 2:
            start_search_labirint_2();
        }
    } while (input != 0);
        
    return 0;
}



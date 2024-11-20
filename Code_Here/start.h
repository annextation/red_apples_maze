#pragma once
#include <iostream>
#include <format>


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

void start_search_labirint_1();

void start_search_labirint_2();

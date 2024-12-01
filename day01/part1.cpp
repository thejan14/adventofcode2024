#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <set>
#include <ranges>

#include "aoc.h"

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto leftList = std::multiset<int>{};
    auto rightList = std::multiset<int>{};

    std::string line;
    auto parseStream = std::stringstream(input);
    while (getline(parseStream, line))
    {
        leftList.emplace(std::stoi(line.substr(0, 5)));
        rightList.emplace(std::stoi(line.substr(5+3, 5)));
    }
    auto answer = 0;
    for (auto const pair : std::views::zip(leftList, rightList))
    {
        answer += std::abs(std::get<0>(pair) - std::get<1>(pair));
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

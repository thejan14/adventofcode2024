﻿#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>

#include "aoc.h"

std::vector<std::string_view> map;

bool checkPair(char const a, char const b)
{
    if (a == 'M')
    {
        return b == 'S';
    }

    if (a == 'S')
    {
        return b == 'M';
    }

    return false;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */
    
    map = input
        | std::views::split('\n')
        | std::views::transform([](auto const& line) { return std::string_view(line); })
        | std::ranges::to<std::vector>();

    auto answer = 0;
    for (auto y = 1ULL; y < map.size() - 1; y++)
    {
        for (auto x = 1ULL; x < map[y].size() - 1; x++)
        {
            if (map[y][x] == 'A')
            {
                answer += checkPair(map[y - 1][x - 1], map[y + 1][x + 1])
                    && checkPair(map[y + 1][x - 1], map[y - 1][x + 1]);
            }
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

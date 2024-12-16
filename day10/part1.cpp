#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>
#include <map>
#include <set>
#include <numeric>  
#include <algorithm>

#include "aoc.h"

// north, east, south, west
const std::array<std::pair<int, int>, 4> directions
{
    { {-1, 0}, {0, 1}, {1, 0}, {0, -1} }
};

void findTrail(std::vector<std::vector<int>> const& map, std::set<std::pair<int, int>>& visited, int& score, int i, int j)
{
    auto const current = map[i][j];
    for (auto const [di, dj] : directions)
    {
        auto const ni = i + di;
        auto const nj = j + dj;
        if (ni > -1
            && ni < map.size()
            && nj > -1
            && nj < map[ni].size()
            && map[ni][nj] == current + 1)
        {
            if (auto const [_, isNew] = visited.emplace(ni, nj); isNew)
            {
                if (map[ni][nj] == 9)
                {
                    score += 1;
                }
                else
                {
                    findTrail(map, visited, score, ni, nj);
                }
            }
        }
    }
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto map = input
        | std::views::split('\n')
        | std::views::transform([](auto const& line)
            {
                return line
                    | std::views::transform([](auto const& c) { return c - '0'; })
                    | std::ranges::to<std::vector>();
            })
        | std::ranges::to<std::vector>();

    auto answer = 0;
    for (auto i = 0; i < map.size(); i++)
    {
        for (auto j = 0; j < map.size(); j++)
        {
            if (map[i][j] == 0)
            {
                auto visited = std::set<std::pair<int, int>>{ { i, j } };
                findTrail(map, visited, answer, i, j);
            }
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

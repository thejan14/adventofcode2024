#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>

#include "aoc.h"

constexpr std::array<char, 4> term{ 'X', 'M', 'A', 'S' };
constexpr std::array<std::pair<int, int>, 8> directions
{
    { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} }
};

std::vector<std::vector<char>> map;

// (sx, sy) => start position
// (dx, dy) => direction vector
bool checkDirection(int sx, int sy, int const dx, int const dy)
{
    if (map[sy][sx] != term[0])
    {
        return false;
    }

    for (auto i = 1; i < 4; i++)
    {
        sx += dx;
        sy += dy;
        if (sy < 0
            || sy > map.size() - 1
            || sx < 0
            || sx > map[sy].size() - 1
            || map[sy][sx] != term[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    for (auto const line : input | std::views::split('\n'))
    {
        auto const row = std::string_view{ line };
        map.emplace_back(row.begin(), row.end());
    }

    auto answer = 0;
    for (auto y = 0ULL; y < map.size(); y++)
    {
        for (auto x = 0ULL; x < map[y].size(); x++)
        {
            for (auto const& [dx, dy] : directions)
            {
                answer += checkDirection(x, y, dx, dy);
            }
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

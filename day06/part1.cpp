#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>
#include <map>
#include <set>
#include <algorithm>

#include "aoc.h"

constexpr int DIMENSION = 10 + 1; // +1 for line endings '\n'

enum Direction { N, E, S, W };
std::vector<std::string> map;

template <Direction D>
bool findCollision(int& x, int& y)
{
    auto cx = int{};
    auto cy = int{};
    while (map[y][x] != '#')
    {
        cx = x;
        cy = y;

        map[y][x] = 'X';
        if constexpr (D == N)
            y -= 1;
        if constexpr (D == E)
            x += 1;
        if constexpr (D == S)
            y += 1;
        if constexpr (D == W)
            x -= 1;

        if constexpr (D == N || D == S)
        {
            if (y < 0 || y > map.size() - 1)
                return false;
        }
        else
        {
            if (x < 0 || x > map[y].size() - 1)
                return false;
        }
    }

    x = cx;
    y = cy;
    return true;
}

bool findCollision(Direction d, int& x, int& y)
{
    switch (d)
    {
        case N:
            return findCollision<N>(x, y);
        case E:
            return findCollision<E>(x, y);
        case S:
            return findCollision<S>(x, y);
        default:
            return findCollision<W>(x, y);
    }
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    map = input
        | std::views::split('\n')
        | std::views::transform([](auto const& line) { return std::string(line.begin(), line.end()); })
        | std::ranges::to<std::vector>();

    auto it = std::ranges::find(input, '^');
    auto index = it - input.begin();
    auto currentX = static_cast<int>(index % (map[0].size() + 1));
    auto currentY = static_cast<int>(index / (map.size() + 1));
    auto currentD = Direction::N;
    while (findCollision(currentD, currentX, currentY))
    {
        currentD = static_cast<Direction>((currentD + 1) % 4);
    }

    auto answer = 0;
    for (auto const& row : map)
    {
        answer += std::ranges::count(row, 'X');
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

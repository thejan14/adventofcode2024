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
constexpr Direction turnRight()
{
    return static_cast<Direction>((D + 1) % 4);
}

template <Direction D>
bool moveTo(int& x, int& y)
{
    if constexpr (D == N)
    {
        if (y == 0)
            return false;
        y -= 1;
    }
    else if constexpr (D == E)
    {
        if (x == map[y].size() - 1)
            return false;
        x += 1;
    }
    else if constexpr (D == S)
    {
        if (y == map.size() - 1)
            return false;
        y += 1;
    }
    else
    {
        if (x == 0)
            return false;
        x -= 1;
    }

    return true;
}

template <Direction D>
bool checkLoopFrom(int x, int y)
{
    auto constexpr nextD = turnRight<D>();
    if (map[y][x] == nextD)
    {
        return true;
    }

    auto cx = x;
    auto cy = y;
    while (moveTo<nextD>(x, y))
    {
        if (map[x][y] == '#' && map[cy][cx] == turnRight<nextD>())
        {
            return true;
        }

        cx = x;
        cy = y;
    }
    
    return false;
}

template <Direction D>
bool findCollision(int& x, int& y, int& count)
{
    auto cx = x;
    auto cy = y;
    map[y][x] = D;
    while (map[y][x] != '#')
    {
        if (checkLoopFrom<D>(x, y))
        {
            count += 1;
        }

        cx = x;
        cy = y;
        map[y][x] = D;
        if (!moveTo<D>(x, y))
        {
            return false;
        }
    }
    
    x = cx;
    y = cy;
    return true;
}

bool findCollision(Direction d, int& x, int& y, int& count)
{
    switch (d)
    {
    case N:
        return findCollision<N>(x, y, count);
    case E:
        return findCollision<E>(x, y, count);
    case S:
        return findCollision<S>(x, y, count);
    default:
        return findCollision<W>(x, y, count);
    }
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    /* SOLUTION NOT READY, PRODUCES WRONG RESULT */

    map = input
        | std::views::split('\n')
        | std::views::transform([](auto const& line) { return std::string(line.begin(), line.end()); })
        | std::ranges::to<std::vector>();

    auto it = std::ranges::find(input, '^');
    auto index = it - input.begin();
    auto currentX = static_cast<int>(index % (map[0].size() + 1));
    auto currentY = static_cast<int>(index / (map.size() + 1));
    auto currentD = Direction::N;
    auto answer = 0;
    while (findCollision(currentD, currentX, currentY, answer))
    {
        currentD = static_cast<Direction>((currentD + 1) % 4);
        for (auto line : map)
        {
            std::cout << line << "\n";
        }

        std::cout << "\n";
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

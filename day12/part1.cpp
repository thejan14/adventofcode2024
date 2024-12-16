#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>
#include <map>
#include <queue>
#include <set>

#include "aoc.h"

constexpr std::array<std::pair<int, int>, 4> directions
{
    { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }
};

std::vector<std::string> field;

bool isUpper(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool isInBounds(int i, int j)
{
    return i > -1
        && i < field.size()
        && j > -1
        && j < field[i].size();
}

int calculateRegionPrice(int i, int j)
{
    auto const origin = field[i][j];
    auto const visited = static_cast<char>(std::tolower(origin));
    auto area = 0;
    auto perimeter = 0;

    auto queue = std::set<std::pair<int, int>>{};
    queue.emplace(i, j);
    while (!queue.empty())
    {
        auto const it = queue.begin();
        auto [ci, cj] = *it;
        queue.erase(it);

        area += 1;
        field[ci][cj] = visited;
        for (auto const [di, dj] : directions)
        {
            auto const ni = ci + di;
            auto const nj = cj + dj;
            if (isInBounds(ni, nj))
            {
                if (field[ni][nj] == origin)
                {
                    queue.emplace(ni, nj);
                }
                else if (field[ni][nj] != visited)
                {
                    perimeter += 1;
                }
            }
            else
            {
                perimeter += 1;
            }
        }
    }

    return area * perimeter;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto answer = 0;
    field = input
        | std::views::split('\n')
        | std::views::transform([](auto const& line) { return std::string(line.begin(), line.end()); })
        | std::ranges::to<std::vector>();

    auto areaMap = std::map<char, int>{};
    auto perimeterMap = std::map<char, int>{};
    for (auto i = 0ULL; i < field.size(); i++)
    {
        for (auto j = 0ULL; j < field[i].size(); j++)
        {
            if (isUpper(field[i][j]))
            {
                answer += calculateRegionPrice(i, j);
            }
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

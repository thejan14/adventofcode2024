#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>
#include <map>
#include <set>
#include <numeric>

#include "aoc.h"

using vec2 = std::pair<int, int>;

std::vector<std::string_view> scan;
std::map<char, std::vector<vec2>> antennas;
std::set<vec2> antinodes;

vec2 get_direction(vec2 const& a, vec2 const& b)
{
    return { a.first - b.first, a.second - b.second };
}

bool is_in_bounds(vec2 const& pos)
{
    return pos.first > -1
        && pos.first < scan.size()
        && pos.second > -1
        && pos.second < scan[pos.first].size();
}

template <typename T>
void get_antinodes(vec2 const& antennaPos, vec2 const& directionVec, T method)
{
    auto const [i, j] = antennaPos;
    auto const [di, dj] = directionVec;
    auto antinode = std::make_pair(method(i, di), method(j, dj));

    auto n = 1;
    while (is_in_bounds(antinode))
    {
        n += 1;
        antinodes.insert(antinode);
        antinode = std::make_pair(method(i, (di * n)), method(j, (dj * n)));
    }
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    scan = input
        | std::views::split('\n')
        | std::views::transform([](auto const& line) { return std::string_view{ line }; })
        | std::ranges::to<std::vector>();

    for (auto i = 0; i < scan.size(); i++)
    {
        for (auto j = 0; j < scan[i].size(); j++)
        {
            if (scan[i][j] != '.')
            {
                antennas[scan[i][j]].emplace_back(i, j);
            }
        }
    }

    for (auto const& [freq, coordinates] : antennas)
    {
        for (auto n = 0; n < coordinates.size(); n++)
        {
            for (auto m = n + 1; m < coordinates.size(); m++)
            {
                auto const& antenna1 = coordinates[n];
                auto const& antenna2 = coordinates[m];
                auto const [di, dj] = get_direction(antenna1, antenna2);
                auto const directionGcd = std::gcd(di, dj);
                auto const directionVec = std::make_pair(di / directionGcd, dj / directionGcd);
                get_antinodes(antenna1, directionVec, std::plus<int>{});
                get_antinodes(antenna1, directionVec, std::minus<int>{});
                get_antinodes(antenna2, directionVec, std::plus<int>{});
                get_antinodes(antenna2, directionVec, std::minus<int>{});
            }
        }
    }

    auto answer = antinodes.size();

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

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

using ull = unsigned long long;

static ull svtoull(std::string_view const& sv)
{
    ull value;
    if (std::from_chars(sv.data(), sv.data() + sv.size(), value).ec == std::errc{})
    {
        return value;
    }

    throw std::invalid_argument("not a number");
}

int countDigits(ull engraving)
{
    auto count = 0;
    while (engraving > 0)
    {
        engraving /= 10;
        count += 1;
    }

    return count;
}

std::pair<int, int> split(ull engraving, int const digits)
{
    auto result1 = 0;
    for (auto i = 0; i < digits / 2; i++)
    {
        result1 += (engraving % 10) * std::pow(10, i);
        engraving /= 10;
    }

    auto result2 = 0;
    for (auto i = 0; i < digits / 2; i++)
    {
        result2 += (engraving % 10) * std::pow(10, i);
        engraving /= 10;
    }

    return { result1, result2 };
}

std::map<ull, ull> processBlink(std::map<ull, ull>& stoneMap)
{
    auto newMap = std::map<ull, ull>{};
    for (auto [engraving, count] : stoneMap)
    {
        if (engraving == 0)
        {
            newMap[1] += count;
        }
        else if (auto const digits = countDigits(engraving); digits % 2 == 0)
        {
            auto const [split1, split2] = split(engraving, digits);
            newMap[split1] += stoneMap[engraving];
            newMap[split2] += stoneMap[engraving];
        }
        else
        {
            newMap[engraving * 2024] += stoneMap[engraving];
        }
    }
    
    return newMap;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto stonesMap = std::map<ull, ull>{};
    for (auto const stone : input
        | std::views::split(' ')
        | std::views::transform([](auto const& n) { return svtoull(std::string_view{ n }); }))
    {
        stonesMap[stone] += 1;
    }
    
    for (auto i = 0; i < 25; i++)
    {
        stonesMap = processBlink(stonesMap);
    }
    
    auto answer = std::ranges::fold_left(stonesMap | std::views::values, 0, std::plus<ull>{});


    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

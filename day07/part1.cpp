#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>
#include <map>

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

bool checkOperators(ull const& testValue, std::vector<ull> const& numbers, ull acc, int index)
{
    if (index > numbers.size() - 1)
    {
        return acc == testValue;
    }

    if (index == 0)
    {
        return checkOperators(testValue, numbers, numbers[index], index + 1);
    }

    if (checkOperators(testValue, numbers, acc + numbers[index], index + 1))
    {
        return true;
    }
    else
    {
        return checkOperators(testValue, numbers, acc * numbers[index], index + 1);
    }
}


int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto answer = 0ULL;
    for (auto const line : input | std::views::split('\n') | std::views::transform([](auto const l) { return std::string_view{ l }; }))
    {
        auto const testValue = svtoull(line.substr(0, line.find(':')));
        auto const numbers = line.substr(line.find(' ') + 1)
            | std::views::split(' ')
            | std::views::transform([](auto const n) { return svtoull(std::string_view{ n }); })
            | std::ranges::to<std::vector>();
        
        if (checkOperators(testValue, numbers, 0, 0))
        {
            answer += testValue;
        }
    }


    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

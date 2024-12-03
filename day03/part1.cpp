#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <regex>

#include "aoc.h"

const std::regex mulRegex = std::regex(R"(mul\((\d+),(\d+)\))");

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto answer = 0;
    std::smatch match;
    auto it = input.cbegin();
    while (regex_search(it, input.cend(), match, mulRegex))
    {
        answer += stoi(match[1]) * stoi(match[2]);
        it = match.suffix().first - 1;
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

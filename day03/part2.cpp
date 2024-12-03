#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <regex>

#include "aoc.h"

const std::regex mulRegex = std::regex(R"(mul\((\d+),(\d+)\)|(do|don't)\(\))");

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto answer = 0;
    auto multEnabled = true;
    std::smatch match;
    auto it = input.cbegin();
    while (regex_search(it, input.cend(), match, mulRegex))
    {
        if (match[3].matched)
        {
            multEnabled = match[3] == "do";
        }
        else if (multEnabled)
        {
            answer += stoi(match[1]) * stoi(match[2]);
        }

        it = match.suffix().first - 1;
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

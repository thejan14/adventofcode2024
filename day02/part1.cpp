#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <set>
#include <ranges>

#include "aoc.h"

static int sign(int const& number)
{
    return (0 < number) - (number < 0);
}

static int svtoi(std::string_view const& sv)
{
    int value;
    if (std::from_chars(sv.data(), sv.data() + sv.size(), value).ec == std::errc{})
    {
        return value;
    }

    throw std::invalid_argument("not a number");
}

static auto getLevels(std::string const& report)
{
    return report
        | std::views::split(' ')
        | std::views::transform([](auto const t) { return svtoi(std::string_view(t)); });
}

static bool checkReportLevels(std::string const& report)
{
    auto reportDirection = 0;
    auto lastLevel = -1;
    for (auto const level : getLevels(report))
    {
        if (lastLevel > -1)
        {
            auto delta = lastLevel - level;
            auto distance = std::abs(delta);
            if (distance < 1 || distance > 3)
            {
                return false;
            }

            auto levelDirection = sign(delta);
            if (reportDirection == 0)
            {
                reportDirection = levelDirection;
            }
            else if (levelDirection != reportDirection)
            {
                return false;
            }
        }

        lastLevel = level;
    }

    return true;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto answer = 0;
    std::string line;
    auto parseStream = std::stringstream(input);
    while (getline(parseStream, line))
    {
        if (checkReportLevels(line))
        {
            answer += 1;
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

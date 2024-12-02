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

static bool checkReportLevels(std::vector<int> const& report)
{
    auto badLevels = 0;
    auto reportDirection = 0;
    auto lastLevel = -1;
    for (auto const level : report)
    {
        auto ignoreLevel = bool{};
        if (lastLevel > -1)
        {
            auto delta = lastLevel - level;
            auto distance = std::abs(delta);
            if (distance < 1 || distance > 3)
            {
                badLevels += 1;
                ignoreLevel = true;
            }
            else
            {
                auto levelDirection = sign(delta);
                if (reportDirection == 0)
                {
                    reportDirection = levelDirection;
                }
                else if (levelDirection != reportDirection)
                {
                    badLevels += 1;
                    ignoreLevel = true;
                }
            }
        }

        if (badLevels > 1)
        {
            return false;
        }

        if (!ignoreLevel)
        {
            lastLevel = level;
        }
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
        auto report = getLevels(line) | std::ranges::to<std::vector>();
        if (checkReportLevels(report))
        {
            answer += 1;
        }
        else
        {
            // in case of a problem there are always two candidates to "fix" the report
            // the algorithm in checkReportLevels will always remove the one that doesn't
            // match to its predecessor. By checking the report in reverse the other
            // candidate will now also be considered.
            std::reverse(report.begin(), report.end());
            if (checkReportLevels(report))
            {
                answer += 1;
            }
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

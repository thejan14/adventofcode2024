#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <set>
#include <ranges>
#include <algorithm>

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

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto const answer = std::ranges::count_if(input | std::views::split('\n'), [](auto const line)
        {
            auto lastDirection = 0;
            for (auto const [levelA, levelB] : line
                | std::views::split(' ')
                | std::views::transform([](auto const t) { return svtoi(std::string_view(t)); })
                | std::views::adjacent<2>)
            {
                auto const delta = levelA - levelB;
                auto const distance = std::abs(delta);
                if (distance < 1 || distance > 3)
                {
                    return false;
                }

                auto direction = sign(delta);
                if (direction != lastDirection && lastDirection != 0)
                {
                    return false;
                }

                lastDirection = direction;
            }

            return true;
        });

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

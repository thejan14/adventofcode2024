#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <ranges>
#include <map>
#include <algorithm> // for std::find

#include "aoc.h"

static int svtoi(std::string_view const& sv)
{
    if (int value; std::from_chars(sv.data(), sv.data() + sv.size(), value).ec == std::errc{})
    {
        return value;
    }

    throw std::invalid_argument("not a number");
}

void parseRules(std::string_view const& block, std::map<int, std::vector<int>>& rules)
{
    for (auto const line : block | std::views::split('\n'))
    {
        auto const row = std::string_view{ line };
        auto const a = svtoi(row.substr(0, 2));
        auto const b = svtoi(row.substr(3, 2));
        rules[a].push_back(b);
    }
}

void parsePrints(std::string_view const& block, std::vector<std::vector<int>>& prints)
{
    for (auto const line : block | std::views::split('\n'))
    {
        auto pages = line
            | std::views::split(',')
            | std::views::transform([](auto const& n) { return svtoi(std::string_view(n)); });
        prints.emplace_back(pages.begin(), pages.end());
    }
}

bool fixPrint(std::map<int, std::vector<int>>& rules, std::vector<int>& print)
{
    auto fixApplied = false;
    for (auto pageIt = print.begin(); pageIt < print.end();)
    {
        auto advance = true;
        auto const page = *pageIt;
        if (auto const ruleIt = rules.find(page); ruleIt != rules.end())
        {
            auto const& [_, followers] = *ruleIt;
            for (auto const follower : followers)
            {
                auto const followerIt = std::ranges::find(print.begin(), pageIt, follower);
                if (followerIt != pageIt)
                {
                    fixApplied = true;

                    // swap pages
                    *pageIt = *followerIt;
                    *followerIt = page;

                    // recheck new page order
                    advance = false;
                    pageIt = followerIt; 
                    break;
                }
            }
        }

        if (advance)
        {
            ++pageIt;
        }
    }

    return fixApplied;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto rules = std::map<int, std::vector<int>>{};
    auto prints = std::vector<std::vector<int>>{};
    auto blockId = 0;
    for (auto const block : input | std::views::split(std::string_view("\n\n")))
    {
        if (blockId == 0)
        {
            parseRules(std::string_view(block), rules);
        }
        else if (blockId == 1)
        {
            parsePrints(std::string_view(block), prints);
        }

        blockId += 1;
    }

    auto answer = 0;
    for (auto& print : prints)
    {
        if (fixPrint(rules, print))
        {
            answer += print[print.size() / 2];
        }
    }

    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

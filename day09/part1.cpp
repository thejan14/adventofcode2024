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

bool isFile(int const i)
{
    return i != -1;
}

int main()
{
    auto input = aoc::readInput();
    const auto execStart = std::chrono::high_resolution_clock::now();

    /* begin solution */

    auto isFreeSpace = false;
    auto index = 0;
    auto fileSystem = std::vector<int>(input.size() * 9, -1); // prepare max size free space
    auto endIt = std::ranges::fold_left(input, fileSystem.begin(), [&isFreeSpace, &index](auto it, auto const c)
        {
            auto nextIt = std::next(it, c - '0');
            if (!isFreeSpace)
            {
                std::ranges::fill(it, nextIt, index);
                index += 1;
            }

            isFreeSpace = !isFreeSpace;
            return nextIt;
        });

    fileSystem.resize(endIt - fileSystem.begin());
    auto freeSpaceIt = std::ranges::find(fileSystem, -1);
    auto fileSpaceIt = std::ranges::find_if(fileSystem | std::views::reverse, isFile);
    do
    {
        *freeSpaceIt = *fileSpaceIt;
        *fileSpaceIt = -1;
        freeSpaceIt = std::ranges::find(std::next(freeSpaceIt), fileSystem.end(), -1);
        fileSpaceIt = std::ranges::find_if(std::next(fileSpaceIt), fileSystem.rend(), isFile);
    } while (freeSpaceIt - fileSystem.begin() < fileSystem.rend() - fileSpaceIt);

    auto answer = 0ULL;
    auto it = fileSystem.begin();
    while (it != fileSystem.end())
    {
        if (*it != -1)
        {
            auto i = it - fileSystem.begin();
            answer += i * *it;

        }

        std::advance(it, 1);
    }


    /* end solution */

    const auto execEnd = std::chrono::high_resolution_clock::now();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds> (execEnd - execStart);
    std::cout << std::format("{} ({})", answer, micros);
}

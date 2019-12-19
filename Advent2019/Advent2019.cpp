// Advent2019.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "shared/types.h"

#include "day01.hpp"
#include "day02.hpp"
#include "day03.hpp"

int main()
{
	printf("Advent of Code 2019\n\n");

	day01("./input/day01.txt");
	day02("./input/day02.txt");
	day03("./input/day03.txt");

	return 0;
}

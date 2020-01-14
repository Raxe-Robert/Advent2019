// Advent2019.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "advent2019.h"

int main()
{
	printf("Advent of Code 2019\n\n");

	auto input_day01 = ReadAllText("./input/day01.txt");
	day01(input_day01);

	auto input_day02 = ReadAllText("./input/day02.txt");
	day02(input_day02);

	auto input_day03 = ReadAllText("./input/day03.txt");
	day03(input_day03);

	s32 day04_lower = 168630;
	s32 day04_upper = 718098;
	day04(day04_lower, day04_upper);

	return 0;
}

// Advent2019.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "advent2019.h"

int main()
{
	printf("Advent of Code 2019\n\n");

	auto input_day01 = ReadAllText("./input/day01.txt");
	stopwatch(day01, input_day01);

	auto input_day02 = ReadAllText("./input/day02.txt");
	stopwatch(day02, input_day02);

	auto input_day03 = ReadAllText("./input/day03.txt");
	stopwatch(day03, input_day03);

	string day04_lower = String("168630", 6);
	string day04_upper = String("718098", 6);
	stopwatch(day04, day04_lower, day04_upper);

	return 0;
}

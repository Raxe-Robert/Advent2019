void day05(string input)
{
	intcodeArr arr = ReadIntcodeInput(input);

	printf("[Day05][1] Input should be 1\n");
	auto val1 = IntcodeComputer(arr);
	printf("[Day05][1] %i\n", val1);

	printf("[Day05][2] Input should be 5\n");
	auto val2 = IntcodeComputer(arr);
	printf("[Day05][2] %i\n", val2);

}
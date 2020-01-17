void day05(string input)
{
	intcodeArr arr = ReadIntcodeInput(input);

	auto val = IntcodeComputer(arr);
	printf("[Day05][1] %i\n", val);

}
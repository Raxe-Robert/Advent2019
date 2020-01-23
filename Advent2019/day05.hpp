void day05(string input)
{
	intcodeArr arr = ReadIntcodeInput(input);

	printf("[Day05][1] Input should be 1\n");
	s32* userInput1 = new s32[2]{ 1, '\0' };
	auto val1 = IntcodeComputer(arr, userInput1);
	printf("[Day05][1] %i\n", val1);

	printf("[Day05][2] Input should be 5\n");
	s32* userInput2 = new s32[2]{ 5, '\0' };
	auto val2 = IntcodeComputer(arr, userInput2);
	printf("[Day05][2] %i\n", val2);

}
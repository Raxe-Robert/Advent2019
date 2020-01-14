void day05(string input)
{
	intcodeArr arr = ReadIntcodeInput(input);

	// "before running the program, replace position 1 with the value 12 and replace position 2 with the value 2."
	arr[1] = 12;
	arr[2] = 2;

	auto val = IntcodeComputer(arr);
	printf("[Day02][1] %i\n", val);

}
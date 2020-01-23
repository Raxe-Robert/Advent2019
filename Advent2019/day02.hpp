void day02(string input)
{
	s32_array arr = ReadIntcodeInput(input);

	// "before running the program, replace position 1 with the value 12 and replace position 2 with the value 2."
	arr[1] = 12;
	arr[2] = 2;

	auto val = IntcodeComputer(arr);
	printf("[Day02][1] %i\n", val);

	for (auto noun = 0; noun < 100; noun++)
	for (auto verb = 0; verb < 100; verb++)
	{
		arr[1] = noun;
		arr[2] = verb;

		auto val = IntcodeComputer(arr);
		if (val == 19690720)
		{
			printf("[Day02][2] %i\n", 100 * noun + verb);
			return;
		}
	}
}
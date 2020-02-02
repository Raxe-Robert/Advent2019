void day02(string input)
{
	s32_array arr = readIntcodeInput(input);

	// "before running the program, replace position 1 with the value 12 and replace position 2 with the value 2."
	arr[1] = 12;
	arr[2] = 2;

	auto result = solveIntcodeSequence(arr);
	printf("[Day02][1] %i\n", result.StatusCode);

	for (auto noun = 0; noun < 100; noun++)
	for (auto verb = 0; verb < 100; verb++)
	{
		arr[1] = noun;
		arr[2] = verb;

		result = solveIntcodeSequence(arr);
		if (result.StatusCode == 19690720)
		{
			printf("[Day02][2] %i\n", 100 * noun + verb);
			return;
		}
	}
}
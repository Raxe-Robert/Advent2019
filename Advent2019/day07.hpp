s32 getUnsetBit(u32 n, s32 skip)
{
	u32 index = 0;
	while (n)
	{
		if (!(n & 1))
		{
			if (skip == 0)
				return index;
			skip--;
		}

		index++;
		n >>= 1;
	}
	return index + skip;
}

/*
	returns a sequential array of all combinations
	single combination: i * size to i * size + size
*/
s32_array generateCombinations(s32 size)
{
	s32 count = factorial(size);
	const s32 mask = 0x00;

	s32_array arr;
	arr.Capacity = count;
	arr.Length = 0;
	arr.Data = new s32[arr.Capacity * size];
	
	for (s32 i = 0; i < count; i++)
	{
		auto val = i;
		auto maskCopy = mask;

		for (s32 j = 0; j < size; j++)
		{
			auto divider = factorial(size - 1 - j);
			auto times = 0;

			if (divider > 0)
			{
				times = val / divider;
				val %= divider;
			}

			auto bitIndex = getUnsetBit(maskCopy, times);
			maskCopy = maskCopy | (1 << bitIndex);

			arr.Data[(i * size) + j] = bitIndex;
			arr.Length++;
		}
	}

	return arr;
}

void day07(string input)
{
	constexpr s32 phase_count = 5;
	auto sequence = readIntcodeInput(input);
	auto combinations = generateCombinations(phase_count);
	s32 biggestOutput = -1;

	for (auto i = 0; i < combinations.Length; i += phase_count)
	{
		s32 output = 0;

		for (auto j = 0; j < phase_count; j++)
		{
			s32 phaseSetting = combinations.Data[i + j];
			s32 data[] = { phaseSetting, output };

			auto result = solveIntcodeSequence(sequence, { data, 2, 2 });
			output = result.OutputArr[result.OutputArr.Length - 1];
		}

		if (output > biggestOutput)
			biggestOutput = output;
	}

	printf("[Day07][1] %i\n", biggestOutput);
}

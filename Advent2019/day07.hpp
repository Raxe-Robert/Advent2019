inline
u32 setBit(u32 data, u32 pos)
{
	return data | (1 << pos);
}

inline
u32 unsetBit(u32 data, u32 pos)
{
	return data & (~(0 << pos));
}

inline
u32 getBit(u32 data, u32 pos)
{
	return data & (1 << pos) ? 1 : 0;
}

s32 countSetBits(u32 n)
{
	u32 count = 0;
	while (n)
	{
		count += n & 1;
		n >>= 1;
	}
	return count;
}

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

void printBits(u32 n)
{
	while (n)
	{
		printf("%i", n & 1 ? 1 : 0);
		n >>= 1;
	}
	printf("\n");
}

void recursive_combination(s32_array& comb, const u32 mask, void(*callback)(s32_array))
{
	auto depth = countSetBits(mask);
	auto remaining = comb.Length - depth;

	if (remaining == 0)
		callback(comb);
	else
	{
		for (s32 i = 0; i < remaining; i++)
		{
			auto maskCopy = mask;
			auto bitIndex = getUnsetBit(maskCopy, i);

			comb.Data[depth] = bitIndex;
			maskCopy = setBit(maskCopy, bitIndex);

			recursive_combination(comb, maskCopy, *callback);
		}
	}
}

s32_array intcodeSequence;
s32 biggestOutput = 0;

void execute(s32_array combination)
{
	s32 output = 0;

	for (auto i = 0; i < combination.Length; i++)
	{
		s32 phaseSetting = combination.Data[i];

		s32_array intcodeInput;
		intcodeInput.Length = 2;
		intcodeInput.Data = new s32[intcodeInput.Length]{ phaseSetting, output };
		
		auto result = IntcodeComputer(intcodeSequence, intcodeInput);
		output = result.OutputArr[result.OutputArr.Length - 1];
	}

	if (output > biggestOutput)
		biggestOutput = output;
}

void day07(string input)
{
	intcodeSequence = ReadIntcodeInput(input);

	u32 mask = 0x00;
	s32 phase_count = 5;

	s32_array iterable;
	iterable.Length = phase_count;
	iterable.Data = new s32[iterable.Length]{ 0, 1, 2, 3, 4 };
	
	recursive_combination(iterable, mask, execute);

	printf("[Day07][1] %i\n", biggestOutput);
}
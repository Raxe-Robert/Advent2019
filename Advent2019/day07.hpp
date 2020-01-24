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

void recursive_combination(s32_array& comb, const u32 mask)
{
	auto depth = countSetBits(mask);
	auto remaining = comb.Length - depth;

	if (remaining == 0)
	{
		for (auto i = 0; i < comb.Length; i++)
			printf("%i ", comb.Data[i]);
		printf("\n");
	}
	else
	{
		for (s32 i = 0; i < remaining; i++)
		{
			auto maskCopy = mask;
			auto bitIndex = getUnsetBit(maskCopy, i);

			comb.Data[depth] = bitIndex;
			maskCopy = setBit(maskCopy, bitIndex);

			recursive_combination(comb, maskCopy);
		}
	}
}

void day07(string input)
{
	u32 mask = 0x00;
	s32 phase_count = 5;

	//mask = setBit(mask, 2);
	//printBits(mask);
	//printf("Index %i\n", getUnsetBit(mask, 0));
	//printf("Index %i\n", getUnsetBit(mask, 1));
	//printf("Index %i\n", getUnsetBit(mask, 2));
	//printf("Index %i\n", getUnsetBit(mask, 3));

	s32_array iterable;
	iterable.Length = 5;
	iterable.Data = new s32[iterable.Length + 1]{ 0, 1, 2, 3, 4 };
	iterable.Data[iterable.Length] = '\0';
	
	recursive_combination(iterable, mask);
}
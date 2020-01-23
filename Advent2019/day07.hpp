inline
u32 setBit(u32 data, u32 pos)
{
	return data | (1 << pos);
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
	return index;
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
	auto maskCopy = mask;
	auto depth = countSetBits(maskCopy);
	auto remaining = depth - comb.Length;

	if (remaining == 0)
	{
		for (auto i = 0; i < comb.Length; i++)
			printf("%i ", comb.Data[i]);
		printf("\n");
	}
	else
	{
		for (s32 i = 0; i < depth; i++)
		{
			comb.Data[depth] = 
			setBit(maskCopy, 1);

			recursive_combination(comb, maskCopy);
		}
	}

}

void day07(string input)
{

	/*

		3 : 3 * 2 * 1 = 6
		0 1 2 
		0 2 1
		1 0 2	
		1 2 0
		2 0 1
		2 1 0
		
		4 : 4 * 3 * 2 * 1 = 24
		1 2 3 4
		1 2 4 3
		1 3 2 4
		1 3 4 2
		1 4 2 3
		1 4 3 2

		2 1 3 4
		2 1 4 3
		2 3 1 4
		2 3 4 1
		2 4 1 3
		2 4 3 1

		3 1 2 4
		3 1 4 2
		3 2 1 4
		3 2 4 1
		3 4 1 2
		3 4 2 1

		4 1 2 3
		4 1 3 2
		4 2 1 3
		4 2 3 1
		4 3 1 2
		4 3 2 1



		1 2 3 4  
 		2 1 3 4  0 1
		3 1 2 4  0 2
		4 1 2 3  1 3
				 
		1 2 4 3  
		2 1 4 3  0 1 
		3 1 4 2  0 3
		4 1 3 2  0 2

		1 3 2 4  
		2 3 1 4  0 2
		3 2 1 4  0 1
		4 2 1 3  0 3

		1 3 4 2  
		2 3 4 1  
		3 2 4 1
		4 2 3 1
		
		1 4 2 3
		2 4 1 3
		3 4 1 2
		4 3 1 2

		1 4 3 2
		2 4 3 1
		3 4 2 1
		4 3 2 1
	
	*/
	u32 mask = 0x00;
	s32 phase_count = 5;

	mask = setBit(mask, 2);
	printBits(mask);
	auto val = getUnsetBit(mask, 1);
	printf("Index %i\n", val);

	s32_array iterable;
	iterable.Length = 5;
	iterable.Data = new s32[iterable.Length + 1]{ 0, 1, 2, 3, 4 };
	iterable.Data[iterable.Length] = '\0';
	
	//recursive_combination(iterable, mask);
}
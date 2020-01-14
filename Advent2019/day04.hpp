struct byteArr
{
	char* Data;
	s32 Length;
};

void day04(string lower, string upper)
{
	byteArr arr;
	arr.Length = 6;
	arr.Data = reinterpret_cast<char*>(malloc(arr.Length + (s32)1));
	memcpy(arr.Data, lower.Data, arr.Length);
	arr.Data[arr.Length] = 0;

	 s32 part1 = 0;
	 s32 part2 = 0;

	while (!Equals(arr.Data, upper.Data, arr.Length))
	{
		int pairCount = 0;
		int perfectPairCount = 0;

		bool increasing = true;

		// Check criteria
		for (s32 j = 0; j < arr.Length - 1; ++j)
		{
			s32 num0 = arr.Data[j];
			s32 num1 = arr.Data[j + 1];

			if (num0 == num1)
			{
				pairCount++;

				s32 numPrev = j > 0
					? arr.Data[j - 1]
					: -1;

				s32 numNext = j < arr.Length - 2
					? arr.Data[j + 2]
					: -1;

				if ((num0 != numPrev) && (num1 != numNext))
					perfectPairCount++;
			}
			else if (num0 > num1)
				increasing = false;
		}

		if (pairCount > 0 && increasing)
			part1++;

		if (perfectPairCount > 0 && increasing)
			part2++;

		for (s32 i = arr.Length - 1; i >= 0; i--)
		{
			arr.Data[i]++;
			if (arr.Data[i] > '9')
				arr.Data[i] = '0';
			else break;
		}
	}

	printf("[Day04][1] %i\n", part1);
	printf("[Day04][2] %i\n", part2);
}
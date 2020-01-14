
void day04(s32 lower, s32 upper)
{
	s32 part1 = 0;
	s32 part2 = 0;

	for (auto i = lower; i <= upper; ++i)
	{
		int pairCount = 0;
		int perfectPairCount = 0;

		bool increasing = true;

		s32 numPrev = -1;

		for (s32 j = 6; j > 1; --j)
		{
			s32 mod0 = pow(10, j);
			s32 num0 = i % mod0 / (mod0 / 10);

			s32 mod1 = pow(10, j - 1);
			s32 num1 = i % mod1 / (mod1 / 10);

			if (num0 == num1)
			{
				pairCount++;
				
				s32 numNext = -1;
				if (j > 2)
				{
					s32 modNext = pow(10, j - 2);
					numNext = i % modNext / (modNext / 10);
				}

				if ((num0 != numPrev) && (num1 != numNext))
					perfectPairCount++;
			}
			if (num0 > num1)
				increasing = false;

			numPrev = num0;
		}

		if (pairCount > 0 && increasing)
			part1++;

		if (perfectPairCount > 0 && increasing)
			part2++;
	}

	printf("[Day04][1] %i\n", part1);
	printf("[Day04][2] %i\n", part2);
}
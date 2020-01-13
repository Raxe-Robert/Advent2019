
void day01(string input)
{	
	auto buffer = new char[16];
	char* ptr = buffer;

	s32 part1 = 0;
	s32 part2 = 0;

	for (auto i = 0; i < input.Length; i++)
	{
		s32 start = i;
		memset(buffer, 0, 16);

		while (input.SData[i] != '\n' && input.SData[i] != '\0')
			*ptr++ = input.SData[i++];
		
		ptr = buffer;

		auto num = atoi(ptr);
		auto val = (num / 3) - 2;

		part1 += val;

		while (1)
		{
			num = (num / 3) - 2;
			if (num <= 0)
				break;
			
			part2 += num;
		}
	}

	printf("[Day01][1] %i\n", part1);
	printf("[Day01][2] %i\n", part2);
}
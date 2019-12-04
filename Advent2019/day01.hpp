
void day01(const char* filepath)
{
	auto file = fopen(filepath, "rb");
	auto buffer = new char[64];

	s32 part1 = 0;
	s32 part2 = 0;

	while (!feof(file))
	{
		char* line = fgets(buffer, 64, file);
		if (line == 0)
			break;

		auto num = atoi(line);
		
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
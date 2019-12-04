
constexpr s32 COMMA = 44;

void day02(const char* filepath)
{
	auto file = fopen(filepath, "rb");

	char* buffer = new char[4]{ 0, 0, 0, '\0' };
	s32 buffer_length = 0;

	s32* arr;
	arr = reinterpret_cast<s32*>(malloc(sizeof(s32) * 1024));
	s32 arr_length = 0;

	while (1)
	{
		s32 c = fgetc(file);
		if (c == COMMA || c == EOF)
		{
			s32 num = atoi(buffer);
			arr[arr_length] = num;
			arr_length++;

			memset(buffer, 0, buffer_length);
			buffer_length = 0;

			if (c == EOF)
				break;
		}
		else
		{
			char num_part = (char)c;
			buffer[buffer_length] = num_part;
			buffer_length++;
		}

	}

	// before running the program, replace position 1 with the value 12 and replace position 2 with the value 2.
	arr[1] = 12;
	arr[2] = 2;

	for (auto i = 0; i < arr_length; i += 4)
	{
		auto method = arr[i];
		if (method == 99)
			break;

		auto valPos = arr[i + 1];
		auto valPos2 = arr[i + 2];
		auto outputPos = arr[i + 3];

		auto val = arr[valPos];
		auto val2 = arr[valPos2];

		if (method == 1)
			arr[outputPos] = val + val2;
		else if (method == 2)
			arr[outputPos] = val * val2;
	}

	s32 part2 = 0;

	printf("[Day02][1] %i\n", arr[0]);
	printf("[Day02][2] %i\n", part2);
}
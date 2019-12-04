
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

	s32* arr_copy;
	arr_copy = reinterpret_cast<s32*>(malloc(sizeof(s32) * 1024 * 1024));
	memset(arr_copy + sizeof(s32) * 1024, 0, sizeof(s32) * 1024);
	memcpy(arr_copy, arr, sizeof(s32) * 1024);

	// "before running the program, replace position 1 with the value 12 and replace position 2 with the value 2."
	arr_copy[1] = 12;
	arr_copy[2] = 2;

	for (auto i = 0; i < arr_length; i += 4)
	{
		auto method = arr_copy[i];
		if (method == 99)
		{
			printf("[Day02][1] %i\n", arr_copy[0]);
			break;
		}

		auto valPos = arr_copy[i + 1];
		auto valPos2 = arr_copy[i + 2];
		auto outputPos = arr_copy[i + 3];

		auto val = arr_copy[valPos];
		auto val2 = arr_copy[valPos2];

		if (method == 1)
			arr_copy[outputPos] = val + val2;
		else if (method == 2)
			arr_copy[outputPos] = val * val2;
	}

	for (auto noun = 0; noun < 100; noun++)
	for (auto verb = 0; verb < 100; verb++)
	{
		memset(arr_copy + sizeof(s32) * 1024, 0, sizeof(s32) * 1024);
		memcpy(arr_copy, arr, sizeof(s32) * 1024);

		arr_copy[1] = noun;
		arr_copy[2] = verb;

		for (auto i = 0; i < arr_length; i += 4)
		{
			auto method = arr_copy[i];
			if (method == 99)
			{
				if (arr_copy[0] == 19690720)
				{
					printf("[Day02][2] %i\n", 100 * noun + verb);
					return;
				}

				break;
			}

			auto valPos = arr_copy[i + 1];
			auto valPos2 = arr_copy[i + 2];
			auto outputPos = arr_copy[i + 3];

			auto val = arr_copy[valPos];
			auto val2 = arr_copy[valPos2];

			if (method == 1)
				arr_copy[outputPos] = val + val2;
			else if (method == 2)
				arr_copy[outputPos] = val * val2;
		}
	}
}
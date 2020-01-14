inline
s32 IntcodeComputer(const intcodeArr inputArr)
{
	intcodeArr arr;
	arr.Length = inputArr.Length * inputArr.Length;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * arr.Length));

	memset(arr.Data, 0, sizeof(s32) * arr.Length);
	memcpy(arr.Data, inputArr.Data, sizeof(s32) * inputArr.Length);

	for (auto i = 0; i < arr.Length;)
	{
		char numberstring[(sizeof(arr[i]) * CHAR_BIT + 2) / 3 + 2];
		sprintf(numberstring, "%i", arr[i]);

		// todo, use lines above
		auto opcode = arr[i];

		// Opcode is the rightmost two digits of the first value in an instruction
		// Parameter modes are single digits, one per paramter, read right-to-left from the opcode
		//		The first paramter's mode is in the hundreds digit
		//		The second parameter's mode is in the the thousands digit
		//		Etc... Any missing modes are 0!
		//		

		auto valPos = arr[i + 1];
		auto valPos2 = arr[i + 2];
		auto outputPos = arr[i + 3];

		auto val1 = arr[valPos];
		auto val2 = arr[valPos2];

		switch (opcode)
		{
			case 99:
				return arr[0];
			case 1:

				arr[outputPos] = val1 + val2;

				i += 4;
				break;
			case 2:

				arr[outputPos] = val1 * val2;

				i += 4;
				break;
			case 3:

				i += 2; //?
				break;
			case 4:

				i += 2; //?
				break;
		}
	}
}

intcodeArr ReadIntcodeInput(string input)
{
	char* buffer = new char[4]{ 0, 0, 0, '\0' };
	s32 buffer_length = 0;

	intcodeArr arr;
	arr.Length = 0;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * (1024 + 1)));

	for (s32 i = 0; i < input.Length; i++)
	{
		s32 c = input[i];
		if (c == COMMA || c == EOF)
		{
			s32 num = atoi(buffer);
			arr[arr.Length] = num;
			arr.Length++;

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

	return arr;
}

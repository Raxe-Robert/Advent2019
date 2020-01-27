constexpr s32 UNICODE_NUMBER_OFFSET = 48;

enum class instruction_type : s32 {
	/*	Adds together numbers read from two positions and stores the result in a third position. The three integers immediately after the opcode tell you these three 
		positions - the first two indicate the positions from which you should read the input values, and the third indicates the position at which the output should be stored. */
	add = 1,
	/*	Works exactly like opcode 1, except it multiplies the two inputs instead of adding them. Again, the three integers after the opcode indicate where the inputs and outputs are, not their values. */
	multiply = 2,
	/*	Takes a single integer as input and saves it to the position given by its only parameter. For example, the instruction 3,50 would take an input value and store it at address 50. */
	user_input = 3,
	/*	Outputs the value of its only parameter. For example, the instruction 4,50 would output the value at address 50. */
	output = 4,
	/*	If the first parameter is non-zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing. */
	jump_if_true = 5,
	/*	If the first parameter is zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing. */
	jump_if_false = 6,
	/*	If the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0. */
	less_than = 7,
	/*	If the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0. */
	equals = 8,
	/*	Means that the program is finished and should immediately halt. */
	terminate_program = 99
};

enum class parameter_mode : s32 {
	position = 0,
	immediate = 1
};

struct intcode_result
{
	s32 StatusCode;
	s32_array OutputArr;
};

s32 ReadParameter(const s32_array& arr, s32 i, parameter_mode paramMode)
{
	switch (paramMode)
	{
		case parameter_mode::position:
		{
			auto pos = arr.Data[i];
			return arr.Data[pos];
		}
		case parameter_mode::immediate:
		{
			return arr.Data[i];
		}
		default:
		{
			printf("[Excep] Parameter mode %i does not exist", paramMode);
			return -1;
		}
	}
}

intcode_result IntcodeComputer(const s32_array inputArr, s32_array userInput = { 0, 0 })
{
	s32_array arr;
	arr.Length = inputArr.Length * inputArr.Length;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * arr.Length));

	memset(arr.Data, 0, sizeof(s32) * arr.Length);
	memcpy(arr.Data, inputArr.Data, sizeof(s32) * inputArr.Length);

	char instruction[sizeof(instruction_type) * 64];
	instruction_type opcode;
	parameter_mode paramModes[sizeof(parameter_mode) * 64];

	s32 userInputIndex = 0;

	intcode_result result;
	result.StatusCode = -1;
	result.OutputArr.Capacity = 20;
	result.OutputArr.Data = new s32[result.OutputArr.Capacity];
	result.OutputArr.Length = 0;

	for (auto i = 0; i < arr.Length;)
	{
		// Reset memory
		memset(paramModes, 0, (s32)64);

		// Read instruction
		sprintf(instruction, "%i", arr[i]);
		s32 instruction_length = 0;

		while (instruction[instruction_length] != '\0')
			instruction_length++;		

		if (instruction_length <= 0)
			throw std::length_error("invalid instruction");
		else if (instruction_length == 1)
			opcode = instruction_type(instruction[0] - UNICODE_NUMBER_OFFSET);
		else
		{
			auto left = (instruction[instruction_length - 2] - UNICODE_NUMBER_OFFSET) * 10;
			auto right = instruction[instruction_length - 1] - UNICODE_NUMBER_OFFSET;
			opcode = instruction_type(left + right);
		}

		s32 paramModes_length = instruction_length > 2 ? instruction_length - 2 : 0;
		for (s32 j = 0; j < paramModes_length; ++j)
		{
			auto val = instruction[(paramModes_length - 1) - j];
			paramModes[j] = parameter_mode(val - UNICODE_NUMBER_OFFSET);
		}

		switch (opcode)
		{
			case instruction_type::terminate_program:
			{
				result.StatusCode = arr[0];
				return result;
			}				
			case instruction_type::add:
			{
				s32 param1 = ReadParameter(arr, i + 1, paramModes[0]);
				s32 param2 = ReadParameter(arr, i + 2, paramModes[1]);
				s32 param3 = arr[i + 3]; // Parameters that an instruction writes to will never be in immediate mode

				arr[param3] = param1 + param2;

				i += 4;
				break;
			}
			case instruction_type::multiply:
			{
				s32 param1 = ReadParameter(arr, i + 1, paramModes[0]);
				s32 param2 = ReadParameter(arr, i + 2, paramModes[1]);
				s32 param3 = arr[i + 3]; // Parameters that an instruction writes to will never be in immediate mode

				arr[param3] = param1 * param2;

				i += 4;
				break;
			}
			case instruction_type::user_input:
			{
				s32 param1 = arr[i + 1]; // Parameters that an instruction writes to will never be in immediate mode

				s32 inputVal;
				if (userInput.Length == 0 || userInputIndex >= userInput.Length)
				{
					printf("[input] Enter Value: ");
					if (scanf("%d", &inputVal) == NULL)
					{
						printf("[Excep] Invalid input\n");

						result.StatusCode = -1;
						return result;
					}
				}
				else
				{
					inputVal = userInput[userInputIndex];
					userInputIndex++;
					//printf("%i\n", inputVal);
				}
				
				arr[param1] = inputVal;

				i += 2;
				break;
			}
			case instruction_type::output:
			{
				s32 param1 = ReadParameter(arr, i + 1, paramModes[0]);
				//printf("[outpt] %i\n", param1);

				result.OutputArr[result.OutputArr.Length] = param1;
				result.OutputArr.Length++;

				i += 2;
				break;
			}
			case instruction_type::jump_if_true:
			{
				if (ReadParameter(arr, i + 1, paramModes[0]) != 0)
					i = ReadParameter(arr, i + 2, paramModes[1]);
				else
					i += 3;

				break;
			}
			case instruction_type::jump_if_false:
			{
				if (ReadParameter(arr, i + 1, paramModes[0]) == 0)
					i = ReadParameter(arr, i + 2, paramModes[1]);
				else
					i += 3;

				break;
			}
			case instruction_type::less_than:
			{
				s32 param1 = ReadParameter(arr, i + 1, paramModes[0]);
				s32 param2 = ReadParameter(arr, i + 2, paramModes[1]);
				s32 param3 = arr[i + 3]; // Parameters that an instruction writes to will never be in immediate mode

				arr[param3] = param1 < param2 ? 1 : 0;
					
				i += 4;
				break;
			}
			case instruction_type::equals:
			{
				s32 param1 = ReadParameter(arr, i + 1, paramModes[0]);
				s32 param2 = ReadParameter(arr, i + 2, paramModes[1]);
				s32 param3 = arr[i + 3]; // Parameters that an instruction writes to will never be in immediate mode

				arr[param3] = param1 == param2 ? 1 : 0;
				
				i += 4;
				break;
			}
			default:
			{
				printf("[Excep] Opcode %i does not exist\n", opcode);

				result.StatusCode = -1;
				return result;
			}
		}
	}

	result.StatusCode = 0;
	return result;
}

s32_array ReadIntcodeInput(string input)
{
	char* buffer = new char[4]{ 0, 0, 0, '\0' };
	s32 buffer_length = 0;

	s32_array arr;
	arr.Length = 0;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * (1024 + 1)));

	for (s32 i = 0; i < input.Capacity; i++)
	{
		s32 c = input[i];
		if (c == COMMA || c == '\0')
		{
			s32 num = atoi(buffer);
			arr[arr.Length] = num;
			arr.Length++;

			memset(buffer, 0, buffer_length);
			buffer_length = 0;

			if (c == '\0')
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

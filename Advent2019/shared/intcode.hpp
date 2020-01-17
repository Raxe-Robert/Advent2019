constexpr s32 UNICODE_NUMBER_OFFSET = 48;

constexpr bool debug_output = true;

template<typename... Args>
inline
void debug_log(const char* message, Args... args)
{
#if !debug_output
	printf(message, args...);
#endif
}

enum class instruction_type : s32 {
	/*
		Adds together numbers read from two positions and stores the result in a third position. The three integers immediately after the 
		opcode tell you these three positions - the first two indicate the positions from which you should read the input values, and the 
		third indicates the position at which the output should be stored.
	*/
	add = 1,
	/*
		Works exactly like opcode 1, except it multiplies the two inputs instead of adding them. 
		Again, the three integers after the opcode indicate where the inputs and outputs are, not their values.
	*/
	multiply = 2,
	/*
		Takes a single integer as input and saves it to the position given by its only parameter. 
		For example, the instruction 3,50 would take an input value and store it at address 50.
	*/
	user_input = 3,
	/*
		Outputs the value of its only parameter. For example, the instruction 4,50 would output the value at address 50.
	*/
	output = 4,
	/*
		If the first parameter is non-zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
	*/
	jump_if_true = 5,
	/*
		If the first parameter is zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.	
	*/
	jump_if_false = 6,
	/*
		If the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
	*/
	less_than = 7,
	/*
		If the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
	*/
	equals = 8,
	/*
		Means that the program is finished and should immediately halt.
	*/
	terminate_program = 99
};

enum class parameter_mode : s32 {
	position = 0,
	immediate = 1
};

inline
s32 IntcodeComputer(const intcodeArr inputArr)
{
	intcodeArr arr;
	arr.Length = inputArr.Length * inputArr.Length;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * arr.Length));

	memset(arr.Data, 0, sizeof(s32) * arr.Length);
	memcpy(arr.Data, inputArr.Data, sizeof(s32) * inputArr.Length);

	char instruction[sizeof(instruction_type) * 64];
	instruction_type opcode;
	parameter_mode parameterModes[sizeof(parameter_mode) * 64];

	for (auto i = 0; i < arr.Length;)
	{
		// Reset memory
		memset(parameterModes, 0, (s32)64);

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

		s32 parameterModes_length = instruction_length > 2 ? instruction_length - 2 : 0;
		for (s32 j = 0; j < parameterModes_length; ++j)
		{
			auto val = instruction[(parameterModes_length - 1) - j];
			parameterModes[j] = parameter_mode(val - UNICODE_NUMBER_OFFSET);
		}

		debug_log(">>> %s = opcode: %i\n", instruction, opcode);

		debug_log("[modes]");
		for (s32 j = 0; j < parameterModes_length; ++j)
			debug_log(" %i", parameterModes[j]);
		debug_log("\n");

		switch (opcode)
		{
			case instruction_type::terminate_program:
				return arr[0];
			case instruction_type::add:
			{
				s32 parameter0 = arr[i + 1];
				s32 parameter1 = arr[i + 2];
				s32 parameter2 = arr[i + 3]; // Parameters that an instruction writes to will never be in imediate mode
				debug_log("[param] %i, %i, %i\n", parameter0, parameter1, parameter2);

				auto val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				auto val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

				debug_log("[wrtng] val: '%i' to position: '%i'\n", val0 + val1, parameter2);
				arr[parameter2] = val0 + val1;

				i += 4;
				break;
			}
			case instruction_type::multiply:
			{
				s32 parameter0 = arr[i + 1];
				s32 parameter1 = arr[i + 2];
				s32 parameter2 = arr[i + 3]; // Parameters that an instruction writes to will never be in imediate mode
				debug_log("[param] %i, %i, %i\n", parameter0, parameter1, parameter2);

				auto val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				auto val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

				debug_log("[wrtng] val: '%i' to position: '%i'\n", val0 * val1, parameter2);
				arr[parameter2] = val0 * val1;

				i += 4;
				break;
			}
			case instruction_type::user_input:
			{
				s32 parameter0 = arr[i + 1]; // Parameters that an instruction writes to will never be in imediate mode
				debug_log("[param] %i\n", parameter0);

				s32 inputVal;
				printf("[input] Enter ID: ");
				if (scanf("%d", &inputVal) == NULL)
				{
					printf("[Excep] Invalid input");
					return -1;
				}

				debug_log("[wrtng] val: '%i' to position: '%i'\n", inputVal, parameter0);
				arr[parameter0] = inputVal;

				i += 2;
				break;
			}
			case instruction_type::output:
			{
				s32 parameter0 = arr[i + 1];
				debug_log("[param] %i\n", parameter0);

				s32 val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				printf("[outpt] %i\n", val0);

				i += 2;
				break;
			}
			case instruction_type::jump_if_true:
			{
				s32 parameter0 = arr[i + 1];
				s32 val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				if (val0 != 0)
				{
					s32 parameter1 = arr[i + 2];
					s32 val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

					i = val1;
				}
				else
					i += 3;

				break;
			}
			case instruction_type::jump_if_false:
			{
				s32 parameter0 = arr[i + 1];
				s32 val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				if (val0 == 0)
				{
					s32 parameter1 = arr[i + 2];
					s32 val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

					i = val1;
				}
				else
					i += 3;

				break;
			}
			case instruction_type::less_than:
			{
				s32 parameter0 = arr[i + 1];
				s32 parameter1 = arr[i + 2];
				s32 parameter2 = arr[i + 3]; // Parameters that an instruction writes to will never be in imediate mode

				s32 val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				s32 val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

				arr[i] = val0 < val1 ? 1 : 0;
					
				i += 3;
				break;
			}
			case instruction_type::equals:
			{
				s32 parameter0 = arr[i + 1];
				s32 parameter1 = arr[i + 2];
				s32 parameter2 = arr[i + 3]; // Parameters that an instruction writes to will never be in imediate mode

				s32 val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				s32 val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

				arr[i] = val0 == val1 ? 1 : 0;
				
				i += 3;
				break;
			}
			default:
			{
				debug_log("[Excep] Opcode %i does not exist", opcode);
				return -1;
			}
		}
		debug_log("\n");
	}
	return 0;
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

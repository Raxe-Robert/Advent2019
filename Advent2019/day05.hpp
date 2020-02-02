void day05(string input)
{
	s32_array arr = readIntcodeInput(input);

	s32_array userInput1;
	userInput1.Length = 1;
	userInput1.Data = new s32[userInput1.Length]{ 1 };

	auto result1 = solveIntcodeSequence(arr, userInput1);
	printf("[Day05][1] %i\n", result1.OutputArr[result1.OutputArr.Length - 1]);

	s32_array userInput2;
	userInput2.Length = 1;
	userInput2.Data = new s32[userInput2.Length]{ 5 };

	auto result2 = solveIntcodeSequence(arr, userInput2);
	printf("[Day05][2] %i\n", result2.OutputArr[0]);

}
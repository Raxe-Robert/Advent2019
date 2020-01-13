#include "CppUnitTest.h"

#include "../Advent2019/advent2019.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(day03Tests)
	{
	public:
		
		TEST_METHOD(testData)
		{
			auto day03_test_input = ReadAllText("./input/day03test.txt");
			day03(day03_test_input);

			Assert::AreEqual(1, 1);
		}
	};
}

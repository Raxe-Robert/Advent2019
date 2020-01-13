#include "CppUnitTest.h"

#include "../Advent2019/advent2019.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(day01Tests)
	{
	public:
		
		TEST_METHOD(testData)
		{
			day01("./input/day01test01.txt");
			Assert::AreEqual(1, 1);
		}
	};
}

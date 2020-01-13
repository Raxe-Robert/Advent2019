#include "CppUnitTest.h"

#include "Advent2019/shared/types.h"
#include "Advent2019/shared/file.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(fileTests)
	{
	public:
		
		TEST_METHOD(readAllTextTest)
		{
			const char* expected = "R75,D30,R83,U83,L12,D49,R71,U7,L72\r\nU62,R66,U55,R34,D71,R55,D58,R83";

			string result = ReadAllText(PROJECT_DIR "input\\day03\\part1\\test01.txt");

			Assert::AreEqual(expected, result.Data);
		}
	};
}

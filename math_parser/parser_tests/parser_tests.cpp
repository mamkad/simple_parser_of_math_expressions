#include "pch.h"
#include "CppUnitTest.h"

#include <string>

using std::string;

#include "..\math_parser\primary_expression_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace parsertests
{
	
	string mainExpr, resExpr;

	TEST_CLASS(parsertests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{

			mainExpr = "2 + 2 + @";
			Assert::IsTrue(SortYardAlgorithm(mainExpr, resExpr) == -5);
		}
		TEST_METHOD(TestMethod2)
		{
			/*
			string mainExpr = "COS(2*0.342104+5*2+5/(34+4*(4-2^(9.4520023^(8/(5*2+9/21)-2*2)))) + SIN(5.23))";
			long double val;

			Assert::IsTrue(SortYardAlgorithm(mainExpr, resExpr) == 0);
			ExecuteExpr(mainExpr, val);	
		    //Assert::IsTrue(ExecuteExpr(mainExpr, val) == 0);
			Assert::IsTrue(val == -0.878001);*/
		}

		TEST_METHOD(TestMethod3)
		{
			/*
			string mainExpr = "LOG(2.2352, 8) + 1 / (12)";
			long double val;

			Assert::IsTrue(SortYardAlgorithm(mainExpr, resExpr) == 0);
			ExecuteExpr(mainExpr, val);
			//Assert::IsTrue(ExecuteExpr(mainExpr, val) == 0);
			Assert::IsTrue(val == 2.66864, std_tosval);*/
		}

		TEST_METHOD(TestMethod4)
		{
			/*
			string mainExpr = "(-67) + 45 + 22 + 15 + (-15)";
			long double val;

			Assert::IsTrue(SortYardAlgorithm(mainExpr, resExpr) == 0);
			ExecuteExpr(mainExpr, val);
			//Assert::IsTrue(ExecuteExpr(mainExpr, val) == 0);
			Assert::IsTrue(val == 0);*/
		}

		TEST_METHOD(TestMethod5)
		{
			/*
			string mainExpr = "SIN(45 + 23 * (2 - 5 + 3 - 5)) + COS(3 + 3 * 2 / 9 + 3)";
			long double val;

			Assert::IsTrue(SortYardAlgorithm(mainExpr, resExpr) == 0);
			ExecuteExpr(mainExpr, val);
			//Assert::IsTrue(ExecuteExpr(mainExpr, val) == 0);
			Assert::IsTrue(val == 0.153477);*/
		}
	};
	
};

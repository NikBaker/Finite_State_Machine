#include "pch.h"
#include "CppUnitTest.h"
#include "..\Finit_State_Machine_v1.0\FSM.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<std::vector<int>>(const std::vector<int>& vec) {
				return L"FinishStates";
			}
		}
	}
}

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Check_Final_States)
		{
			FSM F4({ '0', '1' }, { 1, 2 }, 1, { 2 }, { { 1, 2 }, { 2, 2 } });
			FSM F5({ '0', '1' }, { 1, 2, 3, 4 }, 1, { 3, 4 }, { { 2, 1 }, { 2, 3 }, { 3, 3 }, { 4, 4 } });
			FSM res = F4 * F5;
			std::vector<int> final = { 23, 24 };
			Assert::AreEqual(res.GetFinalStates(), final);
		}
		TEST_METHOD(Check_All_States)
		{
			FSM F4({ '0', '1' }, { 1, 2 }, 1, { 2 }, { { 1, 2 }, { 2, 2 } });
			FSM F5({ '0', '1' }, { 1, 2, 3, 4 }, 1, { 3, 4 }, { { 2, 1 }, { 2, 3 }, { 3, 3 }, { 4, 4 } });
			FSM res = F4 * F5;
			std::vector<int> all = { 11, 12, 13, 14, 21, 22, 23, 24 };
			Assert::AreEqual(res.GetAllStates(), all);
		}
		TEST_METHOD(Check_Start_State)
		{
			FSM F4({ '0', '1' }, { 1, 2 }, 1, { 2 }, { { 1, 2 }, { 2, 2 } });
			FSM F5({ '0', '1' }, { 1, 2, 3, 4 }, 1, { 3, 4 }, { { 2, 1 }, { 2, 3 }, { 3, 3 }, { 4, 4 } });
			FSM res = F4 * F5;
			int start = 11;
			Assert::AreEqual(res.GetStart(), start);
		}
		TEST_METHOD(Check_No_Rule)
		{
			FSM F4({ '0', '1' }, { 1, 2 }, 1, { 2 }, { { 1, -1 }, { 2, 2 } });
			FSM F5({ '0', '1' }, { 1, 2, 3, 4 }, 1, { 3, 4 }, { { 2, 1 }, { 2, 3 }, { 3, 3 }, { 4, 4 } });
			FSM res = F4 * F5;
			
			Assert::AreEqual(res.GetRules()[0][1], -1);
		}
	};
}

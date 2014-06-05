#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			EditRow er(10);
			cout << er.getRowSize() << endl;
			er.setColumn(0, L"hello");
			er.setColumn(1, L"hmm");
			wcout << er.getRow(0) << endl;
			wcout << er.getRow(1) << endl;
			er.setColumnSize(3);
			er.setColumn(0, L"hello1");
			er.setColumn(1, L"hmm1");
			wcout << er.getRow(0) << endl;
			wcout << er.getRow(1) << endl;
		}

	};
}
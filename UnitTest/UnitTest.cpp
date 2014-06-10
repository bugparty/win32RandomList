// UnitTest.cpp : Defines the entry point for the console application.
//
#define TEST
#include "stdafx.h"
using namespace std;
void testEditRow();
void testStrUlits();
void testRowHelper();
void testEditRow2();
void testCsvReader();
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	
	//testStrUlits();
	//testEditRow2();
	//testRowHelper();
	testCsvReader();
	return 0;
}
void testCsvReader(){

	CsvReader cr;
	cr.open(L"unicode_test1.csv");
	cout << "csvReader reads " << cr.getRowCount() << " lines" << endl;
	EditRow *per = NULL;
	assert(cr.getRow(1, &per));
	cout << "Row 0 total column" << per->getColumnSize() << endl;
	for (int i = 0; i < per->getColumnSize(); i++){
		wcout << L"pos " << i << L"`s value:" << per->getColumn(i) << endl;
	}
	
	EditRow r1 = cr.getRow(0);
	EditRow r2 = cr.getRow(1);
	wcout << r1.serial() << r2.serial() << endl;
	cr.swap(r1, r2);
	wcout << r1.serial() << r2.serial() << endl;

}
void testRowHelper(){
	RowHelper rh(L"title,name,sex");
	EditRow &myer = rh.getObj();

}


void testStrUlits1(){
	int pos[10];
	TCHAR* str1 = L"no,title,bow,m,an";
	TCHAR* str2 = L"no,title,bow,m,andddddd,ddddddd,dd,dddd,dddddd,ddddd,dddd,dddd,dddddddd,dddddddddd,dddddd,";
	TCHAR* str3 = L"no,title,bow,m,ansdfsfs,";
	TCHAR* str4 = L"notitlebowman";
	wcout << str1 << findColons(str1, pos, 10) << endl;
	wcout << str2 << findColons(str2, pos, 10) << endl;
	wcout << str3 << findColons(str3, pos, 10) << endl;
	wcout << str4 << findColons(str4, pos, 10) << endl;
}
void testStrUlits2(){
	int pos[20];
	TCHAR* str2 = L"no,title,bow,m,andddddd,ddddddd,dd,dddd,dddddd,ddddd,dddd,dddd,dddddddd,dddddddddd,dddddd,";
	int nfound = findColons(str2, pos, 10);
	wcout << str2 << nfound << endl;
	while (nfound--){
		wcout << pos[nfound] << ",";
	}
}
void testStrUlits(){
	
	testStrUlits2();
}
void testEditRow(){
	EditRow er(10);
	cout << er.getColumnSize() << endl;
	er.setColumn(0, L"hello");
	er.setColumn(1, L"hmm");
	wcout << er.getColumn(0) << endl;
	wcout << er.getColumn(1) << endl;
	er.setColumnSize(3);
	er.setColumn(0, L"hello1");
	er.setColumn(1, L"hmm1");
	wcout << er.getColumn(0) << endl;
	wcout << er.getColumn(1) << endl;

	EditRow er1;
	er1.setColumnSize(3);
	er1.setColumn(0, L"hello");
	er1.setColumn(1, L"hmm");
	wcout << er1.getColumn(0) << endl;
	wcout << er1.getColumn(1) << endl;

	//copy conststructer
	EditRow er1_1(er);
	wcout << er1_1.getColumn(0) << endl;
	wcout << er1_1.getColumn(1) << endl;
	er1_1 = er1;
	wcout << er1_1.getColumn(0) << endl;
	wcout << er1_1.getColumn(1) << endl;
}
void testEditRow2(){
	EditRow er(10);
	er.setColumn(0, L"hello");
	er.setColumn(1, L"hmm");
	
	er.setColumnSize(3);
	er.setColumn(0, L"hello1");
	er.setColumn(1, L"hmm1");
	

	EditRow er1;
	er1.setColumnSize(3);
	er1.setColumn(0, L"hello");
	er1.setColumn(1, L"hmm");
	

	//copy conststructer
	EditRow er1_1(er);
	wcout << er1_1.getColumn(0) << endl;
	wcout << er1_1.getColumn(1) << endl;
	er1_1 = er1;
	wcout << er1_1.getColumn(0) << endl;
	wcout << er1_1.getColumn(1) << endl;
	

}
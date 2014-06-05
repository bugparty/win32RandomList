#pragma once
#include "EditRow.h"
class CsvReader
{
public:
	CsvReader();
	~CsvReader();
	
private:
	FILE* fp;
	TCHAR headString[MAX_LINE];
	int rowCount;
	EditRow headRow;
	EditRow rows[5000];
	bool isOpen;
public:
	CsvReader(TCHAR* filePath);
	bool isOpened();
	bool getHeader(TCHAR** header);
	bool getRow(int pos, EditRow** ppEr);
	bool setRow(int pos, EditRow & er);
	int open(const TCHAR * filepath);
	int getRowCount();
};


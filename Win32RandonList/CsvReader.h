#pragma once
#include "EditRow.h"
#include "config.h"
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
	EditRow rows[MAX_ROW_LOAD];
	bool isOpen;
	void load_utf8();
	void load_unicode();
	const TCHAR *filepath;
public:
	CsvReader(TCHAR* filePath);
	bool isOpened();
	bool getHeaderPtr(TCHAR** header);
	TCHAR* getHeader();
	bool getHeadRow(EditRow** ppEr);
	EditRow *getHeadRow();
	bool getRow(int pos, EditRow** ppEr);
	bool setRow(int pos, EditRow & er);
	int open(const TCHAR * filepath);
	int getRowCount();
};


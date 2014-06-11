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
	int skiplines;
	
public:
	void CsvReader::load_gb2312();
	void swap(EditRow& left, EditRow &right);
	void swapRow(int pos, EditRow& left, EditRow &right);
	CsvReader(TCHAR* filePath);
	bool isOpened();
	bool getHeaderPtr(TCHAR** header);
	TCHAR* getHeader();
	bool getHeadRow(EditRow** ppEr);
	EditRow *getHeadRow();
	bool getRow(int pos, EditRow** ppEr);
	EditRow &getRow(int pos);
	bool setRow(int pos, EditRow & er);
	int CsvReader::open(const TCHAR * filepath, int skiplines = 0);
	int getRowCount();
	void randSort(int column);
	void save(const TCHAR*filepath);
};


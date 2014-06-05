#include "stdafx.h"
#include "CsvReader.h"
using namespace std;
CsvReader::CsvReader()
{
	rowCount = 0;
	fp = NULL;
	this->isOpen = false;
}


CsvReader::~CsvReader()
{
	if (fp!=NULL)
		fclose(fp);
}

bool CsvReader::getRow(int pos, EditRow** ppEr)
{
	if (pos < 0 || pos > rowCount){
		return FALSE;
	}
	*ppEr = rows + pos;
	return TRUE;
}
bool CsvReader::setRow(int pos, EditRow & er){
	if (pos < 0 || pos > rowCount){
		return FALSE;
	}
	rows[pos] = er;
	return TRUE;
}

CsvReader::CsvReader(TCHAR* filePath)
{
	
	open(filePath);
	
}
int CsvReader::getRowCount(){
	return rowCount;
}
bool CsvReader::getHeader(TCHAR** header){
	*header = (headString);
	return true;
}
bool CsvReader::isOpened(){
	return isOpen;
}
int CsvReader::open(const TCHAR * filepath)
{
	fp = _tfopen(filepath, L"rt,ccs=UNICODE");
	assert(fp != NULL);
	TCHAR buf[80];
	fwscanf(fp, L"%s", buf);
	lstrcpy(headString, buf);
	RowHelper rh(buf);
	EditRow &er =  rh.getObj();
	headRow = er;
	while (!feof(fp)){
		fwscanf(fp, L"%s", buf);
		RowHelper r(buf);
		rows[rowCount++] = r.getObj();

	}
	isOpen = true;

	return 0;
}

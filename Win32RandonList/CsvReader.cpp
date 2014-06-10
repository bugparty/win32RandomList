#include "stdafx.h"
#include "CsvReader.h"
#include "Codec.h"
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
EditRow &CsvReader::getRow(int pos){
	if (pos < 0 || pos > rowCount){
		return rows[0];
	}
	return (rows[pos]);
}
bool CsvReader::getRow(int pos, EditRow** ppEr)
{
	if (pos < 0 || pos > rowCount){
		return FALSE;
	}
	*ppEr = (rows + pos);

	return TRUE;
}
EditRow* CsvReader::getHeadRow()
{

	return &headRow;
}
void CsvReader::swapRow(int pos, EditRow& left, EditRow &right){
	TCHAR buf[COLUMN_WIDTH];
	lstrcpy(buf, left.getColumn(pos));
	left.setColumn(pos, right.getColumn(pos));
	lstrcpy(right.getColumn(pos), buf);


}
bool CsvReader::getHeadRow(EditRow** ppEr)
{

	*ppEr = &headRow;

	return TRUE;
}
bool CsvReader::setRow(int pos, EditRow & er){
	if (pos < 0 || pos > rowCount){
		return FALSE;
	}
	rows[pos] = er;
	return TRUE;
}

void CsvReader::swap(EditRow& left, EditRow &right){
	EditRow t = left;
	left = right;
	right = t;
}
CsvReader::CsvReader(TCHAR* filePath)
{
	
	open(filePath);
	
}
int CsvReader::getRowCount(){
	return rowCount;
}
TCHAR* CsvReader::getHeader(){
	return headString;
}
void CsvReader::randSort(int column){
	for (int i = 0; i < rowCount; i++)
	{
		int j;
		do{
			j = rand() % rowCount;
		} while (j == i);
		swapRow(column,rows[i], rows[j]);
		
	}
}
bool CsvReader::getHeaderPtr(TCHAR** header)
{
	*header = (headString);
	return true;
}
bool CsvReader::isOpened(){
	return isOpen;
}
void CsvReader::load_unicode(){
	fp = _tfopen(filepath, L"rt,ccs=UNICODE");
	assert(fp != NULL);
	TCHAR buf[80];
	fwscanf(fp, L"%s", buf);
	lstrcpy(headString, buf);
	RowHelper rh(buf);
	EditRow &er = rh.getObj();
	headRow = er;
	while (!feof(fp)){
		fwscanf(fp, L"%s", buf);
		RowHelper r(buf);
		rows[rowCount++] = r.getObj();

	}
	isOpen = true;
}
void CsvReader::load_utf8(){
	fp = _tfopen(filepath, L"rt,ccs=UNICODE");
	assert(fp != NULL);
	TCHAR buf[80];
	fwscanf(fp, L"%s", buf);
	lstrcpy(headString, buf);
	RowHelper rh(buf);
	EditRow &er = rh.getObj();
	headRow = er;
	while (!feof(fp)){
		fwscanf(fp, L"%s", buf);
		RowHelper r(buf);
		rows[rowCount++] = r.getObj();
		if (rowCount >= MAX_ROW_LOAD)
			break;

	}
	isOpen = true;
}
int CsvReader::open(const TCHAR * filepath)
{
	rowCount = 0;
	this->filepath = filepath;
	switch (judge_file_codec(filepath)){
	case TX_UNICODE16:
		load_unicode();
		break;
	case TX_UTF8:
		load_utf8();
		break;
	default:
		load_utf8();
		break;
	}
	

	return 0;
}

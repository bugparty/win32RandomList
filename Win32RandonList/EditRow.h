#pragma once
#include "config.h"

class EditRow
{
public:
	EditRow();
	~EditRow();
	EditRow(int columnSize);
	EditRow::EditRow(const EditRow &orig);
	EditRow & EditRow::operator =( EditRow &orig);

	void setColumnSize(int size);
	bool setColumn(int pos,TCHAR* text);

	int getColumnSize();
	TCHAR* getColumn(int pos);
private:
	bool initMem();
	void freeMem();
	inline bool validatePos(int pos);
	TCHAR **pszBufs;
	int m_columnSize;


	
};


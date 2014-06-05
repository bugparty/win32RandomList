#include "stdafx.h"

#include "EditRow.h"
#include "StrUlits.h"
#include "rowHelper.h"
RowHelper::RowHelper(TCHAR* rowString)
{
	int pos[MAX_ROWS+1];
	int count;
	count = findColons(rowString, pos, MAX_ROWS);

	er.setColumnSize(count+1);

	
	pos[count] = lstrlen(rowString);

	TCHAR buffer[MAX_COLUMN_SIZE];
	wmemcpy(buffer, rowString, pos[0]);
	buffer[pos[0]] = L'\0';
#ifdef TEST
	fwprintf(stderr, L"%i:%s\n", 0, buffer);
#endif

	er.setColumn(0, buffer);

	for (int i = 0; i < count; i++){
		wmemcpy(buffer, rowString + pos[i]+1, pos[i + 1] - pos[i]-1);
		buffer[pos[i + 1] - pos[i]-1] = L'\0';
#ifdef TEST
		fwprintf(stderr, L"%i:%s\n", i+1, buffer);
#endif

		er.setColumn(i+1, buffer);

	}
	
	

}


RowHelper::~RowHelper()
{
}


EditRow RowHelper::getObj()
{
	return this->er;
}

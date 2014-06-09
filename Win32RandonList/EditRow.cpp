#include "stdafx.h"
#include "EditRow.h"

using namespace std;

EditRow::EditRow(){
	pszBufs = NULL;

	m_columnSize = 0;
#ifdef TEST_EDIT_ROW_LIFECYCLE
	wcerr << "hello EditRow " << this << endl;
#endif

}
EditRow::EditRow(const EditRow &orig){
	EditRow(orig.m_columnSize);
	m_columnSize = orig.m_columnSize;
	pszBufs = (TCHAR **)malloc(sizeof(TCHAR *)*m_columnSize);
	assert(pszBufs != NULL);

	for (int i = 0; i < m_columnSize; i++){
		pszBufs[i] = (TCHAR*)malloc(MAX_COLUMN_SIZE);
		memcpy(pszBufs[i], orig.pszBufs[i],MAX_COLUMN_SIZE);
		
		assert(pszBufs[i] != NULL);
	}
	

}
EditRow & EditRow::operator =( EditRow &orig){
	if (this == &orig){
		return *this;
	}

	freeMem();
	m_columnSize = orig.m_columnSize;
	initMem();
	TCHAR buf[MAX_COLUMN_SIZE];

	for (int i = 0; i < orig.getColumnSize(); i++){

		setColumn(i, orig.getColumn(i));
	}

	return *this;

}
EditRow::EditRow(int columnSize)
{
	pszBufs = NULL;
	m_columnSize = columnSize;
	initMem();
#ifdef TEST_EDIT_ROW_LIFECYCLE
	wcerr << "hello EditRow " << this << endl;
#endif

}
EditRow::~EditRow()
{
#ifdef TEST_EDIT_ROW_LIFECYCLE
	wcerr << L"byebye EditRow" << this << endl;
#endif
	if (pszBufs)
		freeMem();

}


void EditRow::setColumnSize(int size)
{
	if (m_columnSize != size){
		if (pszBufs)
			freeMem();
		m_columnSize = size;
		initMem();

		
	}
}


bool EditRow::setColumn(int pos, TCHAR* text)
{
	assert(m_columnSize > 0 );
	if (pos < 0 || pos >= m_columnSize){
#ifdef TEST
		wcerr << "setColumn pos out of range:" << pos << endl;
#endif
		return false;
	}
		

	if (!validatePos(pos))
		return false;
	lstrcpy(pszBufs[pos], text);
	return true;

}





bool EditRow::initMem()
{
	pszBufs = (TCHAR **)malloc(sizeof(TCHAR *)*m_columnSize);
	if (pszBufs == NULL) return false;

	for (int i = 0; i < m_columnSize; i++){
		pszBufs[i] = (TCHAR*)malloc(MAX_COLUMN_SIZE);
		if (pszBufs[i] == NULL) return false;
	}
	return true;
}


void EditRow::freeMem()
{
	if (pszBufs == NULL)return;
	for (int i = 0; i < m_columnSize; i++){

		free(pszBufs[i]);	

	}
	free(pszBufs);
	//防止多次析构问题
	pszBufs = NULL;

}


int EditRow::getColumnSize()
{
	return m_columnSize;
}


TCHAR* EditRow::getColumn(int pos)
{
	if (!pszBufs || !validatePos(pos))
		return NULL;
	return pszBufs[pos];

	
}


inline bool EditRow::validatePos(int pos)
{
	return (pos < MAX_COLUMN_SIZE && pos >= 0);
	
}

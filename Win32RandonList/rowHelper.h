#pragma once
#include "config.h"
#include <tchar.h>


class RowHelper
{
public:
	RowHelper::RowHelper(TCHAR *rowString);
	~RowHelper();
	EditRow getObj();
private:
	EditRow er;
};


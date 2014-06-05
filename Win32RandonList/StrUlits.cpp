#include "stdafx.h"
#include "StrUlits.h"


int findColons(const TCHAR * src, int * pos,int maxCount){
	int slen = lstrlen(src);
	int i = 0;

	for (const TCHAR *cur = src; cur < slen + src; cur++){
		if (*cur == L','){
			pos[i] = cur - src;
			i++;
			if (i <maxCount)
				continue;
			else break;
		}
	} 
	return i ;
		
	
}

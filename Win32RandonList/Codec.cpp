#include "stdafx.h"
#include "Codec.h"
#define BUF_SIZE 512
bool is_utf8_special_byte(unsigned char c);
bool is_utf8_code(const char * str, int size);
TEXT_CODEC judge_file_codec(const TCHAR *filePath){
	char *buf = (char*)malloc(BUF_SIZE+2);
	FILE*fp;
	assert(buf != NULL);
	int isize;
	fp = _tfopen(filePath, _T("r"));
	isize = fread(buf, 1, BUF_SIZE, fp);
	assert(isize > 0);
	int Ret;
	if (IsTextUnicode(buf, isize, &Ret)){
		if (Ret &IS_TEXT_UNICODE_ASCII16){
			free(buf);
			return TX_UNICODE16;
		}
		free(buf);
		return TX_UNKNOWN;
	}
	if (is_utf8_code(buf, isize)){
		free(buf);
		return TX_UTF8;
	}
	free(buf);
	return TX_UNKNOWN;
	


}
bool is_utf8_special_byte(unsigned char c)
{
	unsigned special_byte = 0X02; //binary 00000010    
	if (c >> 6 == special_byte) {
		return 1;
	}
	else {
		return 0;
	}
}

bool is_utf8_code(const char * str, int strSize)
{
	unsigned one_byte = 0X00; //binary 00000000
	unsigned two_byte = 0X06; //binary 00000110
	unsigned three_byte = 0X0E; //binary 00001110  
	unsigned four_byte = 0X1E; //binary 00011110
	unsigned five_byte = 0X3E; //binary 00111110
	unsigned six_byte = 0X7E; //binary 01111110

	int utf8_yes = 0;
	int utf8_no = 0;

	unsigned char k = 0;
	unsigned char m = 0;
	unsigned char n = 0;
	unsigned char p = 0;
	unsigned char q = 0;

	unsigned char c = 0;
	for (unsigned int i = 0; i < strSize; ) {
		c = (unsigned char)str[i];
		if (c >> 7 == one_byte) {
			i++;
			continue;
		}
		else if (c >> 5 == two_byte) {
			k = (unsigned char)str[i + 1];
			if (is_utf8_special_byte(k)) {
				utf8_yes++;
				i += 2;
				continue;
			}
		}
		else if (c >> 4 == three_byte) {
			m = (unsigned char)str[i + 1];
			n = (unsigned char)str[i + 2];
			if (is_utf8_special_byte(m)
				&& is_utf8_special_byte(n)) {
				utf8_yes++;
				i += 3;
				continue;
			}
		}
		else if (c >> 3 == four_byte) {
			k = (unsigned char)str[i + 1];
			m = (unsigned char)str[i + 2];
			n = (unsigned char)str[i + 3];
			if (is_utf8_special_byte(k)
				&& is_utf8_special_byte(m)
				&& is_utf8_special_byte(n)) {
				utf8_yes++;
				i += 4;
				continue;
			}
		}
		else if (c >> 2 == five_byte) {
			unsigned char k = (unsigned char)str[i + 1];
			unsigned char m = (unsigned char)str[i + 2];
			unsigned char n = (unsigned char)str[i + 3];
			unsigned char p = (unsigned char)str[i + 4];
			if (is_utf8_special_byte(k)
				&& is_utf8_special_byte(m)
				&& is_utf8_special_byte(n)
				&& is_utf8_special_byte(p)) {
				utf8_yes++;
				i += 5;
				continue;
			}
		}
		else if (c >> 1 == six_byte) {
			k = (unsigned char)str[i + 1];
			m = (unsigned char)str[i + 2];
			n = (unsigned char)str[i + 3];
			p = (unsigned char)str[i + 4];
			q = (unsigned char)str[i + 5];
			if (is_utf8_special_byte(k)
				&& is_utf8_special_byte(m)
				&& is_utf8_special_byte(n)
				&& is_utf8_special_byte(p)
				&& is_utf8_special_byte(q)) {
				utf8_yes++;
				i += 6;
				continue;
			}
		}

		utf8_no++;
		i++;
	}

	printf("%d %d\n", utf8_yes, utf8_no);
	if (utf8_yes == 0 && utf8_no == 0) //in case of ascii
		return true;

	int ret = (100 * utf8_yes) / (utf8_yes + utf8_no);
	if (ret > 90) {
		return true;
	}
	else {
		return false;
	}
}


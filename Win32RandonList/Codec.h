#define TX_UNKNOWN 0
#define TX_UTF8 1
#define TX_GBK 2
#define TX_UNICODE16 3

typedef int TEXT_CODEC;
TEXT_CODEC judge_file_codec(const TCHAR *filePath);

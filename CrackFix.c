#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int SearchAndReplaceHexInFile(const char* fileName, const unsigned char* searchHex, const unsigned char* replaceHex, size_t searchSize, size_t replaceSize) {

	size_t i;	/* 因为编译器是C90，在循环外部声明变量 */

	FILE* file;
	unsigned char buffer[BUFFER_SIZE];
	size_t bytesRead;
	long pos = 0;
	int replacements = 0;
	/*	int found = 0;*/

	if (fopen_s(&file, fileName, "rb+") != 0) {
		printf("无法打开文件 %s\n", fileName);
		return -1;
	}

	while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
		for (i = 0; i < bytesRead - searchSize + 1; ++i) {
			if (memcmp(buffer + i, searchHex, searchSize) == 0) {
				fseek(file, pos + i, SEEK_SET);
				fwrite(replaceHex, 1, replaceSize, file);
				fseek(file, pos + i + replaceSize, SEEK_SET);
				printf("正在修补，位于文件 %lu 处。\n", (unsigned long)(pos + i));
				replacements++;
				/* found = 1; */
				/* break;	替换完成后跳出内层循环 */
			}
		}
		pos += bytesRead;

		/*	if (found == 1) {
				break;	* 找到并替换了一个位置，跳出外层循环 *
		}*/
	}

	fclose(file);

	if (replacements == 1) {
		return 0;	/* 必须替换了一个位置，或多或少都是失败 */
	} else {
		return -1;	/* 没有找到或过多替换或替换失败 */
	}
}

int CrackFix(char* fileName) {

	struct HexPair {
		unsigned char *searchHex;
		unsigned char *replaceHex;
		int searchSize;
		int replaceSize;
	};

	struct HexPair hexPairs[] = {	/* 定义 HexPair 结构体数组 */
		{ NULL, NULL, 0, 0 }, /* 第一个结构体占位，后面在赋值 */
		{ NULL, NULL, 0, 0 },
		{ NULL, NULL, 0, 0 },
		{ NULL, NULL, 0, 0 }
	};

	int i;	/* 因为编译器是C90，在循环外部声明变量 */
	int fixCount = 0;
	int numPairs = sizeof(hexPairs) / sizeof(hexPairs[0]);

	unsigned char pattern1[] = { 0xFB, 0xFF, 0xFF, 0x83, 0xF8, 0x06, 0x75, 0x16, 0x8B, 0xCE, 0xE8 };
	unsigned char replacement1[] = { 0xFB, 0xFF, 0xFF, 0x83, 0xF8, 0x07, 0x75, 0x16, 0x8B, 0xCE, 0xE8 };

	unsigned char pattern2[] = { 0x76, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xE9 };
	unsigned char replacement2[] = { 0x76, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0xE9 };

	unsigned char pattern3[] = { 0x63, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xE9 };
	unsigned char replacement3[] = { 0x63, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0xE9 };

	unsigned char pattern4[] = { 0x76, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xE9 };
	unsigned char replacement4[] = { 0x76, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0xE9 };

	hexPairs[0].searchHex = pattern1;
	hexPairs[0].replaceHex = replacement1;
	hexPairs[0].searchSize = 11;
	hexPairs[0].replaceSize = 11;

	hexPairs[1].searchHex = pattern2;
	hexPairs[1].replaceHex = replacement2;
	hexPairs[1].searchSize = 8;
	hexPairs[1].replaceSize = 8;

	hexPairs[2].searchHex = pattern3;
	hexPairs[2].replaceHex = replacement3;
	hexPairs[2].searchSize = 8;
	hexPairs[2].replaceSize = 8;

	hexPairs[3].searchHex = pattern4;
	hexPairs[3].replaceHex = replacement4;
	hexPairs[3].searchSize = 8;
	hexPairs[3].replaceSize = 8;

	for (i = 0; i < numPairs; ++i) {	/* 循环遍历每个十六进制对并执行搜索和替换 */
		if (SearchAndReplaceHexInFile(fileName, hexPairs[i].searchHex, hexPairs[i].replaceHex, hexPairs[i].searchSize, hexPairs[i].replaceSize) == 0) {
			fixCount++;
		}
	}

	if (fixCount == numPairs) {	/* 如果所有替换都成功，则返回成功 */
		return 0;
	} else {
		return -1;
	}
}

/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 1024

int fixCount = 0;

int SearchAndReplaceHexInFile(const char* fileName, const unsigned char* searchHex, const unsigned char* replaceHex, size_t searchSize, size_t replaceSize) {

FILE* file = fopen(fileName, "rb+");
if (file == NULL) {
printf("无法打开文件 %s\n", fileName);
return -1;
}

unsigned char buffer[BUFFER_SIZE];
size_t bytesRead;
long pos = 0;
while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {	// 搜索并修补
for (size_t i = 0; i < bytesRead - searchSize + 1; ++i) {
if (memcmp(buffer + i, searchHex, searchSize) == 0) {
fseek(file, pos + i, SEEK_SET);
fwrite(replaceHex, 1, replaceSize, file);
fseek(file, pos + i + replaceSize, SEEK_SET);
printf("正在修补，位于文件 %zu 处。\n", pos + i);
fixCount++;
return 0;
}
}
pos += bytesRead;
}

fclose(file);

return 0;
}

int CrackFix(const char* fileName) {

unsigned char searchHex1[] = { 0xFB, 0xFF, 0xFF, 0x83, 0xF8, 0x06, 0x75, 0x16, 0x8B, 0xCE, 0xE8 };
unsigned char replaceHex1[] = { 0xFB, 0xFF, 0xFF, 0x83, 0xF8, 0x07, 0x75, 0x16, 0x8B, 0xCE, 0xE8 };
SearchAndReplaceHexInFile(fileName, searchHex1, replaceHex1, sizeof(searchHex1), sizeof(replaceHex1));

unsigned char searchHex2[] = { 0x76, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xE9 };
unsigned char replaceHex2[] = { 0x76, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0xE9 };
SearchAndReplaceHexInFile(fileName, searchHex2, replaceHex2, sizeof(searchHex2), sizeof(replaceHex2));

unsigned char searchHex3[] = { 0x63, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xE9 };
unsigned char replaceHex3[] = { 0x63, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0xE9 };
SearchAndReplaceHexInFile(fileName, searchHex3, replaceHex3, sizeof(searchHex3), sizeof(replaceHex3));

unsigned char searchHex4[] = { 0x76, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xE9 };
unsigned char replaceHex4[] = { 0x76, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0xE9 };
SearchAndReplaceHexInFile(fileName, searchHex4, replaceHex4, sizeof(searchHex4), sizeof(replaceHex4));

if (fixCount != 4) {	// 修补失败返回-1，成功返回0

return -1;
} else {

return 0;
}
}*/

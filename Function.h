#pragma once

#ifndef Function
#define Function

/* 声明函数 */

int GenerateRandomString(char* str, size_t len);

int BackupFile(const char* fileName, char* backupFileName, char* randomSuffix);

int Declare();

int InputKeyGo(const char* inputS, const char* inputB);

int InputPassword();

int PrintfHelp();

int SearchAndReplaceHexInFile(const char* fileName, const unsigned char* searchHex, const unsigned char* replaceHex, size_t searchSize, size_t replaceSize);

int CrackFix(const char* fileName);

#endif

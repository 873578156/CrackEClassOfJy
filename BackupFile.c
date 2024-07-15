#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int GenerateRandomString(char* str, size_t len) {

	size_t i;	/* 因为编译器是C90，在循环外部声明变量 */
	char charSet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size_t charsetSize = strlen(charSet);

	srand((unsigned int)time(NULL));

	for (i = 0; i < len; ++i) {
		int index = rand() % charsetSize;
		str[i] = charSet[index];
	}

	str[len] = '\0';	/* 在末尾添加 null 终止符 */
	return 0;
}

int BackupFile(const char* fileName, char* backupFileName, char* randomSuffix) {

	errno_t err;
	FILE* source, * target;

	int requiredSize = snprintf(NULL, 0, "%s.bak.%s", fileName, randomSuffix);	/* 构建备份文件名：在文件名后添加 .bak 后缀 */
	int ch;	/* 复制文件内容 */

	err = fopen_s(&source, fileName, "rb");	/* 打开源文件进行读取 */
	if (err != 0 || source == NULL) {
		perror("打开源文件错误！");
		return -1;
	}

	if (requiredSize < 0) {
		perror("计算备份文件名大小错误！");
		fclose(source);
		return -1;
	}

	err = sprintf_s(backupFileName, requiredSize + 1, "%s.bak.%s", fileName, randomSuffix);
	if (err < 0) {
		perror("构建备份文件名错误！");
		fclose(source);
		return -1;
	}

	err = fopen_s(&target, backupFileName, "wb");	/* 打开备份文件进行写入 */
	if (err != 0 || target == NULL) {
		perror("创建备份文件错误！");
		fclose(source);
		return -1;
	}

	while ((ch = fgetc(source)) != EOF) {
		fputc(ch, target);
	}

	fclose(source);	/* 关闭文件 */
	fclose(target);

	return 0;
}

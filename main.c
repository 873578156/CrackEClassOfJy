#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Function.h"

int main(int argc, char* argv[]) {

	char* fileName = NULL;	/* 默认文件名路径 */
	char randomSuffix[9];	/* 随机字符变量初始化 + '\0' */
	char backupFileName[256];	/* 假设备份文件名不超过255字符 */

	if (argc >= 3 && strcmp(argv[1], "-path") == 0) {
		fileName = argv[2];	/* 使用传递的路径参数 */
		Declare();	/* 执行作者声明函数 */
		if (argc > 3 && strcmp(argv[argc - 1], "-y") == 0) {	/* 如果最后一个参数是 "-y"，则不需要用户输入，直接执行 */
		} else {
			if (InputPassword() == -1) {
				return -1;
			}
			if (InputKeyGo("y", "Y") == -1) {
				return -1;
			}
		}
		if (GenerateRandomString(randomSuffix, sizeof(randomSuffix) - 1) != -1) {	/* 生成随机后缀 */
			if (BackupFile(fileName, backupFileName, randomSuffix) != -1) {	/* 执行备份文件函数 */
				printf("备份文件创建成功！%s \n", backupFileName);
				if (CrackFix(fileName) != -1) {	/* 调用修补文件参数 */
					printf("修补成功，请启动软件尝试。\n");
					return 0;
				} else {
					printf("修补失败，可能文件不正确或以前修补过，请启动软件尝试。\n");
					return -1;
				}
			} else {
				printf("备份文件创建失败！ \n");
				return -1;
			}
		} else {
			return -1;
		}
	} else {	/* 参数不符合要求的情况 */
		Declare();	/* 执行作者声明函数 */
		PrintfHelp();	/* 执行帮助参数 */

		return -1;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int InputKeyGo(char* inputS, char* inputB) {

	char userInput[255];
	printf("请输入 (%s) 或 (%s) 继续：", inputS, inputB);

	if (scanf_s("%s", userInput, (unsigned)_countof(userInput)) != 1) {
		printf("输入失败或格式错误！\n");
		return -1;	/* 处理输入失败的情况，可以返回错误或者采取其他措施 */
	}

	if (strlen(userInput) != 1) {
		printf("输入长度不正确！\n");
		return -1;	/* 立即退出程序，表示输入不合法 */
	}

	if (strcmp(userInput, inputS) == 0 || strcmp(userInput, inputB) == 0) {
		return 0;
	} else {
		printf("输入了其他值！\n");
		return -1;	/* 处理输入失败的情况，可以返回错误或者采取其他措施 */
	}

	return 0;
}

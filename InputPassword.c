#include <stdio.h>
#include <time.h>
#include <stdlib.h>	/* 为了使用 exit 函数 */

int InputPassword() {

	time_t t;
	struct tm currentTime;
	int currentMinute, currentHour;
	int inputPassword;

	time(&t);	/* 获取当前时间（从1970年1月1日开始的秒数） */
	localtime_s(&currentTime, &t);	/* 将时间转换为本地时间结构体 */
	currentMinute = currentTime.tm_min;	/* 获取当前分钟数 */
	currentHour = currentTime.tm_hour;	/* 获取当前小时数 */

	printf("请输入密码: ");
	if (scanf_s("%d", &inputPassword) != 1) {
		printf("输入错误！\n");
		return -1;	/* 处理输入失败的情况，可以返回错误或者采取其他措施 */
	}

	if (inputPassword != (currentHour + currentMinute) % (currentHour - currentMinute)) {
		printf("密码错误，程序退出。\n");
		return -1;	/* 输入错误直接退出程序 */
	}

	printf("密码正确，欢迎使用程序。\n");

	return 0;
}

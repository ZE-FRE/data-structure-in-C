#ifndef STRING_H_
#define STRING_H_

#include <stdbool.h>

/*
 * 串：字符串的简称
 */

typedef struct {
	// 若是非空串，则按串长分配存储区，否则ch为NULL。ch不需要以'\0'结尾
	char* ch;
	// 串长度
	int length;
} String;

void InitString(String* str);

/*======串的基本操作======*/
// 生成一个其值等于串常量chars的串
bool StringAssign(String* str, const char* chars);

int StringLength(const String* str);

// 若str1 > str2，返回值>0，若str1 == str2，返回值为0，若str1 < str2，返回值<0
int StringCompare(const String* str1, const String* str2);

// 将串str清为空串，并释放str所占空间
bool ClearString(String *str);

// 用str返回str1和str2联接而成的新串
bool StringConcat(String* str, const String *str1, const String *str2);

/*
 * 用str返回串s第pos个字符起长度为len的字串
 * 1 <= pos <= StringLength(str)，且0 <= len <= StringLength(str) - pos + 1
 */
bool SubString(String *str, const String *s, int pos, int len);

/*======串的基本操作======*/

void printString(const String* str);

void testString();

#endif


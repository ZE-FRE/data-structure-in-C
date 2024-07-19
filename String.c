#include "String.h"
#include <stdio.h>
#include <stdlib.h>

void InitString(String* str)
{
	if (!str) return;
	str->ch = NULL;
	str->length = 0;
}

bool StringAssign(String* str, const char* chars)
{
	// 释放原有空间
	if (str->ch) free(str->ch);
	// chars == NULL || *chars == '\0'
	if (!chars || !*chars) { 
		// 初始化为空串
		str->ch = NULL;
		str->length = 0;
		return true;
	}
	// 计算chars的长度
	int len = 0;
	for (const char* c = chars; *c; ++c, ++len);

	str->ch = (char*)malloc(sizeof(char) * len);
	if (!str->ch) return false;
	for (int i = 0; i < len; ++i)
		str->ch[i] = chars[i];
	str->length = len;
	return true;
}

int StringLength(const String* str)
{
	return !str ? 0 : str->length;
}

int StringCompare(const String* str1, const String* str2)
{
	for (int i = 0; i < str1->length && i < str2->length; ++i)
		if (str1->ch[i] != str2->ch[i])
			return str1->ch[i] - str2->ch[i];
	return str1->length - str2->length;
}

bool ClearString(String* str)
{
	if (str) {
		free(str->ch);
		str->ch = NULL;
		str->length = 0;
	}
	return true;
}

bool StringConcat(String* str, const String* str1, const String* str2)
{
	// 其实按理来说，str用于接收返回值，应该是个空串
	if (str->ch) free(str->ch);

	int len1 = StringLength(str1);
	int len2 = StringLength(str2);

	str->ch = (char*)malloc(sizeof(char) * (len1 + len2));
	if (!str->ch) return false;

	for (int i = 0; i < len1; ++i)
		str->ch[i] = str1->ch[i];
	for (int i = 0, j = len1; i < len2; ++i, ++j)
		str->ch[j] = str2->ch[i];
	str->length = len1 + len2;
	return true;
}


bool SubString(String* str, const String* s, int pos, int len)
{
	if (pos < 1 || pos > s->length || len < 0 || len > s->length - pos + 1)
		return false;
	if (str->ch) {
		free(str->ch);
		str->length = 0;
	}
	if (len == 0) {
		str->ch = NULL;
		str->length = 0;
		return true;
	}
	str->ch = (char*)malloc(sizeof(char) * len);
	if (!str->ch) return false;
	for (int i = 0; i < len; ++i) 
		str->ch[i] = s->ch[pos - 1 + i];
	str->length = len;
	return true;
}

void printString(const String* str)
{
	if (str && str->length > 0) {
		for (int i = 0; i < str->length; ++i)
			printf("%c", str->ch[i]);
	}
}

void testString()
{
	String str1;
	InitString(&str1);
	StringAssign(&str1, "hello world!");

	String str2;
	InitString(&str2);
	StringAssign(&str2, "hello world!");

	int ret = StringCompare(&str1, &str2);
	printf("str1 compare to str2 = %d", ret);

	String str;
	InitString(&str);
	StringConcat(&str, &str1, &str2);
	printf("\nstr = ");
	printString(&str);

	String sub;
	InitString(&sub);
	SubString(&sub, &str, 13, 5);
	printf("\nsub = ");
	printString(&sub);

	ClearString(&str1);
	ClearString(&str2);
	ClearString(&str);
	ClearString(&sub);
}

#ifndef STACK_IMPL_2_H_
#define STACK_IMPL_2_H_

#include <stdbool.h>

#define STACK_INIT_LENGTH 5
#define STACK_INCREASE 2

typedef int StackElemType;

typedef struct {
	// 栈底指针，指向动态数组首地址
	StackElemType* base;
	// 栈顶指针，指向栈顶元素的下一个位置
	StackElemType* top;
	// 动态数组长度
	int length;
} StackImpl2;

bool InitStack2(StackImpl2* stack);

void DestroyStack2(StackImpl2 *stack);

bool Stack2IsEmpty(const StackImpl2* stack);

bool PushToStack2(StackImpl2* stack, const StackElemType data);

bool PopFromStack2(StackImpl2* stack, StackElemType* data);

bool GetTop(const StackImpl2* stack, StackElemType* data);

int Stack2Length(const StackImpl2* stack);

void testStackImpl2();


/*==========王道书第3章栈算法题=========*/

/*
 * 03：栈的初态和终态均为空，以I和O分别表示入栈和出栈，则出入栈的操作序列可表示为由I和O组成的序列，
 * 可以操作的序列称为合法序列，否则称为非法序列。
 * 1）下面所示的序列中哪些是合法的？
 * A.IOIIOIOO	B.IOOIOIIO	C.IIIOIOIO	D.IIIOOIOO
 * 2）通过对1）的分析，写出一个算法，判定所给的操作序列是否合法。若合法，返回true，
 * 否则返回false（假定被判定的操作序列已存入一维数组中）。
 * date:2024/8/15
 * 解答：A、D是合法的
 * 思路：用一个栈来模拟操作，遍历操作序列，若是I，则入栈；若是O，则尝试出栈，若栈为空导致出栈失败，则表明操作序列非法；
 * 操作序列遍历完时，若栈为空，则表明序列合法，否则不合法。
 */
#define I 69
#define O 79
bool stackOpIsLegal(const char* opSerial, int len);
void testStackIsOpLegal();

/*
 * 04：设单链表的表头指针为L，结点结构由data和next两个域构成，其中data域为字符型。
 * 试设计算法判断该链表的全部n个字符是否中心对称。例如xyx、xyyx都是中心对称。
 * date:2024/8/16
 * 思路：本章判断链表是否中心对称，即要求使用栈。
 * 使用快慢指针，慢指针每次走一步，把指针所指的值入栈，快指针每次走两步，当快指针走到链表尾时，慢指针走到链表中部，
 * 然后用慢指针遍历链表后半部分，与栈顶出栈元素对比，若相等，则继续遍历，若不相等，则表明链表不是中心对称，返回false。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
// 模拟
#define a 0
#define b 1
#define c 2
#include "ForwardList.h"
bool listIsSymmetry(ForwardList list);
void testListIsSymmetry();

/*
 *
 * 栈和队列的应用：
 * 01：假设一个算术表达式中包含圆括号、方括号和花括号3种类型的括号，编写一个算法来判别表达式中的括号是否配对，
 * 以字符“\0”作为算术表达式的结束符。
 */
// 圆括号
#define L_PARENTHESIS 40
#define R_PARENTHESIS 41
// 方括号
#define L_BRACKET 91
#define R_BRACKET 93
// 大括号
#define L_BRACE 123
#define R_BRACE 125
/*
 * 思路：遍历表达式，遇到左括号入栈，遇到右括号出栈，若出栈括号与当前右括号不匹配或者栈为空，则返回false；
 * 当表达式遍历完毕且栈为空时，说明表达式中的括号是配对的，否则不配对。
 * date:2024/8/16
 */
bool bracketIsMatch(const char *brackets);
void testBracketIsMatch();

/*==========王道书第3章栈算法题=========*/

#endif
#include "StackImpl2.h"
#include <stdio.h>
#include <stdlib.h>

bool InitStack2(StackImpl2* stack)
{
    StackElemType* base = (StackElemType*)malloc(sizeof(StackElemType) * STACK_INIT_LENGTH);
    if (!base) return false;
    stack->base = stack->top = base;
    stack->length = STACK_INIT_LENGTH;
    return true;
}

void DestroyStack2(StackImpl2* stack)
{
    if (stack)
        free(stack->base);
}

bool Stack2IsEmpty(const StackImpl2* stack)
{
    return !stack || stack->base == stack->top;
}

bool PushToStack2(StackImpl2* stack, const StackElemType data)
{
    if (stack->top - stack->base >= stack->length) { // 栈满，扩容
        printf("扩容了\n");
        int oldLength = stack->length;
        int newLength = oldLength + STACK_INCREASE;
        StackElemType* newBase = (StackElemType*)realloc(stack->base, sizeof(StackElemType) * newLength);
        if (!newBase) return false;
        stack->base = newBase;
        stack->top = stack->base + oldLength;
        stack->length = newLength;
    }
    *stack->top++ = data;
    return true;
}

bool PopFromStack2(StackImpl2* stack, StackElemType* data)
{
    if (Stack2IsEmpty(stack)) return false;
    *data = *--stack->top;
    return true;
}

bool GetTop(const StackImpl2* stack, StackElemType* data)
{
    if (Stack2IsEmpty(stack)) return false;
    *data = *(stack->top - 1);
    return true;
}

int Stack2Length(const StackImpl2* stack)
{
    return stack->length;
}

void testStackImpl2()
{
    //StackImpl2 stack;
    //InitStack2(&stack);
    //for (int i = 1; i <= STACK_INIT_LENGTH + 3; ++i)
    //    PushToStack2(&stack, i);
    //StackElemType data;
    //if (GetTop(&stack, &data))
    //    printf("top data is %d ", data);
    //printf("\nstack data is: ");
    //for (int i = 0; i < Stack2Length(&stack); ++i) 
    //    if (PopFromStack2(&stack, &data))
    //        printf("%d ", data);
    //if (!PopFromStack2(&stack, &data))
    //    printf("\nstack is empty");
    //DestroyStack2(&stack);

    //testStackIsOpLegal();

    //testListIsSymmetry();

    testBracketIsMatch();

}

bool stackOpIsLegal(const char* opSerial, int len)
{
    StackImpl2 stack;
    InitStack2(&stack);
    int data;
    for (int i = 0; i < len; ++i) {
        if (opSerial[i] == I)
            PushToStack2(&stack, I);
        else if (opSerial[i] == O) {
            if (!PopFromStack2(&stack, &data))
                return false;
        }
    }
    bool ret = Stack2IsEmpty(&stack);
    DestroyStack2(&stack);
    return ret;
}

void testStackIsOpLegal()
{
    int len = 8;
    char A[] = { I,O,I,I,O,I,O,O };
    char B[] = { I,O,O,I,O,I,I,O };
    char C[] = { I,I,I,O,I,O,I,O };
    char D[] = { I,I,I,O,O,I,O,O };
    puts("王道03：判定所给的操作序列是否合法。");
    printf("操作序列 A=IOIIOIOO 是否合法？%d\n", stackOpIsLegal(A, len));
    printf("操作序列 B=IOOIOIIO 是否合法？%d\n", stackOpIsLegal(B, len));
    printf("操作序列 C=IIIOIOIO 是否合法？%d\n", stackOpIsLegal(C, len));
    printf("操作序列 D=IIIOOIOO 是否合法？%d\n", stackOpIsLegal(D, len));
}

bool listIsSymmetry(ForwardList list)
{
    // 空链表或链表只有一个结点
    if (ListEmpty(list) || list->next->next == NULL) return true;

    StackImpl2 stack;
    InitStack2(&stack);
    ListNode *slow = list, *fast = list;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        PushToStack2(&stack, slow->elem);
    }
    
    int data;
    if (fast == NULL) // 链表长度为奇数，正中间结点不需要比较，退栈
        PopFromStack2(&stack, &data);
    // 遍历链表后半部分，判断是否中心对称
    ListNode *p = slow->next;
    while (p) {
        PopFromStack2(&stack, &data);
        if (p->elem != data)
            return false;
        p = p->next;
    }
    DestroyStack2(&stack);
    return true;
}
void testListIsSymmetry()
{
    int elems[] = { a,b,c,a,c,b,a };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道03：判断该链表的全部n个字符是否中心对称");
    printf("初始链表：");
    printList(list);

    printf("\n是否中心对称？%d", listIsSymmetry(list));
    DestroyList(&list);
}

bool bracketIsMatch(const char* brackets)
{
    StackImpl2 stack;
    InitStack2(&stack);

    int top;
    for (const char* p = brackets; *p; ++p) {
        // 左括号入栈
        if (*p == L_PARENTHESIS || *p == L_BRACKET || *p == L_BRACE)
            PushToStack2(&stack, *p);
        else { // 右括号出栈
            if (!PopFromStack2(&stack, &top))
                return false;
            if (*p == R_PARENTHESIS && top != L_PARENTHESIS)
                return false;
            else if (*p == R_BRACKET && top != L_BRACKET)
                return false;
            else if (*p == R_BRACE && top != L_BRACE)
                return false;
        }
    }
    bool ret = Stack2IsEmpty(&stack);
    DestroyStack2(&stack);
    return ret;
}
void testBracketIsMatch()
{
    puts("王道栈和队列的应用：01：括号匹配。");
    char expression1[] = "{[()]}";
    printf("%s是否匹配？%d\n", expression1, bracketIsMatch(expression1));
    char expression2[] = "[(){(]";
    printf("%s是否匹配？%d\n", expression2, bracketIsMatch(expression2));
    char expression3[] = "([]){()[{}]}";
    printf("%s是否匹配？%d\n", expression3, bracketIsMatch(expression3));
    char expression4[] = "]";
    printf("%s是否匹配？%d\n", expression4, bracketIsMatch(expression4));
}

/*
   Question:
	 How would you design a stack which, in addition to push and pop, also has a
	 function min which returns the minimum element? Push, pop and min should 
	 all operate in O(1) time.
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#define MAXINT (~(1 << (8 * sizeof(int) - 1)))
#define MAX_ITERATOR 1024

/*-------------------------------------------------------------------------------*/
#define IS_STACK_EMPTY(s) ((s)->top == -1)
#define IS_STACK_FULL(s) ((s)->top == (s)->length)
struct stack{
	int *d;
	int  top;
	int  length;
};

/**
 * @brief 初始化栈
 *
 * @param s
 * @param length 栈的最大元素个数
 *
 * @return  栈的最大元素个数
 */
int stack_init(struct stack *s, int length)
{
	s->d      = malloc(sizeof(int) * length);
	s->top    = -1;
	s->length = length;
	return length;
}

/**
 * @brief 销毁栈s
 *
 * @param s
 *
 * @return 返回栈大小
 */
int stack_destroy(struct stack *s)
{
	free(s->d);
	s->d = NULL;
	s->top = -1;
	return s->length;
}


/**
 * @brief 打印栈中元素，栈顶在右
 *
 * @param s
 *
 * @return 
 */
void stack_print(struct stack *s)
{
	int i;
	printf("stack:{");
	for (i = 0; i <= s->top; i++)
	{
		printf("%d --> ", s->d[i]);
	}
	printf("NULL}\n");
}

/**
 * @brief 返回栈顶元素的位置
 *
 * @param s
 *
 * @return 成功返回栈顶元素的位置, 失败返回-1
 */
int stack_top(struct stack *s)
{
	return s->top;
}

/**
 * @brief 将栈顶元素弹出
 *
 * @param s
 *
 * @return 成功返回所弹出的栈顶元素的位置, 失败返回-1
 */
int stack_pop(struct stack *s)
{
	return (s->top --);
}

/**
 * @brief 将元素key压入到栈s中
 *
 * @param s
 * @param key
 *
 * @return 成功返回压入后的栈顶的位置, 失败返回-1
 */
int stack_push(struct stack *s, int key)
{
	if(IS_STACK_FULL(s))
		return -1;
	s->top ++;
	s->d[s->top] = key;
	return s->top;
}

/*-------------------------------------------------------------------------------*/

#define IS_STACKMIN_EMPTY(s)	IS_STACK_EMPTY(&(s)->d)
#define IS_STACKMIN_FULL(s)		IS_STACK_FULL(&(s)->d)
struct stackmin{
	struct stack  d;
	struct stack  min;
	int          *dd;
	int            length;
};

/**
 * @brief 初始化栈sm
 *
 * @param sm
 * @param length
 *
 * @return 栈的最大元素个数
 */
int stackmin_init(struct stackmin *sm, int length)
{
	stack_init(&sm->d, length);
	stack_init(&sm->min, length);
	sm->length = length;
	sm->dd     = sm->d.d;
	return length;
}


/**
 * @brief 销毁栈sm
 *
 * @param sm
 *
 * @return 返回栈sm的大小
 */
int stackmin_destroy(struct stackmin *sm)
{
	stack_destroy(&sm->d);
	stack_destroy(&sm->min);
	sm->dd = NULL;
	return sm->length;
}

/**
 * @brief 返回栈sm的栈顶元素位置
 *
 * @param sm
 *
 * @return 成功返回栈sm的栈顶元素位置, 失败返回-1
 */
int stackmin_top(struct stackmin *sm)
{
	return stack_top(&sm->d);
}

/**
 * @brief 返回栈sm中的最小元素的位置(多个相同最小值时返回第一个进入栈的)
 *
 * @param sm
 *
 * @return 成功返回栈sm中的最小元素, 失败返回-1
 */
int stackmin_min(struct stackmin *sm)
{
	if (IS_STACKMIN_EMPTY(sm))
		return -1;
	else
		return sm->min.d[stack_top(&sm->min)];
}


/**
 * @brief 弹出栈sm的栈顶元素
 *
 * @param sm
 *
 * @return 成功返回所弹出的栈顶元素的位置, 失败返回-1
 */
int stackmin_pop(struct stackmin *sm)
{
	if (IS_STACKMIN_EMPTY(sm))
		return -1;
	int imin = stackmin_min(sm);
	int ipop = stack_pop(&sm->d);
	if (imin == ipop)
	{
		stack_pop(&sm->min);
	}
	return ipop;

}

/**
 * @brief 将key压入栈sm中
 *
 * @param sm
 * @param key
 *
 * @return 成功返回压入后的栈顶元素位置，失败返回-1
 */
int stackmin_push(struct stackmin *sm, int key)
{
	if(IS_STACKMIN_FULL(sm))
		return -1;
	int imin = stackmin_min(sm);
	int ipush = stack_push(&sm->d, key);
	if(-1 == imin || key < sm->dd[imin])
	{
		int ret = stack_push(&sm->min, ipush);
		if(-1 == ret)
			return -1;
	}
	return ipush;
}


/**
 * @brief 用朴素算法求栈sm中的最小元素的位置
 *
 * @param sm
 *
 * @return 成功返回sm中的最小元素的位置，失败返回-1
 */
int stackmin_naive_min(struct stackmin *sm)
{
	if(IS_STACKMIN_EMPTY(sm))
		return -1;
	int top = stackmin_top(sm);
	int i, imin = 0;
	for(i = 1; i <= top; i++)
	{
		if(sm->dd[i] < sm->dd[imin])
			imin = i;
	}

	return imin;

}

/**
 * @brief 打印栈sm
 *
 * @param sm
 */
void stackmin_print(struct stackmin *sm)
{
	if(IS_STACKMIN_EMPTY(sm))
		return ;
	int imin = stackmin_min(sm);
	printf("min{}=%d: ", sm->dd[imin]);
	stack_print(&sm->d);
	printf("minstack: ");
	stack_print(&sm->min);
}

/*-------------------------------------------------------------------------------*/

//#define TEST_STACK
#define TEST_STACKMIN
int main()
{

	srand((unsigned int)time((time_t*)NULL));
#ifdef TEST_STACK
	printf("maxint=%d\n", MAXINT);
	struct stack st;
	stack_init(&st, MAX_ITERATOR);
	int i;
	for (i = 0; i < MAX_ITERATOR; i++)
	{
		int key = rand() & 0x07;
		printf("key = %d\n", key);

		if(!IS_STACK_EMPTY(&st) && key < 3)
		{
			int pop = stack_pop(&st);
			printf("pop=%d\n", st.d[pop]);
		}

		stack_push(&st, key);
		stack_print(&st);
	}
	stack_destroy(&st);
#endif//TEST_STACK

#ifdef TEST_STACKMIN
	printf("=====================================================\n");
	struct stackmin stm;
	stackmin_init(&stm, MAX_ITERATOR);
	int j;
	for (j = 0; j < MAX_ITERATOR; j++)
	{
		int key = rand() & 0x0F;
		//printf("key = %d\n", key);

		if(key < 0x08)
		{
			if (!IS_STACKMIN_EMPTY(&stm))
			{
				int pop = stackmin_pop(&stm);
				//printf("pop=%d\n", stm.dd[pop]);
			}
			stackmin_print(&stm);
		}
		else
		{
			stackmin_push(&stm, key);
			stackmin_print(&stm);
		}
		//printf("%d %d\n", stackmin_min(&stm), stackmin_naive_min(&stm));
		assert(stm.dd[stackmin_min(&stm)] == stm.dd[stackmin_naive_min(&stm)]);
	}
	stackmin_destroy(&stm);

#endif//TEST_STACKMIN

	return 0;
}

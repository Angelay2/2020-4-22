#include "stack.h"
#include "queue.h"

//一个队列实现栈
typedef struct {
	Queue _q;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
	MyStack* ms = (MyStack*)malloc(sizeof(MyStack));
	queueInit(&ms->_q);
	return ms;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	queuePush(&obj->_q, x);
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	int sz = QueueSize(&obj->_q);
	while (sz > 1)
	{
		int tmp = queueFront(&obj->_q);
		queuePop(&obj->_q);
		queuePush(&obj->_q, tmp);
		--sz;
	}
	int ret = queueFront(&obj->_q);
	queuePop(&obj->_q);
	return ret;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	return queueBack(&obj->_q);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	if (queueEmpty(&obj->_q))
		return true;
	return false;
}

void myStackFree(MyStack* obj) {
	queueDestory(&obj->_q);
	free(obj);
}


//两个栈实现队列
typedef struct {
	Stack pushSt;
	Stack popSt;
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* mq = (MyQueue*)malloc(sizeof(MyQueue));
	stackInit(&(mq->pushSt), 10);
	stackInit(&(mq->popSt), 10);
	return mq;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	//入队栈进行入队
	stackPush(&obj->pushSt, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	//首先判断出队栈是否为空
	if (stackEmpty(&obj->popSt))
	{
		//把入队栈的元素全部导入出队栈
		while (stackEmpty(&obj->pushSt) != 1)
		{
			int e = stackTop(&obj->pushSt);
			stackPop(&obj->pushSt);
			stackPush(&obj->popSt, e);
		}
	}
	int ret = stackTop(&obj->popSt);
	stackPop(&obj->popSt);
	return ret;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	//首先判断出队栈是否为空
	if (stackEmpty(&obj->popSt))
	{
		//把入队栈的元素全部导入出队栈
		while (stackEmpty(&obj->pushSt) != 1)
		{
			int e = stackTop(&obj->pushSt);
			stackPop(&obj->pushSt);
			stackPush(&obj->popSt, e);
		}
	}
	return stackTop(&obj->popSt);
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	if (stackEmpty(&obj->pushSt) && stackEmpty(&obj->popSt))
		return true;
	return false;
}

void myQueueFree(MyQueue* obj) {
	stackDestory(&obj->pushSt);
	stackDestory(&obj->popSt);
	free(obj);
}

typedef struct {
	int*  _array;
	int _front;
	int _rear;
	int _k;
} MyCircularQueue;

/** Initialize your data structure here. Set the size of the queue to be k. */

MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue* q = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	q->_array = (int*)malloc(sizeof(int)* (k + 1));
	q->_front = q->_rear = 0;
	q->_k = k;
	return q;
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->_front == obj->_rear)
		return true;
	return false;
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
	if ((obj->_rear + 1) % (obj->_k + 1) == obj->_front)
		return true;
	return false;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	//判断队列是否已满
	if (myCircularQueueIsFull(obj))
		return false;
	//队尾插入
	obj->_array[obj->_rear++] = value;
	//判断队尾是否越界
	if (obj->_rear == obj->_k + 1)
		obj->_rear = 0;
	return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	//判断队列是否为空
	if (myCircularQueueIsEmpty(obj))
		return false;
	//队头出队
	++obj->_front;
	//判断队头是否越界
	if (obj->_front == obj->_k + 1)
		obj->_front = 0;
	return true;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))
		return -1;
	return obj->_array[obj->_front];
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
	//返回的是rear的前一个位置
	if (myCircularQueueIsEmpty(obj))
		return -1;
	//如果rear执行起始位置，说明最后一个元素在数组的末尾
	if (obj->_rear == 0)
		return obj->_array[obj->_k];
	return obj->_array[obj->_rear - 1];
}

void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->_array);
	free(obj);
}

//方法二

typedef struct {
	int*  _array;
	int _front;
	int _rear;
	int _size;
	int _k;
} MyCircularQueue;

/** Initialize your data structure here. Set the size of the queue to be k. */

MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue* q = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	q->_array = (int*)malloc(sizeof(int)* (k));
	q->_front = q->_rear = 0;
	q->_k = k;
	q->_size = 0;
	return q;
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->_size == 0)
		return true;
	return false;
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
	if (obj->_size == obj->_k)
		return true;
	return false;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	//判断队列是否已满
	if (myCircularQueueIsFull(obj))
		return false;
	//队尾插入
	obj->_array[obj->_rear++] = value;
	obj->_size++;
	//判断队尾是否越界
	if (obj->_rear == obj->_k)
		obj->_rear = 0;
	return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	//判断队列是否为空
	if (myCircularQueueIsEmpty(obj))
		return false;
	//队头出队
	++obj->_front;
	obj->_size--;
	//判断队头是否越界
	if (obj->_front == obj->_k)
		obj->_front = 0;
	return true;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))
		return -1;
	return obj->_array[obj->_front];
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
	//返回的是rear的前一个位置
	if (myCircularQueueIsEmpty(obj))
		return -1;
	//如果rear执行起始位置，说明最后一个元素在数组的末尾
	if (obj->_rear == 0)
		return obj->_array[obj->_k - 1];
	return obj->_array[obj->_rear - 1];
}

void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->_array);
	free(obj);
}

void testStack()
{
	Stack st;
	stackInit(&st, 10);
	stackPush(&st, 1);
	stackPush(&st, 2);
	stackPush(&st, 3);
	stackPush(&st, 4);
	stackPush(&st, 5);
	while (stackEmpty(&st) != 1)
	{
		printf("%d ", stackTop(&st));
		stackPop(&st);
	}
	printf("\n");
}

void testQueue()
{
	Queue q;
	queueInit(&q);
	queuePush(&q, 1);
	queuePush(&q, 2);
	queuePush(&q, 3);
	queuePush(&q, 4);
	queuePush(&q, 5);

	while (queueEmpty(&q) != 1)
	{
		printf("%d ", queueFront(&q));
		queuePop(&q);
	}
	printf("\n");
}

int main()
{
	testStack();
	testQueue();
	return 0;
}

bool isValid(char * s){
	static char array[][2] = { { '(', ')' }
	, { '{', '}' }
	, { '[', ']' } };
	Stack st;
	stackInit(&st, 10);
	while (*s)
	{
		int i = 0;
		//左括号入栈
		for (; i < 3; ++i)
		{
			if (*s == array[i][0])
			{
				stackPush(&st, *s);
				++s;
				break;
			}
		}

		//右括号
		if (i == 3)
		{
			if (stackEmpty(&st))
				return false;
			char topChar = stackTop(&st);
			stackPop(&st);
			//找到是哪个右括号
			for (int j = 0; j < 3; ++j)
			{
				if (*s == array[j][1])
				{
					if (topChar != array[j][0])
						return false;

					++s;
					break;
				}
			}
		}
	}

	//判断栈是否为空
	if (stackEmpty(&st))
		return true;
	return false;

}
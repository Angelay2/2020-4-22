#include "stack.h"
#include "queue.h"

//һ������ʵ��ջ
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


//����ջʵ�ֶ���
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
	//���ջ�������
	stackPush(&obj->pushSt, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	//�����жϳ���ջ�Ƿ�Ϊ��
	if (stackEmpty(&obj->popSt))
	{
		//�����ջ��Ԫ��ȫ���������ջ
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
	//�����жϳ���ջ�Ƿ�Ϊ��
	if (stackEmpty(&obj->popSt))
	{
		//�����ջ��Ԫ��ȫ���������ջ
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
	//�ж϶����Ƿ�����
	if (myCircularQueueIsFull(obj))
		return false;
	//��β����
	obj->_array[obj->_rear++] = value;
	//�ж϶�β�Ƿ�Խ��
	if (obj->_rear == obj->_k + 1)
		obj->_rear = 0;
	return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	//�ж϶����Ƿ�Ϊ��
	if (myCircularQueueIsEmpty(obj))
		return false;
	//��ͷ����
	++obj->_front;
	//�ж϶�ͷ�Ƿ�Խ��
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
	//���ص���rear��ǰһ��λ��
	if (myCircularQueueIsEmpty(obj))
		return -1;
	//���rearִ����ʼλ�ã�˵�����һ��Ԫ���������ĩβ
	if (obj->_rear == 0)
		return obj->_array[obj->_k];
	return obj->_array[obj->_rear - 1];
}

void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->_array);
	free(obj);
}

//������

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
	//�ж϶����Ƿ�����
	if (myCircularQueueIsFull(obj))
		return false;
	//��β����
	obj->_array[obj->_rear++] = value;
	obj->_size++;
	//�ж϶�β�Ƿ�Խ��
	if (obj->_rear == obj->_k)
		obj->_rear = 0;
	return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	//�ж϶����Ƿ�Ϊ��
	if (myCircularQueueIsEmpty(obj))
		return false;
	//��ͷ����
	++obj->_front;
	obj->_size--;
	//�ж϶�ͷ�Ƿ�Խ��
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
	//���ص���rear��ǰһ��λ��
	if (myCircularQueueIsEmpty(obj))
		return -1;
	//���rearִ����ʼλ�ã�˵�����һ��Ԫ���������ĩβ
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
		//��������ջ
		for (; i < 3; ++i)
		{
			if (*s == array[i][0])
			{
				stackPush(&st, *s);
				++s;
				break;
			}
		}

		//������
		if (i == 3)
		{
			if (stackEmpty(&st))
				return false;
			char topChar = stackTop(&st);
			stackPop(&st);
			//�ҵ����ĸ�������
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

	//�ж�ջ�Ƿ�Ϊ��
	if (stackEmpty(&st))
		return true;
	return false;

}
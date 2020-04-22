#pragma  once

//带有尾指针的单链表实现队列
#include <stdio.h>
typedef int QDataType;
typedef struct QNode
{
	struct QNode* _next;
	QDataType _data;
} QNode;

typedef struct Queue
{
	//头尾指针
	QNode* _front;
	QNode* _rear;
	size_t _size;
}Queue;

void queueInit(Queue* q);

void queuePush(Queue* q, QDataType data);

void queuePop(Queue* q);

QDataType queueFront(Queue* q);

QDataType queueBack(Queue* q);

int queueEmpty(Queue* q);

size_t QueueSize(Queue* q);

void queueDestory(Queue* q);
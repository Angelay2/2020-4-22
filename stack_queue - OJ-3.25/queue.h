#pragma  once
//����βָ��ĵ�����ʵ�ֶ���
#include <stdio.h>
typedef int DataType;
typedef struct Node
{
	struct Node* _next;
	DataType _data;
} Node;

typedef struct Queue
{
	//ͷβָ��
	Node* _front;
	Node* _rear;
	size_t _size;
}Queue;

void queueInit(Queue* q);

void queuePush(Queue* q, DataType data);

void queuePop(Queue* q);

DataType queueFront(Queue* q);

DataType queueBack(Queue* q);

int queueEmpty(Queue* q);

size_t QueueSize(Queue* q);

void queueDestory(Queue* q);
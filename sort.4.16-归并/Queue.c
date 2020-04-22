#include "queue.h"
#include <stdlib.h>

void queueInit(Queue* q){
	//空队列
	q->_front = q->_rear = NULL;
	q->_size = 0;
}

void queuePush(Queue* q, QDataType data)
{
	//创建节点
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->_data = data;
	node->_next = NULL;
	//尾插
	//如果是空队列
	if (q->_front == NULL)
	{
		q->_front = q->_rear = node;
	}
	else
		q->_rear->_next = node;

	//更新尾结点
	q->_rear = node;
	++q->_size;
}

void queuePop(Queue* q)
{
	if (q->_front != NULL)
	{
		QNode* next = q->_front->_next;
		//删除头结点
		free(q->_front);
		//跟新头结点
		q->_front = next;
		if (q->_front == NULL)
			q->_rear = NULL;

		--q->_size;
	}
}

QDataType queueFront(Queue* q)
{
	return q->_front->_data;
}

QDataType queueBack(Queue* q)
{
	return q->_rear->_data;
}

int queueEmpty(Queue* q)
{
	// if(q->_size == 0)
	if (q->_front == NULL)
		return 1;
	return 0;
}

size_t QueueSize(Queue* q)
{
	return q->_size;
}

void queueDestory(Queue* q)
{
	QNode* cur = q->_front;
	while (cur)
	{
		QNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	q->_rear = q->_front = NULL;
	q->_size = 0;
}
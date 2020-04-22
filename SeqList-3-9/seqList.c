#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
typedef int DataType;

// ��̬˳���(���ݵĴ����е��)
// ���ܿ��˺ܶ�Ŀռ� ����û���� 
// ����β���βɾO(1) ������ʱ�临�Ӷ�ΪO(N) ���Բ������ܺ�ɾ�����ܲ����Ǻܸ�
// ������Ҫ�Ӻ���ǰ�ƶ� 
// ɾ��Ԫ��ֻ���ú�������ݸ���ǰ������� (��ǰ�����ƶ�) Ϊ�˷�ֹ���ݱ�����

typedef struct seqList
{
	//��̬���ٿռ䣺 ���ϵĿռ�  ---> ָ�� malloc()
	DataType* _data;
	//size: ˳���ǰ��ŵ�Ԫ�ظ���
	// typedef unsigned int  size_t
	size_t _size;
	//capacity: ˳�����Դ�ŵ����Ԫ�ظ���
	size_t _capacity;
} seqList;

void printSeqList(seqList* sq)
{
	for (size_t i = 0; i < sq->_size; ++i)
	{
		printf("%d ", sq->_data[i]);
	}
	printf("\n");
}

void seqInit(seqList* sq)
{
	//�յ�˳���
	sq->_data = NULL;
	sq->_capacity = 0;
	sq->_size = 0;
}

void checkCapacity(seqList* sq)
{
	if (sq->_size == sq->_capacity)
	{
		//˳����Ѿ����ˣ����ݣ� 1. ���¿ռ䣬 2. ����ԭ�пռ����ݣ� 3. �ͷ�ԭ�пռ�
		size_t newCapacity = sq->_size == 0 ? 4 : 2 * sq->_capacity;
		/*
		// malloc, memcpy, free
		DataType* newData = (DataType*)malloc(newCapacity * sizeof(DataType));
		memcpy(newData, sq->_data, sq->_size * sizeof(DataType));
		DataType* tmp = sq->_data;
		free(sq->_data);
		sq->_data = newData;
		//free(tmp);
		*/
		// realloc
		sq->_data = (DataType*) realloc(sq->_data, newCapacity * sizeof(DataType));
		sq->_capacity = newCapacity;
	}
}

//����λ�ò���Ԫ��
void seqInsert(seqList* sq, size_t position, DataType value)
{
	//��֤�����λ������ȷ�� [0, size]
	assert(position <= sq->_size);
	checkCapacity(sq);

	//Ԫ���ƶ�
	for (int i = sq->_size; i > position; --i)
	{
		sq->_data[i] = sq->_data[i - 1];   // size - 1, position
	}
	//����
	sq->_data[position] = value;
	++sq->_size;
}

//�����ӿڣ� ��ɾ���
//����ӿ�
//ͷ��
void seqPushFront(seqList* sq, DataType value)
{
	/*
	checkCapacity(sq);
	*/
	// �ƶ�Ԫ�أ�����Ԫ��ȫ������ƶ�һ��λ��
	
	/*
	// ��ǰ���Ų�����������ݻᱻ����
	for (int i = 0; i < sq->_size; ++i)
	{
		sq->_data[i + 1] = sq->_data[i];
	}
	*/
	/*
	// �Ӻ���ǰŲ��: ע�� ����д�� i >= 0 : ��ѭ���� ����Խ�磬 �Ǹ���������С��0
	for (size_t i = sq->_size; i > 0; --i)
	{
		sq->_data[i] = sq->_data[i - 1];
	}
	// ����
	sq->_data[0] = value;
	++sq->_size;
	*/
	seqInsert(sq, 0, value);
}

//β��
void seqPushBack(seqList* sq, DataType value)
{
	/*
	//�������
	checkCapacity(sq);
	//����
	sq->_data[sq->_size] = value;
	//���µ�ǰ˳�����Ԫ�صĸ���
	sq->_size++;
	*/
	//β��
	seqInsert(sq, sq->_size, value);
}


//ɾ��
void seqErase(seqList* sq, size_t position)
{
	if (position >= sq->_size)
		return;

	//assert(position < sq->_size);  // assertֻ��debug

	//�ƶ�Ԫ�أ� ע��Ԫ�ظ�������---> ��ǰ����ƶ�, βɾ
	for (size_t i = position + 1; i < sq->_size; ++i)
	{
		sq->_data[i - 1] = sq->_data[i];  // position + 1 ---> position,  size-1 ---> size-2
	}
	--sq->_size;
}
//ͷɾ
void seqPopFront(seqList* sq)
{
	seqErase(sq, 0);
}
//βɾ
void seqPopBack(seqList* sq)
{
	seqErase(sq, sq->_size - 1);
}

//����
size_t seqFind(seqList* sq, DataType value)
{
	for (size_t i = 0; i < sq->_size; ++i)
	{
		if (sq->_data[i] == value)
			return i;
	}
	return -1;
}

void test1()
{
	seqList sq;
	seqInit(&sq);
	seqPushBack(&sq, 0);
	seqPushBack(&sq, 1);
	printSeqList(&sq);
	seqPopFront(&sq);
	printSeqList(&sq);
	seqPushBack(&sq, 2);
	seqPushBack(&sq, 3);
	seqPushBack(&sq, 4);
	seqPopBack(&sq);
	
	//seqInsert(&sq, 2, 100);
	printSeqList(&sq);  // 0 1 2 3 4
	seqPushFront(&sq, -1);
	printSeqList(&sq);
	printf("Erase: \n");
	seqErase(&sq, 3);
	printSeqList(&sq);
	seqErase(&sq, 2);
	printSeqList(&sq);
	seqErase(&sq, 3);
	printSeqList(&sq);
	seqErase(&sq, 0);
	printSeqList(&sq);
	seqErase(&sq, 0);
	printSeqList(&sq);
	seqErase(&sq, 0);
	printSeqList(&sq);
	seqErase(&sq, 0);
	printSeqList(&sq);
	/*
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);
	seqPushBack(&sq, 4);*/
	/*for (int i = 0; i < 10000; i++)
	{
		seqPushBack(&sq, i);
	}
	printf("pushBack finish!\n");*/
}

void test2()
{
	seqList sq;
	seqInit(&sq);
	seqPushBack(&sq, 0);
	seqPushBack(&sq, 1);
	seqPushBack(&sq, 2);
	seqPushBack(&sq, 3);
	seqPushBack(&sq, 4);
	printSeqList(&sq);
	printf("%u \n", seqFind(&sq, 3));
	printf("%u \n", seqFind(&sq, 0));
	printf("%u \n", seqFind(&sq, 100));
}

int main()
{
	//test1();
	test2();

	return 0;
}


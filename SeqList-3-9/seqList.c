#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
typedef int DataType;

// 动态顺序表(增容的代价有点大)
// 可能开了很多的空间 但并没有用 
// 除过尾插和尾删O(1) 其他的时间复杂度为O(N) 所以插入性能和删除性能并不是很高
// 插入需要从后往前移动 
// 删除元素只是用后面的数据覆盖前面的数据 (从前往后移动) 为了防止数据被覆盖

typedef struct seqList
{
	//动态开辟空间： 堆上的空间  ---> 指针 malloc()
	DataType* _data;
	//size: 顺序表当前存放的元素个数
	// typedef unsigned int  size_t
	size_t _size;
	//capacity: 顺序表可以存放的最大元素个数
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
	//空的顺序表
	sq->_data = NULL;
	sq->_capacity = 0;
	sq->_size = 0;
}

void checkCapacity(seqList* sq)
{
	if (sq->_size == sq->_capacity)
	{
		//顺序表已经满了，增容： 1. 开新空间， 2. 拷贝原有空间内容， 3. 释放原有空间
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

//任意位置插入元素
void seqInsert(seqList* sq, size_t position, DataType value)
{
	//保证插入的位置是正确的 [0, size]
	assert(position <= sq->_size);
	checkCapacity(sq);

	//元素移动
	for (int i = sq->_size; i > position; --i)
	{
		sq->_data[i] = sq->_data[i - 1];   // size - 1, position
	}
	//插入
	sq->_data[position] = value;
	++sq->_size;
}

//操作接口： 增删查改
//插入接口
//头插
void seqPushFront(seqList* sq, DataType value)
{
	/*
	checkCapacity(sq);
	*/
	// 移动元素：所有元素全部向后移动一个位置
	
	/*
	// 从前向后挪动：错误，数据会被覆盖
	for (int i = 0; i < sq->_size; ++i)
	{
		sq->_data[i + 1] = sq->_data[i];
	}
	*/
	/*
	// 从后向前挪动: 注意 不能写成 i >= 0 : 死循环， 访问越界， 非负数不可能小于0
	for (size_t i = sq->_size; i > 0; --i)
	{
		sq->_data[i] = sq->_data[i - 1];
	}
	// 插入
	sq->_data[0] = value;
	++sq->_size;
	*/
	seqInsert(sq, 0, value);
}

//尾插
void seqPushBack(seqList* sq, DataType value)
{
	/*
	//检查容量
	checkCapacity(sq);
	//插入
	sq->_data[sq->_size] = value;
	//更新当前顺序表中元素的个数
	sq->_size++;
	*/
	//尾插
	seqInsert(sq, sq->_size, value);
}


//删除
void seqErase(seqList* sq, size_t position)
{
	if (position >= sq->_size)
		return;

	//assert(position < sq->_size);  // assert只在debug

	//移动元素： 注意元素覆盖问题---> 从前向后移动, 尾删
	for (size_t i = position + 1; i < sq->_size; ++i)
	{
		sq->_data[i - 1] = sq->_data[i];  // position + 1 ---> position,  size-1 ---> size-2
	}
	--sq->_size;
}
//头删
void seqPopFront(seqList* sq)
{
	seqErase(sq, 0);
}
//尾删
void seqPopBack(seqList* sq)
{
	seqErase(sq, sq->_size - 1);
}

//查找
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


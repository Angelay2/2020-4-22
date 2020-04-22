#include "stack.h"


void stackInit(Stack* st, size_t n)
{
	st->_array = (DataType*)malloc(sizeof(DataType)* n);
	st->_size = 0;
	st->_capacity = n;
}



void stackPush(Stack* st, DataType data)
{
	//¼ì²éÈÝÁ¿
	if (st->_size == st->_capacity)
	{
		st->_array = (DataType*)realloc(st->_array, sizeof(DataType)* 2 * st->_capacity);
		st->_capacity *= 2;
	}

	//Î²²å
	st->_array[st->_size++] = data;
}

void stackPop(Stack* st)
{
	if (st->_size > 0)
	{
		--st->_size;
	}
}

DataType stackTop(Stack* st)
{
	return st->_array[st->_size - 1];
}

size_t stackSize(Stack* st)
{
	return st->_size;
}

int stackEmpty(Stack* st)
{
	if (st->_size == 0)
		return 1;
	return 0;
}

void stackDestory(Stack* st)
{
	if (st->_array)
	{
		free(st->_array);
		st->_size = st->_capacity = 0;
	}
}
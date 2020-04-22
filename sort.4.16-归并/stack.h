#pragma once
#include <stdio.h>
#include <stdlib.h>
//À≥–Ú±Ì µœ÷’ª

typedef int DataType;

typedef struct Stack
{
	DataType* _array;
	size_t _size;
	size_t _capacity;
}Stack;

void stackInit(Stack* st, size_t n);

void stackPush(Stack* st, DataType data);

void stackPop(Stack* st);

DataType stackTop(Stack* st);

size_t stackSize(Stack* st);

int stackEmpty(Stack* st);

void stackDestory(Stack* st);





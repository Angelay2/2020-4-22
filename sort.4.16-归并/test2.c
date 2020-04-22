#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sort.h"
void printArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void test1()
{
	int array[] = { 10, -1, 2, 9, 3, 4, 5, 6, 7, 10, 3 };
	int num = sizeof(array) / sizeof(array[0]);
	int* copy = (int*)malloc(num * sizeof(int));
	int* copy2 = (int*)malloc(num * sizeof(int));
	int* copy3 = (int*)malloc(num * sizeof(int));
	int* copy4 = (int*)malloc(num * sizeof(int));
	int* copy5 = (int*)malloc(num * sizeof(int));
	int* copy6 = (int*)malloc(num * sizeof(int));
	int* copy7 = (int*)malloc(num * sizeof(int));
	int* copy8 = (int*)malloc(num * sizeof(int));
	int* copy9 = (int*)malloc(num * sizeof(int));
	int* copy10 = (int*)malloc(num * sizeof(int));
	int* copy11 = (int*)malloc(num * sizeof(int));

	memcpy(copy, array, sizeof(int)* num);
	memcpy(copy2, array, sizeof(int)* num);
	memcpy(copy3, array, sizeof(int)* num);
	memcpy(copy4, array, sizeof(int)* num);
	memcpy(copy5, array, sizeof(int)* num);
	memcpy(copy6, array, sizeof(int)* num);
	memcpy(copy7, array, sizeof(int)* num);
	memcpy(copy8, array, sizeof(int)* num);
	memcpy(copy9, array, sizeof(int)* num);
	memcpy(copy10, array, sizeof(int)* num);
	memcpy(copy11, array, sizeof(int)* num);

	printArray(array, num);
	insertSort(array, num);
	printArray(array, num);

	printArray(copy, num);
	shellSort(copy, num);
	printArray(copy, num);

	printArray(copy2, num);
	selectSort(copy2, num);
	printArray(copy2, num);

	printArray(copy3, num);
	selectSort2(copy3, num);
	printArray(copy3, num);

	printArray(copy4, num);
	heapSort(copy4, num);
	printArray(copy4, num);

	printArray(copy5, num);
	bubbleSort(copy5, num);
	printArray(copy5, num);

	printf("quickSort:\n");
	printArray(copy6, num);
	quickSort(copy6, 0, num - 1);
	printArray(copy6, num);

	printf("quickSortNoR:\n");
	printArray(copy7, num);
	quickSortNoR(copy7, num);
	printArray(copy7, num);

	printf("quickSortNoR2:\n");
	printArray(copy8, num);
	quickSortNoR2(copy8, num);
	printArray(copy8, num);

	printf("mergeSort:\n");
	printArray(copy9, num);
	mergeSort(copy9, num);
	printArray(copy9, num);

	printf("mergeSortNoR:\n");
	printArray(copy10, num);
	mergeSortNoR(copy10, num);
	printArray(copy10, num);

	printf("countSort:\n");
	printArray(copy11, num);
	countSort(copy11, num);
	printArray(copy11, num);


}

void testTime()
{
	int n;
	int* array, *copy, *copy2;
	scanf("%d", &n);
	array = (int*)malloc(sizeof(int)* n);
	copy = (int*)malloc(sizeof(int)* n);
	copy2 = (int*)malloc(sizeof(int)* n);
	int *copy3 = (int*)malloc(sizeof(int)* n);
	int *copy4 = (int*)malloc(sizeof(int)* n);
	int *copy5 = (int*)malloc(sizeof(int)* n);
	int *copy6 = (int*)malloc(sizeof(int)* n);
	int *copy7 = (int*)malloc(sizeof(int)* n);

	srand(time(NULL));
	for (int i = 0; i < n; ++i)
	{
		array[i] = rand();
	}
	
	memcpy(copy, array, sizeof(int)* n);
	memcpy(copy2, array, sizeof(int)* n);
	memcpy(copy3, array, sizeof(int)* n);
	memcpy(copy4, array, sizeof(int)* n);
	memcpy(copy5, array, sizeof(int)* n);
	memcpy(copy6, array, sizeof(int)* n);
	memcpy(copy7, array, sizeof(int)* n);
	
	size_t  begin = clock();
	insertSort(array, n);
	size_t  end = clock();
	printf("insertSort: %d\n", end - begin);
	/*
	begin = clock();
	insertSort(array, n);
	end = clock();
	printf("%d\n", end - begin);
	*/
	begin = clock();
	shellSort(copy, n);
	end = clock();
	printf("shellSort: %d\n", end - begin);

	begin = clock();
	selectSort(copy2, n);
	end = clock();
	printf("selectSort: %d\n", end - begin);

	begin = clock();
	selectSort(copy2, n);
	end = clock();
	printf("sorted selectSort: %d\n", end - begin);

	begin = clock();
	selectSort2(copy3, n);
	end = clock();
	printf("selectSort2: %d\n", end - begin);

	begin = clock();
	heapSort(copy4, n);
	end = clock();
	printf("heapSort: %d\n", end - begin);

	begin = clock();
	heapSort(copy4, n);
	end = clock();
	printf("Sorted heapSort: %d\n", end - begin);
	
	/*begin = clock();
	bubbleSort(copy5, n);
	end = clock();
	printf("bubbleSort: %d\n", end - begin);

	begin = clock();
	bubbleSort(copy5, n);
	end = clock();
	printf("Sorted bubbleSort: %d\n", end - begin);*/

	begin = clock();
	quickSort(copy6, 0, n - 1);
	end = clock();
	printf("quickSort: %d\n", end - begin);

	begin = clock();
	quickSort(copy6, 0, n - 1);
	end = clock();
	printf("Sorted quickSort: %d\n", end - begin);

	begin = clock();
	quickSortNoR(copy6, n);
	end = clock();
	printf("Sorted quickSortNoR: %d\n", end - begin);

	begin = clock();
	quickSortNoR2(copy6, n);
	end = clock();
	printf("Sorted quickSortNoR2: %d\n", end - begin);

	begin = clock();
	mergeSort(copy7, n);
	end = clock();
	printf("mergeSort: %d\n", end - begin);

	begin = clock();
	mergeSort(copy7, n);
	end = clock();
	printf("sorted mergeSort: %d\n", end - begin);
}
int main()
{
	test1();
	//testTime();
	return 0;
}
#include "sort.h"
#include "stack.h"
#include "queue.h"
#include <memory.h>
#include <stdlib.h>
void swap(int* array, int i, int j)
{
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}


/*
时间复杂度：最坏O(n^2)  平均O(n^2)  最好O(n): 数据本身有序
空间复杂度：O(1)
稳定性: 稳定
数据敏感：敏感
*/
void insertSort(int* array, int n)
{
	//i: 有序序列的最后一个位置
	for (int i = 0; i < n - 1; ++i)
	{
		int end = i;
		int key = array[end + 1];
		//从后向前找一个合适的位置，进行插入
		while (end >= 0 && array[end] > key)
		{
			array[end + 1] = array[end];
			--end;
		}
		//array[end] < key:  key放在end的下一个位置
		//插入
		array[end + 1] = key;
	}
}
/*
时间复杂度：平均O(n^1.3)  最好O(n): 数据本身有序
空间复杂度：O(1)
稳定性: 不稳定  ---> 预排序会破坏稳定性： 数据可能会分到不同的组
数据敏感：敏感
*/
void shellSort(int* array, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		// gap > 1:  预排序
		for (int i = 0; i < n - gap; ++i)
		{
			int end = i;
			int key = array[end + gap];
			while (end >= 0 && array[end] > key)
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}

}

void selectSort(int* array, int n)
{
	//i： 未排序的元素个数
	for (int i = n; i > 0; --i)
	{
		//每次选一个最小的值，存入未排序数据的起始位置
		int start = n - i;
		int min = start;
		for (int j = start; j < n; ++j)
		{
			if (array[j] < array[min])
				min = j;
		}
		swap(array, start, min);
	}
}


/*
时间复杂度：最坏 O(n^2)  平均 O(n^2)  最好  O(n^2)
空间复杂度：O(1)
稳定性: 稳定
数据敏感：不敏感
*/
void selectSort2(int* array, int n)
{
	int begin = 0;
	int end = n - 1;
	int min, max;
	while (begin < end)
	{
		//每次找一个最大值和最小值所在的位置
		min = max = begin;
		for (int j = begin + 1; j <= end; ++j)
		{
			if (array[j] >= array[max])
				max = j;
			if (array[j] < array[min])
				min = j;
		}
		//最小值和起始位置交换
		swap(array, begin, min);
		//最大值和结束位置交换, 如果最大值的位置在begin处， 此时需要更新
		if (max == begin)
			max = min;
		swap(array, end, max);

		++begin;
		--end;
	}
}

void shiftDown(int* array, int n, int parent)
{
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n && array[child + 1] > array[child])
			++child;
		if (array[child] > array[parent])
		{
			swap(array, child, parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}

/*
时间复杂度：最坏O(nlogn)  平均O(nlogn)   最好O(nlogn)  
空间复杂度：O(1)
稳定性: 不稳定 ---> 向下调整可能会破坏相对位置
数据敏感：不敏感
*/
//升序
void heapSort(int* array, int n)
{
	int end = n - 1;
	//建大堆
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		shiftDown(array, n, i);
	}
	//循环执行： swap, shiftDown
	while (end > 0)
	{
		swap(array, 0, end);
		//给剩余元素向下调整
		shiftDown(array, end, 0);
		--end;
	}
}

/*
时间复杂度：最坏O(n^2)  平均O(n^2)   最好O(n)
空间复杂度：O(1)
稳定性: 稳定 
数据敏感：敏感
*/
void bubbleSort(int* array, int n)
{
	int end = n;
	while (end > 0)
	{
		//一趟排序
		// flag: 一趟排序中是否发生了交换操作
		int flag = 1;
		for (int i = 1; i < end; ++i)
		//for (int i = 0; i < end - 1; ++i) : array[i] > array[i + 1]
		{
			//大的向后移动， 相等的元素不会交换，相等位置不会改变
			if (array[i - 1] > array[i])
			{
				flag = 0;
				swap(array, i - 1, i);
			}
		}
		//如果没有发生交换，说明序列元素之间就是一个递增的关系，已有序
		if (flag)
			break;

		--end;
	}
}
//三数取中
int getMid(int* array, int left, int right)
{
	int mid = left + (right - left) / 2;
	//从 array[left], array[mid], array[right]选一个中间值的位置
	if (array[mid] > array[left])
	{
		if (array[mid] < array[right])   // left mid right
			return mid;
		else
		{
			// mid > left   mid >= right    
			if (array[left] > array[right])   //  right  left   mid
				return left;
			else
				return right;  //  left  right  mid
		}
	}
	else
	{
		// mid <= left
		if (array[mid] > array[right])  // right  mid  left
			return mid;
		else
		{
			//mid <= right   mid <= left
			if (array[left] < array[right])   // mid  left  right
				return left;
			else
				return right;  // mid  right  left  
		}

	}
}

int partion(int* array, int begin, int end)
{
	//第一个数据作为基准值
	int key = array[begin];
	int start = begin;
	while (begin < end)
	{
		//从后向前找小
		while (begin < end && array[end] >= key)
			--end;
		//从前向后找大
		while (begin < end && array[begin] <= key)
			++begin;
		//可能找到了两个数据， 交换
		swap(array, begin, end);
	}
	//交换基准值和相遇位置的值
	swap(array, start, begin);
	//返回基准值位置
	return begin;
}

//挖坑法
int partion2(int* array, int begin, int end)
{
	int key = array[begin];
	while (begin < end)
	{
		//从后向前找小
		while (begin < end && array[end] >= key)
			--end;
		//填begin位置的坑
		array[begin] = array[end];
		while (begin < end && array[begin] <= key)
			++begin;
		//填end坑
		array[end] = array[begin];
	}
	//key 放入相遇的位置： 最后一个坑
	array[begin] = key;
	return begin;
}

//前后指针法
int partion3(int* array, int begin, int end)
{
	int mid = getMid(array, begin, end);
	swap(array, mid, begin);
	//prev: 最后一个小于key的位置
	int prev = begin;
	//cur: 下一个小于key的位置
	int cur = begin + 1;
	int key = array[begin];
	while (cur <= end)
	{
		// 如果下一个小于key的位置与最后一个小于key的位置不连续，
		// 说明cur, prev中间是有大于key的值, 则需要大小元素进行交换
		if (array[cur] < key && ++prev != cur)
			swap(array, cur, prev);
		++cur;
	}
	swap(array, begin, prev);
	return prev;
}

/*
    时间复杂度：最好: nlogn  平均  nlogn   最坏： n^2  (数据有序, 一般会进行优化，比如三数取中法， 最坏不会发生）
	空间复杂度： logn
	稳定性：不稳定  --> 划分是，数据会发生交换，可能会导致相对位置发生变化
	数据敏感： 敏感
*/

void quickSort(int* array, int begin, int end)
{
	if (begin >= end)
		return;
	//小区间优化，减少底层递归的调用
	if (end - begin + 1 < 10)
	{
		shellSort(array + begin, end - begin + 1);
	}
	else
	{
		int mid = partion3(array, begin, end);
		//划分小区间
		quickSort(array, begin, mid - 1);
		quickSort(array, mid + 1, end);
	} 
	
}

// 非递归： 记录每一个确定的起始和结束位置，
//         然后按照先划分大区间，再划分小区间的顺序完成所有区间的划分， 即可完成排序
// 1. 用栈保存区间的起始和结束位置

void quickSortNoR(int* array, int n)
{
	Stack st;
	stackInit(&st, 10);
	//首先保存大区间
	if (n > 0)
	{
		stackPush(&st, n - 1);
		stackPush(&st, 0);
	}
	//给所有区间进行划分
	while (stackEmpty(&st) != 1)
	{
			//还有区间没有划分
			//取出一个区间的起始和结束位置
			int left = stackTop(&st);
			stackPop(&st);
			int right = stackTop(&st);
			stackPop(&st);
			//划分当前区间
			int div = partion3(array, left, right);
			//保存子区间的起始和结束位置
			if (left < div - 1)
			{
				stackPush(&st, div - 1);
				stackPush(&st, left);
			}
			if (div + 1 < right)
			{
				stackPush(&st, right);
				stackPush(&st, div + 1);
			}
	}
	
}

// 快排非递归
// 用队列保存区间的起始和结束位置
void quickSortNoR2(int* array, int n)
{
	//初始化队列
	Queue q;
	queueInit(&q);
	if (n > 1)
	{
		//存放顺序： 先左后右
		queuePush(&q, 0);
		queuePush(&q, n - 1);
	}
	while (queueEmpty(&q) != 1)
	{
		//从队头获取区间信息
		int left = queueFront(&q);
		queuePop(&q);
		int right = queueFront(&q);
		queuePop(&q);

		//划分
		int div = partion3(array, left, right);
		//划分之后的区间入队
		if (left < div - 1)
		{
			queuePush(&q, left);
			queuePush(&q, div - 1);
		}
		if (div + 1 < right)
		{
			queuePush(&q, div + 1);
			queuePush(&q, right);
		}
	}
}


void mergeInternal(int* array, int left, int mid, int right, int* tmp)
{
	//有序子区间归并: [left, mid]  和  [mid + 1, right]
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int idx = left;
	//归并
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (array[begin1] <= array[begin2])
			tmp[idx++] = array[begin1++];
		else
			tmp[idx++] = array[begin2++];
	}
	//保存剩余元素
	if (begin1 <= end1)
		memcpy(tmp + idx, array + begin1, sizeof(int)* (end1 - begin1 + 1));
	if (begin2 <= end2)
		memcpy(tmp + idx, array + begin2, sizeof(int)* (end2 - begin2 + 1));
	//当前区间已有有序，把辅助空间对应位置的元素拷回去
	memcpy(array + left, tmp + left, sizeof(int)* (right - left + 1));
}

void merge(int* array, int left, int right, int* tmp)
{
	//区间只有一个元素，不需要分解，不需要归并
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	
	//1.分解
	//首先进行子区间的归并排序
	// [left, mid]
	merge(array, left, mid, tmp);
	// [mid + 1, right]
	merge(array, mid + 1, right, tmp);
	
	//2.合并
	// 前提： [left, mid], [mid + 1, right]有序
	//归并： [left, mid], [mid + 1, right]
	mergeInternal(array, left, mid, right, tmp);
}

/*
  时间复杂度： 最坏 nlogn   平均nlog   最好 nlogn
  空间复杂度： n   借助辅助空间
  稳定性：稳定
  敏感： 不敏感
*/

void mergeSort(int* array, int n)
{
	//辅助空间
	int* tmp = (int*)malloc(sizeof(int)* n);
	merge(array, 0, n - 1, tmp);
	free(tmp);
}

void mergeSortNoR(int* array, int n)
{
	//num: 每次待归并的子区间元素个数
	int num = 1;
	int* tmp = (int*)malloc(sizeof(int)* n);
	while (num < n)
	{
		//每次都要把整个区间的元素进行归并
		for (int i = 0; i < n; i += 2 * num)
		{
			//第一个区间 [left, mid], 第二个区间 [mid + 1, right]
			int left = i;
			int mid = i + num - 1;

			if (mid >= n - 1)
				//没有第二个区间, 不需要归并, 剩余的一个区间不要归并
				continue;

			int right = i + 2 * num - 1;
			//判断第二个区间的结束位置是否越界
			if (right >= n)
				right = n - 1;

			mergeInternal(array, left, mid, right, tmp);
		}
		num *= 2;
	}
	free(tmp);
}

/*
时间复杂度： max(n, range)
空间复杂度： range
稳定性：稳定
敏感： 不敏感
只适合小范围的数据
*/
void countSort(int* array, int n)
{
	//找到最大值和最小值
	int max = array[0], min = array[0];
	int range;
	int* countArr;
	int idx = 0;
	for (int i = 1; i < n; ++i)
	{
		if (array[i] < min)
			min = array[i];
		if (array[i] > max)
			max = array[i];
	}
	//数据范围
	range = max - min + 1;
	countArr = (int*)malloc(sizeof(int)* range);
	// countArr = (int*)calloc(sizeof(int)* range);  calloc: 完成空间申请和0的初始化
	memset(countArr, 0, sizeof(int)* range);
	//记录每一个数据出现的次数
	for (int i = 0; i < n; ++i)
	{
		countArr[array[i] - min]++;
	}
	//遍历计数数组
	for (int i = 0; i < range; ++i)
	{
		//有可能有重复数据
		while (countArr[i]--)
		{
			array[idx++] = i + min;
		}
	}
}



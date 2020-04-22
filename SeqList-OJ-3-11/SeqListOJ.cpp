int removeElement(int* nums, int numsSize, int val){
	int i = 0;
	int pos = 0;
	for (i = 0; i < numsSize; i++)
	{
		if (nums[i] != val)
		{
			//i++; 会跳过一个元素
			nums[pos] = nums[i];
			pos++;
		}

	}
	return pos;
}

int removeDuplicates(int* nums, int numsSize){
	int idx = 0;
	int i = 0;
	int j = 1;
	while (j < numsSize)
	{
		nums[idx++] = nums[i];
		if (nums[i] != nums[j])
		{
			++i;
			++j;
		}
		else{
			//找第一个不相同的位置
			while (j < numsSize && nums[i] == nums[j])
				++j;
			i = j;
			++j;
		}
	}
	//保存最后一个值
	if (i < numsSize)
		nums[idx++] = nums[i];

	return idx;

}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
	int total = m + n;
	//开一个新的数组
	int* ret = (int*)malloc(sizeof(int)* total);
	//同时遍历两个数组
	int n1 = 0;
	int n2 = 0;
	int idx = 0;
	while (n1 < m && n2 < n)
	{
		//选小的数据进行存放
		if (nums1[n1] <= nums2[n2])
		{
			ret[idx++] = nums1[n1++];
		}
		else
		{
			ret[idx++] = nums2[n2++];
		}
	}
	//有可能还有未合并的数据
	if (n1 < m)
	{
		memcpy(ret + idx, nums1 + n1, sizeof(int)* (m - n1));
	}
	if (n2 < n)
	{
		memcpy(ret + idx, nums2 + n2, sizeof(int)* (n - n2));
	}
	//把ret数组的数据拷贝到nums1中
	memcpy(nums1, ret, total * sizeof(int));
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
	int pos = m + n - 1;
	int n1 = m - 1;
	int n2 = n - 1;
	//从后向前先合并大元素
	while (n1 >= 0 && n2 >= 0)
	{
		if (nums1[n1] >= nums2[n2])
		{
			nums1[pos--] = nums1[n1--];
		}
		else
		{
			nums1[pos--] = nums2[n2--];
		}
	}
	//检查第二个数组是否还有剩余元素
	if (n2 >= 0)
	{
		memcpy(nums1, nums2, (n2 + 1) * sizeof(int));
	}
}

void reverse(int* ret, int left, int right)
{
	while (left < right)
	{
		int tmp = ret[left];
		ret[left] = ret[right];
		ret[right] = tmp;
		++left;
		--right;
	}
}
int* addToArrayForm(int* A, int ASize, int K, int* returnSize){

	//新开空间， 保存结果
	//获取两数的最大长度
	int klen = 0;
	int tmp = K;
	while (tmp)
	{
		++klen;
		tmp /= 10;
	}
	//考虑进位的存放
	int retSize = ASize > klen ? ASize + 1 : klen + 1;
	int* ret = (int*)malloc(sizeof(int)* retSize);

	int len = ASize - 1;
	int step = 0;
	int idx = 0;
	while (len >= 0 || K > 0)
	{
		//当前对应位的结果,首先加上一步的进位
		ret[idx] = step;
		//逐位相加
		if (len >= 0)
		{
			ret[idx] += A[len];
		}
		if (K > 0)
		{
			ret[idx] += K % 10;
		}
		//更新结果
		if (ret[idx] > 9)
		{
			ret[idx] %= 10;
			step = 1;
		}
		else
		{
			step = 0;
		}
		//保存当前位的结果

		--len;
		K /= 10;
		++idx;
	}
	//看最高位是否有进位
	if (step == 1)
	{
		ret[idx++] = 1;
	}
	//逆转
	reverse(ret, 0, idx - 1);
	*returnSize = idx;
	return ret;
}
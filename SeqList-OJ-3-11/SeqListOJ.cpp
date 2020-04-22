int removeElement(int* nums, int numsSize, int val){
	int i = 0;
	int pos = 0;
	for (i = 0; i < numsSize; i++)
	{
		if (nums[i] != val)
		{
			//i++; ������һ��Ԫ��
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
			//�ҵ�һ������ͬ��λ��
			while (j < numsSize && nums[i] == nums[j])
				++j;
			i = j;
			++j;
		}
	}
	//�������һ��ֵ
	if (i < numsSize)
		nums[idx++] = nums[i];

	return idx;

}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
	int total = m + n;
	//��һ���µ�����
	int* ret = (int*)malloc(sizeof(int)* total);
	//ͬʱ������������
	int n1 = 0;
	int n2 = 0;
	int idx = 0;
	while (n1 < m && n2 < n)
	{
		//ѡС�����ݽ��д��
		if (nums1[n1] <= nums2[n2])
		{
			ret[idx++] = nums1[n1++];
		}
		else
		{
			ret[idx++] = nums2[n2++];
		}
	}
	//�п��ܻ���δ�ϲ�������
	if (n1 < m)
	{
		memcpy(ret + idx, nums1 + n1, sizeof(int)* (m - n1));
	}
	if (n2 < n)
	{
		memcpy(ret + idx, nums2 + n2, sizeof(int)* (n - n2));
	}
	//��ret��������ݿ�����nums1��
	memcpy(nums1, ret, total * sizeof(int));
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
	int pos = m + n - 1;
	int n1 = m - 1;
	int n2 = n - 1;
	//�Ӻ���ǰ�Ⱥϲ���Ԫ��
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
	//���ڶ��������Ƿ���ʣ��Ԫ��
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

	//�¿��ռ䣬 ������
	//��ȡ��������󳤶�
	int klen = 0;
	int tmp = K;
	while (tmp)
	{
		++klen;
		tmp /= 10;
	}
	//���ǽ�λ�Ĵ��
	int retSize = ASize > klen ? ASize + 1 : klen + 1;
	int* ret = (int*)malloc(sizeof(int)* retSize);

	int len = ASize - 1;
	int step = 0;
	int idx = 0;
	while (len >= 0 || K > 0)
	{
		//��ǰ��Ӧλ�Ľ��,���ȼ���һ���Ľ�λ
		ret[idx] = step;
		//��λ���
		if (len >= 0)
		{
			ret[idx] += A[len];
		}
		if (K > 0)
		{
			ret[idx] += K % 10;
		}
		//���½��
		if (ret[idx] > 9)
		{
			ret[idx] %= 10;
			step = 1;
		}
		else
		{
			step = 0;
		}
		//���浱ǰλ�Ľ��

		--len;
		K /= 10;
		++idx;
	}
	//�����λ�Ƿ��н�λ
	if (step == 1)
	{
		ret[idx++] = 1;
	}
	//��ת
	reverse(ret, 0, idx - 1);
	*returnSize = idx;
	return ret;
}
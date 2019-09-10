/*
1. ����һ�����������һ��Ŀ��ֵ�����������ҵ�Ŀ��ֵ����������������
2. ���Ŀ��ֵ�������������У����������ᱻ��˳������λ�á�
3. ����Լ������������ظ�Ԫ�ء�

ʾ�� 1: ����: [1,3,5,6], 5 ���: 2
ʾ�� 2: ����: [1,3,5,6], 2 ���: 1
ʾ�� 3: ����: [1,3,5,6], 7 ���: 4
ʾ�� 4: ����: [1,3,5,6], 0 ���: 0
*/

#include<iostream>
#include<vector>
using namespace std;


// last one is better...

class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int res = 0;
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (nums[mid] == target) {
				return mid;
			}
			else if (nums[mid] < target) {
				left = mid + 1;
				res = left;
			}
			else {
				right = mid - 1;
				res = right + 1;
			}
		}
		return res;
	}
};

// --------------- one...------------
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] >= target) return i;
		}
		return nums.size();
	}
};

// -------------- two...-------------- �����Ż�ʱ�临�Ӷ�...------------better...------
// ���岿�ܹؼ�������
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		if (nums.back() < target) return nums.size();
		// target <= right...
		int left = 0, right = nums.size() - 1;
		while (left < right) { // left < right...
			int mid = (right + left) >> 1;
			if (nums[mid] == target) return mid;
			else if (nums[mid] < target) left = mid + 1;  // left = mid + 1;
			else right = mid;  // right = mid;
		}
		// left == right:
		return right;
	}
};

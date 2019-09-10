/*
1. 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
2. 如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
3. 你可以假设数组中无重复元素。

示例 1: 输入: [1,3,5,6], 5 输出: 2
示例 2: 输入: [1,3,5,6], 2 输出: 1
示例 3: 输入: [1,3,5,6], 7 输出: 4
示例 4: 输入: [1,3,5,6], 0 输出: 0
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

// -------------- two...-------------- 二分优化时间复杂度...------------better...------
// 这五部很关键！！！
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

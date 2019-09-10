/*
给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

示例 1:
给定数组 nums = [1,1,2],
函数应该返回新的长度 2, 并且原数组 nums 的前两个元素被修改为 1, 2。
你不需要考虑数组中超出新长度后面的元素。

示例 2:
给定 nums = [0,0,1,1,1,2,2,3,3,4],
函数应该返回新的长度 5, 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
你不需要考虑数组中超出新长度后面的元素。

说明:
1. 为什么返回数值是整数，但输出的答案是数组呢?
2. 请注意，输入数组是以“引用”方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
*/

#include<vector>
using namespace std;

// ------------------------------ timeout...-----------------------------------------
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		for (int i = 0; i < nums.size() - 1; i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[j] == nums[i]) {
					nums.erase(nums.begin() + j, nums.begin() + j + 1);
					j--;
				}
			}
		}
		return nums.size();
	}
};

// ------------------------------------ Mine: 256ms... 4.27%...lowest of history...------
// 原来是给定一个排序数组啊，我想成乱序了，怪不得。。。我就说邻居比较怎么可能实现。。。

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		//if (nums.size() < 2)return nums.size();
		int n = nums.size();
		// 这里有个坑...条件：i<n-1 可以， i<nums.size()-1 不可以...
		// if(nums.size()==0) nums.size() - 1 == 4294967295...
		// for the res of nums.size() is a size_t type. unsigned int...
		for (int i = 0; i < n - 1; i++) {
			if (nums[i] == INT_MAX)continue;
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[j] == INT_MAX)continue;
				if (nums[j] == nums[i]) {
					nums[j] = INT_MAX;
				}
			}
		}
		int k = 0;
		for (int i = 0; i < n; i++) {
			if (nums[i] != INT_MAX) {
				nums[k++] = nums[i];
			}
		}
		return k;
	}
};

// ----------------------------- 24ms...----------- speedup to 16ms..------------
#include<iostream>
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int number = 1;
		for (int i = 1; i<nums.size(); i++) {
			if (nums[i] != nums[i - 1]) {
				nums[number] = nums[i];
				number++;
			}
		}
		return number;
	}
};

// -------------------------------------- 16ms...-------- try:36ms..----------------
class Solution {
public:
	int removeDuplicates(std::vector<int>& nums) {
		int len = nums.size();
		int res = 0;
		if (len == 0 || len == 1) return len;
		for (int i = 0; i < len; ++i) {
			if (i == 0) res++;
			else {
				if (nums[i] == nums[i - 1]) continue;
				else {
					nums[res] = nums[i];
					res++;
				}
			}
		}
		return res;
	}
};


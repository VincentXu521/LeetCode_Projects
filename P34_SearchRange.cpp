/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
你的算法时间复杂度必须是 O(log n) 级别。
如果数组中不存在目标值，返回 [-1, -1]。
示例 1: 输入: nums = [5,7,7,8,8,10], target = 8 输出: [3,4]
示例 2: 输入: nums = [5,7,7,8,8,10], target = 6 输出: [-1,-1]
*/

#include<iostream>
#include<vector>
using namespace std;

// ----------------------------- Mine: 4ms...100%...---------不是正真意义上的log(N)...--------
static int _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (nums[mid] == target) {
				int l = mid - 1, r = mid + 1;
				while (l >= 0) {
					if (nums[l] == target)l--;
					else break;
				}
				while (r <= nums.size() - 1) {
					if (nums[r] == target)r++;
					else break;
				}
				return { l + 1, r - 1 };
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		return{ -1,-1 };
	}
};

// -------------------------------- first...------- this same to mine.-----
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int idx = search(nums, 0, nums.size() - 1, target);
		if (idx == -1) return { -1, -1 };
		int left = idx, right = idx;
		while (left > 0 && nums[left - 1] == nums[idx]) --left;
		while (right < nums.size() - 1 && nums[right + 1] == nums[idx]) ++right;
		return { left, right };
	}
	int search(vector<int>& nums, int left, int right, int target) {
		if (left > right) return -1;
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) return mid;
		else if (nums[mid] < target) return search(nums, mid + 1, right, target);
		else return search(nums, left, mid - 1, target);
	}
};

/*
可能有些人会觉得上面的算法不是严格意义上的O(logn)的算法，因为在最坏的情况下会变成O(n)，
比如当数组里的数全是目标值的话，从中间向两边找边界就会一直遍历完整个数组，
那么我们下面来看一种真正意义上的O(logn)的算法，使用两次二分查找法，
第一次找到左边界，第二次调用找到右边界即可.
*/

// ------------------------------ second...------------------------
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> res(2, -1);
		int left = 0, right = nums.size() - 1;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] < target) left = mid + 1;
			else right = mid;
		}
		if (nums[right] != target) return res;
		res[0] = right;
		right = nums.size();
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] <= target) left = mid + 1;
			else right = mid;
		}
		res[1] = left - 1;
		return res;
	}
};

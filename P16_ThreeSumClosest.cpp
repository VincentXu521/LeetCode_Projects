/*
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。
返回这三个数的和。假定每组输入只存在唯一答案。

例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
*/
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int res = 0;
		if (nums.size() <= 3) {
			for (int i = 0; i < nums.size(); i++) {
				res += nums[i];
			}
			return res;
		}
		res = nums[0] + nums[1] + nums[2];
		int diff = abs(res - target);
		if (diff == 0)return target;
		sort(nums.begin(), nums.end());
		for (int k = 0; k < nums.size() - 2; k++) {
			int l = k + 1, r = nums.size() - 1;
			while (l < r) {
				int sum = nums[k] + nums[l] + nums[r];
				int newdiff = abs(sum - target);
				if (newdiff == 0)return target;
				if (newdiff < diff) {
					diff = newdiff;
					res = sum;
				}
				if (sum > target)r--;
				else l++;
			}
		}
		return res;
	}
};


// ------------------------------ 执行用时为 4 ms 的范例 ---------------------------------
class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		vector<int> result;
		sort(nums.begin(), nums.end());

		for (unsigned int i = 0; i < nums.size() - 2; ++i) {
			int l = i + 1, r = nums.size() - 1;
			int small = nums[l] + nums[l + 1] + nums[i];

			int big = nums[r] + nums[r - 1] + nums[i];
			if (small > target) result.push_back(small);
			else if (big < target) result.push_back(big);
			else {
				while (l < r) {
					int tmp_sum = nums[l] + nums[r] + nums[i];
					result.push_back(tmp_sum);
					if (tmp_sum < target) ++l;
					else if (tmp_sum > target)--r;
					else return target;
				}
			}
		}
		sort(result.begin(), result.end(), [target](const int x1, const int x2) {
			return abs(x1 - target) < abs(x2 - target);
		});
		return result[0];
	}
};

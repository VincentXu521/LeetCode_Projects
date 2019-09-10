/*
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。
例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
[-1, 0, 1],
[-1, -1, 2]
]
*/

#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

static const auto _ = [](){ios::sync_with_stdio(false);cin.tie(nullptr);return nullptr;}();

// --------------------------------------- 暴力 超时 -------------------------------------
#include<set>
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		set<vector<int>> res;
		vector<int> ans;
		int len = nums.size();
		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len - 1; j++) {
				for (int k = j + 1; k < len; k++) {
					if (nums[i] + nums[j] + nums[k] == 0) {
						ans.push_back(nums[i]);
						ans.push_back(nums[j]);
						ans.push_back(nums[k]);
						sort(ans.begin(), ans.end());
						res.insert(ans);
						ans.clear();
					}
				}
			}
		}
		return vector<vector<int>>(res.begin(), res.end());
	}
};


// ---------------- new method 1: ----------------------
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> res;
		// 先排序，与符号有关系.
		sort(nums.begin(), nums.end());
		// 简单分支优先考虑.
		if (nums.size() < 3 || nums.front() > 0 || nums.back() < 0) return {};
		// 确立目标，降维 && 易于排除相同组合情况.
		for (int k = 0; k < nums.size() - 2; k++) {
			if (nums[k] > 0)break;
			if (k > 0 && nums[k] == nums[k - 1])continue;
			int target = 0 - nums[k];
			int i = k + 1, j = nums.size() - 1;
			while (i < j) {
				// 移动方式很关键.
				if (nums[i] + nums[j] == target) {
					res.push_back({ nums[k], nums[i], nums[j] });
					while (i < j&&nums[i] == nums[i + 1])i++;
					while (i < j&&nums[j] == nums[j - 1])j--;
					i++; j--;
				}
				else if (nums[i] + nums[j] < target) i++;
				else j--;
			}
		}
		return res;
	}
};

// ------------------ new method 2: set() avoid repeation ------------------------------------
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		set<vector<int>> res;
		sort(nums.begin(), nums.end());
		if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
		for (int k = 0; k < nums.size(); ++k) {
			if (nums[k] > 0) break;
			int target = 0 - nums[k];
			int i = k + 1, j = nums.size() - 1;
			while (i < j) {
				if (nums[i] + nums[j] == target) {
					res.insert({ nums[k], nums[i], nums[j] });
					while (i < j && nums[i] == nums[i + 1]) ++i;
					while (i < j && nums[j] == nums[j - 1]) --j;
					++i; --j;
				}
				else if (nums[i] + nums[j] < target) ++i;
				else --j;
			}
		}
		return vector<vector<int>>(res.begin(), res.end());
	}
};


// ------------------------ 执行用时为 64 ms 的范例 -------------------------------
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {

		vector<vector<int>>  result;
		if (nums.size()<3)
			return result;
		sort(nums.begin(), nums.end());
		int sum;
		for (int i = 0; i<nums.size() - 2; i++) {
			while (i>0 && nums[i] == nums[i - 1]) {
				i++;
			}
			if (nums[i] > 0) break;
			int j = i + 1, k = nums.size() - 1;
			while (j<k) {
				sum = nums[i] + nums[j] + nums[k];
				if (sum == 0) {
					result.push_back(vector<int>({ nums[i], nums[j], nums[k] }));
					while (nums[j + 1] == nums[j++]) { ; }
					while (nums[k - 1] == nums[k--]) { ; }
				}
				else if (sum>0)
					k--;
				else // sum<0
					j++;
			}

		}
		return result;
	}
};
static int x = []() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	return 0;
}();

/*
给定一个可包含重复数字的序列，返回所有不重复的全排列。

示例:

输入: [1,1,2]
输出:
[
[1,1,2],
[1,2,1],
[2,1,1]
]

https://www.cnblogs.com/grandyang/p/4359825.html
*/

#include<vector>
#include<set>
#include<algorithm>

using namespace std;


// set: easiest to understand for me: 68_11.7
class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		if (nums.empty()) return vector<vector<int>>(1, vector<int>());
		// the method is same with P46. diff: type of res: set replace vector.
		set<vector<int>> res;
		int first = nums[0];
		nums.erase(nums.begin());
		vector<vector<int>> words = permuteUnique(nums);
		for (auto &a : words) {
			for (int i = 0; i <= a.size(); ++i) {
				a.insert(a.begin() + i, first);
				res.insert(a);
				a.erase(a.begin() + i);
			}
		}
		return vector<vector<int>>(res.begin(), res.end());
	}
};


//same with P46: lazy and stupid solution: (but effcient):44_9.7
class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		res.push_back(nums);
		//next_permutation:
		while (next_permutation(nums.begin(), nums.end())) {
			res.push_back(nums);
		}
		return res;
	}
};



// mark: easiest to understand for me: 108_10.5
class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		if (nums.empty()) return { {} };
		vector<vector<int>> res;
		vector<vector<int>>::iterator it;
		int first = nums[0];
		nums.erase(nums.begin());
		vector<vector<int>> words = permuteUnique(nums);
		for (auto &a : words) {
			for (int i = 0; i <= a.size(); ++i) {
				a.insert(a.begin() + i, first);
				it = find(res.begin(), res.end(), a);
				if (it == res.end()) {
					res.push_back(a);
				}
				a.erase(a.begin() + i);
			}
		}
		return res;
	}
};

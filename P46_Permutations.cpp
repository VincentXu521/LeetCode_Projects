/*
给定一个没有重复数字的序列，返回其所有可能的全排列。

示例:

输入: [1,2,3]
输出:
[
[1,2,3],
[1,3,2],
[2,1,3],
[2,3,1],
[3,1,2],
[3,2,1]
]

https://www.cnblogs.com/grandyang/p/4358848.html
*/

#include<vector>

using namespace std;

// easiest method i think: recursion; (Solution 3:)
class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		//Todo:
		if (nums.size() == 0)return{ {} };
		vector<vector<int>> ret;
		int first = nums[0];
		nums.erase(nums.begin());
		vector<vector<int>> rest = permute(nums);
		for (auto &a : rest) {
			for (int i = 0; i <= a.size(); i++) {
				a.insert(a.begin() + i, first);
				ret.push_back(a);
				a.erase(a.begin() + i);
			}
		}
		return ret;
	}
};


// Solution 1: dfs:
class Solution {
public:
	vector<vector<int>> permute(vector<int>& num) {
		vector<vector<int>> res;
		vector<int> out, visited(num.size(), 0);
		permuteDFS(num, 0, visited, out, res);
		return res;
	}
	void permuteDFS(vector<int>& num, int level, vector<int>& visited, vector<int>& out, vector<vector<int>>& res) {
		if (level == num.size()) { res.push_back(out); return; }
		for (int i = 0; i < num.size(); ++i) {
			if (visited[i] == 1) continue;
			visited[i] = 1;
			out.push_back(num[i]);
			permuteDFS(num, level + 1, visited, out, res);
			out.pop_back();
			visited[i] = 0;
		}
	}
};


// Solution 2: dfs;
class Solution {
public:
	vector<vector<int>> permute(vector<int>& num) {
		vector<vector<int>> res;
		permuteDFS(num, 0, res);
		return res;
	}
	void permuteDFS(vector<int>& num, int start, vector<vector<int>>& res) {
		if (start >= num.size()) res.push_back(num);
		for (int i = start; i < num.size(); ++i) {
			swap(num[start], num[i]);
			permuteDFS(num, start + 1, res);
			swap(num[start], num[i]);
		}
	}
};


// Solution 4: 迭代:
class Solution {
public:
	vector<vector<int>> permute(vector<int>& num) {
		vector<vector<int>> res{ {} };
		for (int a : num) {
			for (int k = res.size(); k > 0; --k) {
				vector<int> t = res.front();
				res.erase(res.begin());
				for (int i = 0; i <= t.size(); ++i) {
					vector<int> one = t;
					one.insert(one.begin() + i, a);
					res.push_back(one);
				}
			}
		}
		return res;
	}
};


// Solution 5: ATL: 偷懒;
#include<algorithm>
class Solution {
public:
	vector<vector<int>> permute(vector<int>& num) {
		vector<vector<int>> res;
		sort(num.begin(), num.end());
		res.push_back(num);
		while (next_permutation(num.begin(), num.end())) {
			res.push_back(num);
		}
		return res;
	}
};

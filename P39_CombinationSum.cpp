/*
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。

说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。

示例 1: 输入: candidates = [2,3,6,7], target = 7, 所求解集为:
[
[7],
[2,2,3]
]

示例 2: 输入: candidates = [2,3,5], target = 8, 所求解集为:
[
[2,2,2,2],
[2,3,3],
[3,5]
]
*/

#include<vector>
#include<algorithm>
using namespace std;


// dfs recursive method1... half copy...
class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>>res;
		dfs(candidates, target, 0, {}, res);
		return res;
	}
	void dfs(vector<int>& candidates, int target, int start, vector<int> out, vector<vector<int>> &res) {
		if (target < 0)return;
		if (target == 0) { res.push_back(out); return; }
		for (int i = start; i < candidates.size(); i++) {
			out.push_back(candidates[i]);
			dfs(candidates, target - candidates[i], i, out, res);
			out.pop_back();
		}
	}
};


// exe 8ms e.g.(32ms)
class Solution {
public:
	vector<vector<int>> ans;
	vector<int> t;
	void dfs(int i, int j, const vector<int>& v)
	{
		if (!j) {
			ans.push_back(t);
			return;
		}
		if (i == v.size())return;
		if (j >= v[i]) {
			t.push_back(v[i]);
			dfs(i, j - v[i], v);
			t.pop_back();
		}
		dfs(i + 1, j, v);
		return;
	}

	vector<vector<int>> combinationSum(vector<int>& v, int target) {
		dfs(0, target, v);
		return ans;
	}
};


// method2...didn't get it...to ok.
/*
我们也可以不使用额外的函数，就在一个函数中完成递归，还是要先给数组排序，然后遍历，
如果当前数字大于target，说明肯定无法组成target，由于排过序，之后的也无法组成target，直接break掉.
如果当前数字正好等于target，那么当前单个数字就是一个解，组成一个数组然后放到结果res中。
然后我们将当前位置之后的数组取出来，调用递归函数，注意此时的target要减去当前的数字，
然后我们遍历递归结果返回的二维数组，将当前数字加到每一个数组最前面，
然后再将每个数组加入结果res即可.
*/
class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> res;
		sort(candidates.begin(), candidates.end());
		for (int i = 0; i < candidates.size(); ++i) {
			if (candidates[i] > target) break; // these two if condition can be regarded as return sentence.
			if (candidates[i] == target) { res.push_back({ candidates[i] }); break; }
			vector<int> vec = vector<int>(candidates.begin() + i, candidates.end());
			vector<vector<int>> tmp = combinationSum(vec, target - candidates[i]);// 一层一层剥开。
			for (auto a : tmp) {//一层一层合上。
				a.insert(a.begin(), candidates[i]);
				res.push_back(a);
			}
		}
		return res;
	}
};


//method3...didn't get it too...still.
/*
我们也可以用迭代的解法来做，建立一个三维数组dp，这里dp[i]表示目标数为i的所有解法集合。
这里的i就从1遍历到target即可，对于每个i，我们都新建一个二维数组cur，然后遍历candidates数组，
如果遍历到的数字大于i，说明当前及之后的数字都无法组成i，直接break掉。
否则如果相等，那么把当前数字自己组成一个数组，并且加到cur中。
否则就遍历dp[i - candidates[j] - 1] 中的所有数组，
如果当前数字大于数组的首元素，则跳过，因为我们的结果要求是要有序的。
否则就将当前数字加入数组的开头，并且将数组放入cur之中即可.
*/
class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<vector<int>>> dp;
		sort(candidates.begin(), candidates.end());
		for (int i = 1; i <= target; ++i) {
			vector<vector<int>> cur;
			for (int j = 0; j < candidates.size(); ++j) {
				if (candidates[j] > i) break;
				if (candidates[j] == i) { cur.push_back({ candidates[j] }); break; }
				for (auto a : dp[i - candidates[j] - 1]) {
					if (candidates[j] > a[0]) continue;
					a.insert(a.begin(), candidates[j]);
					cur.push_back(a);
				}
			}
			dp.push_back(cur);
		}
		return dp[target - 1];
	}
};


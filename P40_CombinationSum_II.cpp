/*
����һ������ candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
candidates �е�ÿ��������ÿ�������ֻ��ʹ��һ�Ρ�

˵����
�������֣�����Ŀ������������������
�⼯���ܰ����ظ�����ϡ�

ʾ�� 1: ����: candidates = [10,1,2,7,6,1,5], target = 8, ����⼯Ϊ:
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]

ʾ�� 2: ����: candidates = [2,5,2,1,2], target = 5, ����⼯Ϊ:
[
[1,2,2],
[5]
]
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

static const auto __ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

// exe: 60ms...
class Solution {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>> res;
		sort(candidates.begin(), candidates.end());
		dfs(candidates, target, 0, {}, res);
		return res;
	}
	void dfs(vector<int>& candidates, int target, int start, vector<int> out, vector<vector<int>> &res) {	
		if (target < 0)return;
		if (target == 0) { res.push_back(out); return; }
		for (int i = start; i < candidates.size(); i++) {
			if (i > start&&candidates[i] == candidates[i - 1])continue;
			out.push_back(candidates[i]);
			dfs(candidates, target - candidates[i], i + 1, out, res);
			out.pop_back();
		}
	}
};


// exe: 20ms...too long to refuse to read it...
class Solution {
public:
	inline void dfs(vector<int>& f, int tar, vector<int>& have, int step, vector<vector<int> >& ans, bool last) {
		if (tar<0) {
			return;
		}
		if (tar == 0) {
			ans.push_back(have);
			return;
		}
		if (step >= f.size()) {
			return;
		}
		if (tar<f[step]) {
			return;
		}
		if (tar == f[step]) {
			have.push_back(f[step]);
			ans.push_back(have);
			have.pop_back();
			return;
		}
		if (step == 0 || f[step] != f[step - 1] || last) {
			have.push_back(f[step]);
			dfs(f, tar - f[step], have, step + 1, ans, true);
			have.pop_back();
		}
		dfs(f, tar, have, step + 1, ans, false);
	}
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int> > ans;
		vector<int> have;
		vector<bool> vis(candidates.size(), false);
		sort(candidates.begin(), candidates.end());
		dfs(candidates, target, have, 0, ans, true);
		return ans;
	}
};

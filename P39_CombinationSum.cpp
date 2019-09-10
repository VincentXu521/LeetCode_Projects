/*
����һ�����ظ�Ԫ�ص����� candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
candidates �е����ֿ����������ظ���ѡȡ��

˵����
�������֣����� target��������������
�⼯���ܰ����ظ�����ϡ�

ʾ�� 1: ����: candidates = [2,3,6,7], target = 7, ����⼯Ϊ:
[
[7],
[2,2,3]
]

ʾ�� 2: ����: candidates = [2,3,5], target = 8, ����⼯Ϊ:
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
����Ҳ���Բ�ʹ�ö���ĺ���������һ����������ɵݹ飬����Ҫ�ȸ���������Ȼ�������
�����ǰ���ִ���target��˵���϶��޷����target�������Ź���֮���Ҳ�޷����target��ֱ��break��.
�����ǰ�������õ���target����ô��ǰ�������־���һ���⣬���һ������Ȼ��ŵ����res�С�
Ȼ�����ǽ���ǰλ��֮�������ȡ���������õݹ麯����ע���ʱ��targetҪ��ȥ��ǰ�����֣�
Ȼ�����Ǳ����ݹ������صĶ�ά���飬����ǰ���ּӵ�ÿһ��������ǰ�棬
Ȼ���ٽ�ÿ�����������res����.
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
			vector<vector<int>> tmp = combinationSum(vec, target - candidates[i]);// һ��һ�������
			for (auto a : tmp) {//һ��һ����ϡ�
				a.insert(a.begin(), candidates[i]);
				res.push_back(a);
			}
		}
		return res;
	}
};


//method3...didn't get it too...still.
/*
����Ҳ�����õ����Ľⷨ����������һ����ά����dp������dp[i]��ʾĿ����Ϊi�����нⷨ���ϡ�
�����i�ʹ�1������target���ɣ�����ÿ��i�����Ƕ��½�һ����ά����cur��Ȼ�����candidates���飬
��������������ִ���i��˵����ǰ��֮������ֶ��޷����i��ֱ��break����
���������ȣ���ô�ѵ�ǰ�����Լ����һ�����飬���Ҽӵ�cur�С�
����ͱ���dp[i - candidates[j] - 1] �е��������飬
�����ǰ���ִ����������Ԫ�أ�����������Ϊ���ǵĽ��Ҫ����Ҫ����ġ�
����ͽ���ǰ���ּ�������Ŀ�ͷ�����ҽ��������cur֮�м���.
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


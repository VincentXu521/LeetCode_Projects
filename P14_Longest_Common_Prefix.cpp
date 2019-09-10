#include<string>
#include<vector>
#include<iostream>

using namespace std;


// ------------------------------------- Mine 4ms -----------------------------------------
static const auto _ = []()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();
#define MIN(x, y) (x<y?x:y)
class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		// importance...
		if (strs.size() == 0)return "";
		if (strs.size() == 1)return strs[0];

		int res = -1, N = INT_MAX;
		bool flag = true;
		for (int k = 0; k < strs.size(); k++) {
			N = MIN(N, strs[k].size());
		}
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < strs.size() - 1; i++) {
				if (strs[i][j] != strs[i + 1][j]) {
					flag = false;
					break;
				}
			}
			if (flag == true)res = j;
			else break;
		}
		return strs[0].substr(0, res + 1);
	}
};


// ---------------------------- 执行用时为 0ms 的范例 --------------------------------
static const auto _ = []()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();
class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if ((strs.size() == 0) || (strs[0].size() == 0))return "";
		if (strs.size() == 1) return strs[0];
		string res;
		int len = strs.size();
		// Q: strs[0][i],strs[j][i] can't be out of range ???
		// A: if a string size is len, string[len]=="", string[len+1] will be out range.
		// this method use string this point well.
		for (int i = 0;; i++) {
			char temp = strs[0][i];
			for (int j = 0; j<len; j++) {
				if (strs[j][i] != temp)
					return res;
			}
			res += temp;
		}
		return res;
	}
};
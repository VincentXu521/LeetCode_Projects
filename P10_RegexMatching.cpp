/*
给定一个字符串 (s) 和一个字符模式 (p)。实现支持 '.' 和 '*' 的正则表达式匹配。
'.' 匹配任意单个字符。
'*' 匹配零个或多个前面的元素。
匹配应该覆盖整个字符串 (s) ，而不是部分字符串。

说明:
  s 可能为空，且只包含从 a-z 的小写字母。
  p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
*/

#include<string>
#include<iostream>
using namespace std;

static const auto __ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	bool isMatch(string s, string p) {
		// recursive method:(imit the following solution)
		if (p.empty())
			return s.empty();
		if (p.size() > 1 && '*' == p.at(1))
			return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p));
		else
			return !s.empty() && (s.at(0) == p.at(0) || '.' == p.at(0)) && isMatch(s.substr(1), p.substr(1));
	}
};

// ---------------- copy from http://www.cnblogs.com/grandyang/p/4461713.html -----------
// 1.递归：
class Solution {
public:
	bool isMatch(string s, string p) {
		if (p.empty()) return s.empty();
		if (p.size() > 1 && p[1] == '*') {
			return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
		}
		else {
			return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
		}
	}
};

// 2.DP()动态规划：
#include<vector>
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;
		for (int i = 0; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (j > 1 && p[j - 1] == '*') {
					dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
				}
				else {
					dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}
		return dp[m][n];
	}
};


//--------------------------------执行用时为 4 ms 的范例-----------------------------------
static int x = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();
class Solution {
public:
	bool cmatch(char s, char p) {
		return p == '*' || p == '.' || s == p;
	}
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		int i, j;
		bool *arr = new bool[n + 1]();
		arr[0] = 1;
		for (i = 2; i <= n; ++i)
		{
			if (p[i - 1] == '*'&&arr[i - 2] == true)
			{
				arr[i] = true;
			}
		}

		int j2 = arr[0];
		int j1 = arr[1];
		int sa = arr[2];
		for (i = 1; i <= m; ++i)
		{
			for (j = 0; j <= n; ++j)
			{
				if (j == 0)
				{
					j2 = arr[0];
					arr[0] = false;
				}
				else if (j == 1)
				{
					j1 = arr[1];
					arr[1] = i == 1 && cmatch(s[0], p[0]);
				}
				else
				{
					sa = arr[j];
					if (p[j - 1] == '*')
						arr[j] = cmatch(s[i - 1], p[j - 2]) && (arr[j] || arr[j - 1] || j1 || j2 || arr[j - 2]) ? true : arr[j - 2];
					else
						arr[j] = cmatch(s[i - 1], p[j - 1]) ? j1 : false;
					j2 = j1;
					j1 = sa;
				}
			}
		}
		return arr[n];
	}
};
/*
给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。

两个字符串完全匹配才算匹配成功。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。


示例 1: 输入: s = "aa" p = "a" 输出: false 解释: "a" 无法匹配 "aa" 整个字符串。

示例 2: 输入: s = "aa" p = "*" 输出: true 解释: '*' 可以匹配任意字符串。

示例 3: 输入: s = "cb" p = "?a" 输出: false 解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。

示例 4: 输入: s = "adceb" p = "*a*b" 输出: true 解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".

示例 5: 输入: s = "acdcb" p = "a*c?b" 输入: false

https://www.cnblogs.com/grandyang/p/4401196.html
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;


// Solution 1: 比较费脑子;
/*执行用时 : 4 ms 99.18%; 内存消耗 : 8.8 MB 91.02% */
class Solution {
public:
	bool isMatch(string s, string p) {
		int i = 0, j = 0, iStar = -1, jStar = -1;
		while (i < s.size()) {
			// 没有星号的一对一;
			if (s[i] == p[j] || p[j] == '?') {
				++i; ++j;
			}
			// p中出现星号;(i不动，j加一；标记位置)
			else if (p[j] == '*') {
				iStar = i;
				jStar = j++;
			}
			// iStar != -1; p中出现过星号;当下j既不是*和?，也不和i匹配;
			else if (iStar >= 0) {
				i = ++iStar;
				j = jStar + 1;
			}
			else return false;
		}
		// s已经结束，p仍没有结束，只允许p后面全是星号；
		while (j < p.size() && p[j] == '*') ++j;
		return j == p.size();
	}
};

// Solution 2: 动态规划，相对第一种容易理解一点;
/*执行用时 : 120 ms 47.73%; 内存消耗 : 13.6 MB 71.60% */
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		// 若s和p都为空的话，应该返回 true;
		dp[0][0] = true;
		// 当s为空,判断p是否为连续的星号;
		for (int i = 1; i <= n; ++i) {
			if (p[i - 1] == '*') dp[0][i] = dp[0][i - 1];
		}
		// else:
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j - 1] == '*') {
					// one2more or one2zero;
					dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
				}
				else {
					// one2one;
					dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
				}
			}
		}
		return dp[m][n];
	}
};

// Solution 3: 递归; 还未理解，待重读;
/*执行用时 : 12 ms 90.17%; 内存消耗 : 8.7 MB 94.66% */
class Solution {
public:
	bool isMatch(string s, string p) {
		return helper(s, p, 0, 0) > 1;
	}
	int helper(string& s, string& p, int i, int j) {
		if (i == s.size() && j == p.size()) return 2;
		if (i == s.size() && p[j] != '*') return 0;
		if (j == p.size()) return 1;
		if (s[i] == p[j] || p[j] == '?') {
			return helper(s, p, i + 1, j + 1);
		}
		if (p[j] == '*') {
			if (j + 1 < p.size() && p[j + 1] == '*') {
				return helper(s, p, i, j + 1);
			}
			for (int k = 0; k <= (int)s.size() - i; ++k) {
				int res = helper(s, p, i + k, j + 1);
				if (res == 0 || res == 2) return res;
			}
		}
		return 1;
	}
};

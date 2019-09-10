/*
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
*/

#include<string>
using namespace std;

// 暴力破解法：(超时,n*n*n)
class Solution {
public:
	string longestPalindrome(string s) {
		if (s.length() < 1) return "";
		string maxstr = "";
		for (int i = 0; i < s.length();i++) {
			for (int j = i; j < s.length(); j++) {
				string subs = s.substr(i, j - i + 1);
				int flag = 1;
				for (int k = 0; k < subs.length()/2; k++) {
					if (subs.at(k) != subs.at(subs.length() - k - 1)) {
						flag = 0;
						break;
					}
				}
				if (flag==1 && subs.length() > maxstr.length())maxstr = subs;
			}
		}
		return maxstr;
	}
};

//--------------------- 官方正解：中心扩展算法(O(n*n)_O(1)) ------------O(N*N)中(暂时觉得最容易理解的)
#include<algorithm>
class Solution {
public:
	string longestPalindrome(string s) {
		if (s.empty()) return "";
		if (s.length() == 1) return s;
		int start = 0, end = 0;
		for (int i = 0; i < s.length(); i++) {
			int len1 = expandAroundCenter(s, i, i);
			int len2 = expandAroundCenter(s, i, i + 1);
			int len = max(len1, len2);
			if (len > end - start) {
				start = i - (len - 1) / 2;
				end = i + len / 2;
			}
		}
		return s.substr(start, end - start + 1);
	}

	int expandAroundCenter(string s, int left, int right) {
		int L = left, R = right;
		while (L >= 0 && R < s.length() && s.at(L) == s.at(R)) {
			L--;
			R++;
		}
		return R - L - 1;
	}
};



//----------------------------------- 执行0秒的范例！！------------------------------------------
#include<iostream>
static const auto __ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	string longestPalindrome(string s) {
		int iLen((int)s.length());
		if (s.empty())
		{
			return "";
		}

		if (iLen == 1)
		{
			return s;
		}

		int iStart(0);
		int iMaxLen(1);
		for (int i = 0; i < iLen; /*++i*/)
		{
			if (iLen - i <= iMaxLen / 2)
			{
				break;
			}

			int iLeft(i);
			int iRight(i);
			while (iRight < iLen - 1 && s.at(iRight) == s.at(iRight + 1))
			{
				++iRight;
			}

			i = iRight + 1;

			while (iRight < iLen - 1 && iLeft > 0 && s.at(iLeft - 1) == s.at(iRight + 1))
			{
				--iLeft;
				++iRight;
			}

			int iNewLen(iRight - iLeft + 1);
			if (iNewLen > iMaxLen)
			{
				iStart = iLeft;
				iMaxLen = iNewLen;
			}
		}

		return s.substr(iStart, iMaxLen);
	}
};

//--------------- Manacher Algorithm O(N) --------------------------------------------
// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) {
	int n = s.length();
	if (n == 0) return "^$";
	string ret = "^";
	for (int i = 0; i < n; i++)
		ret += "#" + s.substr(i, 1);

	ret += "#$";
	return ret;
}

string longestPalindrome(string s) {
	string T = preProcess(s);
	int n = T.length();
	int *P = new int[n];
	int C = 0, R = 0;
	for (int i = 1; i < n - 1; i++) {
		int i_mirror = 2 * C - i; // equals to i' = C - (i-C)

		P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0;

		// Attempt to expand palindrome centered at i
		while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
			P[i]++;

		// If palindrome centered at i expand past R,
		// adjust center based on expanded palindrome.
		if (i + P[i] > R) {
			C = i;
			R = i + P[i];
		}
	}

	// Find the maximum element in P.
	int maxLen = 0;
	int centerIndex = 0;
	for (int i = 1; i < n - 1; i++) {
		if (P[i] > maxLen) {
			maxLen = P[i];
			centerIndex = i;
		}
	}
	delete[] P;

	return s.substr((centerIndex - 1 - maxLen) / 2, maxLen);
}
/*
实现 strStr() 函数。
给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。
如果不存在，则返回  -1。
示例 1: 输入: haystack = "hello", needle = "ll"  输出: 2
示例 2: 输入: haystack = "aaaaa", needle = "bba" 输出: -1
说明:
1. 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
2. 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。
*/

#include<string>
using namespace std;

// ------- Mine: 执行用时: 544 ms, 在Implement strStr()的C++提交中击败了15.81% 的用户.gg.
class Solution {
public:
	int strStr(string haystack, string needle) {
		if (needle.empty())return 0;
		///if (needle.size() > haystack.size())return -1;
		bool flag = false;
		int res;
		for (int i = 0; i < haystack.size(); i++) {
			///if (haystack[i] != needle[0])continue;
			int j = i, k = 0, res = i;
			while (j<haystack.size() && k<needle.size()) {
				if (haystack[j++] == needle[k++]) flag = true;
				else {
					flag = false;
					break;
				}
			}
			if (k != needle.size())flag = false;
			if (flag == true)return res;
		}
		if (flag == true)return res;
		else return -1;
	}
};

// ---------------------------- same thought, good code...---------- try: 4ms..------
class Solution {
public:
	int strStr(string haystack, string needle) {
		if (needle.empty()) return 0;
		int m = haystack.size(), n = needle.size();
		if (m < n) return -1;
		for (int i = 0; i <= m - n; ++i) {
			int j = 0;
			for (j = 0; j < n; ++j) {
				if (haystack[i + j] != needle[j]) break;
			}
			if (j == n) return i;
		}
		return -1;
	}
};

// ---------------------------- 执行时间 0ms 范例：--------- try 4ms..---------
#include<iostream>
static const auto _ = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();
class Solution {
public:
	int strStr(std::string haystack, std::string needle) {
		if (needle.empty()) return 0;
		int len1 = haystack.size();
		int len2 = needle.size();
		for (int i = 0; i < len1; ++i) {
			if (haystack[i] != needle[0]) continue;
			else {
				int flag = 1, m = 0, n = len2 - 1;
				int left = i, right = i + len2 - 1;
				if (right > len1 - 1) break;
				while (left <= right) {
					if (needle[m] != haystack[left] || needle[n] != haystack[right]) {
						flag = 0;
						break;
					}
					else {
						m++;
						left++;
						n--;
						right--;
					}
				}
				if (flag) return i;
			}
		}
		return -1;
	}
};


// ------------ 偷懒的人 ---- 8ms ----- try:20ms ---
class Solution {
public:
	int strStr(string haystack, string needle) {
		return haystack.find(needle);
	}
};


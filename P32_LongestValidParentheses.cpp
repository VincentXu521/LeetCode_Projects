/*
给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
示例 1:
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
示例 2:
输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"
*/

#include<string>
#include<stack>
#include<algorithm>
#include<iostream>
using namespace std;


// ----------------------- 4ms...---------------------------------------------
static int _ = [](){ios::sync_with_stdio(false);cin.tie(nullptr);return 0;}();

// 思路太好了，怎么想到的？？？愚蠢的我就想不到。。。

class Solution {
public:
	int longestValidParentheses(string s) {
		int res = 0, start = 0;
		stack<int> ps;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') ps.push(i);
			else if (s[i] == ')') {
				if (ps.empty()) start = i + 1;
				else {
					ps.pop();
					// 这里是妙笔，既包括了两种状态，也为胜于前者的后来者能居上。。。
					res = ps.empty() ? max(res, i + 1 - start) : max(res, i - ps.top());
				}
			}
		}
		return res;
	}
};

/*
判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
*/

// ------------------------ through string ---------------（最开始只有56ms，after++）----
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
	bool isPalindrome(int x) {
		if (x < 0)
			return false;  // 不要这两行也行，毕竟整型数位数很少
		string s_r = to_string(x);
		string s = s_r;
		reverse(s_r.begin(), s_r.end());
		return s == s_r;
	}
};

// ---------------------------- not through string --------------------------------
//--------------- 执行用时为 44 ms 的范例 -----（try:60ms...）---------------------
static const auto _ = []()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	bool isPalindrome(int x) {
		if (x<0)
			return false;

		int t = x, ans = 0;
		while (t) {
			ans = ans * 10 + t % 10;
			t /= 10;
		}
		return x == ans;
	}
};
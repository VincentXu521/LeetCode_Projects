/*
�ж�һ�������Ƿ��ǻ���������������ָ���򣨴������ң��͵��򣨴������󣩶�����һ����������
*/

// ------------------------ through string ---------------���ʼֻ��56ms��after++��----
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
			return false;  // ��Ҫ������Ҳ�У��Ͼ�������λ������
		string s_r = to_string(x);
		string s = s_r;
		reverse(s_r.begin(), s_r.end());
		return s == s_r;
	}
};

// ---------------------------- not through string --------------------------------
//--------------- ִ����ʱΪ 44 ms �ķ��� -----��try:60ms...��---------------------
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
/*
����һ������������ 2-9 ���ַ����������������ܱ�ʾ����ĸ��ϡ�
�������ֵ���ĸ��ӳ�����£���绰������ͬ����ע�� 1 ����Ӧ�κ���ĸ��
1: ***  2: abc  3: def
4: ghi  5: jkl  6: mno
7: pqrs 8: tuv  9: wxyz

ʾ��:
���룺"23"
�����["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
˵��:
��������Ĵ��ǰ��ֵ������еģ��������������ѡ��������˳��
*/

#include<map>
#include<vector>
#include<iostream>

using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

// -------------------------------Mine good: 0ms...--------------------------------
class Solution {
private:
	map<char, string > mp = {
		{ '2', "abc" },
		{ '3', "def" },
		{ '4', "ghi" },
		{ '5', "jkl" },
		{ '6', "mno" },
		{ '7', "pqrs" },
		{ '8', "tuv" },
		{ '9', "wxyz" }
	};
public:
	vector<string> letterCombinations(string digits) {
		if (digits.empty())return{};
		// �ؼ������� vector ������ֵ��Ȼ��ͬ��һ���ǿյ� vector, һ���Ǻ��пմ��� vector.
		vector<string> res{""};  // C11: a new universe way to give value using {}.
		// a different way to use for loop:
		for (char digit: digits) {
			string s = mp[digit];
			vector<string> tmp_res;
			for (char c : s) {
				for (string e : res) {
					tmp_res.push_back(e + c);
				}
			}
			res = tmp_res;
		}
		return res;
	}
};

// ---------------------- ��Ҫ���de�������� --------------------------
class Solution {
public:
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) return {};
		vector<string> res{ "" };
		string dict[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		for (int i = 0; i < digits.size(); ++i) {
			vector<string> t;
			string str = dict[digits[i] - '0'];
			for (int j = 0; j < str.size(); ++j) {
				for (string s : res) t.push_back(s + str[j]);
			}
			res = t;
		}
		return res;
	}
};

// ------------------- δ����ĵݹ鷽�� dfs(depth first search)---(good too)--------------------------
class Solution {
public:
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) return {};
		vector<string> res;
		string dict[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		letterCombinationsDFS(digits, dict, 0, "", res);
		return res;
	}
	void letterCombinationsDFS(string digits, string dict[], int level, string out, vector<string> &res) {
		if (level == digits.size()) { res.push_back(out); return; }
		string str = dict[digits[level] - '0'];
		for (int i = 0; i < str.size(); ++i) {
			letterCombinationsDFS(digits, dict, level + 1, out + string(1, str[i]), res);
		}
	}
};

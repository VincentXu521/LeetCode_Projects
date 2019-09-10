/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
1: ***  2: abc  3: def
4: ghi  5: jkl  6: mno
7: pqrs 8: tuv  9: wxyz

示例:
输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
说明:
尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
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
		// 关键！！！ vector 赋不赋值截然不同。一个是空的 vector, 一个是含有空串的 vector.
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

// ---------------------- 主要借鉴de迭代方法 --------------------------
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

// ------------------- 未借鉴的递归方法 dfs(depth first search)---(good too)--------------------------
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

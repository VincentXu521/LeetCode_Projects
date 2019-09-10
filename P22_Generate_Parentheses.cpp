/*
给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
例如，给出 n = 3，生成结果为：
[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]
*/

#include<iostream>
#include<vector>
#include<string>
#include<set>

using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

// -------------------- Mine: 4ms --------------- 迭代 -----------------

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		if (n < 1)return{};
		if (n == 1)return{ "()" };
		set<string> res = { "()" };
		for (int i = 0; i < n - 1; i++) {
			set<string> res_tmp;
			for (string s : res) {
				for (int j = 0; j < s.size(); j++) {
					// string类是stl类，已经封装好了，当然是深度拷贝，直接用就可以.
					string s_cpy = s;
					if (s[j] == '(') {
						res_tmp.insert(s_cpy.insert(j, "()"));
						res_tmp.insert(s_cpy.erase(j, 2).insert(j + 1, "()"));
					}
					if (s[j] == ')') {
						res_tmp.insert(s_cpy.insert(j + 1, "()"));
					}
				}
			}
			res = res_tmp;
		}

		return vector<string>(res.begin(), res.end());
	}
};

// --------------------- 0ms 范例: ------------- dfs 递归 -----------------------
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> arr;
		generate(arr, "", 0, 0, n);
		return arr;
	}
	void generate(vector<string>& arr, string str, int l, int r, int n) {
		// l 左括号的个数，r 右括号的个数
		if (r>l || l>n || r>n)return;
		if (l == n && r == n) {
			arr.push_back(str);
			return;
		}
		generate(arr, str + "(", l + 1, r, n);
		generate(arr, str + ")", l, r + 1, n);
	}
};
// 为什么会比我的快？我用的迭代，这个是递归，
// 我直接插入 "()" 避免了很多情况，这个甚至还会有 "(((" 只不过没有push罢了。


// ------------------------ still dfs... ------------------------------
/*
思路：
对于这种列出所有结果的题首先还是考虑用递归Recursion来解，由于字符串只有左括号和右括号两种字符，
而且最终结果必定是左括号3个，右括号3个，所以我们定义两个变量left和right分别表示剩余左右括号的个数，
如果在某次递归时，左括号的个数大于右括号的个数，说明此时生成的字符串中右括号的个数大于左括号的个数，
即会出现')('这样的非法串，所以这种情况直接返回，不继续处理。如果left和right都为0，
则说明此时生成的字符串已有3个左括号和3个右括号，且字符串合法，则存入结果中后返回。
如果以上两种情况都不满足，若此时left大于0，则调用递归函数，注意参数的更新，
若right大于0，则调用递归函数，同样要更新参数。
*/
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		generateParenthesisDFS(n, n, "", res);
		return res;
	}
	void generateParenthesisDFS(int left, int right, string out, vector<string> &res) {
		if (left > right) return;
		if (left == 0 && right == 0) res.push_back(out);
		else {
			if (left > 0) generateParenthesisDFS(left - 1, right, out + '(', res);
			if (right > 0) generateParenthesisDFS(left, right - 1, out + ')', res);
		}
	}
};

// ---------------------- use set like me...------- but use recursion still...
/*
再来看那一种方法，这种方法是CareerCup书上给的方法，感觉也是满巧妙的一种方法，
这种方法的思想是找左括号，每找到一个左括号，就在其后面加一个完整的括号，
最后再在开头加一个()，就形成了所有的情况，需要注意的是，有时候会出现重复的情况，
所以我们用set数据结构，好处是如果遇到重复项，不会加入到结果中，最后我们再把set转为vector即可.
*/

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		set<string> t;
		if (n == 0) t.insert("");
		else {
			vector<string> pre = generateParenthesis(n - 1);
			for (auto a : pre) {
				for (int i = 0; i < a.size(); ++i) {
					if (a[i] == '(') {
						a.insert(a.begin() + i + 1, '(');
						a.insert(a.begin() + i + 2, ')');
						t.insert(a);
						a.erase(a.begin() + i + 1, a.begin() + i + 3);
					}
				}
				t.insert("()" + a);
			}
		}
		return vector<string>(t.begin(), t.end());
	}
};

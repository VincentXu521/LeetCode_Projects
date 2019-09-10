/*
���� n �����������ŵĶ���������д��һ��������ʹ���ܹ��������п��ܵĲ�����Ч��������ϡ�
���磬���� n = 3�����ɽ��Ϊ��
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

// -------------------- Mine: 4ms --------------- ���� -----------------

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
					// string����stl�࣬�Ѿ���װ���ˣ���Ȼ����ȿ�����ֱ���þͿ���.
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

// --------------------- 0ms ����: ------------- dfs �ݹ� -----------------------
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> arr;
		generate(arr, "", 0, 0, n);
		return arr;
	}
	void generate(vector<string>& arr, string str, int l, int r, int n) {
		// l �����ŵĸ�����r �����ŵĸ���
		if (r>l || l>n || r>n)return;
		if (l == n && r == n) {
			arr.push_back(str);
			return;
		}
		generate(arr, str + "(", l + 1, r, n);
		generate(arr, str + ")", l, r + 1, n);
	}
};
// Ϊʲô����ҵĿ죿���õĵ���������ǵݹ飬
// ��ֱ�Ӳ��� "()" �����˺ܶ������������������� "(((" ֻ����û��push���ˡ�


// ------------------------ still dfs... ------------------------------
/*
˼·��
���������г����н���������Ȼ��ǿ����õݹ�Recursion���⣬�����ַ���ֻ�������ź������������ַ���
�������ս���ض���������3����������3�����������Ƕ�����������left��right�ֱ��ʾʣ���������ŵĸ�����
�����ĳ�εݹ�ʱ�������ŵĸ������������ŵĸ�����˵����ʱ���ɵ��ַ����������ŵĸ������������ŵĸ�����
�������')('�����ķǷ����������������ֱ�ӷ��أ��������������left��right��Ϊ0��
��˵����ʱ���ɵ��ַ�������3�������ź�3�������ţ����ַ����Ϸ�����������к󷵻ء�
���������������������㣬����ʱleft����0������õݹ麯����ע������ĸ��£�
��right����0������õݹ麯����ͬ��Ҫ���²�����
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
��������һ�ַ��������ַ�����CareerCup���ϸ��ķ������о�Ҳ���������һ�ַ�����
���ַ�����˼�����������ţ�ÿ�ҵ�һ�������ţ�����������һ�����������ţ�
������ڿ�ͷ��һ��()�����γ������е��������Ҫע����ǣ���ʱ�������ظ��������
����������set���ݽṹ���ô�����������ظ��������뵽����У���������ٰ�setתΪvector����.
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

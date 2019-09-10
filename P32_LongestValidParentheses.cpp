/*
����һ��ֻ���� '(' �� ')' ���ַ������ҳ���İ�����Ч���ŵ��Ӵ��ĳ��ȡ�
ʾ�� 1:
����: "(()"
���: 2
����: ���Ч�����Ӵ�Ϊ "()"
ʾ�� 2:
����: ")()())"
���: 4
����: ���Ч�����Ӵ�Ϊ "()()"
*/

#include<string>
#include<stack>
#include<algorithm>
#include<iostream>
using namespace std;


// ----------------------- 4ms...---------------------------------------------
static int _ = [](){ios::sync_with_stdio(false);cin.tie(nullptr);return 0;}();

// ˼·̫���ˣ���ô�뵽�ģ������޴����Ҿ��벻��������

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
					// ��������ʣ��Ȱ���������״̬��ҲΪʤ��ǰ�ߵĺ������ܾ��ϡ�����
					res = ps.empty() ? max(res, i + 1 - start) : max(res, i - ps.top());
				}
			}
		}
		return res;
	}
};

/*
����һ��ֻ���� '('��')'��'{'��'}'��'['��']' ���ַ������ж��ַ����Ƿ���Ч��
��Ч�ַ��������㣺
1. �����ű�������ͬ���͵������űպϡ�
2. �����ű�������ȷ��˳��պϡ�
3. ע����ַ����ɱ���Ϊ����Ч�ַ�����

ʾ�� 1: ����: "()"     ���: true
ʾ�� 2: ����: "()[]{}" ���: true
ʾ�� 3: ����: "(]"     ���: false
ʾ�� 4: ����: "([)]"   ���: false
ʾ�� 5: ����: "{[]}"   ���: true
*/

#include<iostream>
#include<string>
#include<stack>

using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

// -------------------------------- Mine: 4ms...---------------------------------------
class Solution {
public:
	bool isValid(string s) {
		if (s.empty())return true;
		if (s.size() == 1)return false;
		stack<char> c_stack;
		c_stack.push('=');
		while (!s.empty()) {
			char c = s[0];
			s = s.substr(1);
			if (osp(c) != isp(c_stack.top())) c_stack.push(c);
			else c_stack.pop();
		}
		if (c_stack.size() == 1) return true;
		return false;
	}
	int isp(char c) {
		if (c == '=')return 0;
		else if (c == '(')return 1;
		else if (c == '[')return 2;
		else if (c == '{')return 3;
		else if (c == ')')return 4;
		else if (c == ']')return 5;
		else if (c == '}')return 6;
	}
	int osp(char c) {
		if (c == ')')return 1;
		else if (c == ']')return 2;
		else if (c == '}')return 3;
		else if (c == '(')return 7;
		else if (c == '[')return 8;
		else if (c == '{')return 9;
	}
};


// ------------------------------ ִ����ʱΪ 0 ms �ķ��� --(4ms)----------------------------------
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();// 0ms...

class Solution {
public:
	bool isValid(string s) {
		stack<int> st;
		if (s.length() == 0) return true;
		if (s.length() == 1) return false;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(')
				st.push(s[i]);
			else if (s[i] == '[')
				st.push(s[i]);
			else if (s[i] == '{')
				st.push(s[i]);
			else if (s[i] == ')') {
				if (st.empty())
					return false;
				else if (st.top() == '(')// || st.top() == ']' || st.top() == '}' || st.top() == ')')
					st.pop();
				else
					return false;
			}
			else if (s[i] == ']') {
				if (st.empty())
					return false;
				else if (st.top() == '[')//|| st.top() == ']' || st.top() == '}' || st.top() == ')')
					st.pop();
				else
					return false;
			}
			else if (s[i] == '}') {
				if (st.empty())
					return false;
				else if (st.top() == '{')//|| st.top() == ']' || st.top() == '}' || st.top() == ')')
					st.pop();
				else
					return false;
			}
		}
		if (st.empty())
			return true;
		else
			return false;
	}
};

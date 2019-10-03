/*
����һ���ַ��� (s) ��һ���ַ�ģʽ (p) ��ʵ��һ��֧�� '?' �� '*' ��ͨ���ƥ�䡣

'?' ����ƥ���κε����ַ���
'*' ����ƥ�������ַ������������ַ�������

�����ַ�����ȫƥ�����ƥ��ɹ���

˵��:

s ����Ϊ�գ���ֻ������ a-z ��Сд��ĸ��
p ����Ϊ�գ���ֻ������ a-z ��Сд��ĸ���Լ��ַ� ? �� *��


ʾ�� 1: ����: s = "aa" p = "a" ���: false ����: "a" �޷�ƥ�� "aa" �����ַ�����

ʾ�� 2: ����: s = "aa" p = "*" ���: true ����: '*' ����ƥ�������ַ�����

ʾ�� 3: ����: s = "cb" p = "?a" ���: false ����: '?' ����ƥ�� 'c', ���ڶ��� 'a' �޷�ƥ�� 'b'��

ʾ�� 4: ����: s = "adceb" p = "*a*b" ���: true ����: ��һ�� '*' ����ƥ����ַ���, �ڶ��� '*' ����ƥ���ַ��� "dce".

ʾ�� 5: ����: s = "acdcb" p = "a*c?b" ����: false

https://www.cnblogs.com/grandyang/p/4401196.html
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;


// Solution 1: �ȽϷ�����;
/*ִ����ʱ : 4 ms 99.18%; �ڴ����� : 8.8 MB 91.02% */
class Solution {
public:
	bool isMatch(string s, string p) {
		int i = 0, j = 0, iStar = -1, jStar = -1;
		while (i < s.size()) {
			// û���Ǻŵ�һ��һ;
			if (s[i] == p[j] || p[j] == '?') {
				++i; ++j;
			}
			// p�г����Ǻ�;(i������j��һ�����λ��)
			else if (p[j] == '*') {
				iStar = i;
				jStar = j++;
			}
			// iStar != -1; p�г��ֹ��Ǻ�;����j�Ȳ���*��?��Ҳ����iƥ��;
			else if (iStar >= 0) {
				i = ++iStar;
				j = jStar + 1;
			}
			else return false;
		}
		// s�Ѿ�������p��û�н�����ֻ����p����ȫ���Ǻţ�
		while (j < p.size() && p[j] == '*') ++j;
		return j == p.size();
	}
};

// Solution 2: ��̬�滮����Ե�һ���������һ��;
/*ִ����ʱ : 120 ms 47.73%; �ڴ����� : 13.6 MB 71.60% */
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		// ��s��p��Ϊ�յĻ���Ӧ�÷��� true;
		dp[0][0] = true;
		// ��sΪ��,�ж�p�Ƿ�Ϊ�������Ǻ�;
		for (int i = 1; i <= n; ++i) {
			if (p[i - 1] == '*') dp[0][i] = dp[0][i - 1];
		}
		// else:
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j - 1] == '*') {
					// one2more or one2zero;
					dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
				}
				else {
					// one2one;
					dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
				}
			}
		}
		return dp[m][n];
	}
};

// Solution 3: �ݹ�; ��δ��⣬���ض�;
/*ִ����ʱ : 12 ms 90.17%; �ڴ����� : 8.7 MB 94.66% */
class Solution {
public:
	bool isMatch(string s, string p) {
		return helper(s, p, 0, 0) > 1;
	}
	int helper(string& s, string& p, int i, int j) {
		if (i == s.size() && j == p.size()) return 2;
		if (i == s.size() && p[j] != '*') return 0;
		if (j == p.size()) return 1;
		if (s[i] == p[j] || p[j] == '?') {
			return helper(s, p, i + 1, j + 1);
		}
		if (p[j] == '*') {
			if (j + 1 < p.size() && p[j + 1] == '*') {
				return helper(s, p, i, j + 1);
			}
			for (int k = 0; k <= (int)s.size() - i; ++k) {
				int res = helper(s, p, i + k, j + 1);
				if (res == 0 || res == 2) return res;
			}
		}
		return 1;
	}
};

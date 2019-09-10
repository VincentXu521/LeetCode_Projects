/*
ʵ�� strStr() ������
����һ�� haystack �ַ�����һ�� needle �ַ������� haystack �ַ������ҳ� needle �ַ������ֵĵ�һ��λ�� (��0��ʼ)��
��������ڣ��򷵻�  -1��
ʾ�� 1: ����: haystack = "hello", needle = "ll"  ���: 2
ʾ�� 2: ����: haystack = "aaaaa", needle = "bba" ���: -1
˵��:
1. �� needle �ǿ��ַ���ʱ������Ӧ������ʲôֵ�أ�����һ���������кܺõ����⡣
2. ���ڱ�����ԣ��� needle �ǿ��ַ���ʱ����Ӧ������ 0 ������C���Ե� strstr() �Լ� Java�� indexOf() ���������
*/

#include<string>
using namespace std;

// ------- Mine: ִ����ʱ: 544 ms, ��Implement strStr()��C++�ύ�л�����15.81% ���û�.gg.
class Solution {
public:
	int strStr(string haystack, string needle) {
		if (needle.empty())return 0;
		///if (needle.size() > haystack.size())return -1;
		bool flag = false;
		int res;
		for (int i = 0; i < haystack.size(); i++) {
			///if (haystack[i] != needle[0])continue;
			int j = i, k = 0, res = i;
			while (j<haystack.size() && k<needle.size()) {
				if (haystack[j++] == needle[k++]) flag = true;
				else {
					flag = false;
					break;
				}
			}
			if (k != needle.size())flag = false;
			if (flag == true)return res;
		}
		if (flag == true)return res;
		else return -1;
	}
};

// ---------------------------- same thought, good code...---------- try: 4ms..------
class Solution {
public:
	int strStr(string haystack, string needle) {
		if (needle.empty()) return 0;
		int m = haystack.size(), n = needle.size();
		if (m < n) return -1;
		for (int i = 0; i <= m - n; ++i) {
			int j = 0;
			for (j = 0; j < n; ++j) {
				if (haystack[i + j] != needle[j]) break;
			}
			if (j == n) return i;
		}
		return -1;
	}
};

// ---------------------------- ִ��ʱ�� 0ms ������--------- try 4ms..---------
#include<iostream>
static const auto _ = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();
class Solution {
public:
	int strStr(std::string haystack, std::string needle) {
		if (needle.empty()) return 0;
		int len1 = haystack.size();
		int len2 = needle.size();
		for (int i = 0; i < len1; ++i) {
			if (haystack[i] != needle[0]) continue;
			else {
				int flag = 1, m = 0, n = len2 - 1;
				int left = i, right = i + len2 - 1;
				if (right > len1 - 1) break;
				while (left <= right) {
					if (needle[m] != haystack[left] || needle[n] != haystack[right]) {
						flag = 0;
						break;
					}
					else {
						m++;
						left++;
						n--;
						right--;
					}
				}
				if (flag) return i;
			}
		}
		return -1;
	}
};


// ------------ ͵������ ---- 8ms ----- try:20ms ---
class Solution {
public:
	int strStr(string haystack, string needle) {
		return haystack.find(needle);
	}
};


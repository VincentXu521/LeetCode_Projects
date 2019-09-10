/*
����������һ���������У��������е�������˳����б������õ���һ��������ǰ�������£�
1.     1
2.     11
3.     21
4.     1211
5.     111221

1 ������  "one 1"  ("һ��һ") , �� 11��
11 ������ "two 1s" ("����һ"��, �� 21��
21 ������ "one 2",  "one 1" ��"һ����" ,  "һ��һ") , �� 1211��
����һ�������� n��1 �� n �� 30��������������еĵ� n �
ע�⣺����˳�򽫱�ʾΪһ���ַ�����

ʾ�� 1:
����: 1
���: "1"
ʾ�� 2:
����: 4
���: "1211"
*/


#include <string>
using namespace std;


// copy ??? 
class Solution {
public:
	string countAndSay(int n) {
		if (n <= 0) return "";
		string res = "1";
		while (--n) {
			string cur = "";
			for (int i = 0; i < res.size(); ++i) {
				int cnt = 1;
				while (i + 1 < res.size() && res[i] == res[i + 1]) {
					++cnt;
					++i;
				}
				cur += to_string(cnt) + res[i];
			}
			res = cur;
		}
		return res;
	}
};

// try it by yourself...
class Solution {
public:
	string countAndSay(int n) {
		if (n < 1)return "";
		string res = "1";
		while (--n) {
			string cur = "";
			for (int i = 0; i < res.size(); i++) {
				int cnt = 1;
				while (i + 1 < res.size() && res.at(i) == res.at(i + 1)) {
					cnt++;
					i++;
				}
				cur += to_string(cnt) + res.at(i);
			}
			res = cur;
		}
		return res;
	}
};
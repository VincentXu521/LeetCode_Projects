/*
给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1: 输入: num1 = "2", num2 = "3" 输出: "6"

示例 2: 输入: num1 = "123", num2 = "456" 输出: "56088"

说明：

num1 和 num2 的长度小于110。
num1 和 num2 只包含数字 0-9。
num1 和 num2 均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。

*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;


// 1. vector->string;
class Solution {
public:
	string multiply(string num1, string num2) {
		string res = "";
		int m = num1.size(), n = num2.size();
		vector<int> vals(m + n);
		for (int i = m - 1; i >= 0; --i) {
			for (int j = n - 1; j >= 0; --j) {
				int mul = (num1[i] - '0') * (num2[j] - '0');
				int p1 = i + j, p2 = i + j + 1, sum = mul + vals[p2];
				vals[p1] += sum / 10;
				vals[p2] = sum % 10;
			}
		}
		for (int val : vals) {
			if (!res.empty() || val != 0) res.push_back(val + '0');
		}
		return res.empty() ? "0" : res;
	}
};


// 2. string.substr;
class Solution {
public:
	string multiply(string num1, string num2) {
		int n1 = num1.size();
		int n2 = num2.size();
		string res(n1 + n2, '0');
		for (int i = n1 - 1; i >= 0; i--) {
			for (int j = n2 - 1; j >= 0; j--) {
				int temp = (num1[i] - '0')*(num2[j] - '0') + res[i + j + 1] - '0';
				// 需要 +'0': 因为是直接赋值；
				res[i + j + 1] = temp % 10 + '0';
				// 不需要：因为是 char型的 +=，已经转化了；
				res[i + j] += temp / 10;
			}
		}
		//cout << res << endl;
		for (int i = 0; i<n1 + n2; i++)
			if (res[i] != '0')
				return res.substr(i);
		return "0";
	}
};



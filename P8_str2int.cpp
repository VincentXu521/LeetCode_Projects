/*
请你来实现一个 atoi 函数，使其能将字符串转换成整数。
首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；
假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
在任何情况下，若函数不能进行有效的转换时，请返回 0。
说明：
假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−2**31,  2**31 − 1]。
如果数值超过这个范围，请返回  INT_MAX (2**31 − 1) 或 INT_MIN (−2**31)
*/

#include<string>
#include<iostream>
using namespace std;

static const auto __ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	int myAtoi(string str) {
		str.erase(0, str.find_first_not_of(" "));
		if (str.empty())return 0;
		long long base = 0;
		long long mult = 10;
		string str2;
		if (str.at(0) == '+' || isdigit(str.at(0)) || (str.at(0) == '-')) {
			char judge = str.at(0);
			if (!isdigit(str.at(0)))str = str.substr(1);
			for (int i = 0; i < str.length(); i++) {
				if (isdigit(str.at(i))) {
					base = base*mult;
					if (base > INT_MAX)break;
					base += (int(str.at(i))-48);
				}
				else break;
			}
			if (judge == '+' || isdigit(judge)) {
				if (base <= INT_MAX)return base;
				else return INT_MAX;
			}
			else if (judge == '-') {
				if (base*(-1) >= INT_MIN)return base*(-1);
				else return INT_MIN;
			}
			/*
			if (judge == '+' || isdigit(judge)) {
				return (base <= INT_MAX) ? base : INT_MAX;
			}
			else if (judge == '-') {
				return (base*(-1) >= INT_MIN) ? base*(-1) : INT_MIN;
			}
			*/
		}
		return 0;
	}
};


//-------------- 执行8ms 范例 -----------------------------------------
static const auto speedup = [] {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	return 0;
}();

class Solution {
public:
	int getNum(char num) {
		if (num<'0' || num>'9')
			return -1;
		else return num - '0';
	}

	int myAtoi(string str) {
		if (str.empty()) return 0;
		int sgn = 1;
		long ret = 0;
		int digit = 0;
		int n = str.size();
		int i = 0;
		while (i < n&&str[i] == ' ') i++;//discard whitespace characters and zeros
		if (str[i] == '-') {
			sgn = -1;
			i++;
		}
		else if (str[i] == '+') {
			sgn = 1;
			i++;
		}
		while (i < n&&str[i] == '0') i++;
		for (; i<n; i++) {
			int temp = getNum(str[i]);
			if (temp == -1) {
				if (digit>10) return (sgn>0) ? INT_MAX : INT_MIN;
				else if (ret>INT_MAX) return (sgn>0) ? INT_MAX : INT_MIN;
				else return (int)sgn*ret;
			}
			else {
				ret = ret * 10 + temp;
				digit++;
			}
		}
		if (digit>10) return (sgn>0) ? INT_MAX : INT_MIN;
		else if (ret>INT_MAX) return (sgn>0) ? INT_MAX : INT_MIN;
		else return (int)sgn*ret;
	}
};
/*
给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
返回被除数 dividend 除以除数 divisor 得到的商。

示例 1: 输入: dividend = 10, divisor = 3 输出:  3
示例 2: 输入: dividend = 7, divisor = -3 输出: -2

说明:
1. 被除数和除数均为 32 位有符号整数。
2. 除数不为 0。
3. 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2**31,  2**31 − 1].
4. 本题中，如果除法结果溢出，则返回 2**31 − 1.
*/

#include<algorithm>
#include<iostream>
using namespace std;

static auto x = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

// ------------------ Mine: ?????????????? ------------------------------

class Solution {
public:
	int divide(int dividend, int divisor) {
		/// 好懵逼，位运算...
		if (dividend == INT_MIN && divisor == -1) return INT_MAX;
		return dividend / divisor;
	}
};

/*
这道题让我们求两数相除，而且规定我们不能用乘法，除法和取余操作，那么我们还可以用另一神器位操作Bit Operation，
思路是，如果被除数大于或等于除数，则进行如下循环，定义变量t等于除数，定义计数p，当t的两倍小于等于被除数时，
进行如下循环，t扩大一倍，p扩大一倍，然后更新res和m。这道题的OJ给的一些test case非常的讨厌，
因为输入的都是int型，比如被除数是-2147483648，在int范围内，当除数是-1时，结果就超出了int范围，
需要返回INT_MAX，所以对于这种情况我们就在开始用if判定，将其和除数为0的情况放一起判定，返回INT_MAX。
然后我们还要根据被除数和除数的正负来确定返回值的正负，这里我们采用长整型long来完成所有的计算，
最后返回值乘以符号即可.
*/
// --------------------- solution 1..-------- try 20ms...-----------------
class Solution {
public:
	int divide(int dividend, int divisor) {
		if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
		long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
		int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
		if (n == 1) return sign == 1 ? m : -m;
		while (m >= n) {
			long long t = n, p = 1;
			while (m >= (t << 1)) {
				t <<= 1;
				p <<= 1;
			}
			res += p;
			m -= t;
		}
		return sign == 1 ? res : -res;
	}
};

// -------------------- simplify up -------- try 12ms...------------
class Solution {
public:
	int divide(int dividend, int divisor) {
		long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
		if (m < n) return 0;
		while (m >= n) {
			long long t = n, p = 1;
			while (m >(t << 1)) {
				t <<= 1;
				p <<= 1;
			}
			res += p;
			m -= t;
		}
		if ((dividend < 0) ^ (divisor < 0)) res = -res;
		return res > INT_MAX ? INT_MAX : res;
	}
};

// ------------------- solution 3..------ recursion..---- try 12ms...-----------
class Solution {
public:
	int divide(int dividend, int divisor) {
		long long res = 0;
		long long m = abs((long long)dividend), n = abs((long long)divisor);
		if (m < n) return 0;
		long long t = n, p = 1;
		while (m >(t << 1)) {
			t <<= 1;
			p <<= 1;
		}
		res += p + divide(m - t, n);
		if ((dividend < 0) ^ (divisor < 0)) res = -res;
		return res > INT_MAX ? INT_MAX : res;
	}
};

//---------------- 执行用时为 4 ms 的范例 ------- 未涉及 long long 型.------try 12ms...

class Solution {
public:
	int divide(int dividend, int divisor) {
		//初始条件
		if (dividend == 0)return 0;
		if (dividend == INT_MIN && divisor == -1)return INT_MAX;

		//定义变量
		int result = 0;
		bool flag = true;//记录结果的正负
		if ((divisor^dividend) >> 31)flag = false;
		//处理
		//先都变成正的
		if (dividend < 0)
		{
			dividend = ~dividend + 1;
		}
		if (divisor < 0)
		{
			divisor = ~divisor + 1;
		}

		//做除法
		//先看除数有多少位
		int count = 0;
		for (int i = 31; i > 0; i--)
		{
			if (!((1 << i)&divisor))count++;
			else break;
		}

		//做除法运算
		for (int i = count; i >= 0; i--)
		{
			if (dividend&&dayu(dividend, (divisor << i)))
			{
				dividend -= (divisor << i);
				result = (result << 1) + 1;
			}
			else
				result = (result << 1) + 0;
		}

		if (flag)return result;
		else return -result;
	}
	//重新定义一下大于等于
	bool dayu(int a, int b)
	{
		for (int i = 31; i >= 0; i--)
		{
			int pica = (1 << i)&a;
			int picb = (1 << i)&b;
			if (!pica && picb) return false;
			else if (pica && !picb)return true;
		}
		return true;
	}
};

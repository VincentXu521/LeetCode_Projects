/*
给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转.
假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−2**31,  2**31 − 1].
请根据这个假设，如果反转后整数溢出那么就返回 0.
*/

#include<iostream>
#include<string>
#include<algorithm>  // reverse(string.begin(), string.end());
#include <sstream>   // std::stringstream(推荐使用)
#include <strstream> // std::strstream(已废弃)
using namespace std;

// ----------------------------------- 12ms 也不错嘛 ------------------------------------------
static const auto __ = [] {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	int reverse(int x) {
		if (x<-pow(2, 31) || x>pow(2, 31) - 1) {
			return 0;
		}
		stringstream ss;
		ss << x;
		string s;
		ss >> s;
		/*
		原来clear() 方法只是重置了stringstream的状态标志，并没有清空数据。
		如果需要清空数据，可以用是ss.str("")来实现这个目的。
		谨记！不然很容易使你的程序出现错误，并且吃掉你的内存！
		*/
		ss.clear();  // 必要；
		//总结：clear解决复用问题，ss.str("");//清空缓冲区
		//s.reserve();  // Attention: reserve and reverse...
		if (s.at(0) == '-') {
			std::reverse(s.begin()+1, s.end());
		}
		else {
			std::reverse(s.begin(), s.end());
		}
		ss << s;
		long long y;
		ss >> y;
		if (y<-pow(2, 31) || y>pow(2, 31) - 1) {
			return 0;
		}
		ss.str("");
		return int(y);
	}
};

//--------------------------------- 官方解答 （也是12ms）-----------这个思路也简单，通俗易懂 ---------
class Solution {
public:
	int reverse(int x) {
		int rev = 0;
		while (x != 0) {
			int pop = x % 10;
			x /= 10;
			if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;  // INT_MAX 2147483647  (tail 7)
			if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0; // INT_MIN -2147483648 (tail 8)
			rev = rev * 10 + pop;
		}
		return rev;
	}
};


//---------------------------------  执行用时为 4 ms 的范例 (but if I run, it's still 12ms...)--------
static const auto io_sync_off = []()
{
	// turn off sync
	std::ios::sync_with_stdio(false);
	// untie in/out streams
	std::cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	int reverse(int x) {
		long long out = 0;
		bool bfu = x < 0;
		bool startZero = true;
		if (bfu)
			x *= -1;
		while (x) {
			if (x < 10) {
				out *= 10;
				out += x;
				break;
			}
			else {
				int yu = x % 10;
				if (yu != 0) {
					out = 10 * out + yu;

					startZero = false;
				}
				else if (!startZero) {
					out *= 10;
				}
			}
			x /= 10;
		}

		if (bfu)
			out *= -1;

		if (out >= INT_MAX || out <= -INT_MIN)
			return 0;

		return out;
	}
};
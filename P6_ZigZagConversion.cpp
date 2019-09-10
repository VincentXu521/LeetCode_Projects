/*
将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：
L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

示例 2:
输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G
*/

#include<string>
#include<iostream>
using namespace std;

static const auto __ = [](){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();
// 按行访问的思路，和官方解答的方法二基本一致.
class Solution {
public:
	string convert(string s, int numRows) {
		int sLen = s.size();
		if (sLen == 0)return "";
		if (sLen == 1 || sLen <= numRows || numRows==1)return s;
		int numClass = 2 * numRows - 2;
		string res;
		for (int row = 0; row < numRows; row ++) {
			for (int step = 0; row + step < sLen; step += numClass) {
				res += s.at(row + step);
				// 第三个条件限制不够循环位数的；
				if (row != 0 && row != numRows - 1 && numClass - row + step < sLen) {
					res += s.at(numClass - row + step);
				}
			}
		}
		return res;
	}
};

//-------------------- 用时 8ms ----------------------------- 暂时还未搞懂，尴尬。。。-----------
static const int _ = []
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}();

class Solution {
public:
	string convert(string s, int numRows) {
		if (numRows == 1)
			return s;
		char *res = new char[s.size() + 1];
		res[s.size()] = '\0';
		int j = 0;
		int sp = (numRows << 1) - 2;
		for (int i = 0; i < numRows; ++i)
		{
			int p = i;
			bool flag = true;
			while (p < s.size() && j < s.size())
			{
				res[j++] = s[p];
				int csp = flag ? sp - (i << 1) : (i << 1);
				if (0 == csp)
				{
					j--;
				}
				p += csp;
				flag = !flag;
			}
		}
		return res;
	}
};
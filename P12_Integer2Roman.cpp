/*
罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

例如:
罗马数字 2 写做 II ，即为两个并列的 I;
12 写做 XII ，即为 X + II;
27 写做  XXVII, 即为 XX + V + II;

通常情况下，罗马数字中小的数字在大的数字的右边。
但也存在特例，例如 4 不写做 IIII，而是 IV。
数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

给定一个整数，将其转为罗马数字。输入确保在 1 到 3999 的范围内。
*/


#include<string>
#include<map>
#include<iostream>

using namespace std;

// --------------------------------- Mine: 24ms -----------------------------------------
static const auto _ = []()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class i2roman {
public:
	map<int, string> mp;

	i2roman() {
		mp[1] = "I";
		mp[5] = "V";
		mp[10] = "X";
		mp[50] = "L";
		mp[100] = "C";
		mp[500] = "D";
		mp[1000] = "M";
		mp[4] = "IV";
		mp[9] = "IX";
		mp[40] = "XL";
		mp[90] = "XC";
		mp[400] = "CD";
		mp[900] = "CM";
	}
};

class Solution {
public:
	string intToRoman(int num) {
		if (num > 3999 || num < 1)
			exit(-1);
		//i2roman* i2r = new i2roman();
		//map<int, string> mp = i2r->mp;
		//delete i2r;
		map<int, string> mp = i2roman().mp;
		string res;
		int head = 0;

		// 千位:
		head = num / 1000;
		num %= 1000;
		if (head != 0) {
			for (int i = 0; i < head; i++) {
				res += mp[1000];
			}
		}
		// 百位：
		head = num / 100;
		num %= 100;
		if (head != 0) {
			if (head < 4) {
				for (int i = 0; i < head; i++) {
					res += mp[100];
				}
			}
			else if (head == 4) {
				res += mp[400];
			}
			else if (head < 9){
				res += mp[500];
				for (int i = 5; i < head; i++) {
					res += mp[100];
				}
			}
			else {
				res += mp[900];
			}
		}

		// 十位：
		head = num / 10;
		num %= 10;
		if (head != 0) {
			if (head < 4) {
				for (int i = 0; i < head; i++) {
					res += mp[10];
				}
			}
			else if (head == 4) {
				res += mp[40];
			}
			else if (head < 9) {
				res += mp[50];
				for (int i = 5; i < head; i++) {
					res += mp[10];
				}
			}
			else {
				res += mp[90];
			}
		}
		// 个位：
		head = num;
		if (head != 0) {
			if (head < 4) {
				for (int i = 0; i < head; i++) {
					res += mp[1];
				}
			}
			else if (head == 4) {
				res += mp[4];
			}
			else if (head < 9) {
				res += mp[5];
				for (int i = 5; i < head; i++) {
					res += mp[1];
				}
			}
			else {
				res += mp[9];
			}
		}
		return res;
	}
};

// ----------------------执行用时为 16 ms 的范例 ---------------------------
static const auto _ = []()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	string intToRoman(int num) {
		int q = num / 1000;
		int b = num % 1000 / 100;
		int s = num / 10 % 10;
		int g = num % 10;

		string str;
		// --> 是什么意思？？？while(q-- > 0)...gg...论空格的重要...
		while (q-->0)
			str += 'M';

		if (b<4)
			while (b-->0)
				str += 'C';
		else if (b == 4)
			str += "CD";
		else if (b<9)
		{
			str += "D";
			while (b-->5)
				str += 'C';
		}
		else if (b == 9)
			str += "CM";

		if (s<4)
			while (s-->0)
				str += 'X';
		else if (s == 4)
			str += "XL";
		else if (s<9)
		{
			str += "L";
			while (s-->5)
				str += 'X';
		}
		else if (s == 9)
			str += "XC";

		if (g<4)
			while (g-->0)
				str += 'I';
		else if (g == 4)
			str += "IV";
		else if (g<9)
		{
			str += "V";
			while (g-->5)
				str += 'I';
		}
		else if (g == 9)
			str += "IX";

		return str;
	}
};


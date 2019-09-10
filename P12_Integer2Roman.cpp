/*
�������ְ������������ַ��� I�� V�� X�� L��C��D �� M��

�ַ�          ��ֵ
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

����:
�������� 2 д�� II ����Ϊ�������е� I;
12 д�� XII ����Ϊ X + II;
27 д��  XXVII, ��Ϊ XX + V + II;

ͨ������£�����������С�������ڴ�����ֵ��ұߡ�
��Ҳ�������������� 4 ��д�� IIII������ IV��
���� 1 ������ 5 ����ߣ�����ʾ�������ڴ��� 5 ��С�� 1 �õ�����ֵ 4 ��
ͬ���أ����� 9 ��ʾΪ IX���������Ĺ���ֻ�������������������

I ���Է��� V (5) �� X (10) ����ߣ�����ʾ 4 �� 9��
X ���Է��� L (50) �� C (100) ����ߣ�����ʾ 40 �� 90��
C ���Է��� D (500) �� M (1000) ����ߣ�����ʾ 400 �� 900��

����һ������������תΪ�������֡�����ȷ���� 1 �� 3999 �ķ�Χ�ڡ�
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

		// ǧλ:
		head = num / 1000;
		num %= 1000;
		if (head != 0) {
			for (int i = 0; i < head; i++) {
				res += mp[1000];
			}
		}
		// ��λ��
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

		// ʮλ��
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
		// ��λ��
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

// ----------------------ִ����ʱΪ 16 ms �ķ��� ---------------------------
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
		// --> ��ʲô��˼������while(q-- > 0)...gg...�ۿո����Ҫ...
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


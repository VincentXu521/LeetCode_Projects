/*
��һ�������ַ������ݸ������������Դ������¡������ҽ��� Z �������С�
���������ַ���Ϊ "LEETCODEISHIRING" ����Ϊ 3 ʱ���������£�
L   C   I   R
E T O E S I I G
E   D   H   N
֮����������Ҫ�����������ж�ȡ��������һ���µ��ַ��������磺"LCIRETOESIIGEDHN"��

ʾ�� 2:
����: s = "LEETCODEISHIRING", numRows = 4
���: "LDREOEIIECIHNTSG"
����:

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
// ���з��ʵ�˼·���͹ٷ����ķ���������һ��.
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
				// �������������Ʋ���ѭ��λ���ģ�
				if (row != 0 && row != numRows - 1 && numClass - row + step < sLen) {
					res += s.at(numClass - row + step);
				}
			}
		}
		return res;
	}
};

//-------------------- ��ʱ 8ms ----------------------------- ��ʱ��δ�㶮�����Ρ�����-----------
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
/*
�����������ַ�����ʽ��ʾ�ķǸ����� num1 �� num2������ num1 �� num2 �ĳ˻������ǵĳ˻�Ҳ��ʾΪ�ַ�����ʽ��

ʾ�� 1: ����: num1 = "2", num2 = "3" ���: "6"

ʾ�� 2: ����: num1 = "123", num2 = "456" ���: "56088"

˵����

num1 �� num2 �ĳ���С��110��
num1 �� num2 ֻ�������� 0-9��
num1 �� num2 �������㿪ͷ������������ 0 ����
����ʹ���κα�׼��Ĵ������ͣ����� BigInteger����ֱ�ӽ�����ת��Ϊ����������

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
				// ��Ҫ +'0': ��Ϊ��ֱ�Ӹ�ֵ��
				res[i + j + 1] = temp % 10 + '0';
				// ����Ҫ����Ϊ�� char�͵� +=���Ѿ�ת���ˣ�
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



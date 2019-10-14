/*
You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).
Note:
You have to rotate the image in-place,
which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.
Example 1:
Given input matrix =
[
[1,2,3],
[4,5,6],
[7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
[7,4,1],
[8,5,2],
[9,6,3]
]
Example 2:
Given input matrix =
[
[ 5, 1, 9,11],
[ 2, 4, 8,10],
[13, 3, 6, 7],
[15,14,12,16]
],

rotate the input matrix in-place such that it becomes:
[
[15,13, 2, 5],
[14, 3, 4, 1],
[12, 6, 8, 9],
[16, 7,10,11]
]

https://www.cnblogs.com/grandyang/p/4389572.html
*/


#include<vector>
using namespace std;


/* Solution 1:
����90�ȵķ�ת�кܶ෽����һ����ಽ�����Խ⣬����������һ��ֱ�ӵķ�����
���ڵ�ǰλ�ã�������ת�����λ�ã�Ȼ���ټ�����һ����λ�ã����ĸ�λ���ֱ�ɵ�ǰλ���ˣ�
�����������ÿ��ѭ�����ĸ����֣�������ʾ��
1  2  3                 7  2  1                 7  4  1
4  5  6       -->       4  5  6       -->       8  5  2����
7  8  9                 9  8  3                 9  6  3
*/

//˼·��򵥣�������Ҫ�����ת90�ȵľ���index��Ӧ��ϵ�Լ���Ҫע��ij��Χ��
class Solution {
public:
	void rotate(vector<vector<int> > &matrix) {
		int n = matrix.size();
		for (int i = 0; i < n / 2; ++i) {
			for (int j = i; j < n - 1 - i; ++j) {
				int tmp = matrix[i][j];
				matrix[i][j] = matrix[n - 1 - j][i];
				matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
				matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
				matrix[j][n - 1 - i] = tmp;
			}
		}
	}
};


/* Solution 2:
����һ�ֽⷨ�������ԴӶԽ���Ϊ�ᷭת��Ȼ������x���������·�ת���ɵõ������
����ͼ��ʾ(������ɫ���ֱ�ʾ��ת��)��
1  2  3            9  6  3            7  4  1
4  5  6    -->     8  5  2    -->     8  5  2����
7  8  9            7  4  1            9  6  3
*/
class Solution {
public:
	void rotate(vector<vector<int> > &matrix) {
		int n = matrix.size();
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < n - i; ++j) {
				swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
			}
		}
		for (int i = 0; i < n / 2; ++i) {
			for (int j = 0; j < n; ++j) {
				swap(matrix[i][j], matrix[n - 1 - i][j]);
			}
		}
	}
};


/* Solution 3:
���������һ�ַ��������ַ������ȶ�ԭ����ȡ��ת�þ���Ȼ���ÿ�е����ַ�ת�ɵõ������
������ʾ(������ɫ���ֱ�ʾ��ת��)��
1  2  3            1  4  7            7  4  1
4  5  6    -->     2  5  8    -->     8  5  2����
7  8  9            3  6  9            9  6  3
*/

//solution 2��solution 3������һ����ѧ���⣺��3���������������ÿ��ġ�(love this)
class Solution {
public:
	void rotate(vector<vector<int> > &matrix) {
		int n = matrix.size();
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				swap(matrix[i][j], matrix[j][i]);
			}
			reverse(matrix[i].begin(), matrix[i].end());
		}
	}
};


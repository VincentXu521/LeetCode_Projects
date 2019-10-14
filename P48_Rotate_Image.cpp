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
对于90度的翻转有很多方法，一步或多步都可以解，我们先来看一种直接的方法，
对于当前位置，计算旋转后的新位置，然后再计算下一个新位置，第四个位置又变成当前位置了，
所以这个方法每次循环换四个数字，如下所示：
1  2  3                 7  2  1                 7  4  1
4  5  6       -->       4  5  6       -->       8  5  2　　
7  8  9                 9  8  3                 9  6  3
*/

//思路最简单，但是需要求出旋转90度的矩阵index对应关系以及需要注意ij范围：
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
还有一种解法，首先以从对角线为轴翻转，然后再以x轴中线上下翻转即可得到结果，
如下图所示(其中蓝色数字表示翻转轴)：
1  2  3            9  6  3            7  4  1
4  5  6    -->     8  5  2    -->     8  5  2　　
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
最后再来看一种方法，这种方法首先对原数组取其转置矩阵，然后把每行的数字翻转可得到结果，
如下所示(其中蓝色数字表示翻转轴)：
1  2  3            1  4  7            7  4  1
4  5  6    -->     2  5  8    -->     8  5  2　　
7  8  9            3  6  9            9  6  3
*/

//solution 2和solution 3基本是一个数学问题：但3是所有里面代码最好看的。(love this)
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


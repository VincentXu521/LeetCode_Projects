/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例: 输入: [0,1,0,2,1,0,1,3,2,1,2,1] , 输出: 6
*/


#include<vector>
#include<map>
#define MIN(a,b) (a>b?b:a)

using namespace std;

// Solution 1: count by rol one by one;
class Solution {
public:
	int trap(vector<int>& height) {

		int sum = 0;
		// int(height.size() - 1) cannot be replaced by height.size() - 1
		// 注意数据类型，无符号的0减去1不能变成负数，变为 max unsigned int；
		for (int i = 1; i < int(height.size() - 1); i++) {

			int curr = height.at(i);
			int max_left = curr;
			int max_right = curr;

			// the max_value at left of curr
			for (int j = i - 1; j >= 0; j--) {
				if (height.at(j) > max_left) {
					max_left = height.at(j);
				}
			}
			// the max_value at right of curr
			for (int j = i + 1; j < height.size(); j++) {
				if (height.at(j) > max_right) {
					max_right = height.at(j);
				}
			}
			// min value of max_left and max_right
			int min = MIN(max_left, max_right);

			// add the water at current col
			if (min > curr) {
				sum += (min - curr);
			}

		}
		return sum;
	}
};
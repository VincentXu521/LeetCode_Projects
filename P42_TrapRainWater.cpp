/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例: 输入: [0,1,0,2,1,0,1,3,2,1,2,1] , 输出: 6
*/


#include<vector>
#include<map>
using namespace std;


class Solution {
public:
	int trap(vector<int>& height) {
		map<int, int> max_value;
		int n = height.size();
		if ( n< 3)return 0;
		if (height[0] > height[1])max_value[0] = 1;
		if (height[n - 1] > height[n - 2])max_value[n - 1] = 1;
		for (int i = 1; i < n-1; i++) {
			if (height[i] >= height[i - 1] && height[i] >= height[i + 1])max_value[i] = 1;
		}
	}
};
/*
给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
说明：你不能倾斜容器，且 n 的值至少为 2。
*/

#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

static const auto __ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

// ---------------------------------------- 超时 ---------------------------------------
class Solution {
public:
	int maxArea(vector<int>& height) {
		// max(min(ai, aj) * (j - i))
		vector<int> area;
		for (int i = 0; i < height.size(); i++) {
			for (int j = 0; j < height.size(); j++) {
				area.push_back(min(height[i], height[j])*(j - i));
			}
		}
		sort(area.begin(), area.end());
		int res = *prev(area.end());  // equal to" int res = area.at(area.size()-1);"
		return res;
	}
};


// ------------------------------ 超时 -- still 暴力 ------------ O(N*N) ----------------
class Solution {
public:
	int maxArea(vector<int>& height) {
		// max(min(ai, aj) * (j - i))
		int maxA = 0;
		for (int i = 0; i < height.size(); i++) {
			for (int j = 0; j < height.size(); j++) {
				maxA = max(maxA, min(height[i], height[j])*(j - i));
			}
		}
		return maxA;
	}
};

// -------------------- 双指针法 ---------- O(N) --------------------------
//宏定义函数时,不能把他看作函数,得看做字符串,可以带入代码的字符串,注意括号的运用,or容易出错.
//#define MAX(x, y) x>y?x:y
//#define MIN(x, y) x<y?x:y
class Solution {
public:
	int maxArea(vector<int>& height) {
		int maxarea = 0, l = 0, r = height.size() - 1;
		while (l < r) {
			maxarea = max(maxarea, min(height[l], height[r])*(r - l));
			if (height[l] < height[r])
				l++;
			else
				r--;
		}
		return maxarea;
	}
};
// 深度加深了，宽度的减少才有意义。诫己！！！

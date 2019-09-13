/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例: 输入: [0,1,0,2,1,0,1,3,2,1,2,1] , 输出: 6
*/


#include<vector>

#define MIN(a,b) (a>b?b:a)
#define MAX(a,b) (a<b?b:a)

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


// Solution 2:：执行用时 : 4 ms, C++ 提交中击败98.22%；内存消耗 :9 MB, C++ 提交中击败94.05%；
// Mine: （递归）;
class Solution {
public:
	int trap(vector<int>& height) {

		// 刨除一些特殊情况；
		if (height.size() < 2)return 0;

		int sum = cal_water(0, height.size() - 1, height);

		return sum;
	}

	// 计算最高两峰之间的水量(递归)；-> 总的水量；
	int cal_water(int s, int e, vector<int>& height) {

		int firstHigh = 0;
		int firstIndex = 0;
		int secondHigh = 0;
		int secondIndex = 0;
		int sum = 0;

		for (unsigned int i = s; i <= e; i++) {
			if (height.at(i) > firstHigh) {
				firstHigh = height.at(i);
				firstIndex = i;
			}
		}

		for (unsigned int i = s; i <= e; i++) {
			if (height.at(i) > secondHigh && i != firstIndex) {
				secondHigh = height.at(i);
				secondIndex = i;
			}
		}

		if (firstIndex > secondIndex)swap(firstIndex, secondIndex);
		if (secondHigh != 0) {
			// 计算核心；
			sum = (secondIndex - firstIndex - 1)*secondHigh - sum_pillar(firstIndex, secondIndex, height);
			sum += cal_water(s, firstIndex, height) + cal_water(secondIndex, e, height);
		}

		return sum;
	}

	// 计算（s, e）之间柱子占用的位置；
	int sum_pillar(int s, int e, vector<int>& height) {

		int sum = 0;

		for (unsigned int i = s + 1; i < e; i++) {
			sum += height.at(i);
		}

		return sum;
	}
};



// Solution 3(双指针法)：范例: 左右向内靠近，谁小谁先靠近；时间复杂度O(n),空间复杂度(1);
class Solution {

public:

	int trap(vector<int>& A) {
		int n = A.size();
		int left = 0; int right = n - 1;
		int res = 0;
		int maxleft = 0, maxright = 0;
		while (left <= right) {
			if (A[left] <= A[right]) {
				if (A[left] >= maxleft) maxleft = A[left];
				else res += maxleft - A[left];
				left++;
			}
			else {
				if (A[right] >= maxright) maxright = A[right];
				else res += maxright - A[right];
				right--;
			}
		}
		return res;
	}
};

// BEST: OR: 0ms;8.9M;
// tql，好巧；这个lower，level用的一绝；
class Solution {
public:
	int trap(vector<int>& height) {
		int l = 0, r = height.size() - 1, level = 0, res = 0;
		while (l < r) {
			int lower = height[(height[l] < height[r]) ? l++ : r--];
			level = MAX(level, lower);
			res += level - lower;
		}
		return res;
	}
};


#include<stack>
// Solution 4(栈): 
/*
我们用栈保存每堵墙。
当遍历墙的高度的时候，如果当前高度小于栈顶的墙高度，说明这里会有积水，我们将墙的高度的下标入栈。
如果当前高度大于栈顶的墙的高度，说明之前的积水到这里停下，我们可以计算下有多少积水了。
计算完，就把当前的墙继续入栈，作为新的积水的墙。
总体的原则就是，

1. 当前高度小于等于栈顶高度，入栈，指针后移。

2. 当前高度大于栈顶高度，出栈，计算出当前墙和栈顶的墙之间水的多少，然后计算当前的高度和新栈的高度的关系，
重复第 2 步。直到当前墙的高度不大于栈顶高度或者栈空，然后把当前墙入栈，指针后移。

作者：windliang
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-8/

*/
class Solution {
public:
	int trap(vector<int>& height) {
		int sum = 0;
		stack<int> stack;
		int current = 0;
		while (current < height.size()) {
			//如果栈不空并且当前指向的高度大于栈顶高度就一直循环
			while (!stack.empty() && height[current] > height[stack.top()]) {
				int h = height[stack.top()]; //取出要出栈的元素
				stack.pop(); //出栈
				if (stack.empty()) { // 栈空就出去
					break;
				}
				int distance = current - stack.top() - 1; //两堵墙之前的距离。
				int min = MIN(height[stack.top()], height[current]);
				sum = sum + distance * (min - h);
			}
			stack.push(current); //当前指向的墙入栈
			current++; //指针后移
		}
		return sum;
	}
};

// OR:
class Solution {
public:
	int trap(vector<int>& height) {
		stack<int> st;
		int i = 0, res = 0, n = height.size();
		while (i < n) {
			if (st.empty() || height[i] <= height[st.top()]) {
				st.push(i++);
			}
			else {
				int t = st.top(); st.pop();
				if (st.empty()) continue;
				res += (MIN(height[i], height[st.top()]) - height[t]) * (i - st.top() - 1);
			}
		}
		return res;
	}
};


// 动态规划：
class Solution {
public:
	int trap(vector<int>& height) {
		int res = 0, mx = 0, n = height.size();
		vector<int> dp(n, 0);
		for (int i = 0; i < n; ++i) {
			dp[i] = mx;
			mx = MAX(mx, height[i]);
		}
		mx = 0;
		for (int i = n - 1; i >= 0; --i) {
			dp[i] = MIN(dp[i], mx);
			mx = MAX(mx, height[i]);
			if (dp[i] > height[i]) res += dp[i] - height[i];
		}
		return res;
	}
};



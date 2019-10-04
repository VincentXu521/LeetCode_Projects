/*
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。

示例:
输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

说明:
假设你总是可以到达数组的最后一个位置。

https://www.cnblogs.com/grandyang/p/4373533.html
*/

#include<vector>
#define MAX(a,b) a>b?a:b
using namespace std;


// Method 1:
class Solution {
public:
	int jump(vector<int>& nums) {
		// cur和pre分别来保存当前的能到达的最远位置和之前能到达的最远位置;
		int res = 0, n = nums.size(), i = 0, cur = 0;
		while (cur < n - 1) {
			++res;
			int pre = cur;
			for (; i <= pre; ++i) {
				cur = MAX(cur, i + nums[i]);
			}
			if (pre == cur) return -1; // May not need this. (fail to arrive at the end)
		}
		return res;
	}
};


// Method 2:
/* copy:
* We use "last" to keep track of the maximum distance that has been reached
* by using the minimum steps "ret", whereas "curr" is the maximum distance
* that can be reached by using "ret+1" steps. Thus,
* curr = max(i+A[i]) where 0 <= i <= last.
*/
class Solution {
public:
	int jump(int A[], int n) {
		int ret = 0;
		int last = 0;
		int curr = 0;
		for (int i = 0; i < n; ++i) {
			if (i > last) {
				last = curr;
				++ret;
			}
			curr = MAX(curr, i + A[i]);
		}

		return ret;
	}
};


// Method 3: 对2优化：(略有感悟，未得精髓，基本理解了思路和意图)
class Solution {
public:
	int jump(vector<int>& nums) {
		// cur是当前能到达的最远位置，last是上一步能到达的最远位置;
		int res = 0, n = nums.size(), last = 0, cur = 0;
		for (int i = 0; i < n - 1; ++i) {
			cur = MAX(cur, i + nums[i]);
			if (i == last) {
				last = cur;
				++res;
				if (cur >= n - 1) break;//可以注释掉;
			}
		}
		return res;
	}
};
// in leetcode editor, i've type the code once;


// Method 4: BFS:
/*
@zeeng :
我一直没太理解greedy，觉得greedy方法特别神奇但是常常不知道怎么证明用greedy做出来的就是最优解，
比如我自己就想不到怎么证明这样的方法做出来得到的res就是最小步数。
然后这道题我是用BFS的思路理解的。就像在一个图中寻找最短路径。
一个数就是一个node，它的邻居就是它能reach到的那些点。最后写出来的代码跟greedy差不多。
*/

class Solution {
public:
	int jump(vector<int>& nums) {
		if (nums.size() <= 1) return 0;
		int curMax = 0; // 标记一层的最后一个数
		int level = 0, i = 0;
		while (i <= curMax) { // i比curMax还大说明不能继续走到下一层了
			int furthest = curMax; // 标记下一层最远到哪儿
			for (; i <= curMax; i++) {
				furthest = MAX(furthest, nums[i] + i);
				if (furthest >= nums.size() - 1) return level + 1;
			}
			level++;
			curMax = furthest;
		}
		return -1;
	}
};

/*
给定一个未排序的整数数组，找出其中没有出现的最小的正整数。

示例 1: 输入: [1,2,0] 输出: 3
示例 2: 输入: [3,4,-1,1] 输出: 2
示例 3: 输入: [7,8,9,11,12] 输出: 1

说明: 你的算法的时间复杂度应为O(n)，并且只能使用常数级别的空间。
*/

#include<vector>
#include<algorithm> // max
#include<unordered_set> // unordered_set
using namespace std;


// NOT constant space
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int mx = 1;
		unordered_set<int> s;
		for (int num : nums) {
			if (num <= 0) continue;
			s.insert(num);
			mx = max(mx, num);
		}
		for (int i = 1; i <= mx; ++i) {
			if (!s.count(i)) return i;
		}
		return mx;
	}
};


// NOT constant space
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		vector<bool> tmp(nums.size(), 0);
		for (int i : nums)
		{
			if (i <= 0 || i>nums.size())   continue;
			tmp[i - 1] = 1;
		}
		for (int i = 0; i<nums.size(); i++)
		{
			if (!tmp[i])
				return i + 1;
		}
		return nums.size() + 1;
	}
};


/*
但是上面的解法不是O(1)的空间复杂度，所以我们需要另想一种解法，
既然不能建立新的数组，那么我们只能覆盖原有数组，
我们的思路是把1放在数组第一个位置nums[0]，2放在第二个位置nums[1]，
即需要把nums[i]放在nums[nums[i] - 1]上，那么我们遍历整个数组，
如果nums[i] != i + 1, 而nums[i]为整数且不大于n，
另外nums[i]不等于nums[nums[i] - 1]的话，我们将两者位置调换，如果不满足上述条件直接跳过，
最后我们再遍历一遍数组，如果对应位置上的数不正确则返回正确的数.
*/
// right method:(Mine)
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; i++) {
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
				int tmp = nums[i];
				nums[i] = nums[tmp - 1];
				nums[tmp - 1] = tmp;
			}
		}
		for (int i = 0; i < n; i++) {
			if (nums[i] != i + 1)return i + 1;
		}
		return n + 1;
	}
};


// refer:
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (nums[i] != i + 1) return i + 1;
		}
		return n + 1;
	}
};

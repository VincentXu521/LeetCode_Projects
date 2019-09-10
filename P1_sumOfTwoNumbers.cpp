/*P1:
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
*/
#include<vector>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		for (int i = 0; i<nums.size(); i++) {
			for (int j = i + 1; j<nums.size(); j++) {
				if (nums.at(i) + nums.at(j) == target) {
					vector<int> res;
					res.push_back(i);
					res.push_back(j);
					return res;
				}
			}
		}
	}
};
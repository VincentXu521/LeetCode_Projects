/*
����һ������ n ������������ nums ��һ��Ŀ��ֵ target���ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d ��
ʹ�� a + b + c + d ��ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣
ע�⣺
���в����԰����ظ�����Ԫ�顣
ʾ����
�������� nums = [1, 0, -1, 0, -2, 2]���� target = 0��

����Ҫ�����Ԫ�鼯��Ϊ��
[
[-1,  0, 0, 1],
[-2, -1, 1, 2],
[-2,  0, 0, 2]
]
*/
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

// -------------------------- Mine: the fastest 8ms...----------------------------------------------
class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		int n = nums.size();
		if (n < 4)return {};
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		for (int i = 0; i < n - 3; i++) {
			// ��һԪ��ȥ��
			if (i > 0 && nums[i] == nums[i - 1])continue;
			// ��֦(to be faster)
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
				break;
			if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
				continue;

			for (int j = i + 1; j < n - 2; j++) {
				// �ڶ�Ԫ��ȥ��
				if (j > i + 1 && nums[j] == nums[j - 1])continue;
				// ��֦
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
					break;
				if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
					continue;
				// �ƶ�ָ������
				int l = j + 1, r = n - 1;
				while (l < r) {
					int sum = nums[i]+ nums[j]+ nums[l]+ nums[r];
					if (sum == target) {
						res.push_back({ nums[i], nums[j], nums[l], nums[r] });
						// ����Ԫ��ȥ��
						while (l < r&&nums[l] == nums[l + 1])l++;
						while (l < r&&nums[r] == nums[r - 1])r--;
						l++; r--;
					}
					else if (sum < target) {
						l++;
					}
					else if (sum > target) {
						r--;
					}
				}
			}
		}
		return res;
	}
};


// ------------------------- use set ---------------------------------------------
#include<set>
// don't need to cut the repeation by us.
class Solution {
public:
	vector<vector<int>> fourSum(vector<int> &nums, int target) {
		int n = nums.size();
		set<vector<int>> res;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < n - 3; ++i) {
			// ��֦
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
				break;
			if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
				continue;
			for (int j = i + 1; j < n - 2; ++j) {
				// ��֦
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
					break;
				if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
					continue;
				int left = j + 1, right = n - 1;
				while (left < right) {
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum == target) {
						vector<int> out{ nums[i], nums[j], nums[left], nums[right] };
						res.insert(out);
						++left; --right;
					}
					else if (sum < target) ++left;
					else --right;
				}
			}
		}
		return vector<vector<int>>(res.begin(), res.end());
	}
};
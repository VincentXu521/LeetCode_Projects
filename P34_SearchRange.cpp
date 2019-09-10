/*
����һ�������������е��������� nums����һ��Ŀ��ֵ target���ҳ�����Ŀ��ֵ�������еĿ�ʼλ�úͽ���λ�á�
����㷨ʱ�临�Ӷȱ����� O(log n) ����
��������в�����Ŀ��ֵ������ [-1, -1]��
ʾ�� 1: ����: nums = [5,7,7,8,8,10], target = 8 ���: [3,4]
ʾ�� 2: ����: nums = [5,7,7,8,8,10], target = 6 ���: [-1,-1]
*/

#include<iostream>
#include<vector>
using namespace std;

// ----------------------------- Mine: 4ms...100%...---------�������������ϵ�log(N)...--------
static int _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (nums[mid] == target) {
				int l = mid - 1, r = mid + 1;
				while (l >= 0) {
					if (nums[l] == target)l--;
					else break;
				}
				while (r <= nums.size() - 1) {
					if (nums[r] == target)r++;
					else break;
				}
				return { l + 1, r - 1 };
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		return{ -1,-1 };
	}
};

// -------------------------------- first...------- this same to mine.-----
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int idx = search(nums, 0, nums.size() - 1, target);
		if (idx == -1) return { -1, -1 };
		int left = idx, right = idx;
		while (left > 0 && nums[left - 1] == nums[idx]) --left;
		while (right < nums.size() - 1 && nums[right + 1] == nums[idx]) ++right;
		return { left, right };
	}
	int search(vector<int>& nums, int left, int right, int target) {
		if (left > right) return -1;
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) return mid;
		else if (nums[mid] < target) return search(nums, mid + 1, right, target);
		else return search(nums, left, mid - 1, target);
	}
};

/*
������Щ�˻����������㷨�����ϸ������ϵ�O(logn)���㷨����Ϊ���������»���O(n)��
���統���������ȫ��Ŀ��ֵ�Ļ������м��������ұ߽�ͻ�һֱ�������������飬
��ô������������һ�����������ϵ�O(logn)���㷨��ʹ�����ζ��ֲ��ҷ���
��һ���ҵ���߽磬�ڶ��ε����ҵ��ұ߽缴��.
*/

// ------------------------------ second...------------------------
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> res(2, -1);
		int left = 0, right = nums.size() - 1;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] < target) left = mid + 1;
			else right = mid;
		}
		if (nums[right] != target) return res;
		res[0] = right;
		right = nums.size();
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] <= target) left = mid + 1;
			else right = mid;
		}
		res[1] = left - 1;
		return res;
	}
};

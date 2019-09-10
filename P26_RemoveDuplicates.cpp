/*
����һ���������飬����Ҫ��ԭ��ɾ���ظ����ֵ�Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ�Σ������Ƴ���������³��ȡ�
��Ҫʹ�ö��������ռ䣬�������ԭ���޸��������鲢��ʹ�� O(1) ����ռ����������ɡ�

ʾ�� 1:
�������� nums = [1,1,2],
����Ӧ�÷����µĳ��� 2, ����ԭ���� nums ��ǰ����Ԫ�ر��޸�Ϊ 1, 2��
�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�

ʾ�� 2:
���� nums = [0,0,1,1,1,2,2,3,3,4],
����Ӧ�÷����µĳ��� 5, ����ԭ���� nums ��ǰ���Ԫ�ر��޸�Ϊ 0, 1, 2, 3, 4��
�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�

˵��:
1. Ϊʲô������ֵ��������������Ĵ���������?
2. ��ע�⣬�����������ԡ����á���ʽ���ݵģ�����ζ���ں������޸�����������ڵ������ǿɼ��ġ�
*/

#include<vector>
using namespace std;

// ------------------------------ timeout...-----------------------------------------
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		for (int i = 0; i < nums.size() - 1; i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[j] == nums[i]) {
					nums.erase(nums.begin() + j, nums.begin() + j + 1);
					j--;
				}
			}
		}
		return nums.size();
	}
};

// ------------------------------------ Mine: 256ms... 4.27%...lowest of history...------
// ԭ���Ǹ���һ���������鰡������������ˣ��ֲ��á������Ҿ�˵�ھӱȽ���ô����ʵ�֡�����

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		//if (nums.size() < 2)return nums.size();
		int n = nums.size();
		// �����и���...������i<n-1 ���ԣ� i<nums.size()-1 ������...
		// if(nums.size()==0) nums.size() - 1 == 4294967295...
		// for the res of nums.size() is a size_t type. unsigned int...
		for (int i = 0; i < n - 1; i++) {
			if (nums[i] == INT_MAX)continue;
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[j] == INT_MAX)continue;
				if (nums[j] == nums[i]) {
					nums[j] = INT_MAX;
				}
			}
		}
		int k = 0;
		for (int i = 0; i < n; i++) {
			if (nums[i] != INT_MAX) {
				nums[k++] = nums[i];
			}
		}
		return k;
	}
};

// ----------------------------- 24ms...----------- speedup to 16ms..------------
#include<iostream>
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int number = 1;
		for (int i = 1; i<nums.size(); i++) {
			if (nums[i] != nums[i - 1]) {
				nums[number] = nums[i];
				number++;
			}
		}
		return number;
	}
};

// -------------------------------------- 16ms...-------- try:36ms..----------------
class Solution {
public:
	int removeDuplicates(std::vector<int>& nums) {
		int len = nums.size();
		int res = 0;
		if (len == 0 || len == 1) return len;
		for (int i = 0; i < len; ++i) {
			if (i == 0) res++;
			else {
				if (nums[i] == nums[i - 1]) continue;
				else {
					nums[res] = nums[i];
					res++;
				}
			}
		}
		return res;
	}
};


/*
����һ��δ������������飬�ҳ�����û�г��ֵ���С����������

ʾ�� 1: ����: [1,2,0] ���: 3
ʾ�� 2: ����: [3,4,-1,1] ���: 2
ʾ�� 3: ����: [7,8,9,11,12] ���: 1

˵��: ����㷨��ʱ�临�Ӷ�ӦΪO(n)������ֻ��ʹ�ó�������Ŀռ䡣
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
��������Ľⷨ����O(1)�Ŀռ临�Ӷȣ�����������Ҫ����һ�ֽⷨ��
��Ȼ���ܽ����µ����飬��ô����ֻ�ܸ���ԭ�����飬
���ǵ�˼·�ǰ�1���������һ��λ��nums[0]��2���ڵڶ���λ��nums[1]��
����Ҫ��nums[i]����nums[nums[i] - 1]�ϣ���ô���Ǳ����������飬
���nums[i] != i + 1, ��nums[i]Ϊ�����Ҳ�����n��
����nums[i]������nums[nums[i] - 1]�Ļ������ǽ�����λ�õ����������������������ֱ��������
��������ٱ���һ�����飬�����Ӧλ���ϵ�������ȷ�򷵻���ȷ����.
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

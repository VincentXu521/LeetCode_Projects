/*P1:
����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ�����������������������ǵ������±ꡣ
����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ��㲻���ظ��������������ͬ����Ԫ�ء�
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
/*
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��

ʾ��: ����: [0,1,0,2,1,0,1,3,2,1,2,1] , ���: 6
*/


#include<vector>
#include<map>
using namespace std;


class Solution {
public:
	int trap(vector<int>& height) {
		map<int, int> max_value;
		int n = height.size();
		if ( n< 3)return 0;
		if (height[0] > height[1])max_value[0] = 1;
		if (height[n - 1] > height[n - 2])max_value[n - 1] = 1;
		for (int i = 1; i < n-1; i++) {
			if (height[i] >= height[i - 1] && height[i] >= height[i + 1])max_value[i] = 1;
		}
	}
};
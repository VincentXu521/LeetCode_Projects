/*
���� n ���Ǹ����� a1��a2��...��an��ÿ�������������е�һ���� (i, ai) ��
�������ڻ� n ����ֱ�ߣ���ֱ�� i �������˵�ֱ�Ϊ (i, ai) �� (i, 0)��
�ҳ����е������ߣ�ʹ�������� x �Ṳͬ���ɵ�����������������ˮ��
˵�����㲻����б�������� n ��ֵ����Ϊ 2��
*/

#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

static const auto __ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

// ---------------------------------------- ��ʱ ---------------------------------------
class Solution {
public:
	int maxArea(vector<int>& height) {
		// max(min(ai, aj) * (j - i))
		vector<int> area;
		for (int i = 0; i < height.size(); i++) {
			for (int j = 0; j < height.size(); j++) {
				area.push_back(min(height[i], height[j])*(j - i));
			}
		}
		sort(area.begin(), area.end());
		int res = *prev(area.end());  // equal to" int res = area.at(area.size()-1);"
		return res;
	}
};


// ------------------------------ ��ʱ -- still ���� ------------ O(N*N) ----------------
class Solution {
public:
	int maxArea(vector<int>& height) {
		// max(min(ai, aj) * (j - i))
		int maxA = 0;
		for (int i = 0; i < height.size(); i++) {
			for (int j = 0; j < height.size(); j++) {
				maxA = max(maxA, min(height[i], height[j])*(j - i));
			}
		}
		return maxA;
	}
};

// -------------------- ˫ָ�뷨 ---------- O(N) --------------------------
//�궨�庯��ʱ,���ܰ�����������,�ÿ����ַ���,���Դ��������ַ���,ע�����ŵ�����,or���׳���.
//#define MAX(x, y) x>y?x:y
//#define MIN(x, y) x<y?x:y
class Solution {
public:
	int maxArea(vector<int>& height) {
		int maxarea = 0, l = 0, r = height.size() - 1;
		while (l < r) {
			maxarea = max(maxarea, min(height[l], height[r])*(r - l));
			if (height[l] < height[r])
				l++;
			else
				r--;
		}
		return maxarea;
	}
};
// ��ȼ����ˣ���ȵļ��ٲ������塣�뼺������

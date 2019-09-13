/*
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��

ʾ��: ����: [0,1,0,2,1,0,1,3,2,1,2,1] , ���: 6
*/


#include<vector>

#define MIN(a,b) (a>b?b:a)
#define MAX(a,b) (a<b?b:a)

using namespace std;

// Solution 1: count by rol one by one;
class Solution {
public:
	int trap(vector<int>& height) {

		int sum = 0;
		// int(height.size() - 1) cannot be replaced by height.size() - 1
		// ע���������ͣ��޷��ŵ�0��ȥ1���ܱ�ɸ�������Ϊ max unsigned int��
		for (int i = 1; i < int(height.size() - 1); i++) {

			int curr = height.at(i);
			int max_left = curr;
			int max_right = curr;

			// the max_value at left of curr
			for (int j = i - 1; j >= 0; j--) {
				if (height.at(j) > max_left) {
					max_left = height.at(j);
				}
			}
			// the max_value at right of curr
			for (int j = i + 1; j < height.size(); j++) {
				if (height.at(j) > max_right) {
					max_right = height.at(j);
				}
			}
			// min value of max_left and max_right
			int min = MIN(max_left, max_right);

			// add the water at current col
			if (min > curr) {
				sum += (min - curr);
			}

		}
		return sum;
	}
};


// Solution 2:��ִ����ʱ : 4 ms, C++ �ύ�л���98.22%���ڴ����� :9 MB, C++ �ύ�л���94.05%��
// Mine: ���ݹ飩;
class Solution {
public:
	int trap(vector<int>& height) {

		// �ٳ�һЩ���������
		if (height.size() < 2)return 0;

		int sum = cal_water(0, height.size() - 1, height);

		return sum;
	}

	// �����������֮���ˮ��(�ݹ�)��-> �ܵ�ˮ����
	int cal_water(int s, int e, vector<int>& height) {

		int firstHigh = 0;
		int firstIndex = 0;
		int secondHigh = 0;
		int secondIndex = 0;
		int sum = 0;

		for (unsigned int i = s; i <= e; i++) {
			if (height.at(i) > firstHigh) {
				firstHigh = height.at(i);
				firstIndex = i;
			}
		}

		for (unsigned int i = s; i <= e; i++) {
			if (height.at(i) > secondHigh && i != firstIndex) {
				secondHigh = height.at(i);
				secondIndex = i;
			}
		}

		if (firstIndex > secondIndex)swap(firstIndex, secondIndex);
		if (secondHigh != 0) {
			// ������ģ�
			sum = (secondIndex - firstIndex - 1)*secondHigh - sum_pillar(firstIndex, secondIndex, height);
			sum += cal_water(s, firstIndex, height) + cal_water(secondIndex, e, height);
		}

		return sum;
	}

	// ���㣨s, e��֮������ռ�õ�λ�ã�
	int sum_pillar(int s, int e, vector<int>& height) {

		int sum = 0;

		for (unsigned int i = s + 1; i < e; i++) {
			sum += height.at(i);
		}

		return sum;
	}
};



// Solution 3(˫ָ�뷨)������: �������ڿ�����˭С˭�ȿ�����ʱ�临�Ӷ�O(n),�ռ临�Ӷ�(1);
class Solution {

public:

	int trap(vector<int>& A) {
		int n = A.size();
		int left = 0; int right = n - 1;
		int res = 0;
		int maxleft = 0, maxright = 0;
		while (left <= right) {
			if (A[left] <= A[right]) {
				if (A[left] >= maxleft) maxleft = A[left];
				else res += maxleft - A[left];
				left++;
			}
			else {
				if (A[right] >= maxright) maxright = A[right];
				else res += maxright - A[right];
				right--;
			}
		}
		return res;
	}
};

// BEST: OR: 0ms;8.9M;
// tql�����ɣ����lower��level�õ�һ����
class Solution {
public:
	int trap(vector<int>& height) {
		int l = 0, r = height.size() - 1, level = 0, res = 0;
		while (l < r) {
			int lower = height[(height[l] < height[r]) ? l++ : r--];
			level = MAX(level, lower);
			res += level - lower;
		}
		return res;
	}
};


#include<stack>
// Solution 4(ջ): 
/*
������ջ����ÿ��ǽ��
������ǽ�ĸ߶ȵ�ʱ�������ǰ�߶�С��ջ����ǽ�߶ȣ�˵��������л�ˮ�����ǽ�ǽ�ĸ߶ȵ��±���ջ��
�����ǰ�߶ȴ���ջ����ǽ�ĸ߶ȣ�˵��֮ǰ�Ļ�ˮ������ͣ�£����ǿ��Լ������ж��ٻ�ˮ�ˡ�
�����꣬�Ͱѵ�ǰ��ǽ������ջ����Ϊ�µĻ�ˮ��ǽ��
�����ԭ����ǣ�

1. ��ǰ�߶�С�ڵ���ջ���߶ȣ���ջ��ָ����ơ�

2. ��ǰ�߶ȴ���ջ���߶ȣ���ջ���������ǰǽ��ջ����ǽ֮��ˮ�Ķ��٣�Ȼ����㵱ǰ�ĸ߶Ⱥ���ջ�ĸ߶ȵĹ�ϵ��
�ظ��� 2 ����ֱ����ǰǽ�ĸ߶Ȳ�����ջ���߶Ȼ���ջ�գ�Ȼ��ѵ�ǰǽ��ջ��ָ����ơ�

���ߣ�windliang
���ӣ�https://leetcode-cn.com/problems/trapping-rain-water/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-8/

*/
class Solution {
public:
	int trap(vector<int>& height) {
		int sum = 0;
		stack<int> stack;
		int current = 0;
		while (current < height.size()) {
			//���ջ���ղ��ҵ�ǰָ��ĸ߶ȴ���ջ���߶Ⱦ�һֱѭ��
			while (!stack.empty() && height[current] > height[stack.top()]) {
				int h = height[stack.top()]; //ȡ��Ҫ��ջ��Ԫ��
				stack.pop(); //��ջ
				if (stack.empty()) { // ջ�վͳ�ȥ
					break;
				}
				int distance = current - stack.top() - 1; //����ǽ֮ǰ�ľ��롣
				int min = MIN(height[stack.top()], height[current]);
				sum = sum + distance * (min - h);
			}
			stack.push(current); //��ǰָ���ǽ��ջ
			current++; //ָ�����
		}
		return sum;
	}
};

// OR:
class Solution {
public:
	int trap(vector<int>& height) {
		stack<int> st;
		int i = 0, res = 0, n = height.size();
		while (i < n) {
			if (st.empty() || height[i] <= height[st.top()]) {
				st.push(i++);
			}
			else {
				int t = st.top(); st.pop();
				if (st.empty()) continue;
				res += (MIN(height[i], height[st.top()]) - height[t]) * (i - st.top() - 1);
			}
		}
		return res;
	}
};


// ��̬�滮��
class Solution {
public:
	int trap(vector<int>& height) {
		int res = 0, mx = 0, n = height.size();
		vector<int> dp(n, 0);
		for (int i = 0; i < n; ++i) {
			dp[i] = mx;
			mx = MAX(mx, height[i]);
		}
		mx = 0;
		for (int i = n - 1; i >= 0; --i) {
			dp[i] = MIN(dp[i], mx);
			mx = MAX(mx, height[i]);
			if (dp[i] > height[i]) res += dp[i] - height[i];
		}
		return res;
	}
};



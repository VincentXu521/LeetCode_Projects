/*
����һ���Ǹ��������飬�����λ������ĵ�һ��λ�á�
�����е�ÿ��Ԫ�ش������ڸ�λ�ÿ�����Ծ����󳤶ȡ�
���Ŀ����ʹ�����ٵ���Ծ����������������һ��λ�á�

ʾ��:
����: [2,3,1,1,4]
���: 2
����: �������һ��λ�õ���С��Ծ���� 2��
���±�Ϊ 0 �����±�Ϊ 1 ��λ�ã��� 1 ����Ȼ���� 3 ��������������һ��λ�á�

˵��:
���������ǿ��Ե�����������һ��λ�á�

https://www.cnblogs.com/grandyang/p/4373533.html
*/

#include<vector>
#define MAX(a,b) a>b?a:b
using namespace std;


// Method 1:
class Solution {
public:
	int jump(vector<int>& nums) {
		// cur��pre�ֱ������浱ǰ���ܵ������Զλ�ú�֮ǰ�ܵ������Զλ��;
		int res = 0, n = nums.size(), i = 0, cur = 0;
		while (cur < n - 1) {
			++res;
			int pre = cur;
			for (; i <= pre; ++i) {
				cur = MAX(cur, i + nums[i]);
			}
			if (pre == cur) return -1; // May not need this. (fail to arrive at the end)
		}
		return res;
	}
};


// Method 2:
/* copy:
* We use "last" to keep track of the maximum distance that has been reached
* by using the minimum steps "ret", whereas "curr" is the maximum distance
* that can be reached by using "ret+1" steps. Thus,
* curr = max(i+A[i]) where 0 <= i <= last.
*/
class Solution {
public:
	int jump(int A[], int n) {
		int ret = 0;
		int last = 0;
		int curr = 0;
		for (int i = 0; i < n; ++i) {
			if (i > last) {
				last = curr;
				++ret;
			}
			curr = MAX(curr, i + A[i]);
		}

		return ret;
	}
};


// Method 3: ��2�Ż���(���и���δ�þ��裬���������˼·����ͼ)
class Solution {
public:
	int jump(vector<int>& nums) {
		// cur�ǵ�ǰ�ܵ������Զλ�ã�last����һ���ܵ������Զλ��;
		int res = 0, n = nums.size(), last = 0, cur = 0;
		for (int i = 0; i < n - 1; ++i) {
			cur = MAX(cur, i + nums[i]);
			if (i == last) {
				last = cur;
				++res;
				if (cur >= n - 1) break;//����ע�͵�;
			}
		}
		return res;
	}
};
// in leetcode editor, i've type the code once;


// Method 4: BFS:
/*
@zeeng :
��һֱû̫���greedy������greedy�����ر����浫�ǳ�����֪����ô֤����greedy�������ľ������Ž⣬
�������Լ����벻����ô֤�������ķ����������õ���res������С������
Ȼ�������������BFS��˼·���ġ�������һ��ͼ��Ѱ�����·����
һ��������һ��node�������ھӾ�������reach������Щ�㡣���д�����Ĵ����greedy��ࡣ
*/

class Solution {
public:
	int jump(vector<int>& nums) {
		if (nums.size() <= 1) return 0;
		int curMax = 0; // ���һ������һ����
		int level = 0, i = 0;
		while (i <= curMax) { // i��curMax����˵�����ܼ����ߵ���һ����
			int furthest = curMax; // �����һ����Զ���Ķ�
			for (; i <= curMax; i++) {
				furthest = MAX(furthest, nums[i] + i);
				if (furthest >= nums.size() - 1) return level + 1;
			}
			level++;
			curMax = furthest;
		}
		return -1;
	}
};

/*
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。
*/

#include<vector>
using namespace std;

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		vector<int> newVector;
		int i = 0, j = 0;
		while (i < nums1.size() && j < nums2.size()) {
			if (nums1.at(i) < nums2.at(j)) newVector.push_back(nums1.at(i++));
			else newVector.push_back(nums2.at(j++));
		}
		if (i == nums1.size())newVector.insert(newVector.end(), nums2.begin() + j, nums2.end());
		else newVector.insert(newVector.end(), nums1.begin() + i, nums1.end());
		if (newVector.size() % 2 != 0)return (double)newVector.at(newVector.size() / 2);
		else return ((newVector.at(newVector.size() / 2) + newVector.at(newVector.size() / 2 - 1))) / 2.0;
	}
};

//------------------------------------ 官方正解 ----------------------------------------------------------
// 时间复杂度：O(log⁡(min(m, n)))
#include<algorithm>
class Solution_O_log_min_m_n {
	double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
		int m = A.size();
		int n = B.size();
		if (m > n) { // to ensure m<=n
			vector<int> temp = A; A = B; B = temp;
			int tmp = m; m = n; n = tmp;
		}
		int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
		while (iMin <= iMax) {
			int i = (iMin + iMax) / 2;
			int j = halfLen - i;
			if (i < iMax && B[j - 1] > A[i]) {
				iMin = i + 1; // i is too small
			}
			else if (i > iMin && A[i - 1] > B[j]) {
				iMax = i - 1; // i is too big
			}
			else { // i is perfect
				int maxLeft = 0;
				if (i == 0) { maxLeft = B[j - 1]; }
				else if (j == 0) { maxLeft = A[i - 1]; }
				else { maxLeft = max(A[i - 1], B[j - 1]); }
				if ((m + n) % 2 == 1) { return maxLeft; }

				int minRight = 0;
				if (i == m) { minRight = B[j]; }
				else if (j == n) { minRight = A[i]; }
				else { minRight = min(B[j], A[i]); }

				return (maxLeft + minRight) / 2.0;
			}
		}
		return 0.0;
	}
};


// ----------------------------用时 32 ms why? 明明是在下方16ms的基础上简化了代码。。。------------------
#include<iostream>
static const auto _ = []() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	return nullptr;
}();


class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size();
		int n = nums2.size();
		if (m == 0) return n % 2 == 0 ? (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0 : 1.0*nums2[n / 2];
		if (n == 0) return m % 2 == 0 ? (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0 : 1.0*nums1[m / 2];
		vector<int> res;
		int i = 0, j = 0;
		while (i<m&&j<n) {
			if (nums1[i] < nums2[j]) res.push_back(nums1[i++]);
			else res.push_back(nums2[j++]);
		}
		while (i<m) res.push_back(nums1[i++]);
		while (j<n) res.push_back(nums2[j++]);

		int len = m + n;

		return  len % 2 == 0 ? (res[len / 2 - 1] + res[len / 2]) / 2.0 : 1.0*res[len / 2];
	}
};


//----------------------------- 执行用时为 16 ms 的范例 --------------------------------------------------
static const auto _ = []() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	return nullptr;
}();


class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size();
		int n = nums2.size();
		if (m == 0)
			return n % 2 == 0 ? (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0 : 1.0*nums2[n / 2];
		if (n == 0)
			return m % 2 == 0 ? (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0 : 1.0*nums1[m / 2];
		vector<int> res;
		int i = 0, j = 0;
		while (i<m&&j<n) {
			if (nums1[i] < nums2[j]) {
				res.push_back(nums1[i]);
				i++;
			}
			else {
				res.push_back(nums2[j]);
				j++;
			}
		}
		while (i<m) {
			res.push_back(nums1[i]);
			i++;
		}
		while (j<n) {
			res.push_back(nums2[j]);
			j++;
		}
		int len = m + n;

		return  len % 2 == 0 ? (res[len / 2 - 1] + res[len / 2]) / 2.0 : 1.0*res[len / 2];
	}
};
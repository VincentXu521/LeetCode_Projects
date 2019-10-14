/*
Implement pow(x, n), which calculates x raised to the power n(xn).
Example 1:
Input: 2.00000, 10
Output: 1024.00000
Example 2:
Input: 2.10000, 3
Output: 9.26100
Example 3:
Input: 2.00000, -2
Output: 0.25000
Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
Note:
-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]

https://www.cnblogs.com/grandyang/p/4383775.html
*/


//Sulotion 1: recursion. 4_8.3
class Solution {
public:
	double myPow(double x, int n) {
		if (n == 0) return 1;

		//if (x == 0)return 0;
		//if (x == 1)return 1;

		double half = myPow(x, n / 2);
		if (n % 2 == 0) return half * half;
		if (n > 0) return half * half * x;
		return half * half / x;
	}
};


//Solution 2: iteration. 0_8.3
class Solution {
public:
	double myPow(double x, int n) {
		double res = 1.0;
		for (int i = n; i != 0; i /= 2) {
			if (i % 2 != 0) res *= x;
			x *= x;
		}
		return n < 0 ? 1 / res : res;
	}
};



//Sulotion 3: recursion.Mine: 0_8.2
class Solution {
public:
	double myPow(double x, int n) {
		if (n == 0) return 1;
		if (n == 1) return x;
		if (n == 2) return x*x;

		if (n % 2 == 0) return myPow(myPow(x, n / 2), 2);
		if (n > 0) return myPow(myPow(x, n / 2), 2) * x;
		return myPow(myPow(x, n / 2), 2) / x;
	}
};

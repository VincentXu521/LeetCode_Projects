#include<string>
#include<map>
#include<iostream>

using namespace std;

static const auto _ = []()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return nullptr;
}();

// --------------------------------- Mine 32ms --------------------------------------

class Solution {
private:
	map<string, int> mp = {
		{ "I", 1 },
		{ "V", 5 },
		{ "X", 10 },
		{ "L", 50 },
		{ "C", 100 },
		{ "D", 500 },
		{ "M", 1000 },
		{ "IV", 4 },
		{ "IX", 9 },
		{ "XL", 40 },
		{ "XC", 90 },
		{ "CD", 400 },
		{ "CM", 900 }
	};
public:
	int romanToInt(string s) {
		// 前序:
		int res = 0;
		string firstTwo;
		while (!s.empty()) {
			firstTwo = s.substr(0, 2);
			if (mp.find(firstTwo) != mp.end()) {
				res += mp[firstTwo];
				s = (s.size() > 1 ? s.substr(2) : s.substr(1));
			}
			else if (mp.find(s.substr(0, 1)) != mp.end()) {
				res += mp[s.substr(0, 1)];
				s = s.substr(1);
			}
		}
		return res;
	}
};


// ----------------------------------------- 20ms example ------------------------------
static const auto io_speed_up = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}();

class Solution {
public:
	int romanToInt(string s) {
		// 后序：
		if (s == "") {
			return 0;
		}
		int sum = 0;
		int max = 0;
		int len = s.length();

		for (int i = len - 1; i >= 0; i--) {
			int val;
			switch (s[i]) {
			case 'I': val = 1; break;
			case 'V': val = 5; break;
			case 'X': val = 10; break;
			case 'L': val = 50; break;
			case 'C': val = 100; break;
			case 'D': val = 500; break;
			case 'M': val = 1000; break;
			}
			// 这个规律发现得好！大则加，小则减。
			if (val >= max) {
				sum += val;
				max = val;
			}
			else {
				sum -= val;
			}
		}
		return sum;
	}
};
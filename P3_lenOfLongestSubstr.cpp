/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
*/
#include<map>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		map<char, int> charMap;
		int res = 0;
		for (int i = -1, j = 0; j < s.size(); j++) {
			if (charMap.find(s[j]) != charMap.end()) i = max(i, charMap[s[j]]);
			charMap[s[j]] = j;
			res = max(res, j - i);
		}
		return res;
	}
};
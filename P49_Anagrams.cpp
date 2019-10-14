/*
Given an array of strings, group anagrams together.
Example:
Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
["ate","eat","tea"],
["nat","tan"],
["bat"]
]
Note:
All inputs will be in lowercase.
The order of your output does not matter.

https://www.cnblogs.com/grandyang/p/4385822.html
*/


#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;


//solution 1: ����һ�㣬˼·��������������.
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> m;
		for (string str : strs) {
			string t = str;
			sort(t.begin(), t.end());
			m[t].push_back(str);
		}
		for (auto a : m) {
			res.push_back(a.second);
		}
		return res;
	}
};


//solution 2:
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> m;
		for (string str : strs) {
			vector<int> cnt(26, 0);
			string t = "";
			for (char c : str) ++cnt[c - 'a'];
			for (int d : cnt) t += to_string(d) + "/";
			m[t].push_back(str);
		}
		for (auto a : m) {
			res.push_back(a.second);
		}
		return res;
	}
};


//solution 3: ��1���Ż���(good)
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, int> m;
		vector<vector<string>> res;
		for (string s : strs) {
			string x(s);
			sort(x.begin(), x.end());
			if (!m.count(x)) {
				m[x] = res.size();
				res.push_back({});
			}
			res[m[x]].push_back(s);
		}
		return res;
	}
};


//solution 4: ��2���Ż�����2,4Ч������1,3��
/*key������Ӌ��
���� ԭ����1/0/0/0/1/0/0/0/0/0/0/0/0/0/0/0/0/0/0/1/0/0/0/0/0/0/
����׃��a1e1t1
key׃���� �ٶȑ�ԓ�ǿ���������ȥ
*/
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> m;
		for (string str : strs) {
			vector<int> cnt(26, 0);
			string t = "";
			for (char c : str) ++cnt[c - 'a'];
			for (int i = 0; i < 26; i++)
				if (cnt[i] != 0)
					t += string(1, i + 'a') + to_string(cnt[i]);
			m[t].push_back(str);
		}
		for (auto a : m) {
			res.push_back(a.second);
		}
		return res;
	}
};

/*
给定一个字符串 s 和一些长度相同的单词 words。在 s 中找出可以恰好串联 words 中所有单词的子串的起始位置。
注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

示例 1:
输入:
s = "barfoothefoobarman",
words = ["foo","bar"]
输出: [0,9]
解释: 从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。

示例 2:
输入:
s = "wordgoodstudentgoodword",
words = ["word","student"]
输出: []
*/

#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

// ------------------- speedup...-------------------------------------
#include<iostream>
static int _ = []() {ios::sync_with_stdio(false);cin.tie(nullptr);return 0;}();


// -------------- O(N) ------------- copy...------------------------------
/*
这道题还有一种O(n)时间复杂度的解法，设计思路非常巧妙，但是感觉很难想出来，
博主目测还未到达这种水平。这种方法不再是一个字符一个字符的遍历，而是一个词一个词的遍历，
比如根据题目中的例子，字符串s的长度n为18，words数组中有两个单词(cnt=2)，每个单词的长度len均为3，
那么遍历的顺序为0，3，6，8，12，15，然后偏移一个字符1，4，7，9，13，16，
然后再偏移一个字符2，5，8，10，14，17，这样就可以把所有情况都遍历到，
我们还是先用一个哈希表m1来记录words里的所有词，然后我们从0开始遍历，用left来记录左边界的位置，
count表示当前已经匹配的单词的个数。然后我们一个单词一个单词的遍历，如果当前遍历的到的单词t在m1中存在，
那么我们将其加入另一个哈希表m2中，如果在m2中个数小于等于m1中的个数，那么我们count自增1，
如果大于了，那么需要做一些处理，比如下面这种情况, s = barfoofoo, words = {bar, foo, abc}, 
我们给words中新加了一个abc，目的是为了遍历到barfoo不会停止，那么当遍历到第二foo的时候, m2[foo]=2, 
而此时m1[foo]=1，这是后已经不连续了，所以我们要移动左边界left的位置，我们先把第一个词t1=bar取出来，
然后将m2[t1]自减1，如果此时m2[t1]<m1[t1]了，说明一个匹配没了，那么对应的count也要自减1，
然后左边界加上个len，这样就可以了。如果某个时刻count和cnt相等了，说明我们成功匹配了一个位置，
那么将当前左边界left存入结果res中，此时去掉最左边的一个词，同时count自减1，左边界右移len，继续匹配。
如果我们匹配到一个不在m1中的词，那么说明跟前面已经断开了，我们重置m2，count为0，左边界left移到j+len，
参见代码如下：
*/
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		if (s.empty() || words.empty()) return {};
		vector<int> res;
		int n = s.size(), cnt = words.size(), len = words[0].size();
		unordered_map<string, int> m1;
		for (string w : words) ++m1[w];
		for (int i = 0; i < len; ++i) {
			int left = i, count = 0;
			unordered_map<string, int> m2;
			for (int j = i; j <= n - len; j += len) {
				string t = s.substr(j, len);
				if (m1.count(t)) {
					++m2[t];
					if (m2[t] <= m1[t]) {
						++count;
					}
					else {
						while (m2[t] > m1[t]) {
							string t1 = s.substr(left, len);
							--m2[t1];
							if (m2[t1] < m1[t1]) --count;
							left += len;
						}
					}
					if (count == cnt) {
						res.push_back(left);
						--m2[s.substr(left, len)];
						--count;
						left += len;
					}
				}
				else {
					m2.clear();
					count = 0;
					left = j + len;
				}
			}
		}
		return res;
	}
};

// few codes, fast speed, study this...
// -------------- O(N) -------------- copy...-----------------------------
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		if (s.empty() || words.empty()) return {};
		int n = s.size(), len = words[0].size(), total = words.size(), cnt = total;
		vector<int> res;
		unordered_map<string, int> counts;
		for (string s : words) counts[s]++;
		for (int i = 0; i < len; i++) {
			unordered_map<string, int> wordcnt = counts;
			cnt = total;
			for (int j = i; j + len <= n; j += len) {
				string cur = s.substr(j, len);
				if (wordcnt[cur]-- > 0) cnt--;
				if (j - total*len >= 0) {
					string out = s.substr(j - total*len, len); // the word out side of current sliding window
					if (++wordcnt[out] > 0) cnt++;
				}
				if (cnt == 0) res.push_back(j - (total - 1)*len);
			}
		}
		return res;
	}
};

//----------------------------- copy...---------- time cost a lot..------------------
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> res;
		if (s.empty() || words.empty()) return res;
		int n = words.size(), m = words[0].size();
		unordered_map<string, int> m1;
		for (auto &a : words) ++m1[a];
		for (int i = 0; i <= (int)s.size() - n * m; ++i) {
			unordered_map<string, int> m2;
			int j = 0;
			for (j = 0; j < n; ++j) {
				string t = s.substr(i + j * m, m);
				if (m1.find(t) == m1.end()) break;
				++m2[t];
				if (m2[t] > m1[t]) break;
			}
			if (j == n) res.push_back(i);
		}
		return res;
	}
};


/*
map和unordered_map的差别
还不知道或者搞不清unordered_map和map是什么的，请见：
http://blog.csdn.net/billcyj/article/details/78065438
需要引入的头文件不同
map: #include < map >
unordered_map: #include < unordered_map >
内部实现机理不同
map： 
map内部实现了一个红黑树（红黑树是非严格平衡二叉搜索树，而AVL是严格平衡二叉搜索树），
红黑树具有自动排序的功能，因此map内部的所有元素都是有序的，红黑树的每一个节点都代表着map的一个元素。
因此，对于map进行的查找，删除，添加等一系列的操作都相当于是对红黑树进行的操作。
map中的元素是按照二叉搜索树（又名二叉查找树、二叉排序树，
特点就是左子树上所有节点的键值都小于根节点的键值，右子树所有节点的键值都大于根节点的键值）存储的，
使用中序遍历可将键值按照从小到大遍历出来。

unordered_map: 
unordered_map内部实现了一个哈希表（也叫散列表，
通过把关键码值映射到Hash表中一个位置来访问记录，查找的时间复杂度可达到O(1)，其在海量数据处理中有着广泛应用）。
因此，其元素的排列顺序是无序的。

优缺点以及适用处

map：

优点：
有序性，这是map结构最大的优点，其元素的有序性在很多应用中都会简化很多的操作
红黑树，内部实现一个红黑书使得map的很多操作在lgn的时间复杂度下就可以实现，因此效率非常的高

缺点： 空间占用率高，因为map内部实现了红黑树，虽然提高了运行效率，
但是因为每一个节点都需要额外保存父节点、孩子节点和红/黑性质，使得每一个节点都占用大量的空间

适用处：对于那些有顺序要求的问题，用map会更高效一些

unordered_map：

优点： 因为内部实现了哈希表，因此其查找速度非常的快
缺点： 哈希表的建立比较耗费时间
适用处：对于查找问题，unordered_map会更加高效一些，因此遇到查找问题，常会考虑一下用unordered_map

总结：

内存占有率的问题就转化成红黑树 VS hash表 , 还是unorder_map占用的内存要高。
但是unordered_map执行效率要比map高很多
对于unordered_map或unordered_set容器，其遍历顺序与创建该容器时输入的顺序不一定相同，因为遍历是按照哈希表从前往后依次遍历的

原文：https://blog.csdn.net/BillCYJ/article/details/78985895
*/
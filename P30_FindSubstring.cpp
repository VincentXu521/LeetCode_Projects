/*
����һ���ַ��� s ��һЩ������ͬ�ĵ��� words���� s ���ҳ�����ǡ�ô��� words �����е��ʵ��Ӵ�����ʼλ�á�
ע���Ӵ�Ҫ�� words �еĵ�����ȫƥ�䣬�м䲻���������ַ���������Ҫ���� words �е��ʴ�����˳��

ʾ�� 1:
����:
s = "barfoothefoobarman",
words = ["foo","bar"]
���: [0,9]
����: ������ 0 �� 9 ��ʼ���Ӵ��ֱ��� "barfoo" �� "foobar" ��
�����˳����Ҫ, [9,0] Ҳ����Ч�𰸡�

ʾ�� 2:
����:
s = "wordgoodstudentgoodword",
words = ["word","student"]
���: []
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
����⻹��һ��O(n)ʱ�临�ӶȵĽⷨ�����˼·�ǳ�������Ǹо������������
����Ŀ�⻹δ��������ˮƽ�����ַ���������һ���ַ�һ���ַ��ı���������һ����һ���ʵı�����
���������Ŀ�е����ӣ��ַ���s�ĳ���nΪ18��words����������������(cnt=2)��ÿ�����ʵĳ���len��Ϊ3��
��ô������˳��Ϊ0��3��6��8��12��15��Ȼ��ƫ��һ���ַ�1��4��7��9��13��16��
Ȼ����ƫ��һ���ַ�2��5��8��10��14��17�������Ϳ��԰������������������
���ǻ�������һ����ϣ��m1����¼words������дʣ�Ȼ�����Ǵ�0��ʼ��������left����¼��߽��λ�ã�
count��ʾ��ǰ�Ѿ�ƥ��ĵ��ʵĸ�����Ȼ������һ������һ�����ʵı����������ǰ�����ĵ��ĵ���t��m1�д��ڣ�
��ô���ǽ��������һ����ϣ��m2�У������m2�и���С�ڵ���m1�еĸ�������ô����count����1��
��������ˣ���ô��Ҫ��һЩ�������������������, s = barfoofoo, words = {bar, foo, abc}, 
���Ǹ�words���¼���һ��abc��Ŀ����Ϊ�˱�����barfoo����ֹͣ����ô���������ڶ�foo��ʱ��, m2[foo]=2, 
����ʱm1[foo]=1�����Ǻ��Ѿ��������ˣ���������Ҫ�ƶ���߽�left��λ�ã������Ȱѵ�һ����t1=barȡ������
Ȼ��m2[t1]�Լ�1�������ʱm2[t1]<m1[t1]�ˣ�˵��һ��ƥ��û�ˣ���ô��Ӧ��countҲҪ�Լ�1��
Ȼ����߽���ϸ�len�������Ϳ����ˡ����ĳ��ʱ��count��cnt����ˣ�˵�����ǳɹ�ƥ����һ��λ�ã�
��ô����ǰ��߽�left������res�У���ʱȥ������ߵ�һ���ʣ�ͬʱcount�Լ�1����߽�����len������ƥ�䡣
�������ƥ�䵽һ������m1�еĴʣ���ô˵����ǰ���Ѿ��Ͽ��ˣ���������m2��countΪ0����߽�left�Ƶ�j+len��
�μ��������£�
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
map��unordered_map�Ĳ��
����֪�����߸㲻��unordered_map��map��ʲô�ģ������
http://blog.csdn.net/billcyj/article/details/78065438
��Ҫ�����ͷ�ļ���ͬ
map: #include < map >
unordered_map: #include < unordered_map >
�ڲ�ʵ�ֻ���ͬ
map�� 
map�ڲ�ʵ����һ���������������Ƿ��ϸ�ƽ���������������AVL���ϸ�ƽ���������������
����������Զ�����Ĺ��ܣ����map�ڲ�������Ԫ�ض�������ģ��������ÿһ���ڵ㶼������map��һ��Ԫ�ء�
��ˣ�����map���еĲ��ң�ɾ������ӵ�һϵ�еĲ������൱���ǶԺ�������еĲ�����
map�е�Ԫ���ǰ��ն��������������������������������������
�ص���������������нڵ�ļ�ֵ��С�ڸ��ڵ�ļ�ֵ�����������нڵ�ļ�ֵ�����ڸ��ڵ�ļ�ֵ���洢�ģ�
ʹ����������ɽ���ֵ���մ�С�������������

unordered_map: 
unordered_map�ڲ�ʵ����һ����ϣ��Ҳ��ɢ�б�
ͨ���ѹؼ���ֵӳ�䵽Hash����һ��λ�������ʼ�¼�����ҵ�ʱ�临�ӶȿɴﵽO(1)�����ں������ݴ��������Ź㷺Ӧ�ã���
��ˣ���Ԫ�ص�����˳��������ġ�

��ȱ���Լ����ô�

map��

�ŵ㣺
�����ԣ�����map�ṹ�����ŵ㣬��Ԫ�ص��������ںܶ�Ӧ���ж���򻯺ܶ�Ĳ���
��������ڲ�ʵ��һ�������ʹ��map�ĺܶ������lgn��ʱ�临�Ӷ��¾Ϳ���ʵ�֣����Ч�ʷǳ��ĸ�

ȱ�㣺 �ռ�ռ���ʸߣ���Ϊmap�ڲ�ʵ���˺��������Ȼ���������Ч�ʣ�
������Ϊÿһ���ڵ㶼��Ҫ���Ᵽ�游�ڵ㡢���ӽڵ�ͺ�/�����ʣ�ʹ��ÿһ���ڵ㶼ռ�ô����Ŀռ�

���ô���������Щ��˳��Ҫ������⣬��map�����ЧһЩ

unordered_map��

�ŵ㣺 ��Ϊ�ڲ�ʵ���˹�ϣ�����������ٶȷǳ��Ŀ�
ȱ�㣺 ��ϣ��Ľ����ȽϺķ�ʱ��
���ô������ڲ������⣬unordered_map����Ӹ�ЧһЩ����������������⣬���ῼ��һ����unordered_map

�ܽ᣺

�ڴ�ռ���ʵ������ת���ɺ���� VS hash�� , ����unorder_mapռ�õ��ڴ�Ҫ�ߡ�
����unordered_mapִ��Ч��Ҫ��map�ߺܶ�
����unordered_map��unordered_set�����������˳���봴��������ʱ�����˳��һ����ͬ����Ϊ�����ǰ��չ�ϣ���ǰ�������α�����

ԭ�ģ�https://blog.csdn.net/BillCYJ/article/details/78985895
*/
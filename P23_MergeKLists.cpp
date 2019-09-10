/*
合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
示例:
输入:
[
1->4->5,
1->3->4,
2->6
]
输出: 1->1->2->3->4->4->5->6
*/

#include<iostream>
#include<vector>
#include<queue>
#include<functional>  // greater<int>

using namespace std;
static const auto _=[](){ios::sync_with_stdio(false);cin.tie(nullptr);return nullptr;}();

// Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// --------------------- Mine: 24ms...87%, but time and room cost huge...---------------

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		int n = lists.size();
		if (n == 0)return NULL;
		if (n == 1)return lists.front();
		bool flag = false;
		for (int i = 0; i < n; i++) {
			if (lists.at(i)) {
				flag = true;
				break;
			}
		}
		if (flag == false)return NULL;
		ListNode *head = new ListNode(0);
		ListNode *curr = head;
		// priority_queue default state is max_heap, use greater<int> ture to min_heap.
		priority_queue<int, vector<int>, greater<int>> find_smaller;
		for (int i = 0; i < n; i++) {
			ListNode *ele = lists.at(i);
			while (ele) {
				find_smaller.push(ele->val);
				ele = ele->next;
			}
		}
		while (!find_smaller.empty()) {
			curr->val = find_smaller.top();
			find_smaller.pop();
			if (!find_smaller.empty())
				curr = (curr->next = new ListNode(0));
		}
		return head;
	}
};

// ------------------------ 20ms 范例： ---- 看看人家的最小堆，用的比你好得多-----------

// 大于号最小堆，小于号最大堆;(Attention the format of changeing cmp way...)
struct cmp {
	bool operator () (ListNode *a, ListNode *b) {
		return a->val > b->val;
	}
};

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<ListNode*, vector<ListNode*>, cmp> queue;
		for (auto x : lists)
		{
			if (x != NULL) queue.push(x);
		}
		if (queue.empty()) return NULL;
		ListNode * head = queue.top();
		ListNode * cur = queue.top();
		queue.pop();
		if (cur->next) queue.push(cur->next);
		while (!queue.empty()) {
			ListNode * tmp = queue.top();
			cur->next = tmp;
			cur = tmp;
			queue.pop();
			if (tmp->next != NULL) queue.push(tmp->next);
		}
		return head;
	}
};

// ------------------------ 16ms 范例： ---- 2->K: MergeSort Method..思路很好-----------

class Solution {
public:
	ListNode* mergeKLists(std::vector<ListNode*>& lists) {
		if (lists.size() == 0) {
			return NULL;
		}
		if (lists.size() == 1) {
			return lists[0];
		}
		if (lists.size() == 2) {
			return mergeTwoLists(lists[0], lists[1]);
		}

		ListNode* left = NULL;
		ListNode* right = NULL;
		std::vector<ListNode*>left_vec;
		std::vector<ListNode*>right_vec;

		int mid = lists.size() / 2;

		for (int i = 0; i < mid; i++) {
			left_vec.push_back(lists[i]);
		}
		left = mergeKLists(left_vec);

		for (int i = mid; i < lists.size(); i++) {
			right_vec.push_back(lists[i]);
		}
		right = mergeKLists(right_vec);

		ListNode* head = mergeTwoLists(left, right);

		return head;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode new_node(0);
		ListNode* ptr = &new_node;

		while (l1 && l2) {
			if (l1->val < l2->val) {
				ptr->next = l1;
				l1 = l1->next;
			}
			else {
				ptr->next = l2;
				l2 = l2->next;
			}
			ptr = ptr->next;
		}

		if (l1) {
			ptr->next = l1;
		}
		if (l2) {
			ptr->next = l2;
		}
		return new_node.next;
	}

};

// -------------------------------------- 2->K...-------------------------
class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if (lists.size() == 0) return NULL;
		int n = lists.size();
		while (n > 1) {
			int k = (n + 1) / 2;
			for (int i = 0; i < n / 2; ++i) {
				lists[i] = mergeTwoLists(lists[i], lists[i + k]);
			}
			n = k;
		}
		return lists[0];
	}

	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		ListNode *head = new ListNode(-1);
		ListNode *cur = head;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				cur->next = l1;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		if (l1) cur->next = l1;
		if (l2) cur->next = l2;
		return head->next;
	}
};

// ----------------------- min_heap -------------------------------------
struct cmp {
	bool operator () (ListNode *a, ListNode *b) {
		return a->val > b->val;
	}
};

class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		priority_queue<ListNode*, vector<ListNode*>, cmp> q;
		for (int i = 0; i < lists.size(); ++i) {
			if (lists[i]) q.push(lists[i]);
		}
		ListNode *head = NULL, *pre = NULL, *tmp = NULL;
		while (!q.empty()) {
			tmp = q.top();
			q.pop();
			// pre pointer is used well. make all in while loop. code beautiful...
			if (!pre) head = tmp;
			else pre->next = tmp;
			pre = tmp;
			if (tmp->next) q.push(tmp->next);
		}
		return head;
	}
};

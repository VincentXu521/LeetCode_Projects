/*
将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
示例：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
*/

#include<iostream>

using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

// Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// ------------------------------ Mine: 8ms...------------- 有空间花费 ----------------------

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1)return l2;
		if (!l2)return l1;
		ListNode *head = new ListNode(0), *curr = head;
		while (l1 && l2) {
			if (l1->val > l2->val) {
				curr->val = l2->val;
				l2 = l2->next;
			}
			else {
				curr->val = l1->val;
				l1 = l1->next;
			}
			if (l1&&l2) {
				curr->next = new ListNode(0);
				curr = curr->next;
			}
		}
		if (!l1)curr->next = l2;
		if (!l2)curr->next = l1;
		return head;
	}
};

// --------------------------------- 执行用时为 4 ms 的范例 --------- 无空间花费 ----------

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr;
		ListNode* tail = nullptr;
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;
		if (l1->val > l2->val) {
			head = l2;
			l2 = l2->next;
			tail = head;
		}
		else {
			head = l1;
			l1 = l1->next;
			tail = head;
		}
		while (l1 != nullptr || l2 != nullptr) {
			if (l1 == nullptr) {
				tail->next = l2;
				break;
			}
			else if (l2 == nullptr) {
				tail->next = l1;
				break;
			}
			else if (l1->val > l2->val) {
				tail->next = l2;
				tail = tail->next;
				l2 = l2->next;
			}
			else {
				tail->next = l1;
				tail = tail->next;
				l1 = l1->next;
			}

		}
		return head;
	}
};

// ---------------------- The one: only one new Node...--------------------------
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode *dummy = new ListNode(-1), *cur = dummy;
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
		cur->next = l1 ? l1 : l2;
		return dummy->next;
	}
};

// ----------------------------- The two: --- 递归 --------------------------
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1) return l2;
		if (!l2) return l1;
		if (l1->val < l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}
};

// -------------------------------- The three: ---------------------------------
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1) return l2;
		if (!l2) return l1;
		ListNode *head = l1->val < l2->val ? l1 : l2;
		ListNode *nonhead = l1->val < l2->val ? l2 : l1;
		head->next = mergeTwoLists(head->next, nonhead);
		return head;
	}
};

// ---------------------------- The four: only three lines...-------------------
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1 || (l2 && l1->val > l2->val)) swap(l1, l2);
		if (l1) l1->next = mergeTwoLists(l1->next, l2);
		return l1;
	}
};

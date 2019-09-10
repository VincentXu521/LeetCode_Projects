/*
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
示例: 给定 1->2->3->4, 你应该返回 2->1->4->3.

说明:
你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
*/

#include<iostream>
#include<vector>
using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();

// Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// ------------------------- Mine: 4ms...-----------------------------------------------

struct twoNodePtrs {
	ListNode *l1;
	ListNode *l2;
}typedef tNP;

class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (!head)return head;
		ListNode* curr = head;
		vector<tNP> vec_tnp;
		while (curr) {
			tNP t{ curr, curr->next };
			vec_tnp.push_back(t);
			if (!curr->next)break;
			curr = curr->next->next;
		}
		int n = vec_tnp.size();
		for (int i = 0; i < n; i++) {
			if (vec_tnp[i].l2)swapNodePtr(vec_tnp[i].l1, vec_tnp[i].l2);
		}
		// 这里有一个好大的坑，前者可以改变元素的值，后者不可以。。。
		/*
		for (tNP t : vec_tnp) {
		if (t.l2)swapNodePtr(t.l1, t.l2);
		}
		*/
		for (int i = 0; i < n - 1; i++) {
			vec_tnp[i].l2->next = vec_tnp[i + 1].l1;
		}
		if (vec_tnp[n - 1].l2)vec_tnp[n - 1].l2->next = NULL;
		return vec_tnp[0].l1;
	}
	void swapNodePtr(ListNode *&pre, ListNode *&next) {
		next = pre;
		pre = pre->next;
		pre->next = next;
	}
};

// ----------------------------- Way 1...----------------------------------
/*
这道题不算难，是基本的链表操作题，我们可以分别用递归和迭代来实现。
对于迭代实现，还是需要建立dummy节点，注意在连接节点的时候，最好画个图，以免把自己搞晕了，参见代码如下：
*/
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		ListNode *dummy = new ListNode(-1), *pre = dummy;
		dummy->next = head;
		while (pre->next && pre->next->next) {
			ListNode *t = pre->next->next;
			pre->next->next = t->next;
			t->next = pre->next;
			pre->next = t;
			pre = t->next;
		}
		return dummy->next;
	}
};
// ----------------------------- Way 2...--------------- 0ms ------------
// 递归的写法就更简洁了，实际上利用了回溯的思想，递归遍历到链表末尾，然后先交换末尾两个，然后依次往前交换：
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (!head || !head->next) return head;
		ListNode *t = head->next;
		head->next = swapPairs(head->next->next);
		t->next = head;
		return t;
	}
};

// ----------------------------- 4ms e.g. ---------------------------------
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* cur = head;
		ListNode* last = cur;
		while (cur && cur->next) {
			ListNode* temp = cur->next;
			cur->next = temp->next;
			temp->next = cur;

			if (cur == head) {
				head = temp;
			}
			else {
				last->next = temp;
			}
			last = cur;
			cur = cur->next;
		}
		return head;
	}
};

// ---------------- try 4ms ------- 0ms e.g. ----------- same method with former ----------
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL) return head;
		ListNode *p = head, *next_node, *pre_node = head;

		while (p != NULL && p->next != NULL) {
			next_node = p->next;
			p->next = next_node->next;
			next_node->next = p;
			if (pre_node == head) {
				head = next_node;
			}
			else {
				pre_node->next = next_node;
			}
			pre_node = p;
			p = p->next;
		}
		return head;
	}
};
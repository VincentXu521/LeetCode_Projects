/*
����һ���������������������ڵĽڵ㣬�����ؽ����������
ʾ��: ���� 1->2->3->4, ��Ӧ�÷��� 2->1->4->3.

˵��:
����㷨ֻ��ʹ�ó����Ķ���ռ䡣
�㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����
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
		// ������һ���ô�Ŀӣ�ǰ�߿��Ըı�Ԫ�ص�ֵ�����߲����ԡ�����
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
����ⲻ���ѣ��ǻ�������������⣬���ǿ��Էֱ��õݹ�͵�����ʵ�֡�
���ڵ���ʵ�֣�������Ҫ����dummy�ڵ㣬ע�������ӽڵ��ʱ����û���ͼ��������Լ������ˣ��μ��������£�
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
// �ݹ��д���͸�����ˣ�ʵ���������˻��ݵ�˼�룬�ݹ����������ĩβ��Ȼ���Ƚ���ĩβ������Ȼ��������ǰ������
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
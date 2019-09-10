/*
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：
给定的 n 保证是有效的。
*/

#include<iostream>

using namespace std;
static const auto _ = []() {ios::sync_with_stdio(false); cin.tie(nullptr); return nullptr; }();


// Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 
 // --------------------------- Mine: 4ms...the best...--------------------------------

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
		int len = 1;
		ListNode *head1 = head;
		while (head1->next != NULL) {
			len++;
			head1 = head1->next;
		}
		// 特殊节点：长度为 n 的链删除倒数第 n 个节点.
		if (len == n)return head->next;
		// 倒数第 n 个是正数第 m+1 个，需要操作第 m 个；
		int m = len - n;
		len = 0;
		ListNode *head2 = head;
		while (head2->next != NULL) {
			len++;
			if (len == m) {
				head2->next = head2->next->next;
				return head;
			}
			head2 = head2->next;
		}
    }
};

// -------------------------- use stack: 4ms ----------------------------------
#include<stack>
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (head == NULL || n <= 0)
			return head;
		ListNode *cur = head;
		stack<ListNode*> s;
		while (cur != NULL) {
			s.push(cur);
			cur = cur->next;
		}
		if (n>s.size())
			return head;
		int k = 0;
		while (k<n) {
			cur = s.top();
			s.pop();
			++k;
		}
		ListNode *pre = (!s.empty()) ? s.top() : NULL;
		ListNode *suc = cur->next;
		if (pre == NULL)
			head = suc;
		else
			pre->next = suc;
		return head;
	}
};

// -------------------------- 巧妙: 一次遍历 ----------------------------------------------------
/*
这道题让我们移除链表倒数第N个节点，限定n一定是有效的，即n不会大于链表中的元素总数。
还有题目要求我们一次遍历解决问题，那么就得想些比较巧妙的方法了。
比如我们首先要考虑的时，如何找到倒数第N个节点，由于只允许一次遍历，
所以我们不能用一次完整的遍历来统计链表中元素的个数，而是遍历到对应位置就应该移除了。
那么我们需要用两个指针来帮助我们解题，pre和cur指针。
首先cur指针先向前走N步，
如果此时cur指向空，说明N为链表的长度，则需要移除的为首元素，那么此时我们返回head->next即可，
如果cur存在，我们再继续往下走，此时pre指针也跟着走，直到cur为最后一个元素时停止，
此时pre指向要移除元素的前一个元素，我们再修改指针跳过需要移除的元素即可。
*/
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		//if (!head->next) return NULL;
		ListNode *pre = head, *cur = head;
		for (int i = 0; i < n; ++i) cur = cur->next;
		if (!cur) return head->next;
		while (cur->next) {
			cur = cur->next;
			pre = pre->next;
		}
		pre->next = pre->next->next;
		return head;
	}
};
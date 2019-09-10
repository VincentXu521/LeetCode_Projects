/*
给出一个链表，每 k 个节点一组进行翻转，并返回翻转后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么将最后剩余节点保持原有顺序。
示例 :
给定这个链表：1->2->3->4->5
当 k = 2 时，应当返回: 2->1->4->3->5
当 k = 3 时，应当返回: 3->2->1->4->5
说明 :
1. 你的算法只能使用常数的额外空间。
2. 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
*/

#include<iostream>
using namespace std;
static const auto _=[](){ios::sync_with_stdio(false);cin.tie(nullptr);return nullptr;}();

// Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// ------------------------------------ Mine:20ms...------- recursion ------------

class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (k < 2)return head;  // 可有可无，为了 k==1 时加速.
		ListNode *curr = head;
		for (int i = 0; i < k; i++) {
			if (!curr)return head;
			curr = curr->next;
		}
		ListNode *pre = head;
		// 下两个 init 赋值是为了 k==1 时的特殊情况.
		ListNode *new_head = head;
		ListNode *new_head_next = head->next;
		int num = k;
		for (int i = 0; i < k - 1; i++) {
			pre = head;
			for (int j = 0; j < num - 2; j++) {
				pre = pre->next;
			}
			if (num == k) {
				new_head = pre->next;
				new_head_next = new_head->next;
			}
			num--;
			pre->next->next = pre;
		}
		pre->next = reverseKGroup(new_head_next, k);
		return new_head;
	}
};

// other means one: -----------------------------------------------------
class Solution {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		if (!head || k == 1) return head;
		ListNode *dummy = new ListNode(-1);
		ListNode *pre = dummy, *cur = head;
		dummy->next = head;
		int i = 0;
		while (cur) {
			++i;
			if (i % k == 0) {
				pre = reverseOneGroup(pre, cur->next);
				cur = pre->next;
			}
			else {
				cur = cur->next;
			}
		}
		return dummy->next;
	}
	ListNode *reverseOneGroup(ListNode *pre, ListNode *next) {
		ListNode *last = pre->next;
		ListNode *cur = last->next;
		while (cur != next) {
			last->next = cur->next;
			cur->next = pre->next;
			pre->next = cur;
			cur = last->next;
		}
		return last;
	}
};

// other means two: -----------------------------------------------------
/*
我们也可以在一个函数中完成，我们首先遍历整个链表，统计出链表的长度，然后如果长度大于等于k，
我们开始交换节点，当k=2时，每段我们只需要交换一次，当k=3时，每段需要交换2此，所以i从1开始循环,
注意交换一段后更新pre指针，然后num自减k，直到num<k时循环结束，参见代码如下：
*/
class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode *dummy = new ListNode(-1), *pre = dummy, *cur = pre;
		dummy->next = head;
		int num = 0;
		while (cur = cur->next) ++num;
		while (num >= k) {
			cur = pre->next;
			for (int i = 1; i < k; ++i) {
				ListNode *t = cur->next;
				cur->next = t->next;
				t->next = pre->next;
				pre->next = t;
			}
			pre = cur;
			num -= k;
		}
		return dummy->next;
	}
};

// other means three: ----------- think like me, the diff is take out the func "reverse".
/*
我们也可以使用递归来做，我们用head记录每段的开始位置，cur记录结束位置的下一个节点，
然后我们调用reverse函数来将这段翻转，然后得到一个new_head，原来的head就变成了末尾，
这时候后面接上递归调用下一段得到的新节点，返回new_head即可，参见代码如下：
*/
class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode *cur = head;
		for (int i = 0; i < k; ++i) {
			if (!cur) return head;
			cur = cur->next;
		}
		ListNode *new_head = reverse(head, cur);
		head->next = reverseKGroup(cur, k);
		return new_head;
	}
	ListNode* reverse(ListNode* head, ListNode* tail) {
		ListNode *pre = tail;
		while (head != tail) {
			ListNode *t = head->next;
			head->next = pre;
			pre = head;
			head = t;
		}
		return pre;
	}
};

// ------------------- 执行用时 12ms 的范例：--- errr... so long...---------------
class Solution
{
	ListNode *smallReverseK(ListNode *head, int k)
	{
		ListNode *temp = head;
		for (int a = 1; a < k && temp != NULL; a++)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return head;
		}
		ListNode *ans = head;
		ListNode *curr = NULL;
		ListNode *second = NULL;
		ListNode *after = NULL;
		for (int i = 1; i < k; i++)
		{
			if (head != NULL && head->next != NULL)
			{
				second = head->next;
				after = second->next;
				second->next = ans;
				ans = second;
				head->next = after;
			}
		}
		return ans;
	}
	ListNode *ReverseList(ListNode *list, int k, ListNode **head)
	{
		ListNode *curr = list;
		int i = 0;
		while (curr && k > i)
		{
			curr = curr->next;
			++i;
		}
		if (k > i)
		{
			*head = list;
			return NULL;
		}

		curr = list;
		ListNode *prev = NULL;
		while (curr && k > 0)
		{
			ListNode *next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
			--k;
		}
		*head = curr;
		return prev;
	}
public:
	ListNode *reverseKGroup(ListNode *head, int k)
	{
		ListNode dummy(0);
		ListNode *p = &dummy;
		ListNode *temp = head;
		while (head)
		{
			p->next = ReverseList(head, k, &head);
			if (!p->next)
			{
				p->next = head;
				break;
			}
			while (p->next)
			{
				p = p->next;
			}
		}
		return dummy.next;
	}
};

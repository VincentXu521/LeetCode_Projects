/*
����һ������ÿ k ���ڵ�һ����з�ת�������ط�ת�������
k ��һ��������������ֵС�ڻ��������ĳ��ȡ�����ڵ��������� k ������������ô�����ʣ��ڵ㱣��ԭ��˳��
ʾ�� :
�����������1->2->3->4->5
�� k = 2 ʱ��Ӧ������: 2->1->4->3->5
�� k = 3 ʱ��Ӧ������: 3->2->1->4->5
˵�� :
1. ����㷨ֻ��ʹ�ó����Ķ���ռ䡣
2. �㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����
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
		if (k < 2)return head;  // ���п��ޣ�Ϊ�� k==1 ʱ����.
		ListNode *curr = head;
		for (int i = 0; i < k; i++) {
			if (!curr)return head;
			curr = curr->next;
		}
		ListNode *pre = head;
		// ������ init ��ֵ��Ϊ�� k==1 ʱ���������.
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
����Ҳ������һ����������ɣ��������ȱ�����������ͳ�Ƴ�����ĳ��ȣ�Ȼ��������ȴ��ڵ���k��
���ǿ�ʼ�����ڵ㣬��k=2ʱ��ÿ������ֻ��Ҫ����һ�Σ���k=3ʱ��ÿ����Ҫ����2�ˣ�����i��1��ʼѭ��,
ע�⽻��һ�κ����preָ�룬Ȼ��num�Լ�k��ֱ��num<kʱѭ���������μ��������£�
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
����Ҳ����ʹ�õݹ�������������head��¼ÿ�εĿ�ʼλ�ã�cur��¼����λ�õ���һ���ڵ㣬
Ȼ�����ǵ���reverse����������η�ת��Ȼ��õ�һ��new_head��ԭ����head�ͱ����ĩβ��
��ʱ�������ϵݹ������һ�εõ����½ڵ㣬����new_head���ɣ��μ��������£�
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

// ------------------- ִ����ʱ 12ms �ķ�����--- errr... so long...---------------
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

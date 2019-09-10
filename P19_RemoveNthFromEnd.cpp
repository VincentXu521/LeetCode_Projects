/*
����һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ��㡣
ʾ����
����һ������: 1->2->3->4->5, �� n = 2.

��ɾ���˵����ڶ����ڵ�������Ϊ 1->2->3->5.
˵����
������ n ��֤����Ч�ġ�
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
		// ����ڵ㣺����Ϊ n ����ɾ�������� n ���ڵ�.
		if (len == n)return head->next;
		// ������ n ���������� m+1 ������Ҫ������ m ����
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

// -------------------------- ����: һ�α��� ----------------------------------------------------
/*
������������Ƴ���������N���ڵ㣬�޶�nһ������Ч�ģ���n������������е�Ԫ��������
������ĿҪ������һ�α���������⣬��ô�͵���Щ�Ƚ�����ķ����ˡ�
������������Ҫ���ǵ�ʱ������ҵ�������N���ڵ㣬����ֻ����һ�α�����
�������ǲ�����һ�������ı�����ͳ��������Ԫ�صĸ��������Ǳ�������Ӧλ�þ�Ӧ���Ƴ��ˡ�
��ô������Ҫ������ָ�����������ǽ��⣬pre��curָ�롣
����curָ������ǰ��N����
�����ʱcurָ��գ�˵��NΪ����ĳ��ȣ�����Ҫ�Ƴ���Ϊ��Ԫ�أ���ô��ʱ���Ƿ���head->next���ɣ�
���cur���ڣ������ټ��������ߣ���ʱpreָ��Ҳ�����ߣ�ֱ��curΪ���һ��Ԫ��ʱֹͣ��
��ʱpreָ��Ҫ�Ƴ�Ԫ�ص�ǰһ��Ԫ�أ��������޸�ָ��������Ҫ�Ƴ���Ԫ�ؼ��ɡ�
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
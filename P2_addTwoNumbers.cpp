/*
���������ǿյ�����������ʾ�����Ǹ�������������,���Ǹ��Ե�λ���ǰ�������ķ�ʽ�洢�ģ�
�������ǵ�ÿ���ڵ�ֻ�ܴ洢һλ���֡�
��������ǽ��������������������᷵��һ���µ���������ʾ���ǵĺ͡�
�����Լ���������� 0 ֮�⣬���������������� 0 ��ͷ��

ʾ����
���룺(2 -> 4 -> 3) + (5 -> 6 -> 4)
�����7 -> 0 -> 8
ԭ��342 + 465 = 807
*/

#include<iostream>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int carry = 0;
		ListNode *head = new ListNode(0), *curr = head;
		while (l1 != NULL || l2 != NULL) {
			int x = (l1 == NULL) ? 0 : l1->val;
			int y = (l2 == NULL) ? 0 : l2->val;
			int sum = x + y + carry;
			carry = sum / 10;
			curr->next = new ListNode(sum % 10);
			curr = curr->next;
			if (l1 != NULL)l1 = l1->next;
			if (l2 != NULL)l2 = l2->next;
		}
		if (carry > 0)curr->next = new ListNode(carry);
		return head->next;
	}
};
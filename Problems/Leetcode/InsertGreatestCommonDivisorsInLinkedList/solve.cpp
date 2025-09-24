#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head)
    {
        ListNode* current = head;
        while (current && current->next)
        {
            int g = std::gcd(current->val, current->next->val);
            ListNode* n = new ListNode(g);
            n->next = current->next;
            current->next = n;
            current = n->next;
        }

        return head;    
    }
};

int main()
{
    Solution sol;
    ListNode* head = new ListNode(2);
    head->next = new ListNode(3);
    head->next->next = new ListNode(4);
    head->next->next->next = new ListNode(5);
    ListNode* newHead = sol.insertGreatestCommonDivisors(head);
    while (newHead)
    {
        cout << newHead->val << " ";
        newHead = newHead->next;
    }
    cout << endl;
    return 0;
}
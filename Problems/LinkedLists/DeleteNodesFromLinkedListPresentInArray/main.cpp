/**
https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/description/

You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.

Example 1:

Input: nums = [1,2,3], head = [1,2,3,4,5]

Output: [4,5]
*/

#include <iostream>
#include <vector>
#include <unordered_set>

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
    ListNode* modifiedList(vector<int>& nums, ListNode* head)
    {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        std::unordered_set<int> S(nums.begin(), nums.end());
        while (head != nullptr && S.find(head->val) != S.end())
        {
            head = head->next;
        }

        ListNode* temp = head;
        while (temp->next)
        {
            if (S.find(temp->next->val) != S.end())
            {
                temp->next = temp->next->next;
            }
            else
            {
                temp = temp->next;
            }
        }

        return head;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,2,3};
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head = sol.modifiedList(nums, head);
    
    ListNode* temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    return 0;
}
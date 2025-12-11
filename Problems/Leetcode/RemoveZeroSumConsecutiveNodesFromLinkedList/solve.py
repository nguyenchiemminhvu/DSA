from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeZeroSumSublists(self, head: Optional[ListNode]) -> Optional[ListNode]:
        arr = []
        while head:
            arr.append(head.val)
            head = head.next
        
        n = len(arr)
        new_arr = []
        cur_sum = 0
        mp = {}
        mp[0] = -1
        for val in arr:
            cur_sum += val
            if cur_sum in mp:
                last_idx = mp[cur_sum]
                new_arr = new_arr[:last_idx + 1]
                cur_sum = sum(new_arr)
                mp = {sum(new_arr[:i+1]): i for i in range(len(new_arr))}
                mp[0] = -1
            else:
                new_arr.append(val)
                mp[cur_sum] = len(new_arr) - 1
        
        head = ListNode(0)
        p = head
        for val in new_arr:
            p.next = ListNode(val)
            p = p.next
        return head.next
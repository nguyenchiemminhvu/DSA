from typing import Optional, List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        if head.next.next == None:
            return [-1, -1]
        
        arr = []
        i = 0
        prev = float('inf')
        while head:
            val = head.val
            if i > 0 and head.next:
                if val > prev and val > head.next.val:
                    arr.append(i)
                elif val < prev and val < head.next.val:
                    arr.append(i)
            prev = val
            i += 1
            head = head.next
        
        if len(arr) < 2:
            return [-1, -1]
        mx = arr[-1] - arr[0]
        mn = arr[1] - arr[0]
        for i in range(1, len(arr)):
            mn = min(mn, arr[i] - arr[i - 1])
        return [mn, mx]
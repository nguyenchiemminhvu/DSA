import heapq
from collections import defaultdict
from typing import List, Optional

class min_heap:
    def __init__(self):
        self.pq = []
    def push(self, val: int) -> None:
        heapq.heappush(self.pq, val)
    def pop(self) -> Optional[int]:
        if not self.pq:
            return None
        return heapq.heappop(self.pq)
    def get(self) -> Optional[int]:
        if not self.pq:
            return None
        return self.pq[0]
    def __bool__(self):
        return bool(self.pq)

class max_heap:
    def __init__(self):
        self.pq = []
    def push(self, val: int) -> None:
        heapq.heappush(self.pq, -val)
    def pop(self) -> Optional[int]:
        if not self.pq:
            return None
        return -heapq.heappop(self.pq)
    def get(self) -> Optional[int]:
        if not self.pq:
            return None
        return -self.pq[0]
    def __bool__(self):
        return bool(self.pq)

class Solution:
    def longestSubarray(self, nums: List[int], limit: int) -> int:
        res = 0

        pq_min = min_heap()
        pq_max = max_heap()
        freq = defaultdict(int)

        n = len(nums)
        left = 0
        for right in range(n):
            val = nums[right]
            freq[val] += 1
            pq_min.push(val)
            pq_max.push(val)

            # shrink window until valid
            while True:
                while pq_min and freq[pq_min.get()] == 0:
                    pq_min.pop()
                while pq_max and freq[pq_max.get()] == 0:
                    pq_max.pop()
                
                if pq_max.get() - pq_min.get() <= limit:
                    break

                freq[nums[left]] -= 1
                left += 1
            
            res = max(res, right - left + 1)

        return res
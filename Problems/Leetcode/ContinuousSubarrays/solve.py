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
    def continuousSubarrays(self, nums: List[int]) -> int:
        pq_min = min_heap()
        pq_max = max_heap()
        freq = defaultdict(int)

        left = 0
        res = 0

        for right in range(len(nums)):
            val = nums[right]
            pq_min.push(val)
            pq_max.push(val)
            freq[val] += 1

            # shrink window until valid
            while True:
                # clean invalid heap tops
                while pq_min and freq[pq_min.get()] == 0:
                    pq_min.pop()
                while pq_max and freq[pq_max.get()] == 0:
                    pq_max.pop()

                if pq_max.get() - pq_min.get() <= 2:
                    break

                # remove nums[left]
                freq[nums[left]] -= 1
                left += 1

            # count valid subarrays ending at right
            res += right - left + 1

        return res

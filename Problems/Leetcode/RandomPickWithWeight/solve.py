from typing import List
import random

class Solution:

    def __init__(self, w: List[int]):
        running_sum = 0
        self.percents = []
        for val in w:
            running_sum += val
            self.percents.append(running_sum)
        self.total = running_sum

    def pickIndex(self) -> int:
        def lower_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right = 0, n - 1
            idx = n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx
        
        rand = random.randint(1, self.total)
        lower = lower_bound(self.percents, rand)
        return lower

# Your Solution object will be instantiated and called as such:
# obj = Solution(w)
# param_1 = obj.pickIndex()
import sys
from typing import List

input = sys.stdin.readline

class Solution:
    def maxDistinctElements(self, nums: List[int], k: int) -> int:
        nums.sort()
        arr = []
        prev = nums[0] - k - 1
        for val in nums:
            arr.append(min(max(prev + 1, val - k), val + k))
            prev = arr[-1]
        return len(set(arr))
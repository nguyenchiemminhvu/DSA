from typing import List

class Solution:
    def movesToMakeZigzag(self, nums: List[int]) -> int:
        def build_zigzag_up(start:int) -> int:
            n = len(nums)
            ans = 0
            for i in range(start, n, 2):
                left = nums[i - 1] if i - 1 >= 0 else float('inf')
                right = nums[i + 1] if i + 1 < n else float('inf')
                ans += max(0, nums[i] - min(left, right) + 1)
            return ans
        return min(build_zigzag_up(0), build_zigzag_up(1))
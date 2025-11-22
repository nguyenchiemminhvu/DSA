from typing import List

class Solution:
    def countHillValley(self, nums: List[int]) -> int:
        def remove_duplicate(arr:List[int]) -> None:
            i = 0
            prev = 0x7FFFFFFF
            for val in arr:
                if val != prev:
                    nums[i] = val
                    i += 1
                prev = val
            while i < len(arr):
                arr.pop()

        remove_duplicate(nums)
        n = len(nums)
        if n <= 2:
            return 0

        count = 0
        for i in range(1, n - 1):
            if nums[i - 1] > nums[i] < nums[i + 1]:
                count += 1
            elif nums[i - 1] < nums[i] > nums[i + 1]:
                count += 1
        return count
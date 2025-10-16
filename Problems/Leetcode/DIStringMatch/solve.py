from typing import List

class Solution:
    def diStringMatch(self, s: str) -> List[int]:
        nums = [i for i in range(0, len(s) + 1)]
        left = 0
        right = len(nums) - 1
        arr = []
        for c in s:
            if c == 'I':
                arr.append(nums[left])
                left += 1
            else:
                arr.append(nums[right])
                right -= 1
        arr.append(nums[left])
        return arr
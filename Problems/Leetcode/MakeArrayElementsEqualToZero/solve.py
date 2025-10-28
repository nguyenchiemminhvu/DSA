from typing import List

class Solution:
    def countValidSelections(self, nums: List[int]) -> int:
        def moving(start_idx:int, direction:int) -> bool:
            idx = start_idx
            arr = [val for val in nums]
            n = len(arr)
            while idx >= 0 and idx < n:
                if arr[idx] != 0:
                    arr[idx] -= 1
                    direction *= -1
                idx += direction
            return all(val == 0 for val in arr)
        
        count = 0
        for i in range(len(nums)):
            if nums[i] == 0:
                count += 1 if moving(i, -1) else 0
                count += 1 if moving(i, 1) else 0
        return count
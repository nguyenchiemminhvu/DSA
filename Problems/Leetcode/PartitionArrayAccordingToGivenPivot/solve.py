from typing import List

class Solution:
    def pivotArray(self, nums: List[int], pivot: int) -> List[int]:
        less = []
        equal = []
        greater = []
        for val in nums:
            if val == pivot:
                equal.append(val)
            else:
                if val < pivot:
                    less.append(val)
                else:
                    greater.append(val)
        return less + equal + greater
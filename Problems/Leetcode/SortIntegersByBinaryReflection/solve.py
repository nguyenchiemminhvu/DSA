from typing import List

class Solution:
    def sortByReflection(self, nums: List[int]) -> List[int]:
        def reflection(val: int) -> int:
            temp = 0
            while val > 0:
                temp = (temp << 1) | (val & 1)
                val >>= 1
            return temp
        
        arr = [(reflection(val), val) for val in nums]
        arr.sort()
        return [p[1] for p in arr]
from typing import List

class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:
        prefix_a = set()
        for val in arr1:
            temp = val
            while temp:
                prefix_a.add(temp)
                temp //= 10
        
        prefix_b = set()
        for val in arr2:
            temp = val
            while temp:
                prefix_b.add(temp)
                temp //= 10
        
        common = sorted(list(prefix_a & prefix_b), key=lambda x: len(str(x)))
        if not common:
            return 0
        return len(str(common[-1]))
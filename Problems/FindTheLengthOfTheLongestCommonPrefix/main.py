# https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/

from typing import List

class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:
        s1 = set()
        for val in arr1:
            s = str(val)
            prefix = ""
            for ch in s:
                prefix += ch
                s1.add(prefix)
        
        res = 0
        for val in arr2:
            s = str(val)
            prefix = ""
            for ch in s:
                prefix += ch
                if prefix in s1:
                    res = max(res, len(prefix))
        return res

if __name__ == "__main__":
    arr1 = [1234, 5678, 91011]
    arr2 = [123, 567, 910]
    print(Solution().longestCommonPrefix(arr1, arr2))  # Output: 3
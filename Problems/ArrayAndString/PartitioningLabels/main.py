# https://leetcode.com/problems/partition-labels/

from typing import List
from collections import defaultdict

class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        res = []

        n = len(s)
        last_idx = {}
        for i in range(0, n):
            last_idx[s[i]] = i

        i = 0
        left = 0
        while (True):
            right = last_idx[s[i]]
            while (i < right):
                right = max(right, last_idx[s[i]])
                i += 1
            
            res.append(right - left + 1)
            i += 1
            left = i

            if (right == n - 1):
                break

        return res

if __name__ == "__main__":
    s = "ababcbacadefegdehijhklij"
    sol = Solution()
    print(sol.partitionLabels(s))  # Output: [9, 7, 8]
    s = "eccbbbbdec"
    sol = Solution()
    print(sol.partitionLabels(s))  # Output: [10]
    s = "caedbdedda"
    sol = Solution()
    print(sol.partitionLabels(s))  # Output: [1, 9]
    s = "a"
    sol = Solution()
    print(sol.partitionLabels(s))  # Output: [1]
    s = "ab"
    sol = Solution()
    print(sol.partitionLabels(s))  # Output: [1, 1]
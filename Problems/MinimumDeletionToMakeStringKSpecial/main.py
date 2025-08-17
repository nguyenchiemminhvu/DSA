# https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/

from typing import List
from collections import defaultdict

class Solution:
    def minimumDeletions(self, word: str, k: int) -> int:
        freq = defaultdict(int)
        for c in word:
            freq[c] += 1
        
        freqs = []
        for key, val in freq.items():
            freqs.append(val)
        
        res = 100000000
        for base in freqs:
            deletion = 0
            for f in freqs:
                if (f < base):
                    deletion += f
                if (f > base + k):
                    deletion += f - (base + k)
            res = min(res, deletion)

        return 0 if res == 100000000 else res

if __name__ == "__main__":
    word = "aaabbbcc"
    k = 2
    solution = Solution()
    print(solution.minimumDeletions(word, k))
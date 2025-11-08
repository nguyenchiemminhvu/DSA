from typing import List

class Solution:
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        def is_prefix_suffix(s1: str, s2: str) -> bool:
            n1, n2 = len(s1), len(s2)
            if n1 > n2:
                return False
            if n1 == n2:
                return s1 == s2
            return s1 == s2[:n1] and s1 == s2[n2-n1:]
        
        count = 0
        n = len(words)
        for i in range(n):
            for j in range(i + 1, n):
                if is_prefix_suffix(words[i], words[j]):
                    count += 1
        return count
from collections import Counter

class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        n = len(s)
        counter = Counter(s)
        for ch in s:
            if counter[ch] < k:
                subs = s.split(ch)
                res = 0
                for sub in subs:
                    res = max(res, self.longestSubstring(sub, k))
                return res
        return len(s)
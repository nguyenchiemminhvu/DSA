from typing import List

class Solution:
    def numberOfLines(self, w: List[int], s: str) -> List[int]:
        count = 1
        cur = 0
        for c in s:
            pix = w[ord(c) - ord('a')]
            if cur + pix > 100:
                count += 1
                cur = 0
            cur += pix
        return [count, cur]
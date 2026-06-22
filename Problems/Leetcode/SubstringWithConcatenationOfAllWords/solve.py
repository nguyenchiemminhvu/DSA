from collections import Counter, deque
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        n = len(s)
        nws = len(words)
        nw = len(words[0])
        w_counter = Counter(words)
        
        res = set()
        for offset in range(0, nw):
            s_words = deque()
            s_counter = Counter()
            left = offset
            for i in range(offset, n, nw):
                if i + nw <= n:
                    s_words.append(s[i:i + nw])
                    s_counter[s_words[-1]] += 1
                if len(s_words) > nws:
                    pop = s_words.popleft()
                    s_counter[pop] -= 1
                    if s_counter[pop] <= 0:
                        s_counter.pop(pop)
                    left += nw
                
                if len(s_words) == nws:
                    if s_counter == w_counter:
                        res.add(left)
        return sorted(list(res))
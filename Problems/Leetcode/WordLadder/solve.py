from collections import deque
from typing import List

class Solution:
    def ladderLength(self, start: str, end: str, bank: List[str]) -> int:
        if start == end:
            return 0
        if end not in bank:
            return 0

        def count_diff(a: str, b: str) -> int:
            count = 0
            for i in range(len(a)):
                if a[i] != b[i]:
                    count += 1
            return count
        
        bank = set(bank)
        q = deque([(start, 1)])
        visited = set([start])
        while q:
            s, step = q.popleft()
            if s == end:
                return step
            
            for word in bank:
                if word not in visited and count_diff(s, word) == 1:
                    visited.add(word)
                    q.append((word, step + 1))
        
        return 0
from typing import List

class Solution:
    def getHappyString(self, n: int, k: int) -> str:
        letters = 'abc'
        words = []
        def generating(buffer: List[str]) -> None:
            if len(buffer) >= n:
                words.append("".join(buffer))
                return
            
            for c in letters:
                if buffer and buffer[-1] == c:
                    continue
                generating(buffer + [c])
        
        generating([])
        if k > len(words):
            return ""
        return words[k - 1]
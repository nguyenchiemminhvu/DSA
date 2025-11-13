from typing import List

class Solution:
    def cellsInRange(self, s: str) -> List[str]:
        ab, cd = s.split(':')
        a = ord(ab[0]) - ord('A')
        b = int(ab[1])
        c = ord(cd[0]) - ord('A')
        d = int(cd[1])
        return [chr(ord('A') + col) + str(row) for col in range(a, c + 1) for row in range(b, d + 1)]
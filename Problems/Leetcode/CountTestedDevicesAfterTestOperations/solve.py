from typing import List

class Solution:
    def countTestedDevices(self, bat: List[int]) -> int:
        n = len(bat)
        count = 0
        steps = 0
        for b in bat:
            b = max(0, b - steps)
            if b <= 0:
                continue
            count += 1
            steps += 1
        return count
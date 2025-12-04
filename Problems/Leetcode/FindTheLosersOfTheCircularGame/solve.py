from typing import List

class Solution:
    def circularGameLosers(self, n: int, k: int) -> List[int]:
        members = [False for val in range(n)]
        cur_idx = 0
        steps = k
        while True:
            members[cur_idx] = True
            next_idx = (cur_idx + steps) % n
            if members[next_idx]:
                break
            cur_idx = next_idx
            steps += k
        return [i + 1 for i in range(n) if members[i] == False]
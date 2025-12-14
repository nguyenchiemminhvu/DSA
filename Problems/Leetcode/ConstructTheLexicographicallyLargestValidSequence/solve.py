from typing import List

class Solution:
    def constructDistancedSequence(self, n: int) -> List[int]:
        length = 2 * n - 1
        res = [0] * length
        used = [False] * (n + 1)

        def backtrack(idx: int) -> bool:
            # Move to next empty position
            while idx < length and res[idx] != 0:
                idx += 1
            
            if idx == length:
                return True

            # Try larger numbers first for lexicographically largest
            for num in range(n, 0, -1):
                if used[num]:
                    continue

                if num == 1:
                    # 1 appears once
                    res[idx] = 1
                    used[1] = True
                    if backtrack(idx + 1):
                        return True
                    res[idx] = 0
                    used[1] = False
                else:
                    # Check if second position is valid
                    j = idx + num
                    if j < length and res[j] == 0:
                        res[idx] = res[j] = num
                        used[num] = True
                        if backtrack(idx + 1):
                            return True
                        res[idx] = res[j] = 0
                        used[num] = False
            return False

        backtrack(0)
        return res
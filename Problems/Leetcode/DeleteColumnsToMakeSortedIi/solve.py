from typing import List

class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        n = len(strs)
        m = len(strs[0])
        fixed = [False] * (n - 1)
        deletions = 0

        for col in range(m):
            # Check if we must delete this column
            bad = False
            for i in range(n - 1):
                if not fixed[i] and strs[i][col] > strs[i + 1][col]:
                    bad = True
                    break

            if bad:
                deletions += 1
                continue

            # Update fixed pairs
            for i in range(n - 1):
                if not fixed[i] and strs[i][col] < strs[i + 1][col]:
                    fixed[i] = True

        return deletions

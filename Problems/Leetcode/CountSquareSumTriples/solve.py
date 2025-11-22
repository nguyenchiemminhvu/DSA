class Solution:
    def countTriples(self, n: int) -> int:
        candidates = []
        for i in range(1, n + 1):
            candidates.append(i ** 2)

        nc = len(candidates)
        count = 0
        for c in candidates:
            l, r = 0, nc - 1
            while l <= r:
                s = candidates[l] + candidates[r]
                if s == c:
                    count += 1
                    r -= 1
                elif s > c:
                    r -= 1
                else:
                    l += 1
        return count * 2
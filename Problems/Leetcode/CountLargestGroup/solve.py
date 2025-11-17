class Solution:
    def countLargestGroup(self, n: int) -> int:
        f = {}
        for i in range(1, n + 1):
            s = 0
            val = i
            while val:
                s += (val % 10)
                val //= 10
            f[s] = f.get(s, 0) + 1
        ma = max(f.values())
        return sum(1 for v in f.values() if v == ma)
class Solution:
    def isThree(self, n: int) -> bool:
        i = 1
        s = set()
        while i * i <= n:
            if n % i == 0:
                s.add(i)
                if i * i != n and (n // i) not in s:
                    s.add(n // i)
            i += 1
        return len(s) == 3
class Solution:
    def simplifiedFractions(self, n: int) -> list[str]:
        res = []
        for b in range(1, n + 1):
            for a in range(1, b):
                g = math.gcd(a, b)
                if g == 1:
                    res.append(str(a) + '/' + str(b))
        return res
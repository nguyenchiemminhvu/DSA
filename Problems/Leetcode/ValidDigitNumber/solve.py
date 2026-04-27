class Solution:
    def validDigit(self, n: int, x: int) -> bool:
        arr = []
        while n:
            arr.append(n % 10)
            n //= 10
        return x in arr and arr[-1] != x
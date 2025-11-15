class Solution:
    def generateKey(self, a: int, b: int, c: int) -> int:
        k1 = min(a % 10, b % 10, c % 10)
        k2 = min((a // 10) % 10, (b // 10) % 10, (c // 10) % 10)
        k3 = min((a // 100) % 10, (b // 100) % 10, (c // 100) % 10)
        k4 = min((a // 1000) % 10, (b // 1000) % 10, (c // 1000) % 10)
        return k4 * 1000 + k3 * 100 + k2 * 10 + k1
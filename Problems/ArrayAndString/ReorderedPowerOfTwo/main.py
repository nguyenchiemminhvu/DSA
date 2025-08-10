# https://leetcode.com/problems/reordered-power-of-2

class Solution:
    def reorderedPowerOf2(self, n: int) -> bool:
        sn = sorted(str(n))
        attempt = 1
        while (attempt <= int(1e9)):
            sa = sorted(str(attempt))
            if (sa == sn):
                return True
            attempt <<= 1
        return False

if __name__ == "__main__":
    sol = Solution()
    print(sol.reorderedPowerOf2(1))  # True
    print(sol.reorderedPowerOf2(10))  # False
    print(sol.reorderedPowerOf2(16))  # True
    print(sol.reorderedPowerOf2(24))  # False
    print(sol.reorderedPowerOf2(46))  # True
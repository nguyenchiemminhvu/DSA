class Solution:
    def countSymmetricIntegers(self, low: int, high: int) -> int:
        count = 0
        for val in range(low, high + 1):
            s = str(val)
            n = len(s)
            if n & 1:
                continue
            half = n // 2
            left = 0
            right = 0
            for i in range(n):
                if i < half:
                    left += int(s[i])
                else:
                    right += int(s[i])
            if left == right:
                count += 1
        return count
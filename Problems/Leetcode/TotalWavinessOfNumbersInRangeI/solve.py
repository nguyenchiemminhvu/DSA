class Solution:
    def totalWaviness(self, left: int, right: int) -> int:
        count = 0
        for val in range(left, right + 1):
            arr = []
            while val:
                arr.append(val % 10)
                if len(arr) >= 3:
                    a, b, c = arr[-3], arr[-2], arr[-1]
                    if b > a and b > c:
                        count += 1
                    elif b < a and b < c:
                        count += 1
                val //= 10
        return count
class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        count = 0
        for i in range(limit + 1):
            for j in range(limit + 1):
                if n - i - j >= 0 and n - i - j <= limit:
                    count += 1
        return count
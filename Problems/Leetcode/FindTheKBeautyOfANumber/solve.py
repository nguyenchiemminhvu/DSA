class Solution:
    def divisorSubstrings(self, num: int, k: int) -> int:
        s = str(num)
        count = 0
        for i in range(0, len(s) - k + 1):
            val = int(s[i:i + k])
            if val and num % val == 0:
                count += 1
        return count
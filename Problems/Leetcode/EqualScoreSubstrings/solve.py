class Solution:
    def scoreBalance(self, s: str) -> bool:
        prefix = [ord(c) - ord('a') + 1 for c in s]
        total = sum(prefix)
        left = 0
        for i in range(0, len(prefix)):
            left += prefix[i]
            right = total - left
            if left == right:
                return True
        return False
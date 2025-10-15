class Solution:
    def balancedStringSplit(self, s: str) -> int:
        count = 0
        left = 0
        right = 0
        for i, c in enumerate(s):
            if c == 'L':
                left += 1
            else:
                right += 1
            
            if left == right:
                count += 1
                left = 0
                right = 0

        return count
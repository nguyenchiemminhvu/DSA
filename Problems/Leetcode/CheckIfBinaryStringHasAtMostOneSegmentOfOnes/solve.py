class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        return len([sub for sub in s.split('0') if sub]) <= 1
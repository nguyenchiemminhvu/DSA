class Solution:
    def checkZeroOnes(self, s: str) -> bool:
        return max(len(sub) for sub in s.split('0')) > max(len(sub) for sub in s.split('1'))
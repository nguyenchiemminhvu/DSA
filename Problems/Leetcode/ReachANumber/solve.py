class Solution:
    def reachNumber(self, target: int) -> int:
        target = abs(target)
        s = 0
        i = 1
        while s < target:
            s += i
            i += 1
        if s == target:
            return i - 1
        
        while s > target and ((s - target) & 1):
            s += i
            i += 1

        return i - 1
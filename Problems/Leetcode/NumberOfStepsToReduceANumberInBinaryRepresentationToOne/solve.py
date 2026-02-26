class Solution:
    def numSteps(self, s: str) -> int:
        val = int(s, 2)
        steps = 0
        while val > 1:
            if val & 1:
                val += 1
            else:
                val >>= 1
            steps += 1
        return steps
class Solution:
    def minOperations(self, s: str) -> int:
        n = len(s)
        opt1 = ('01' * n)
        opt2 = ('10' * n)
        cost1, cost2 = 0, 0
        for i, c in enumerate(s):
            if c != opt1[i]:
                cost1 += 1
            if c != opt2[i]:
                cost2 += 1
        return min(cost1, cost2)
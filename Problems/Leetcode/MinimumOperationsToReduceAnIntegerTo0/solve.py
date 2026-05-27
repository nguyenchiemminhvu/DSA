class Solution:
    def minOperations(self, n: int) -> int:
        mem = {}
        def F(val: int) -> int:
            if val == 0:
                return 0
            if val & (val - 1) == 0:
                return 1
            if val in mem:
                return mem[val]
            res = float('inf')
            lowbit = val & (-val)
            res = min(res, 1 + F(val + lowbit), 1 + F(val - lowbit))
            mem[val] = res
            return res
        return F(n)
class Solution:
    def kItemsWithMaximumSum(self, a: int, b: int, c: int, k: int) -> int:
        if k <= a:
            return k
        k -= a
        if k <= b:
            return a
        k -= b
        return a - min(k, c)
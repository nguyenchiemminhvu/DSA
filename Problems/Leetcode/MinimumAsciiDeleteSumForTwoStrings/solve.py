class Solution:
    def minimumDeleteSum(self, s1: str, s2: str) -> int:
        total_sum = sum(ord(c) for c in s1) + sum(ord(c) for c in s2)
        memo = {}

        # F(i1, i2) -> biggest sum of common subsequence from s1[:i1+1] and s2[:i2+1]
        def F(i1: int, i2: int) -> int:
            if i1 < 0 or i2 < 0:
                return 0
            
            if (i1, i2) in memo:
                return memo[(i1, i2)]
            
            max_so_far = 0
            if s1[i1] == s2[i2]:
                max_so_far = max(max_so_far, ord(s1[i1]) + ord(s2[i2]) + F(i1-1, i2-1))
            else:
                max_so_far = max([max_so_far, F(i1, i2-1), F(i1-1, i2)])
            
            memo[(i1, i2)] = max_so_far
            return max_so_far

        return total_sum - F(len(s1) - 1, len(s2) - 1)
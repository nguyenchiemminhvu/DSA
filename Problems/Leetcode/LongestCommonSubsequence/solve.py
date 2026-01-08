class Solution:
    def longestCommonSubsequence(self, s1: str, s2: str) -> int:
        n1 = len(s1)
        n2 = len(s2)
        memo = {}

        # F(i1, i2) -> longest common subsequence of s1[:i1+1] and s2[:i2+1]
        def F(i1: int, i2: int) -> int:
            if i1 < 0 or i2 < 0:
                return 0
            
            if (i1, i2) in memo:
                return memo[(i1, i2)]
            
            max_so_far = 0
            if s1[i1] == s2[i2]:
                max_so_far = 1 + F(i1 - 1, i2 - 1)
            else:
                max_so_far = max(F(i1, i2 - 1), F(i1 - 1, i2))
            
            memo[(i1, i2)] = max_so_far
            return max_so_far
        
        return F(n1 - 1, n2 - 1)
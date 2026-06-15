import itertools

class Solution:
    def getPermutation(self, n: int, k: int) -> str:
        perm = itertools.permutations([i for i in range(1, n + 1)])

        while k > 1:
            next(perm)
            k -= 1
        
        return ''.join(str(d) for d in next(perm))
from typing import List

class Solution:
    def checkValid(self, mat: List[List[int]]) -> bool:
        n = len(mat)
        check = set(i for i in range(1, n + 1))

        for row in mat:
            if set(row) != check:
                return False
        
        for i in range(n):
            s = set()
            for row in mat:
                s.add(row[i])
            if s != check:
                return False
        
        return True
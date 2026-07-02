from typing import List

class DSU:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return False
        
        if self.size[root_x] < self.size[root_y]:
            root_x, root_y = root_y, root_x

        self.parent[root_y] = root_x
        self.size[root_x] += self.size[root_y]
        return True

class Solution:
    def equationsPossible(self, equations: List[str]) -> bool:
        dsu = DSU(26)

        for equa in equations:
            if equa[1] == '=':
                left, right = equa[0], equa[-1]
                ileft, iright = ord(left) - ord('a'), ord(right) - ord('a')
                dsu.union(ileft, iright)
        
        for equa in equations:
            if equa[1] == '!':
                left, right = equa[0], equa[-1]
                ileft, iright = ord(left) - ord('a'), ord(right) - ord('a')
                if dsu.find(ileft) == dsu.find(iright):
                    return False
        return True
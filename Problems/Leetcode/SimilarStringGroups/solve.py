from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1

class Solution:
    def numSimilarGroups(self, ss: List[str]) -> int:
        ss = list(set(ss))
        ns = len(ss)
        dsu = DSU(ns)

        s_to_i = {}
        for i, s in enumerate(ss):
            s_to_i[s] = i
        
        def similar(s1: str, s2: str) -> bool:
            n1, n2 = len(s1), len(s2)
            if n1 != n2:
                return False
            
            diff_idx = []
            for i in range(n1):
                if s1[i] != s2[i]:
                    diff_idx.append(i)
            
            if not diff_idx:
                return True
            if len(diff_idx) != 2:
                return False
            i1, i2 = diff_idx
            return s1[i1] == s2[i2] and s2[i1] == s1[i2]
        
        for i in range(ns):
            for j in range(i + 1, ns):
                if similar(ss[i], ss[j]):
                    dsu.union(s_to_i[ss[i]], s_to_i[ss[j]])
        
        ss = set()
        for i in range(ns):
            ss.add(dsu.find(i))
        return len(ss)
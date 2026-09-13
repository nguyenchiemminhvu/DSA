from collections import defaultdict

class Solution:
    def largestOverlap(self, img1: List[List[int]], img2: List[List[int]]) -> int:
        n = len(img1)
        pos1 = []
        pos2 = []
        for r in range(n):
            for c in range(n):
                if img1[r][c] == 1:
                    pos1.append((r, c))
                if img2[r][c] == 1:
                    pos2.append((r, c))
        
        np1 = len(pos1)
        np2 = len(pos2)
        shift = defaultdict(int)
        for i in range(np1):
            r1, c1 = pos1[i]
            for j in range(np2):
                r2, c2 = pos2[j]

                r_shift = r2 - r1
                c_shift = c2 - c1

                shift[(r_shift, c_shift)] += 1
        
        return max(shift.values(), default=0)
from typing import List

class Solution:
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
        n = len(people)

        zero = []
        others = []
        for p in people:
            if p[1] == 0:
                zero.append(p)
            else:
                others.append(p)
        
        zero.sort(key=lambda x: x[0])
        others.sort(key=lambda x: (-x[0], x[1]))

        res = zero[:]
        for p in others:
            count = 0
            for i in range(len(res)):
                if p[0] <= res[i][0]:
                    count += 1
                if count == p[1]:
                    res.insert(i + 1, p)
                    break
        return res
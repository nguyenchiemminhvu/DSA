from typing import List
import bisect

class Solution:
    def longestObstacleCourseAtEachPosition(self, arr: List[int]) -> List[int]:
        n = len(arr)

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i == 0:
        #         return 1
        #     if i in mem:
        #         return mem[i]
        #     longest = 1
        #     for j in range(i):
        #         if arr[i] >= arr[j]:
        #             longest = max(longest, 1 + F(j))
        #     mem[i] = longest
        #     return longest
        # res = [1 for _ in range(n)]
        # for i in range(n):
        #     res[i] = max(res[i], F(i))
        # return res

        res = [1 for _ in range(n)]
        tails = []
        for i in range(n):
            idx = bisect.bisect_right(tails, arr[i])
            if idx == len(tails):
                tails.append(arr[i])
            else:
                tails[idx] = arr[i]
            res[i] = max(res[i], idx + 1)
        
        return res
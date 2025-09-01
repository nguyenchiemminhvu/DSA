# https://leetcode.com/problems/maximum-average-pass-ratio

import heapq

class Solution:
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        def f_gain(p, t):
            return -((p + 1) / (t + 1) - (p / t))

        pq = [(f_gain(p, t), p, t) for p, t in classes]
        heapq.heapify(pq)

        while (extraStudents > 0):
            gain, p, t = heapq.heappop(pq)
            p += 1
            t += 1
            heapq.heappush(pq, (f_gain(p, t), p, t))
            extraStudents -= 1
        
        res = 0.0
        while (pq):
            _, p, t = heapq.heappop(pq)
            res += (p / t)
        return res / len(classes)

if __name__ == "__main__":
    s = Solution()
    print(s.maxAverageRatio([[1,2],[3,5],[2,2]], 2))  # 0.78333
    print(s.maxAverageRatio([[2,4],[3,9],[4,5],[2,10]], 4))  # 0.53485
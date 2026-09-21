class Solution:
    def countIntersectingIntervals(self, intervals: list[list[int]]) -> int:
        n = len(intervals)
        intervals.sort(key=lambda x: x[0])

        def upper_bound(pairs: list[list[int]], end: int) -> int:
            n = len(pairs)
            l, r, idx = 0, n - 1, n
            while l <= r:
                m = l + (r - l) // 2
                if pairs[m][0] > end:
                    idx = m
                    r = m - 1
                else:
                    l = m + 1
            return idx
        
        count = 0
        for i in range(n):
            end = intervals[i][1]
            upper = upper_bound(intervals, end)
            count += max(0, upper - 1 - i)
        
        return count
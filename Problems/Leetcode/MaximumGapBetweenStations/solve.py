class Solution:
    def maximumGap(self, workers: str, stations: str) -> int:
        nw = len(workers)
        ns = len(stations)

        left = [0] * nw
        right = [0] * nw

        # left to right passing
        i, j = 0, 0
        while i < nw and j < ns:
            if workers[i] == stations[j]:
                left[i] = j
                i += 1
            j += 1
        
        # right to left passing
        i, j = nw - 1, ns - 1
        while i >= 0 and j >= 0:
            if workers[i] == stations[j]:
                right[i] = j
                i -= 1
            j -= 1
        
        res = 0
        for i in range(1, nw):
            res = max(res, right[i] - left[i - 1])
        return res
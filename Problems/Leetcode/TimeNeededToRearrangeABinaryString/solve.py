class Solution:
    def secondsToRemoveOccurrences(self, s: str) -> int:
        times = 0
        count_0 = 0
        for c in s:
            if c == '0':
                count_0 += 1
            else:
                if count_0 > 0:
                    times = max(times + 1, count_0)
        return times
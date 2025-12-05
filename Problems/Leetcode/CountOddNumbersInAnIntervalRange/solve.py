class Solution:
    def countOdds(self, low: int, high: int) -> int:
        r = high - low + 1
        if r & 1:
            return r // 2 + int(low & 1 and high & 1)
        else:
            return r // 2
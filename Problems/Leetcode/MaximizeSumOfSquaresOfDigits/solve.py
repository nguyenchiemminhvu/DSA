class Solution:
    def maxSumOfSquares(self, num: int, sum: int) -> str:
        res = ''
        start = min(9, sum)
        while sum:
            times = sum // start
            if times > num:
                return ''
            sum -= (start * times)
            num -= times
            res += str(start) * times
            start = min(9, sum)

        while num:
            res += '0'
            num -= 1
        return res
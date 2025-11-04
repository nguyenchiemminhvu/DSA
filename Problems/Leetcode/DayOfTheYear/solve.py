from datetime import date

class Solution:
    def dayOfYear(self, date: str) -> int:
        y = int(date[0:4])
        m = int(date[5:7])
        d = int(date[8:10])

        ymd = date(y, m, d)
        start = date(y, 1, 1)
        diff = ymd - start
        return diff.days + 1
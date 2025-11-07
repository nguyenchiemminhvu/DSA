from datetime import date

class Solution:
    def dayOfTheWeek(self, day: int, month: int, year: int) -> str:
        ref = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
        d = date(year, month, day)
        p = date(1971, 1, 1)
        diff = d - p
        days = diff.days
        return ref[(5 + (days % 7)) % 7]
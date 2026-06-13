from collections import defaultdict

class MyCalendarThree:

    def __init__(self):
        self.timeline = defaultdict(int)

    def book(self, start: int, end: int) -> int:
        self.timeline[start] += 1
        self.timeline[end] -= 1

        max_book = 0
        stack = 0
        for timestamp in sorted(self.timeline):
            stack += self.timeline[timestamp]
            max_book = max(max_book, stack)
            
        return max_book

# Your MyCalendarThree object will be instantiated and called as such:
# obj = MyCalendarThree()
# param_1 = obj.book(startTime,endTime)
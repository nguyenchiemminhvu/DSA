from collections import defaultdict

class MyCalendar:
    def __init__(self):
        self.timeline = defaultdict(int)
    
    def book(self, start: int, end: int) -> bool:
        self.timeline[start] += 1
        self.timeline[end] -= 1

        stack = 0
        for timestamp in sorted(self.timeline):
            stack += self.timeline[timestamp]
            
            if stack >= 2:
                self.timeline[start] -= 1
                self.timeline[end] += 1
                return False
            
        return True

# Your MyCalendar object will be instantiated and called as such:
# obj = MyCalendar()
# param_1 = obj.book(startTime,endTime)

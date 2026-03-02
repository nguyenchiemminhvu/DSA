from collections import defaultdict

class MyCalendarTwo:

    def __init__(self):
        self.timeline = defaultdict(int)
    
    def book(self, start: int, end: int) -> bool:
        self.timeline[start] += 1
        self.timeline[end] -= 1

        stack = 0
        for timestamp in sorted(self.timeline):
            stack += self.timeline[timestamp]
            
            if stack >= 3:
                self.timeline[start] -= 1
                self.timeline[end] += 1
                return False
            
        return True


# Your MyCalendarTwo object will be instantiated and called as such:
# obj = MyCalendarTwo()
# param_1 = obj.book(startTime,endTime)
import sys
from typing import List

input = sys.stdin.read
output = sys.stdout.write

class Solution:
    def countDays(self, days: int, meetings: List[List[int]]) -> int:
        meetings = sorted(meetings)
        new_meetings = meetings[0:1]
        for meeting in meetings[1:]:
            if (meeting[0] <= new_meetings[-1][1]):
                new_meetings[-1][1] = max(new_meetings[-1][1], meeting[1])
            else:
                new_meetings.append(meeting)
        
        count = 0
        prev = 1
        for meeting in new_meetings:
            if (prev < meeting[0]):
                count += meeting[0] - prev
            prev = meeting[1] + 1
        
        if (prev <= days):
            count += (days - prev) + 1

        return count

if __name__ == "__main__":
    data = input().strip().split("\n")
    days = int(data[0])
    meetings = [list(map(int, line.split())) for line in data[1:]]

    solution = Solution()
    result = solution.countDays(days, meetings)
    output(str(result) + "\n")
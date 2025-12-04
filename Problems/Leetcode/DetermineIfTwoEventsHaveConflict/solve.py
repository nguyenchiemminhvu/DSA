from typing import List

class Solution:
    def haveConflict(self, event1: List[str], event2: List[str]) -> bool:
        def to_minute(s: str) -> int:
            hh, mm = int(s[0:2]), int(s[3:5])
            return hh * 60 + mm

        intervals = [[to_minute(event1[0]), to_minute(event1[1])], [to_minute(event2[0]), to_minute(event2[1])]]
        intervals.sort(key=lambda x: x[0])
        return intervals[1][0] <= intervals[0][1]
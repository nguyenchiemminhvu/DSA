from typing import List
from collections import defaultdict

class Solution:
    def buttonWithLongestTime(self, events: List[List[int]]) -> int:
        m = defaultdict(int)
        prev_time = 0
        max_duration = 0
        max_key = -1
        for key, timestamp in events:
            m[key] = max(m[key], timestamp - prev_time)
            if max_duration < m[key]:
                max_duration = m[key]
                max_key = key
            elif max_duration == m[key]:
                max_key = min(max_key, key)
            prev_time = timestamp
        return max_key
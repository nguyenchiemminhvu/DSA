from typing import List

class Solution:
    def videoStitching(self, clips: List[List[int]], time: int) -> int:
        clips.sort(key=lambda x: (x[0], -x[1]))
        n = len(clips)

        if clips[0][0] > 0:
            return -1
        
        count = 0
        i = 0
        cur_end = 0
        next_end = 0
        while i < n and cur_end < time:
            while i < n and cur_end >= clips[i][0]:
                next_end = max(next_end, clips[i][1])
                i += 1
            
            if next_end == cur_end:
                return -1
            
            count += 1
            cur_end = next_end
        
        if cur_end < time:
            return -1
        
        return count
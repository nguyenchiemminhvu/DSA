from typing import List

class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        res = [0] * n
        stack = []
        prev_time = 0

        for log in logs:
            fid, typ, time = log.split(':')
            fid, time = int(fid), int(time)

            if stack:
                res[stack[-1]] += time - prev_time

            if typ == "start":
                stack.append(fid)
                prev_time = time
            else:  # end
                stack.pop()
                res[fid] += 1
                prev_time = time + 1

        return res

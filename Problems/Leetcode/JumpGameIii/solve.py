from collections import deque
from typing import List

class Solution:
    def canReach(self, arr: List[int], start: int) -> bool:
        n = len(arr)

        def bfs():
            q = deque([start])
            visited = set()
            while q:
                cur = q.popleft()
                if arr[cur] == 0:
                    return True
                visited.add(cur)

                left = cur - arr[cur]
                right = cur + arr[cur]
                if left >= 0 and left not in visited:
                    q.append(left)
                if right < n and right not in visited:
                    q.append(right)
            
            return False
        
        return bfs()
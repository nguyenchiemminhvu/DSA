from collections import deque
from typing import List

class Solution:
    def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        n = len(rooms)
        key_collections = set()
        visited = set()
        visited.add(0)
        Q = deque()
        Q.append(0)
        while len(Q) > 0:
            cur = Q.popleft()
            for key in rooms[cur]:
                if key not in key_collections:
                    if key not in visited:
                        Q.append(key)
                        visited.add(key)
                    key_collections.add(key)
        return len(visited) == n
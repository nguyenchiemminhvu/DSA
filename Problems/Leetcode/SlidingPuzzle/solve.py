from collections import deque
from typing import List

class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:
        target = [1, 2, 3, 4, 5, 0]

        adj_map = {
            0: [1, 3],
            1: [0, 2, 4],
            2: [1, 5],
            3: [0, 4],
            4: [1, 3, 5],
            5: [2, 4],
        }

        cur = [val for row in board for val in row]
        visited = set()
        moves = 0
        q = deque([cur])
        visited.add(tuple(cur))
        while q:
            size = len(q)
            for _ in range(size):
                cur = q.popleft()
                if cur == target:
                    return moves
                                
                idx_0 = cur.index(0)
                for adj in adj_map[idx_0]:
                    next_state = cur[:]
                    next_state[idx_0], next_state[adj] = next_state[adj], next_state[idx_0]
                    if tuple(next_state) not in visited:
                        visited.add(tuple(next_state))
                        q.append(next_state)
            moves += 1
        
        return -1
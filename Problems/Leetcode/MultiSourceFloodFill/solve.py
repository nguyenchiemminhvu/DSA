from collections import deque

class Solution:
    def colorGrid(self, m: int, n: int, sources: list[list[int]]) -> list[list[int]]:
        q = deque()
        # state[r][c] stores (arrival_time, color)
        inf = float('inf')
        state = [[(inf, 0)] * n for _ in range(m)]
        
        q = deque()
        for r, c, color in sources:
            if 0 < state[r][c][0]: 
                state[r][c] = [0, color]
                q.append((0, color, r, c))
            elif 0 == state[r][c][0]:
                state[r][c][1] = max(state[r][c][1], color)
                q.append((0, color, r, c))
        
        while q:
            size = len(q)
            for _ in range(size):
                cur_time, color, r, c = q.popleft()
                if cur_time > state[r][c][0] or (cur_time == state[r][c][0] and color < state[r][c][1]):
                    continue

                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if nr < 0 or nr >= m or nc < 0 or nc >= n:
                        continue
                    next_time = cur_time + 1
                    prev_time, prev_color = state[nr][nc]
                    
                    # Case 1: Found a strictly faster path to this neighbor
                    if next_time < prev_time:
                        state[nr][nc] = [next_time, color]
                        q.append((next_time, color, nr, nc))
                    # Case 2: Same arrival time, but we brought a larger color ID
                    elif next_time == prev_time and color > prev_color:
                        state[nr][nc][1] = color
                        q.append((next_time, color, nr, nc))
        
        return [[state[r][c][1] for c in range(n)] for r in range(m)]
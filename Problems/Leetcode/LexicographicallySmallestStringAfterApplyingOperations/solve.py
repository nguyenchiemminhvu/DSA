from collections import deque
from typing import List

class Solution:
    def findLexSmallestString(self, s: str, a: int, b: int) -> str:
        def operation_add(arr: List[int]) -> None:
            for i in range(1, len(arr), 2):
                arr[i] = (arr[i] + a) % 10
        
        def operation_rotate(arr: List[int]) -> None:
            arr[:] = arr[-b:] + arr[:-b]

        s = [int(val) for val in list(s)]
        candidates = []
        in_set = set()
        in_set.add(tuple(s))
        def bfs() -> None:
            q = deque([s])
            while q:
                cur = q.popleft()
                candidates.append(cur)
                next_rotate = [val for val in cur]
                next_add = [val for val in cur]
                operation_rotate(next_rotate)
                operation_add(next_add)

                if tuple(next_rotate) not in in_set:
                    q.append([val for val in next_rotate])
                    in_set.add(tuple([val for val in next_rotate]))
                if tuple(next_add) not in in_set:
                    q.append([val for val in next_add])
                    in_set.add(tuple([val for val in next_add]))
        
        bfs()
        candidates = ["".join([str(val) for val in candidate]) for candidate in candidates]
        return min(candidates)
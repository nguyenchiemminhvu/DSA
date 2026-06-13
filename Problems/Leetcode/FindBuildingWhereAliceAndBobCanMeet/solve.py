from collections import deque
from typing import List

class Solution:
    def leftmostBuildingQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        n = len(arr)
        nq = len(queries)
        res = [-1] * nq

        queries = [(i, query) for i, query in enumerate(queries)]
        queries.sort(key=lambda x: (-max(x[1]), -min(x[1])))
        
        st = deque()
        idx = n - 1
        for i, (orig_i, (x, y)) in enumerate(queries):
            # check special case
            if x == y:
                res[orig_i] = x
                continue
            
            # ensure x <= y
            if x > y:
                x, y = y, x
            
            # height of right index is higher than left index, can meet at right index
            if arr[y] > arr[x]:
                res[orig_i] = y
                continue
            
            # build monotonic stack
            while idx > y:
                while st and arr[st[0]] <= arr[idx]:
                    st.popleft()
                st.appendleft(idx)
                idx -= 1
            
            # binary search
            max_h = max(arr[x], arr[y])
            pick_idx = len(st)
            l, r = 0, len(st) - 1
            while l <= r:
                m = l + (r - l) // 2
                if arr[st[m]] > max_h:
                    pick_idx = m
                    r = m - 1
                else:
                    l = m + 1
            
            if pick_idx < len(st):
                res[orig_i] = st[pick_idx]
        
        return res
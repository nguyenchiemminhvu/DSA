from typing import List

class Solution:
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        items.sort(key=lambda x : x[0])
        n = len(items)
        cur_max = 0
        for i in range(n):
            cur_max = max(cur_max, items[i][1])
            items[i][1] = cur_max
        
        res = []
        for query in queries:
            # do binary search (upper_bound)
            left, right = 0, n - 1
            idx = n
            while left <= right:
                mid = left + (right - left) // 2
                if items[mid][0] > query:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            idx -= 1
            res.append(0 if idx < 0 else items[idx][1])
        return res
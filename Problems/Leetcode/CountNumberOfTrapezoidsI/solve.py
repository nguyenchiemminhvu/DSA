from typing import List

class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        mod = int(1e9 + 7)
        map_y = {}
        for x, y in points:
            if y not in map_y:
                map_y[y] = []
            map_y[y].append(x)
        
        arr_y = sorted([y for y, arr in map_y.items() if len(arr) >= 2])

        res = 0
        count_pairs = 0
        for y in arr_y:
            n = len(map_y[y])
            pair = n * (n - 1) // 2
            res = (res % mod + (pair * count_pairs) % mod) % mod
            count_pairs += pair
        return res
from typing import List

class Solution:
    def countCoveredBuildings(self, n: int, buildings: List[List[int]]) -> int:
        map_hor = {}
        map_ver = {}
        for x, y in buildings:
            if y not in map_hor:
                map_hor[y] = [x, x]
            mn, mx = map_hor[y]
            map_hor[y] = [min(mn, x), max(mx, x)]

            if x not in map_ver:
                map_ver[x] = [y, y]
            mn, mx = map_ver[x]
            map_ver[x] = [min(mn, y), max(mx, y)]
        
        count = 0
        for x, y in buildings:
            hor_cover = bool(x > map_hor[y][0] and x < map_hor[y][1])
            ver_cover = bool(y > map_ver[x][0] and y < map_ver[x][1])
            count += int(hor_cover and ver_cover)
        return count
class Solution:
    def nearestDrone(self, drones: list[list[int]], target: list[int]) -> int:
        def dist(a: list[int], b: list[int]) -> int:
            return abs(a[0] - b[0]) + abs(a[1] - b[1])
        
        min_dist = float('inf')
        res = -1
        for i, (x, y, r) in enumerate(drones):
            d = dist([x, y], target)
            if d > r:
                continue
            
            if d < min_dist:
                min_dist = d
                res = i
        
        return res
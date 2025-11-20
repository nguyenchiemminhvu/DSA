from typing import List

class Solution:
    def nearestValidPoint(self, x: int, y: int, points: List[List[int]]) -> int:
        min_distance = float('inf')
        result_index = -1
        
        for i, (px, py) in enumerate(points):
            # Check if point is valid (shares x or y coordinate)
            if px == x or py == y:
                # Calculate Manhattan distance
                manhattan_dist = abs(px - x) + abs(py - y)
                
                # Update result if this distance is smaller
                if manhattan_dist < min_distance:
                    min_distance = manhattan_dist
                    result_index = i
        
        return result_index

# Alternative solution using the original approach but with correct distance calculation
class SolutionAlternative:
    def nearestValidPoint(self, x: int, y: int, points: List[List[int]]) -> int:
        def manhattan_dist(xx: int, yy: int) -> int:
            return abs(xx - x) + abs(yy - y)  # Correct Manhattan distance
        
        # Filter valid points and sort by distance
        valid_points = [(xx, yy) for xx, yy in points if xx == x or yy == y]
        if not valid_points:
            return -1
        
        # Sort by distance, keeping original order for ties
        valid_points.sort(key=lambda p: manhattan_dist(p[0], p[1]))
        
        # Find the index of the closest point in the original array
        closest_point = valid_points[0]
        for i, (xx, yy) in enumerate(points):
            if (xx, yy) == closest_point:
                return i
        return -1
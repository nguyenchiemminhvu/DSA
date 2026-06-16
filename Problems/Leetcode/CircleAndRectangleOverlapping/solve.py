class Solution:
    def checkOverlap(self, radius: int, xCenter: int, yCenter: int, x1: int, y1: int, x2: int, y2: int) -> bool:
        
        # Helper function to find the minimum distance from (x0, y0) to a line segment
        def point_to_segment_dist(x0, y0, sx1, sy1, sx2, sy2):
            dx, dy = sx2 - sx1, sy2 - sy1
            if dx == 0 and dy == 0:
                return ((x0 - sx1)**2 + (y0 - sy1)**2)**0.5
                
            # Projection factor t
            t = ((x0 - sx1) * dx + (y0 - sy1) * dy) / (dx**2 + dy**2)
            t = max(0, min(1, t))
            
            # Closest point on the segment
            xc = sx1 + t * dx
            yc = sy1 + t * dy
            
            return ((x0 - xc)**2 + (y0 - yc)**2)**0.5

        # 1. Define the 4 segments of the rectangle
        bottom_segment = point_to_segment_dist(xCenter, yCenter, x1, y1, x2, y1)
        top_segment    = point_to_segment_dist(xCenter, yCenter, x1, y2, x2, y2)
        left_segment   = point_to_segment_dist(xCenter, yCenter, x1, y1, x1, y2)
        right_segment  = point_to_segment_dist(xCenter, yCenter, x2, y1, x2, y2)
        
        # 2. Find the minimum distance to any of the 4 segments
        min_dist = min(bottom_segment, top_segment, left_segment, right_segment)
        
        # 3. Check if the center is strictly inside the rectangle boundary
        is_inside = (x1 <= xCenter <= x2) and (y1 <= yCenter <= y2)
        
        # Overlaps if it touches/crosses a segment, OR if the circle is trapped inside
        return min_dist <= radius or is_inside

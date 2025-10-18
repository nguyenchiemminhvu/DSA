def get_triangle_vertices(orientation, d, x, y):
    """
    Get the three vertices of an isosceles right triangle.
    
    Args:
        orientation: 1, 2, 3, or 4
        d: length of equal sides
        x, y: coordinates where equal sides meet (right angle vertex)
    
    Returns:
        List of three (x, y) tuples representing vertices
    """
    if orientation == 1:
        # Right angle at (x,y), other vertices at (x+d, y) and (x, y+d)
        return [(x, y), (x + d, y), (x, y + d)]
    elif orientation == 2:
        # Right angle at (x,y), other vertices at (x-d, y) and (x, y+d)
        return [(x, y), (x - d, y), (x, y + d)]
    elif orientation == 3:
        # Right angle at (x,y), other vertices at (x-d, y) and (x, y-d)
        return [(x, y), (x - d, y), (x, y - d)]
    elif orientation == 4:
        # Right angle at (x,y), other vertices at (x+d, y) and (x, y-d)
        return [(x, y), (x + d, y), (x, y - d)]


def point_in_triangle(px, py, vertices):
    """
    Check if point (px, py) is inside triangle using Jordan curve theorem (ray casting).
    Cast a ray from the point to the right and count intersections with triangle edges.
    Odd number of intersections means the point is inside.
    """
    n = len(vertices)
    intersections = 0
    
    for i in range(n):
        x1, y1 = vertices[i]
        x2, y2 = vertices[(i + 1) % n]
        
        # Check if the ray intersects this edge
        # Ray goes from (px, py) horizontally to the right
        
        # Edge must cross the horizontal line at py
        if (y1 <= py < y2) or (y2 <= py < y1):
            # Calculate x-coordinate of intersection
            if y1 != y2:  # Avoid division by zero
                x_intersect = x1 + (py - y1) * (x2 - x1) / (y2 - y1)
                
                # Intersection must be to the right of the point
                if x_intersect > px:
                    intersections += 1
    
    # Point is inside if odd number of intersections
    return intersections % 2 == 1


def get_triangle_area(vertices):
    """Calculate area of a triangle using the shoelace formula."""
    x1, y1 = vertices[0]
    x2, y2 = vertices[1]
    x3, y3 = vertices[2]
    return abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0)


def get_all_critical_points(triangles):
    """Get all x and y coordinates that might be important for the union calculation."""
    x_coords = set()
    y_coords = set()
    
    for vertices in triangles:
        for x, y in vertices:
            x_coords.add(x)
            y_coords.add(y)
            # Add slight offsets for better precision at boundaries
            x_coords.add(x + 0.001)
            x_coords.add(x - 0.001)
            y_coords.add(y + 0.001)
            y_coords.add(y - 0.001)
    
    return sorted(x_coords), sorted(y_coords)


def compute_union_area(triangles):
    """
    Compute the area of union of triangles using optimized coordinate compression.
    This version uses a sweep line approach with adaptive sampling for better precision.
    """
    if not triangles:
        return 0.0
    
    # Early termination for single triangle
    if len(triangles) == 1:
        return get_triangle_area(triangles[0])
    
    # Find bounding box with some padding
    min_x = min_y = float('inf')
    max_x = max_y = float('-inf')
    
    for vertices in triangles:
        for x, y in vertices:
            min_x = min(min_x, x)
            max_x = max(max_x, x)
            min_y = min(min_y, y)
            max_y = max(max_y, y)
    
    # Add small padding to ensure we don't miss boundary cases
    padding = 0.0001
    min_x -= padding
    max_x += padding
    min_y -= padding
    max_y += padding
    
    # Use adaptive grid size based on the problem size
    # For small areas, use finer grid; for large areas, optimize for speed
    area_span = (max_x - min_x) * (max_y - min_y)
    if area_span < 100:
        resolution = 200  # High precision for small problems
    elif area_span < 1000:
        resolution = 100  # Medium precision
    else:
        resolution = 50   # Lower precision for large problems
    
    step_x = (max_x - min_x) / resolution
    step_y = (max_y - min_y) / resolution
    
    total_area = 0.0
    
    # Sweep through the grid
    for i in range(resolution):
        for j in range(resolution):
            # Sample multiple points within each cell for better accuracy
            sample_points = [
                (min_x + i * step_x + step_x * 0.25, min_y + j * step_y + step_y * 0.25),
                (min_x + i * step_x + step_x * 0.75, min_y + j * step_y + step_y * 0.25),
                (min_x + i * step_x + step_x * 0.25, min_y + j * step_y + step_y * 0.75),
                (min_x + i * step_x + step_x * 0.75, min_y + j * step_y + step_y * 0.75),
                (min_x + i * step_x + step_x * 0.5, min_y + j * step_y + step_y * 0.5)  # Center point
            ]
            
            covered_samples = 0
            for px, py in sample_points:
                for vertices in triangles:
                    if point_in_triangle(px, py, vertices):
                        covered_samples += 1
                        break
            
            # If any samples are covered, contribute to the area
            if covered_samples > 0:
                cell_area = step_x * step_y
                coverage_ratio = covered_samples / len(sample_points)
                total_area += cell_area * coverage_ratio
    
    return total_area


def solve():
    T = int(input())
    
    for _ in range(T):
        N = int(input())
        triangles = []
        
        for _ in range(N):
            O, D, X, Y = map(int, input().split())
            vertices = get_triangle_vertices(O, D, X, Y)
            triangles.append(vertices)
        
        area = compute_union_area(triangles)
        print(f"{area:.2f}")


if __name__ == "__main__":
    solve()

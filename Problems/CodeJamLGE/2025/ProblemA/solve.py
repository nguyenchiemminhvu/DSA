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
    Check if point (px, py) is inside triangle using barycentric coordinates.
    """
    x1, y1 = vertices[0]
    x2, y2 = vertices[1] 
    x3, y3 = vertices[2]
    
    denom = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)
    if abs(denom) < 1e-10:
        return False
        
    a = ((y2 - y3) * (px - x3) + (x3 - x2) * (py - y3)) / denom
    b = ((y3 - y1) * (px - x3) + (x1 - x3) * (py - y3)) / denom
    c = 1 - a - b
    
    return a >= 0 and b >= 0 and c >= 0


def compute_union_area(triangles):
    """
    Compute the area of union of triangles using grid sampling.
    Since all coordinates are integers <= 100, we can use fine-grained sampling.
    """
    if not triangles:
        return 0.0
    
    # Find bounding box
    min_x = min_y = float('inf')
    max_x = max_y = float('-inf')
    
    for vertices in triangles:
        for x, y in vertices:
            min_x = min(min_x, x)
            max_x = max(max_x, x)
            min_y = min(min_y, y)
            max_y = max(max_y, y)
    
    # Use fine sampling for accuracy
    samples = 1000  # samples per unit
    total_samples = 0
    covered_samples = 0
    
    step = 1.0 / samples
    
    for i in range(int(min_x * samples), int(max_x * samples) + samples):
        for j in range(int(min_y * samples), int(max_y * samples) + samples):
            px = i / samples + step / 2
            py = j / samples + step / 2
            
            total_samples += 1
            
            # Check if point is in any triangle
            for vertices in triangles:
                if point_in_triangle(px, py, vertices):
                    covered_samples += 1
                    break
    
    area_per_sample = step * step
    return covered_samples * area_per_sample


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

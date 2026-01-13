## Problem

https://leetcode.com/problems/separate-squares-i/description/

You are given a 2D integer array `squares` where each `squares[i] = [xi, yi, li]` represents:
- `(xi, yi)`: coordinates of the bottom-left point of a square
- `li`: side length of the square (parallel to x-axis)

**Goal**: Find the minimum y-coordinate value of a horizontal line such that:
- Total area of squares **above** the line = Total area of squares **below** the line

**Important Notes**:
- Answers within 10^-5 of the actual answer are accepted
- Squares may overlap - overlapping areas should be counted multiple times

### Examples

#### Example 1:
```
Input: squares = [[0,0,1],[2,2,1]]
Output: 1.00000
```
**Explanation**: 
- Square 1: bottom-left at (0,0), side length 1, spans from y=0 to y=1
- Square 2: bottom-left at (2,2), side length 1, spans from y=2 to y=3
- Any horizontal line between y=1 and y=2 will have 1 square unit above and 1 below
- The minimum is y=1

#### Example 2:
```
Input: squares = [[0,0,2],[1,1,1]]
Output: 1.16667
```
**Explanation**:
- Square 1: (0,0) to (2,2), area = 4
- Square 2: (1,1) to (2,2), area = 1
- At y = 7/6 ≈ 1.16667:
  - Below: 7/6 * 2 (from Square 1) + 1/6 (from Square 2) = 15/6 = 2.5
  - Above: 5/6 * 2 (from Square 1) + 5/6 (from Square 2) = 15/6 = 2.5

### Constraints
- `1 <= squares.length <= 5 * 10^4`
- `0 <= xi, yi <= 10^9`
- `1 <= li <= 10^9`
- Total area of all squares ≤ 10^12

## Observations

### Key Insights

1. **Total Area is Constant**: The sum of all square areas is fixed. If we find a line where area_above = area_below, then each equals half the total area.

2. **Monotonic Property**: As we move the horizontal line upward:
   - Area above decreases (monotonically)
   - Area below increases (monotonically)
   - **This makes binary search applicable!**

3. **Square Partitioning**: For each square, given a horizontal line at y = `hor`:
   - If `hor >= y_top`: entire square is below (area_above = 0)
   - If `hor <= y_bot`: entire square is above (area_below = 0)
   - Otherwise: square is split into two parts

4. **Split Area Calculation**: When a square is split by line at y = `hor`:
   - Square spans from `y_bot` to `y_top = y_bot + length`
   - Area above line: `(y_top - hor) * length`
   - Area below line: `(hor - y_bot) * length`
   - Verification: sum = `length * length` ✓

5. **Search Space**: 
   - Minimum possible y: 0
   - Maximum possible y: 10^9

6. **Precision**: Binary search with proper rounding to handle floating point precision

## Solution

### Algorithm: Binary Search

Since the area relationship is monotonic, we use binary search to find the optimal horizontal line position.

**Search Strategy**:
- If `area_above > area_below` → line is too low, search higher
- If `area_above < area_below` → line is too high, search lower  
- If `area_above == area_below` → found the answer!

### Implementation Details

#### 1. Area Calculation Helper
```python
def area(x_bot, y_bot, length, hor: float) -> Tuple[float]:
    x_top, y_top = x_bot, y_bot + length
    
    if hor >= y_top:
        return (0, length * length)  # All below
    if hor <= y_bot:
        return (length * length, 0)  # All above
    
    # Split case
    area_above = (y_top - hor) * length
    area_below = (hor - y_bot) * length
    return (area_above, area_below)
```

#### 2. Check Function
```python
def check(hor: float) -> int:
    area_top, area_bot = 0, 0
    
    for x, y, l in squares:
        top, bot = area(x, y, l, hor)
        area_top += top
        area_bot += bot
    
    if area_top == area_bot:
        return 0   # Perfect balance
    if area_top > area_bot:
        return 1   # Too much above, line too low
    return -1      # Too much below, line too high
```

#### 3. Binary Search Main Logic
```python
processed = set()  # Avoid infinite loops with floating point
hor_top = 10**9    # Upper bound
hor_bot = 0        # Lower bound
res = hor_top

while hor_bot <= hor_top:
    mid = round(hor_bot + (hor_top - hor_bot) / 2, 5)
    
    # Check if we've already processed this value
    if mid in processed:
        break
    else:
        processed.add(mid)
    
    stat = check(mid)
    
    if stat <= 0:  # area_above <= area_below
        res = round(mid, 5)
        hor_top = mid  # Search lower half
    else:          # area_above > area_below
        hor_bot = mid  # Search upper half

return res
```

### Complexity Analysis

**Time Complexity: O(n * log(10^9 / ε))**
- Binary search iterations: log(10^9 / 10^-5) ≈ log(10^14) ≈ 47 iterations
- Each iteration: O(n) to calculate total areas for all n squares
- Overall: **O(n * 47) = O(n)**

**Space Complexity: O(log(range))**
- `processed` set stores visited midpoints
- Overall: **O(1)** practical space

### Why This Solution Works

1. **Correctness**: 
   - The monotonic property guarantees binary search convergence
   - Area calculation correctly handles all three cases

2. **Precision Handling**:
   - Rounding to 5 decimal places prevents infinite loops
   - The `processed` set ensures termination
   - Satisfies 10^-5 precision requirement

3. **Efficiency**:
   - Binary search is optimal for monotonic search spaces
   - Each check is linear in squares count (unavoidable)

### Key Takeaways

1. **Recognize monotonic properties** to apply binary search on continuous spaces
2. **Floating point precision** requires careful handling
3. **Problem decomposition**: break complex geometry into simple cases
4. Binary search works on any **monotonic search space**, not just arrays!

# Tags
Binary Search, Geometry, Math, Floating Point Precision


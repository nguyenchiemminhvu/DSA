## Problem

https://leetcode.com/problems/categorize-box-according-to-criteria/description/

```
Given four integers length, width, height, and mass, representing the dimensions and mass of a box, respectively, return a string representing the category of the box.

The box is "Bulky" if:
- Any of the dimensions of the box is greater or equal to 10^4.
- Or, the volume of the box is greater or equal to 10^9.

If the mass of the box is greater or equal to 100, it is "Heavy".

If the box is both "Bulky" and "Heavy", then its category is "Both".
If the box is neither "Bulky" nor "Heavy", then its category is "Neither".
If the box is "Bulky" but not "Heavy", then its category is "Bulky".
If the box is "Heavy" but not "Bulky", then its category is "Heavy".

Note: The volume of the box is the product of its length, width and height.

Example 1:
Input: length = 1000, width = 35, height = 700, mass = 300
Output: "Heavy"
Explanation: 
- None of the dimensions >= 10^4
- Volume = 24,500,000 <= 10^9, so not "Bulky"
- Mass >= 100, so it is "Heavy"
- Result: "Heavy"

Example 2:
Input: length = 200, width = 50, height = 800, mass = 50
Output: "Neither"
Explanation:
- None of the dimensions >= 10^4
- Volume = 8,000,000 <= 10^9, so not "Bulky"
- Mass < 100, so not "Heavy"
- Result: "Neither"

Constraints:
- 1 <= length, width, height <= 10^5
- 1 <= mass <= 10^3
```

## Observations

1. **Two Independent Criteria**: The problem defines two independent boolean conditions:
   - **Bulky**: Based on dimensions or volume
   - **Heavy**: Based solely on mass

2. **Bulky Determination**: A box is bulky if EITHER condition is met:
   - Any single dimension (length, width, or height) >= 10,000
   - Volume (length × width × height) >= 1,000,000,000

3. **Heavy Determination**: Simple threshold check:
   - Mass >= 100

4. **Four Possible Outcomes**: Based on the combination of two boolean flags:
   - Both bulky AND heavy → "Both"
   - Neither bulky NOR heavy → "Neither"
   - Only bulky → "Bulky"
   - Only heavy → "Heavy"

5. **Edge Cases to Consider**:
   - Very large single dimension but small volume (e.g., 10,000 × 1 × 1)
   - Small dimensions but large volume (e.g., 1,000 × 1,000 × 1,000)
   - Heavy mass but small/normal box
   - Large box but lightweight

## Solution

1. **Initialize Flags**: Start with both `bulky` and `heavy` as `False`

2. **Check Bulky Condition**:
   - Use `any()` to check if any dimension >= 10^4
   - OR check if volume (l × w × h) >= 10^9
   - Set `bulky = True` if either condition is met

3. **Check Heavy Condition**:
   - Simple comparison: mass >= 100
   - Set `heavy = True` if condition is met

4. **Determine Category**: Use if-elif chain to return the appropriate category:
   - First check both conditions together
   - Then check neither condition
   - Then check individual conditions

### Complexity Analysis:

- **Time Complexity**: O(1)
  - Checking three dimensions: constant time
  - Volume calculation: constant time
  - Mass comparison: constant time
  - Category determination: constant time

- **Space Complexity**: O(1)
  - Only two boolean variables used
  - No additional data structures

### Key Implementation Details:

- **Using `any()`**: Elegant way to check multiple conditions without explicit loops
- **Short-circuit evaluation**: The `or` operator stops as soon as one condition is true
- **Clear flag-based logic**: Makes the code readable and maintainable
- **Explicit return statements**: Each category is returned explicitly, avoiding confusion

### Alternative Approaches:

1. **Direct Return** (without flags):
```python
def categorizeBox(self, l: int, w: int, h: int, m: int) -> str:
    is_bulky = any(d >= 10**4 for d in [l, w, h]) or l*w*h >= 10**9
    is_heavy = m >= 100
    
    if is_bulky and is_heavy: return "Both"
    if is_bulky: return "Bulky"
    if is_heavy: return "Heavy"
    return "Neither"
```

2. **Dictionary Mapping**:
```python
def categorizeBox(self, l: int, w: int, h: int, m: int) -> str:
    is_bulky = any(d >= 10**4 for d in [l, w, h]) or l*w*h >= 10**9
    is_heavy = m >= 100
    
    categories = {
        (True, True): "Both",
        (True, False): "Bulky",
        (False, True): "Heavy",
        (False, False): "Neither"
    }
    return categories[(is_bulky, is_heavy)]
```

Both alternatives are equally efficient but offer different trade-offs in readability.

# Tags

`Implementation` `Conditional Logic` `Math`


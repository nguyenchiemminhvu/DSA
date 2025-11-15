## Problem

https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/description/

```
You are given an array rectangles where rectangles[i] = [li, wi] represents the ith rectangle of length li and width wi.

You can cut the ith rectangle to form a square with a side length of k if both k <= li and k <= wi. For example, if you have a rectangle [4,6], you can cut it to get a square with a side length of at most 4.

Let maxLen be the side length of the largest square you can obtain from any of the given rectangles.

Return the number of rectangles that can make a square with a side length of maxLen.

Example 1:

Input: rectangles = [[5,8],[3,9],[5,12],[16,5]]
Output: 3
Explanation: The largest squares you can get from each rectangle are of lengths [5,3,5,5].
The largest possible square is of length 5, and you can get it out of 3 rectangles.

Example 2:

Input: rectangles = [[2,3],[3,7],[4,3],[3,7]]
Output: 3

Constraints:

1 <= rectangles.length <= 1000
rectangles[i].length == 2
1 <= li, wi <= 109
li != wi
```

## Observations

1. **Maximum square side length from a rectangle**: For any rectangle with dimensions `[length, width]`, the largest square we can cut from it has side length `min(length, width)`.

2. **Finding the global maximum**: We need to find the maximum possible square side length across all rectangles, which is the maximum value among all `min(length, width)` values.

3. **Counting rectangles with maximum square**: Once we know the maximum square side length, we count how many rectangles can produce a square of this maximum size.

4. **Key insight**: The problem reduces to:
   - Calculate `min(length, width)` for each rectangle
   - Find the maximum of these values
   - Count how many rectangles have this maximum value

## Solution

1. **Extract maximum square sizes**: `[min(r[0], r[1]) for r in rectangles]` calculates the maximum square side length for each rectangle.

2. **Sort in descending order**: `sorted(..., reverse=True)` arranges the square sizes from largest to smallest. The first element `w[0]` is the maximum possible square side length.

3. **Count maximum occurrences**: Iterate through the sorted array and count consecutive elements equal to `w[0]` (the maximum value). Since the array is sorted in descending order, once we encounter a value different from `w[0]`, we can break as all remaining values will be smaller.

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(n) for storing the square sizes array

**Alternative O(n) approach**:
```python
def countGoodRectangles(self, rectangles: List[List[int]]) -> int:
    max_side = 0
    count = 0
    
    # Find maximum square side length
    for rect in rectangles:
        max_side = max(max_side, min(rect[0], rect[1]))
    
    # Count rectangles that can form this maximum square
    for rect in rectangles:
        if min(rect[0], rect[1]) == max_side:
            count += 1
    
    return count
```

# Tags

Array, Math, Greedy


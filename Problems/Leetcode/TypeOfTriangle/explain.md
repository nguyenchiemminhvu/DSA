## Problem

https://leetcode.com/problems/type-of-triangle/description/

You are given a 0-indexed integer array `nums` of size 3 which can form the sides of a triangle.

A triangle is called **equilateral** if it has all sides of equal length.
A triangle is called **isosceles** if it has exactly two sides of equal length.
A triangle is called **scalene** if all its sides are of different lengths.

Return a string representing the type of triangle that can be formed or `"none"` if it cannot form a triangle.

**Example 1:**
```
Input: nums = [3,3,3]
Output: "equilateral"
Explanation: Since all the sides are of equal length, therefore, it will form an equilateral triangle.
```

**Example 2:**
```
Input: nums = [3,4,5]
Output: "scalene"
Explanation: 
nums[0] + nums[1] = 3 + 4 = 7, which is greater than nums[2] = 5.
nums[0] + nums[2] = 3 + 5 = 8, which is greater than nums[1] = 4.
nums[1] + nums[2] = 4 + 5 = 9, which is greater than nums[0] = 3. 
Since the sum of the two sides is greater than the third side for all three cases, therefore, it can form a triangle.
As all the sides are of different lengths, it will form a scalene triangle.
```

**Constraints:**
- `nums.length == 3`
- `1 <= nums[i] <= 100`

## Observations

1. **Triangle Inequality Theorem**: For three sides to form a valid triangle, the sum of any two sides must be greater than the third side. However, after sorting, we only need to check if `a + b > c` (where `a ≤ b ≤ c`), because:
   - If `a + b > c`, then `a + c > b` and `b + c > a` are automatically satisfied
   - This is because `c` is the largest side, so if the two smallest sides can satisfy the inequality, the others will too

2. **Classification Logic**:
   - **Equilateral**: All three sides are equal (`a == b == c`)
   - **Isosceles**: Exactly two sides are equal (`a == b` or `b == c`)
   - **Scalene**: All three sides are different
   - **None**: Doesn't satisfy triangle inequality

3. **Sorting Simplification**: By sorting the array first, we get `a ≤ b ≤ c`, which:
   - Simplifies the triangle validity check to just `a + b > c`
   - Makes classification easier since we know the relative ordering

## Solution

**Time Complexity**: O(1) - Sorting a fixed-size array of 3 elements is constant time

**Space Complexity**: O(1) - Only using a constant amount of extra space

**Algorithm Steps**:
1. Sort the array to get sides in ascending order (a ≤ b ≤ c)
2. Check triangle validity using the inequality theorem on the critical case
3. Classify the triangle type based on equality of sides:
   - First check for equilateral (all equal)
   - Then check for isosceles (two equal)
   - Otherwise, it's scalene (all different)

# Tags

`Array` `Math` `Geometry` `Sorting`


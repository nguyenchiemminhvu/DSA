## Problem

https://leetcode.com/problems/distribute-candies-among-children-i/description/

```
You are given two positive integers n and limit.

Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.

Example 1:

Input: n = 5, limit = 2
Output: 3
Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).

Example 2:

Input: n = 3, limit = 3
Output: 10
Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies: (0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).

Constraints:

1 <= n <= 50
1 <= limit <= 50
```

## Observations

1. **Problem Nature**: This is a combinatorics problem where we need to count the number of ways to distribute `n` candies among 3 children with a constraint that no child gets more than `limit` candies.

2. **Constraint Analysis**: 
   - Each child can receive 0 to `limit` candies (inclusive)
   - The total candies distributed must equal `n`
   - We need to find all valid triplets (x, y, z) where:
     - x + y + z = n
     - 0 ≤ x ≤ limit
     - 0 ≤ y ≤ limit  
     - 0 ≤ z ≤ limit

3. **Brute Force Approach**: Since the constraints are small (n ≤ 50, limit ≤ 50), we can iterate through all possible combinations for the first two children and calculate the third child's candies.

4. **Time Complexity**: O(limit²) - we iterate through all combinations of candies for the first two children.

## Solution

1. **Nested Loop Structure**: Use two nested loops to iterate through all possible candy distributions for the first two children:
   - `i` represents candies given to child 1 (0 to limit)
   - `j` represents candies given to child 2 (0 to limit)

2. **Calculate Third Child**: For each combination (i, j), calculate the remaining candies for child 3:
   - `k = n - i - j`

3. **Validation**: Check if the third child's candy count is valid:
   - `k >= 0`: Ensures we don't have negative candies
   - `k <= limit`: Ensures the third child doesn't exceed the limit

4. **Count Valid Combinations**: If all constraints are satisfied, increment the counter.

**Example Walkthrough** (n=5, limit=2):
- (i=1, j=2): k = 5-1-2 = 2 ✓ (valid: 1,2,2)
- (i=2, j=1): k = 5-2-1 = 2 ✓ (valid: 2,1,2)  
- (i=2, j=2): k = 5-2-2 = 1 ✓ (valid: 2,2,1)
- Total: 3 ways

**Time Complexity**: O(limit²)
**Space Complexity**: O(1)

# Tags
- Combinatorics
- Brute Force
- Math
- Easy


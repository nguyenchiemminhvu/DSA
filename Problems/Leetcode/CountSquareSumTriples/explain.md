## Problem

https://leetcode.com/problems/count-square-sum-triples/

```
A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.

Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.

Example 1:

Input: n = 5
Output: 2
Explanation: The square triples are (3,4,5) and (4,3,5).

Example 2:

Input: n = 10
Output: 4
Explanation: The square triples are (3,4,5), (4,3,5), (6,8,10), and (8,6,10).

Constraints:

1 <= n <= 250
```

## Observations

1. **Pythagorean Triples**: This problem is asking us to find Pythagorean triples (a, b, c) where a² + b² = c².

2. **Constraint Analysis**: With n ≤ 250, we have a manageable search space. The maximum possible c² would be 250² = 62,500.

3. **Order Matters**: The problem counts (3,4,5) and (4,3,5) as different triples, so we need to account for both orderings when a ≠ b.

4. **Brute Force vs Optimization**: A naive O(n³) approach would check all combinations, but we can optimize using the two-pointer technique since we're looking for sum relationships.

5. **Perfect Squares**: We only need to work with perfect squares, so pre-computing them makes sense.

## Solution

1. **Pre-compute Squares**: Create a list of all perfect squares from 1² to n².

2. **For Each Potential Hypotenuse**: Iterate through each square c² in our candidates list.

3. **Two-Pointer Search**: For each c², use two pointers to find pairs (a², b²) such that a² + b² = c²:
   - `l` starts at the beginning (smallest square)
   - `r` starts at the end (largest square)
   - If `candidates[l] + candidates[r] == c`, we found a valid triple
   - If the sum is too large, move `r` left
   - If the sum is too small, move `l` right

4. **Handle Ordering**: Multiply the final count by 2 because each valid (a,b,c) where a ≠ b gives us both (a,b,c) and (b,a,c).

**Time Complexity**: O(n²) - For each of the n squares, we perform a two-pointer search which is O(n).

**Space Complexity**: O(n) - for storing the pre-computed squares.

**Key Insight**: The two-pointer technique works because the candidates array is sorted, allowing us to efficiently find pairs that sum to a target value.

# Tags


## Problem

https://leetcode.com/problems/max-dot-product-of-two-subsequences/description/

```
Given two arrays nums1 and nums2, return the maximum dot product between non-empty subsequences 
of nums1 and nums2 with the same length.

A subsequence of an array is a new array which is formed from the original array by deleting 
some (can be none) of the characters without disturbing the relative positions of the remaining 
characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).

Example 1:
Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
Output: 18
Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
Their dot product is (2*3 + (-2)*(-6)) = 18.

Example 2:
Input: nums1 = [3,-2], nums2 = [2,-6,7]
Output: 21
Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
Their dot product is (3*7) = 21.

Example 3:
Input: nums1 = [-1,-1], nums2 = [1,1]
Output: -1
Explanation: Take subsequence [-1] from nums1 and subsequence [1] from nums2.
Their dot product is -1.

Constraints:
- 1 <= nums1.length, nums2.length <= 500
- -1000 <= nums1[i], nums2[i] <= 1000
```

## Observations

1. **Subsequence property**: We can skip elements but must maintain relative order in both arrays.

2. **Dot product**: For two sequences of equal length, dot product = sum of (element_i * element_j) for all pairs.

3. **Non-empty constraint**: We must include at least one element from each array.

4. **Optimal substructure**: The problem has overlapping subproblems - the maximum dot product for arrays up to index i1 and i2 can be built from solutions of smaller subproblems.

5. **Key insight**: At each position (i1, i2), we have 4 choices:
   - Take both `a1[i1]` and `a2[i2]` and pair them (must consider this product)
   - Take both and add to the best solution from previous indices
   - Skip `a1[i1]`, continue with `a2[i2]`
   - Skip `a2[i2]`, continue with `a1[i1]`

6. **Edge cases**:
   - All negative products: We must still take at least one pair, so we take the least negative
   - Mixed signs: Pairing negatives with negatives gives positive products

## Solution

### Approach: Dynamic Programming with Memoization (Top-Down)

**State Definition:**
- `F(i1, i2)` = maximum dot product of subsequences from `a1[0:i1+1]` and `a2[0:i2+1]`

**Base Case:**
- If `i1 < 0` or `i2 < 0`: return `-inf` (no valid subsequence)

**Recurrence Relation:**
At position (i1, i2), we consider:
1. `cur_prod = a1[i1] * a2[i2]` - the product if we pair these elements
2. Four options:
   - Take just this pair: `cur_prod` (satisfies non-empty requirement)
   - Take this pair + best from previous: `cur_prod + F(i1-1, i2-1)`
   - Skip a1[i1]: `F(i1-1, i2)`
   - Skip a2[i2]: `F(i1, i2-1)`

**Why this works:**
- `cur_prod` alone ensures we can always form a valid subsequence (non-empty)
- `cur_prod + F(i1-1, i2-1)` extends a previous solution by pairing current elements
- Skipping options allow us to find better pairings later

**Time Complexity:** O(n1 × n2) - we compute each state once
**Space Complexity:** O(n1 × n2) - memoization table

```python
class Solution:
    def maxDotProduct(self, a1: List[int], a2: List[int]) -> int:
        n1 = len(a1)
        n2 = len(a2)
        memo = {}

        # F(i1, i2) -> max dot product of subsequences a1[:i1+1] and a2[:i2+1]
        def F(i1:int, i2:int) -> int:
            if i1 < 0 or i2 < 0:
                return float('-inf')
            if (i1, i2) in memo:
                return memo[(i1, i2)]
            
            cur_prod = a1[i1] * a2[i2]
            # Consider 4 options:
            # 1. Take only current pair
            # 2. Take current pair + best from previous
            # 3. Skip a1[i1]
            # 4. Skip a2[i2]
            max_so_far = max([
                cur_prod, 
                cur_prod + F(i1 - 1, i2 - 1), 
                F(i1 - 1, i2), 
                F(i1, i2 - 1)
            ])
            
            memo[(i1, i2)] = max_so_far
            return max_so_far
        
        return F(n1 - 1, n2 - 1)
```

**Example Trace (nums1 = [2,1,-2,5], nums2 = [3,0,-6]):**
- F(3,2): Compare products at various subsequences
- Best: Take [2,-2] from nums1 and [3,-6] from nums2
- Dot product: 2×3 + (-2)×(-6) = 6 + 12 = 18

# Tags

`Dynamic Programming` `Memoization` `Subsequence` `Array` `Optimization`
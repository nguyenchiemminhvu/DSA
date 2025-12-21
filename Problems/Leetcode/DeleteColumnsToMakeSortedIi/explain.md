## Problem

https://leetcode.com/problems/delete-columns-to-make-sorted-ii/description/

```
You are given an array of n strings strs, all of the same length.

We may choose any deletion indices, and we delete all the characters in those indices for each string.

For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, 
then the final array after deletions is ["bef", "vyz"].

Suppose we chose a set of deletion indices answer such that after deletions, 
the final array has its elements in lexicographic order 
(i.e., strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]). 
Return the minimum possible value of answer.length.

Example 1:
Input: strs = ["ca","bb","ac"]
Output: 1
Explanation: After deleting the first column, strs = ["a", "b", "c"].
Now strs is in lexicographic order.

Example 2:
Input: strs = ["xc","yb","za"]
Output: 0
Explanation: strs is already in lexicographic order.

Example 3:
Input: strs = ["zyx","wvu","tsr"]
Output: 3
Explanation: We have to delete every column.

Constraints:
- n == strs.length
- 1 <= n <= 100
- 1 <= strs[i].length <= 100
- strs[i] consists of lowercase English letters.
```

## Observations

1. **Greedy Column-by-Column Processing**: We can process columns from left to right. Once we've processed some columns, we know which adjacent pairs are already "sorted" (lexicographically ordered).

2. **Fixed Pairs Concept**: Once `strs[i] < strs[i+1]` based on the columns we've seen so far, this pair is "fixed" - we don't need to worry about it anymore because the lexicographic order is already established.

3. **Deletion Condition**: We must delete a column if and only if it violates the ordering for at least one pair that isn't already fixed. Specifically, if `strs[i][col] > strs[i+1][col]` for some unfixed pair `i`, we must delete that column.

4. **Order Matters**: The order of columns matters because earlier columns determine the lexicographic ordering. A character comparison only matters if all previous characters are equal.

5. **State Tracking**: We need to track which adjacent pairs are already sorted (fixed) so we can ignore them in future column checks.

## Solution

### Approach: Greedy with Fixed Pairs Tracking

The key insight is that we process columns from left to right and maintain which adjacent pairs have already been "fixed" (determined to be in order).

**Algorithm Steps:**

1. **Initialize State**:
   - `fixed[i]` tracks whether the pair `(strs[i], strs[i+1])` is already sorted
   - Initially, all pairs are unfixed

2. **For Each Column** (left to right):
   - **Check if column must be deleted**:
     - For each unfixed pair `i`, check if `strs[i][col] > strs[i+1][col]`
     - If yes, this column violates ordering → must delete it
     - If deleted, skip to next column
   
   - **Update fixed pairs** (if not deleted):
     - For each unfixed pair `i`, if `strs[i][col] < strs[i+1][col]`
     - Mark that pair as fixed (the ordering is now determined)

3. **Return** the total number of deletions

**Why This Works:**

- **Correctness**: We only delete columns that violate ordering for unfixed pairs. Once a pair is fixed by having `strs[i] < strs[i+1]` lexicographically up to the current column, future columns cannot affect this relationship.

- **Minimality**: We keep every column that doesn't violate ordering, minimizing deletions.

**Example Walkthrough** (`strs = ["ca","bb","ac"]`):

- Column 0: `['c','b','a']`
  - Check pair 0: `'c' > 'b'` → unfixed pair violated → **DELETE**
  
- Column 1: `['a','b','c']`
  - Check pair 0: `'a' < 'b'` → OK, mark pair 0 as fixed
  - Check pair 1: `'b' < 'c'` → OK, mark pair 1 as fixed
  
- Result: 1 deletion

**Time Complexity**: O(n × m) where n is the number of strings and m is the length of each string
**Space Complexity**: O(n) for the fixed array

# Tags
`Greedy`, `String`, `Array`


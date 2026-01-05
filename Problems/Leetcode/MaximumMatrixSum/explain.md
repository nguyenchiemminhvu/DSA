## Problem

https://leetcode.com/problems/maximum-matrix-sum/description/

You are given an `n x n` integer matrix. You can perform the following operation any number of times:

- Choose any two **adjacent** elements of the matrix and multiply each of them by `-1`
- Two elements are considered adjacent if and only if they share a border (horizontally or vertically)

**Goal**: Maximize the summation of the matrix's elements using the operation mentioned above.

### Examples

**Example 1:**
```
Input: matrix = [[1,-1],[-1,1]]
Output: 4

Explanation: 
Step 1: Multiply the 2 elements in the first row by -1
        [[1,-1],[-1,1]] → [[-1,1],[-1,1]]
Step 2: Multiply the 2 elements in the first column by -1
        [[-1,1],[-1,1]] → [[1,1],[1,1]]
Result: Sum = 1 + 1 + 1 + 1 = 4
```

**Example 2:**
```
Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
Output: 16

Explanation:
Multiply the 2 last elements in the second row by -1
[[1,2,3],[-1,-2,-3],[1,2,3]] → [[1,2,3],[-1,2,3],[1,2,3]]
Result: Sum = 1+2+3+(-1)+2+3+1+2+3 = 16
```

### Constraints
- `n == matrix.length == matrix[i].length`
- `2 <= n <= 250`
- `-10^5 <= matrix[i][j] <= 10^5`

## Observations

### 1. **Parity of Negative Numbers is Key**
Each operation flips the sign of exactly **2 adjacent elements**. This means:
- If both elements are negative: 2 negatives → 2 positives (reduces negative count by 2)
- If both are positive: 2 positives → 2 negatives (increases negative count by 2)
- If one positive, one negative: changes which specific elements are negative but keeps count the same

**Critical insight**: The parity (odd/even) of negative numbers can only change by ±2 or stay the same.

### 2. **Reachability Through Operations**
Since elements are connected in a grid and we can flip adjacent pairs:
- We can "move" negativity around the matrix through a series of operations
- We can concentrate negativity to any specific location
- We can eliminate pairs of negative numbers

### 3. **Three Cases to Consider**

**Case A: Matrix contains a zero**
- We can move all negativity toward the zero
- Eventually flip the zero with a negative neighbor
- Zero remains zero (0 × -1 = 0), negative becomes positive
- Result: All negatives can be eliminated

**Case B: Even number of negatives (no zero)**
- Negatives can be paired up and eliminated
- Each pair of negatives can be made positive through operations
- Result: All elements can be made positive

**Case C: Odd number of negatives (no zero)**
- We can eliminate all but one negative
- One negative must remain in the matrix
- To maximize sum: keep the smallest absolute value as negative
- Result: Sum of all absolute values minus 2× (smallest absolute value)

### 4. **Why We Don't Need to Track Actual Operations**
The problem asks for the maximum sum, not the sequence of operations. Due to the connectivity of the grid and the parity invariant, we only need to determine:
- Can we make all elements positive? (zero exists OR even negatives)
- If not, which element should remain negative? (smallest absolute value)

## Solution

### Strategy

The algorithm follows these steps:

1. **Calculate absolute sum**: Add up `|val|` for all elements
2. **Count negative numbers**: Track how many negatives exist
3. **Find minimum absolute value**: This is the element we'd sacrifice if needed
4. **Check for zero**: Zeros allow us to eliminate all negatives

5. **Decision logic**:
   ```
   IF (has_zero OR count_negatives is even):
       return sum_of_absolute_values
   ELSE:
       return sum_of_absolute_values - 2 × min_absolute_value
   ```

### Why subtract `2 × min_abs`?

When we have an odd number of negatives and no zero:
- Best case sum = (sum of all absolute values)
- But one element must stay negative
- If element with value `|x|` is negative instead of positive: 
  - Contribution changes from `+|x|` to `-|x|`
  - Difference = `|x| - (-|x|) = 2|x|`
- To maximize, we choose the smallest `|x|` to remain negative

### Implementation

```python
class Solution:
    def maxMatrixSum(self, mat: List[List[int]]) -> int:
        n = len(mat)
        has_zero = False
        count_neg = 0
        sum_non_neg = 0
        min_abs = float('inf')
        
        # Single pass through the matrix
        for row in mat:
            for val in row:
                if val == 0:
                    has_zero = True
                if val < 0:
                    count_neg += 1
                sum_non_neg += abs(val)
                min_abs = min(min_abs, abs(val))
        
        # If zero exists or even negatives: all can be positive
        if has_zero or count_neg % 2 == 0:
            return sum_non_neg
        
        # Odd negatives, no zero: one must stay negative
        return sum_non_neg - 2 * min_abs
```

### Complexity Analysis

- **Time Complexity**: `O(n²)`
  - Single pass through all `n × n` elements
  - Constant work per element

- **Space Complexity**: `O(1)`
  - Only using a few variables regardless of matrix size
  - No additional data structures needed

### Visual Example

Let's trace Example 1: `matrix = [[1,-1],[-1,1]]`

**Initial state:**
```
[ 1, -1]
[-1,  1]
```
- Negative count: 2 (even)
- Has zero: No
- Sum of absolutes: 1+1+1+1 = 4
- Min absolute: 1

**Since negative count is even** → Can eliminate all negatives → Return 4

**Actual operations to achieve this:**
```
Step 1: Flip (0,0) and (0,1): [[-1, 1], [-1, 1]]
Step 2: Flip (0,0) and (1,0): [[ 1, 1], [ 1, 1]]
```

Final sum: 1+1+1+1 = **4** ✓

### Edge Cases

1. **All positive numbers**: Already maximal, return sum (even negatives: 0)
2. **All negative numbers**: 
   - If even count: all become positive
   - If odd count: smallest magnitude stays negative
3. **Contains zero**: Always return sum of absolute values
4. **Single negative**: Odd count, return `sum_abs - 2×min_abs`
5. **Large matrix (250×250)**: Algorithm handles efficiently in O(n²)

### Key Takeaways

1. **Don't simulate operations**—they're too complex to track; focus on the end state
2. **Mathematical invariant**: Parity of negative count determines possibility
3. **Greedy approach**: Maximize by making all positive OR keep smallest negative
4. **Zero is special**: Acts as a "sink" that absorbs negativity without cost
5. **Connectivity matters**: Grid structure allows moving negativity anywhere

# Tags

`Array` `Matrix` `Greedy` `Math` `Parity`


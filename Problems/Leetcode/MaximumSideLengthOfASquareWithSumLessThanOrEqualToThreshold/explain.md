## Problem

https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/description/

Given a `m x n` matrix `mat` and an integer `threshold`, return the maximum side-length of a square with a sum less than or equal to `threshold` or return `0` if there is no such square.

**Example 1:**
```
Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
```

**Example 2:**
```
Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0
```

**Constraints:**
- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 300`
- `0 <= mat[i][j] <= 10^4`
- `0 <= threshold <= 10^5`

## Observations

1. **Search Space**: The maximum possible square side length is `min(m, n)` since we can't have a square larger than the smallest dimension of the matrix.

2. **Monotonic Property**: If a square of side length `k` has a sum greater than the threshold, then any square of side length greater than `k` will also have a sum greater than the threshold. This monotonic property makes binary search applicable.

3. **Submatrix Sum Problem**: To efficiently calculate the sum of any square submatrix, we need a way to compute submatrix sums in O(1) time. This is where **2D Prefix Sum** comes in.

4. **2D Prefix Sum**: 
   - `ps[i][j]` represents the sum of all elements in the rectangle from `(0,0)` to `(i-1, j-1)`
   - Formula: `ps[i+1][j+1] = mat[i][j] + ps[i][j+1] + ps[i+1][j] - ps[i][j]`
   - To get sum of submatrix from `(r1, c1)` to `(r2, c2)`: 
     ```
     sum = ps[r2+1][c2+1] - ps[r1][c2+1] - ps[r2+1][c1] + ps[r1][c1]
     ```

5. **Binary Search Strategy**: Instead of checking all possible side lengths linearly (1, 2, 3, ..., min(m,n)), we can use binary search to find the maximum valid side length in O(log(min(m,n))) iterations.

## Solution

### Approach: 2D Prefix Sum + Binary Search

**Algorithm:**

1. **Build 2D Prefix Sum Array**:
   - Create a `(m+1) x (n+1)` array where `ps[i][j]` stores the sum of all elements in the rectangle from `(0,0)` to `(i-1, j-1)`
   - Time: O(m × n), Space: O(m × n)

2. **Binary Search on Side Length**:
   - Search range: `[1, min(m, n)]`
   - For each mid value, check if there exists a square of that side length with sum ≤ threshold

3. **Check Function**:
   - For a given side length `k`, iterate through all possible top-left corners `(i, j)`
   - Calculate the sum of the square using the prefix sum array in O(1)
   - If any square satisfies the condition, return `True`

**Time Complexity:** O(m × n × log(min(m, n)))
- Building prefix sum: O(m × n)
- Binary search iterations: O(log(min(m, n)))
- Each check: O(m × n) to iterate through all possible squares

**Space Complexity:** O(m × n) for the prefix sum array

### Implementation Details:

```python
class Solution:
    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        m = len(mat)
        n = len(mat[0])

        # Step 1: Build 2D prefix sum array
        def build_prefix_sum() -> List[List[int]]:
            if not mat or not mat[0]:
                return [[0]]
            rows, cols = len(mat), len(mat[0])
            ps = [[0] * (cols + 1) for _ in range(rows + 1)]
            for i in range(rows):
                for j in range(cols):
                    # Inclusion-exclusion principle
                    ps[i + 1][j + 1] = mat[i][j] + ps[i][j + 1] + ps[i + 1][j] - ps[i][j]
            return ps
        
        ps = build_prefix_sum()

        # Step 2: Helper to calculate submatrix sum in O(1)
        def submatrix_sum(ps: List[List[int]], r1: int, c1: int, r2: int, c2: int) -> int:
            return ps[r2 + 1][c2 + 1] - ps[r1][c2 + 1] - ps[r2 + 1][c1] + ps[r1][c1]

        # Step 3: Check if there exists a square of side length k with sum <= threshold
        def check_len(k: int) -> bool:
            for i in range(m - k + 1):  # Top-left row
                for j in range(n - k + 1):  # Top-left column
                    s = submatrix_sum(ps, i, j, i + k - 1, j + k - 1)
                    if s <= threshold:
                        return True
            return False

        # Step 4: Binary search for maximum valid side length
        res = 0
        left = 1
        right = min(m, n)
        while left <= right:
            mid = left + (right - left) // 2
            if check_len(mid):
                res = mid  # Found valid length, try larger
                left = mid + 1
            else:
                right = mid - 1  # Too large, try smaller
        return res
```

**Key Insights:**
- The 2D prefix sum technique transforms an O(k²) submatrix sum calculation into O(1)
- Binary search reduces the number of side lengths we need to check from O(min(m,n)) to O(log(min(m,n)))
- The combination of these two techniques makes the solution efficient enough for the given constraints (m, n ≤ 300)

# Tags
`Array` `Matrix` `Binary Search` `Prefix Sum` `2D Prefix Sum`


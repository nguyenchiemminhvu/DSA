## Problem

https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/description/

```
You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.

The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).

Find the kth largest value (1-indexed) of all the coordinates of matrix.

Example 1:
Input: matrix = [[5,2],[1,6]], k = 1
Output: 7
Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.

Example 2:
Input: matrix = [[5,2],[1,6]], k = 2
Output: 5
Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd largest value.

Example 3:
Input: matrix = [[5,2],[1,6]], k = 3
Output: 4
Explanation: The value of coordinate (1,0) is 5 XOR 1 = 4, which is the 3rd largest value.

Constraints:
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 1000
- 0 <= matrix[i][j] <= 10^6
- 1 <= k <= m * n
```

## Observations

1. **XOR Rectangle Property**: For each coordinate (i, j), we need the XOR of all elements in the rectangle from (0, 0) to (i, j).

2. **2D Prefix XOR**: Similar to prefix sums, we can compute prefix XOR values. The key insight is:
   - `prefix[i][j] = prefix[i-1][j] XOR prefix[i][j-1] XOR prefix[i-1][j-1] XOR matrix[i][j]`
   - This works because XOR is self-inverse: `a XOR a = 0`

3. **Efficient K-th Largest**: Instead of storing all m*n values and sorting, we can use a min-heap of size k:
   - Keep only the k largest values seen so far
   - The root of the heap will be the k-th largest value

4. **Space Optimization**: We can reuse the input matrix to store prefix XOR values, avoiding extra O(m*n) space.

## Solution

### Approach: 2D Prefix XOR + Min-Heap

**Algorithm:**
1. Compute prefix XOR for each cell (i, j) using the formula:
   - Current row XOR up to column j
   - Add contribution from previous row: `prefix[i-1][j]`
   - The formula: `cur ^= matrix[i][j]`, then `temp = cur ^ prefix[i-1][j]` (if i > 0)

2. Maintain a min-heap of size k:
   - Push each prefix XOR value into the heap
   - If heap size exceeds k, remove the smallest element
   - After processing all cells, the heap root is the k-th largest

3. Store computed prefix XOR values back in the matrix for reuse in subsequent rows.

**Code:**
```python
import heapq

class Solution:
    def kthLargestValue(self, mat: List[List[int]], k: int) -> int:
        m = len(mat)
        n = len(mat[0])
        
        pq = []  # min-heap to store k largest values
        
        for i in range(m):
            cur = 0  # XOR accumulator for current row
            for j in range(n):
                # Compute XOR for current row up to column j
                cur ^= mat[i][j]
                
                # Compute prefix XOR including previous rows
                temp = cur
                if i > 0:
                    # XOR with the prefix XOR value from the cell above
                    temp ^= mat[i - 1][j]
                
                # Maintain min-heap of size k
                heapq.heappush(pq, temp)
                if len(pq) > k:
                    heapq.heappop(pq)
                
                # Store prefix XOR for future rows
                mat[i][j] = temp
        
        return pq[0]  # k-th largest value (minimum in heap of k largest)
```

**Complexity Analysis:**
- **Time Complexity**: O(m * n * log k)
  - We iterate through all m*n cells
  - Each heap operation (push/pop) takes O(log k)
- **Space Complexity**: O(k)
  - Min-heap stores at most k elements
  - We reuse the input matrix for prefix XOR storage

**Why This Works:**
- **XOR Properties**: 
  - `a XOR a = 0` (self-inverse)
  - `a XOR 0 = a` (identity)
  - XOR is commutative and associative
  
- **Prefix XOR Formula**: For cell (i, j):
  ```
  prefix[i][j] = XOR of rectangle from (0,0) to (i,j)
               = prefix[i-1][j] XOR prefix[i][j-1] XOR prefix[i-1][j-1] XOR matrix[i][j]
  ```
  But the code uses row-wise accumulation: `cur` holds XOR of current row up to column j, then XORs with `mat[i-1][j]` to include all previous rows.

- **Min-Heap Optimization**: Keeping only k elements avoids sorting all m*n values, which would be O(m*n log(m*n)).

# Tags
#2D-Array #Prefix-XOR #Heap #Priority-Queue #Bit-Manipulation #Dynamic-Programming


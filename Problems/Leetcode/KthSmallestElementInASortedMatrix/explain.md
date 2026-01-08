## Problem

https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/

Given an `n x n` matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

You must find a solution with a memory complexity better than O(n²).

**Example 1:**
```
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
```

**Example 2:**
```
Input: matrix = [[-5]], k = 1
Output: -5
```

**Constraints:**
- `n == matrix.length == matrix[i].length`
- `1 <= n <= 300`
- `-10⁹ <= matrix[i][j] <= 10⁹`
- All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order
- `1 <= k <= n²`

**Follow-up:**
1. Could you solve the problem with a constant memory (i.e., O(1) memory complexity)?
2. Could you solve the problem in O(n) time complexity?

## Observations

### Key Insights

1. **Sorted Property**: Both rows and columns are sorted in ascending order
   - Each row is sorted: `matrix[i][0] <= matrix[i][1] <= ... <= matrix[i][n-1]`
   - Each column is sorted: `matrix[0][j] <= matrix[1][j] <= ... <= matrix[n-1][j]`
   - The smallest element is always at `matrix[0][0]`
   - The largest element is always at `matrix[n-1][n-1]`

2. **Memory Constraint**: The problem requires memory complexity better than O(n²)
   - Storing all elements would be O(n²), which violates the constraint
   - We need a selective approach

3. **Not Necessarily Sorted Across All Elements**: While rows and columns are individually sorted, elements across different rows/columns may not follow a strict order
   - Example: `matrix[0][2]` might be greater than `matrix[1][0]`

4. **Duplicate Elements**: The problem allows duplicates and counts them separately

5. **Value Range**: We know the minimum and maximum values in the matrix
   - This can be leveraged for binary search approaches

## Solution

### Approach 1: Max Heap (Provided Solution)

**Idea**: Use a max heap to maintain the k smallest elements encountered so far.

**Algorithm**:
```python
import heapq

class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        n = len(mat)
        pq = []
        for row in mat:
            for val in row:
                heapq.heappush(pq, -val)  # Negate to simulate max heap
                if len(pq) > k:
                    heapq.heappop(pq)  # Remove largest element
        
        return -heapq.heappop(pq)  # Return kth smallest
```

**How It Works**:
1. Iterate through all n² elements in the matrix
2. For each element, push its negative value to the heap (Python's heapq is a min heap, so negating creates max heap behavior)
3. If heap size exceeds k, remove the largest element (smallest negative = largest positive)
4. After processing all elements, the heap contains the k smallest elements
5. The root of the max heap (top element) is the kth smallest

**Example Walkthrough** (matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8):
```
After processing [1,5,9,10,11,12,13,13]: heap = [-13,-13,-12,-11,-10,-9,-5,-1]
After 15: heap = [-13,-12,-11,-10,-9,-5,-1,1] (removed -15, kept 8 smallest)
Result: -(-13) = 13
```

**Complexity Analysis**:
- **Time**: O(n² log k) - Process n² elements, each heap operation is O(log k)
- **Space**: O(k) - Heap stores at most k elements

**Pros**: ✅ Simple, works for all cases, memory efficient when k is small  
**Cons**: ❌ Doesn't utilize sorted property, processes all n² elements

---

### Approach 2: Min Heap (Optimized)

**Idea**: Leverage the sorted property by using a min heap to explore elements in increasing order.

**Algorithm**:
```python
import heapq

class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        n = len(mat)
        
        # Min heap: (value, row, col)
        min_heap = [(mat[0][0], 0, 0)]
        visited = {(0, 0)}
        
        for _ in range(k):
            val, r, c = heapq.heappop(min_heap)
            
            # Add right neighbor if valid and not visited
            if c + 1 < n and (r, c + 1) not in visited:
                heapq.heappush(min_heap, (mat[r][c + 1], r, c + 1))
                visited.add((r, c + 1))
            
            # Add bottom neighbor if valid and not visited
            if r + 1 < n and (r + 1, c) not in visited:
                heapq.heappush(min_heap, (mat[r + 1][c], r + 1, c))
                visited.add((r + 1, c))
        
        return val
```

**How It Works**:
1. Start with the smallest element at (0, 0)
2. Repeatedly extract the minimum from the heap
3. For each extracted element, add its right and bottom neighbors to the heap
4. Use a visited set to avoid processing the same cell twice
5. After k extractions, we have the kth smallest element

**Why This Works**: The sorted property guarantees that the next smallest element must be either to the right or below the current smallest unprocessed elements.

**Complexity Analysis**:
- **Time**: O(k log k) - Extract k elements, heap size ≤ k
- **Space**: O(min(n, k)) - Heap and visited set

**Pros**: ✅ Utilizes sorted property, faster when k << n²  
**Cons**: ❌ More complex, requires visited set

---

### Approach 3: Binary Search on Value (Most Efficient)

**Idea**: Binary search on the value range [min, max]. For each mid value, count how many elements ≤ mid.

**Algorithm**:
```python
class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        n = len(mat)
        
        def count_less_equal(mid):
            """Count elements <= mid using sorted property"""
            count = 0
            col = n - 1  # Start from top-right corner
            
            for row in range(n):
                # Move left while elements are > mid
                while col >= 0 and mat[row][col] > mid:
                    col -= 1
                count += (col + 1)
            
            return count
        
        left, right = mat[0][0], mat[n-1][n-1]
        
        while left < right:
            mid = (left + right) // 2
            count = count_less_equal(mid)
            
            if count < k:
                left = mid + 1  # Need larger values
            else:
                right = mid  # mid might be the answer
        
        return left
```

**How It Works**:
1. Binary search on value range [matrix[0][0], matrix[n-1][n-1]]
2. For each mid value, count elements ≤ mid in O(n) time
3. If count < k, search in larger values (left = mid + 1)
4. If count ≥ k, search in smaller values (right = mid)
5. Converge to the kth smallest element

**Counting Trick**: Start from top-right corner and move left/down:
- If current > mid, move left (smaller values)
- If current ≤ mid, count entire column up to current row, move down

**Complexity Analysis**:
- **Time**: O(n log(max - min)) - Binary search × O(n) counting
- **Space**: O(1) - **Constant space! Satisfies follow-up**

**Pros**: ✅ Best time complexity, O(1) space, clever use of sorted property  
**Cons**: ❌ Most complex to understand and implement

---

### Comparison Summary

| Approach | Time | Space | Difficulty | Best For |
|----------|------|-------|------------|----------|
| Max Heap | O(n² log k) | O(k) | Easy | Small k, simple solution |
| Min Heap | O(k log k) | O(min(n,k)) | Medium | k << n², interview optimization |
| Binary Search | O(n log(max-min)) | O(1) | Hard | Large matrices, follow-up |

---

### Interview Strategy

1. **Start with Approach 1**: Show you can solve the problem correctly
2. **Discuss Approach 2**: Demonstrate understanding of the sorted property
3. **Mention Approach 3**: Show advanced knowledge for O(1) space follow-up

---

### Common Pitfalls

❌ Flattening entire matrix into array (violates space constraint)  
❌ Not handling duplicates correctly  
❌ Forgetting visited set in min heap approach  
❌ Incorrect counting logic in binary search  
❌ Not negating values in max heap (Python's heapq is min heap)

# Tags

`Matrix` `Heap` `Binary Search` `Sorted Matrix` `Priority Queue` `Two Pointers`


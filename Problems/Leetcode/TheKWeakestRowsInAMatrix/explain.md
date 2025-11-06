## Problem

https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/

```
You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians). The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all the 0's in each row.

A row i is weaker than a row j if one of the following is true:

The number of soldiers in row i is less than the number of soldiers in row j.
Both rows have the same number of soldiers and i < j.
Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.

Example 1:

Input: mat = 
[[1,1,0,0,0],
 [1,1,1,1,0],
 [1,0,0,0,0],
 [1,1,0,0,0],
 [1,1,1,1,1]], 
k = 3
Output: [2,0,3]
Explanation: 
The number of soldiers in each row is: 
- Row 0: 2 
- Row 1: 4 
- Row 2: 1 
- Row 3: 2 
- Row 4: 5 
The rows ordered from weakest to strongest are [2,0,3,1,4].

Example 2:

Input: mat = 
[[1,0,0,0],
 [1,1,1,1],
 [1,0,0,0],
 [1,0,0,0]], 
k = 2
Output: [0,2]
Explanation: 
The number of soldiers in each row is: 
- Row 0: 1 
- Row 1: 4 
- Row 2: 1 
- Row 3: 1 
The rows ordered from weakest to strongest are [0,2,3,1].

Constraints:

m == mat.length
n == mat[i].length
2 <= n, m <= 100
1 <= k <= m
matrix[i][j] is either 0 or 1.
```

## Observations

1. **Problem Understanding**: We need to find the k weakest rows in a binary matrix where:
   - Each row contains soldiers (1s) followed by civilians (0s)
   - A row is weaker if it has fewer soldiers, or same soldiers but smaller index
   - Return k weakest row indices in order from weakest to strongest

2. **Key Insights**:
   - The strength of a row is determined by the sum of 1s (soldiers count)
   - When soldier counts are equal, the row with smaller index is weaker
   - We need to sort rows by (soldier_count, row_index) and take first k

3. **Algorithm Choice**: Min-heap is perfect for this problem because:
   - We can store (soldier_count, row_index) tuples
   - Python's heapq automatically sorts by first element, then second
   - We can extract the k smallest elements efficiently

4. **Time Complexity**: O(m log m + k log m) where m is number of rows
   - O(m) to count soldiers in each row
   - O(m log m) to build heap
   - O(k log m) to extract k elements

5. **Space Complexity**: O(m) for the heap

## Solution

1. **Initialize**: Create empty min-heap and get matrix dimensions
2. **Build heap**: For each row, calculate soldier count using `sum(mat[i])` and push `(soldier_count, row_index)` to heap
3. **Extract results**: Pop k elements from heap - they come out in ascending order of weakness
4. **Return**: List of row indices in order from weakest to strongest

**Why this works**:
- `sum(mat[i])` counts soldiers since each soldier is represented by 1
- Heap naturally orders by (soldier_count, row_index) due to tuple comparison
- Min-heap ensures we get weakest rows first
- The solution handles tie-breaking automatically (same soldier count → smaller index wins)

**Example walkthrough** with `mat = [[1,1,0,0,0], [1,1,1,1,0], [1,0,0,0,0], [1,1,0,0,0], [1,1,1,1,1]]`:
- Row counts: [2, 4, 1, 2, 5]
- Heap: [(1,2), (2,0), (2,3), (4,1), (5,4)]
- Pop 3 times: (1,2), (2,0), (2,3) → [2, 0, 3]

# Tags

- Array
- Binary Search
- Matrix  
- Heap (Priority Queue)
- Sorting


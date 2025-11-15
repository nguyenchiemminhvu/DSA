## Problem

https://leetcode.com/problems/delete-greatest-value-in-each-row/description/

```
You are given an m x n matrix grid consisting of positive integers.

Perform the following operation until grid becomes empty:

Delete the element with the greatest value from each row. If multiple such elements exist, delete any of them.
Add the maximum of deleted elements to the answer.
Note that the number of columns decreases by one after each operation.

Return the answer after performing the operations described above.

Example 1:

Input: grid = [[1,2,4],[3,3,1]]
Output: 8
Explanation: The diagram above shows the removed values in each step.
- In the first operation, we remove 4 from the first row and 3 from the second row (notice that, there are two cells with value 3 and we can remove any of them). We add 4 to the answer.
- In the second operation, we remove 2 from the first row and 3 from the second row. We add 3 to the answer.
- In the third operation, we remove 1 from the first row and 1 from the second row. We add 1 to the answer.
The final answer = 4 + 3 + 1 = 8.

Example 2:

Input: grid = [[10]]
Output: 10
Explanation: The diagram above shows the removed values in each step.
- In the first operation, we remove 10 from the first row. We add 10 to the answer.
The final answer = 10.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j] <= 100
```

## Observations

1. **Key Insight**: In each operation, we need to find the maximum element in each row and then take the maximum among all those maximum elements.

2. **Pattern Recognition**: If we sort each row in ascending order, the maximum element in each row will always be at the rightmost position. After each operation, we effectively remove the rightmost column.

3. **Optimization Strategy**: Instead of simulating the actual deletion process (which would be O(n) for each deletion), we can:
   - Sort each row once at the beginning
   - Process columns from right to left (largest to smallest within each row)
   - For each column position, find the maximum value across all rows

4. **Time Complexity Analysis**: 
   - Sorting all rows: O(m × n log n) where m is number of rows, n is number of columns
   - Processing columns: O(m × n) to iterate through all elements
   - Overall: O(m × n log n)

5. **Space Complexity**: O(1) extra space if we modify the input grid in-place, or O(m × n) if we create new sorted arrays.

## Solution

1. **Sort Each Row**: `grid = [sorted(row) for row in grid]`
   - Sort each row in ascending order
   - Now the largest element in each row is at the rightmost position
   - The second largest is at the second rightmost position, and so on

2. **Process Columns Right to Left**: `for i in range(n - 1, -1, -1):`
   - Start from the rightmost column (index n-1) and move left
   - This simulates removing the maximum element from each row in each operation

3. **Find Maximum Among Row Maximums**: `max(row[i] for row in grid)`
   - For column i, get the element at position i from each row
   - Find the maximum among these elements
   - This represents the maximum of all deleted elements in this operation

4. **Accumulate Result**: `res += max(...)`
   - Add the maximum deleted element to the total result

**Example Walkthrough**:
- Input: `[[1,2,4],[3,3,1]]`
- After sorting: `[[1,2,4],[1,3,3]]`
- Operation 1 (i=2): max(4, 3) = 4, result = 4
- Operation 2 (i=1): max(2, 3) = 3, result = 7  
- Operation 3 (i=0): max(1, 1) = 1, result = 8

This approach is much more efficient than simulating the actual deletion process, which would require repeatedly finding and removing maximum elements.

# Tags
- Array
- Matrix
- Sorting
- Greedy


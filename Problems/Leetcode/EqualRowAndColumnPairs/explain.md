## Problem

https://leetcode.com/problems/equal-row-and-column-pairs/description

# Equal Row and Column Pairs

## Problem

https://leetcode.com/problems/equal-row-and-column-pairs/description

Given a 0-indexed **n x n** integer matrix `grid`, return the number of pairs `(ri, cj)` such that:
- Row `ri` and column `cj` are **equal**
- A row and column pair is considered equal if they contain the **same elements in the same order** (i.e., an equal array)

### Examples

**Example 1:**
```
Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
Output: 1
Explanation: There is 1 equal row and column pair:
- (Row 2, Column 1): [2,7,7]
```

**Example 2:**
```
Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
Output: 3
Explanation: There are 3 equal row and column pairs:
- (Row 0, Column 0): [3,1,2,2]
- (Row 2, Column 2): [2,4,2,2]
- (Row 3, Column 2): [2,4,2,2]
```

### Constraints
- `n == grid.length == grid[i].length`
- `1 <= n <= 200`
- `1 <= grid[i][j] <= 10^5`

## Observations

1. **Brute Force Approach**: We could compare each row with each column, but that would be **O(n³)** time complexity (n rows × n columns × n comparisons per pair).

2. **Key Insight - Use Hashing**: Instead of comparing each row with every column, we can:
   - Store all rows in a hash map using their tuple representation as a key
   - Count the frequency of each row
   - For each column, check if it exists in the hash map and add its count to the result

3. **Why Tuples?**: 
   - Lists are mutable and cannot be used as dictionary keys
   - Tuples are immutable and hashable, allowing them to be dictionary keys
   - Converting a row/column to a tuple maintains order and content for comparison

4. **Time Complexity**: 
   - Building row map: **O(n²)** (n rows × n elements per row)
   - Extracting and checking columns: **O(n²)** (n columns × n elements per column)
   - Overall: **O(n²)** instead of **O(n³)**

5. **Space Complexity**: **O(n²)** for storing all rows in the hash map

## Solution

```python
from collections import defaultdict
from typing import List

class Solution:
    def equalPairs(self, grid: List[List[int]]) -> int:
        # Step 1: Create a hash map to store row frequencies
        row_map = defaultdict(int)
        for row in grid:
            # Convert row to tuple so it can be used as a dictionary key
            row_map[tuple(row)] += 1

        # Step 2: Count matches by checking each column
        res = 0
        for i in range(len(grid)):
            # Extract column i as a tuple
            col_tup = tuple([row[i] for row in grid])
            # Add the frequency of this column (number of matching rows)
            res += row_map[col_tup]
        
        return res
```

### Step-by-Step Explanation

**Step 1: Build Row Map**
```python
row_map = defaultdict(int)
for row in grid:
    row_map[tuple(row)] += 1
```
- Iterate through each row in the grid
- Convert each row (list) to a tuple so it can be used as a dictionary key
- Increment the count for that row pattern
- For Example 2, after this step:
  - `(3,1,2,2)`: 1 (appears at row 0)
  - `(1,4,4,5)`: 1 (appears at row 1)
  - `(2,4,2,2)`: 2 (appears at rows 2 and 3)

**Step 2: Check Columns Against Row Map**
```python
res = 0
for i in range(len(grid)):
    col_tup = tuple([row[i] for row in grid])
    res += row_map[col_tup]
```
- For each column index `i` from 0 to n-1:
  - Extract column `i` as a tuple: `[row[i] for row in grid]`
  - Look up this column pattern in `row_map`
  - Add the frequency (number of matching rows) to the result

**Example 2 Walkthrough:**
```
Grid:
[3, 1, 2, 2]  <- Row 0
[1, 4, 4, 5]  <- Row 1
[2, 4, 2, 2]  <- Row 2
[2, 4, 2, 2]  <- Row 3

Row Map: {(3,1,2,2): 1, (1,4,4,5): 1, (2,4,2,2): 2}

Column 0: (3, 1, 2, 2) ✓ Matches Row 0 → count += 1
Column 1: (1, 4, 4, 4) ✗ No match → count += 0
Column 2: (2, 4, 2, 2) ✓ Matches Rows 2,3 → count += 2
Column 3: (2, 5, 2, 2) ✗ No match → count += 0

Result: 1 + 2 = 3
```

## Complexity Analysis

| Metric | Value | Explanation |
|--------|-------|-------------|
| **Time Complexity** | O(n²) | n rows × n elements to build map + n columns × n elements to check |
| **Space Complexity** | O(n²) | Storing up to n rows in the hash map, each of size n |

## Key Takeaways

1. **Hash Map Optimization**: Converting an O(n³) brute force solution to O(n²) by using a hash map to store patterns
2. **Immutability for Hashing**: Using tuples instead of lists allows us to use sequences as dictionary keys
3. **Frequency Counting**: Instead of binary matching, count frequencies to handle duplicate row patterns
4. **Column Extraction**: Use list comprehension to elegantly extract columns from the 2D grid

# Tags
- Hash Map / Dictionary
- Frequency Counting
- 2D Array Manipulation
- LeetCode Medium

## Observations

## Solution

# Tags


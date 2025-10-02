## Problem Description

https://leetcode.com/problems/k-th-symbol-in-grammar/description/

```
We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.

Example 1:

Input: n = 1, k = 1
Output: 0
Explanation: row 1: 0

Example 2:

Input: n = 2, k = 1
Output: 0
Explanation: 
row 1: 0
row 2: 01

Example 3:

Input: n = 2, k = 2
Output: 1
Explanation: 
row 1: 0
row 2: 01

Constraints:

1 <= n <= 30
1 <= k <= 2n - 1
```

## Observations

Let's look at how the grammar pattern grows:

```
Row 1: 0
Row 2: 01
Row 3: 0110
Row 4: 01101001
Row 5: 0110100110010110
...
```

### Key Pattern Discovery:

1. **First half = Previous row**: The first half of each row is exactly the same as the previous row
2. **Second half = Flipped previous row**: The second half is the previous row with 0s and 1s flipped (0→1, 1→0)

For example, in Row 3:
- Previous row (Row 2): `01`
- First half of Row 3: `01` (same as Row 2)
- Second half of Row 3: `10` (flipped version of `01`)
- Complete Row 3: `0110`

### Length Pattern:
- Row 1 has length 1 (2^0)
- Row 2 has length 2 (2^1) 
- Row 3 has length 4 (2^2)
- Row n has length 2^(n-1)

This means the previous row (Row n-1) has length 2^(n-2), which is exactly half the current row's length!

## Solution

### Approach: Recursive Divide and Conquer

The key insight is that we don't need to build the entire string. We can use the pattern to find the kth symbol directly:

1. **Base case**: If n=1, the only symbol is 0
2. **Recursive case**: 
   - Calculate the length of the previous row: `2^(n-2)`
   - If k is in the first half (k ≤ previous_length):
     - The symbol is the same as the kth symbol in the previous row
   - If k is in the second half (k > previous_length):
     - The symbol is the flipped version of the (k - previous_length)th symbol in the previous row

### Step-by-Step Example:

Let's trace `kthGrammar(4, 6)`:

```
Row 4: 01101001 (we want the 6th symbol, which is 0)
```

1. n=4, k=6
   - prev_len = 2^(4-2) = 4
   - k=6 > 4, so we're in the second half
   - Return 1 - kthGrammar(3, 6-4) = 1 - kthGrammar(3, 2)

2. n=3, k=2  
   - prev_len = 2^(3-2) = 2
   - k=2 ≤ 2, so we're in the first half
   - Return kthGrammar(2, 2)

3. n=2, k=2
   - prev_len = 2^(2-2) = 1  
   - k=2 > 1, so we're in the second half
   - Return 1 - kthGrammar(1, 2-1) = 1 - kthGrammar(1, 1)

4. n=1, k=1
   - Base case: return 0

5. Backtrack: 1 - 0 = 1, then 1, then 1 - 1 = 0

So the 6th symbol in row 4 is 0!

### Time & Space Complexity:
- **Time**: O(n) - we make at most n recursive calls
- **Space**: O(n) - recursion stack depth is n

## Tags

string, recursion
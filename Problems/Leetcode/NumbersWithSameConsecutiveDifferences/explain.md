## Problem

https://leetcode.com/problems/numbers-with-same-consecutive-differences/description/

```
Given two integers n and k, return an array of all the integers of length n where the difference between every two consecutive digits is k. You may return the answer in any order.

Note that the integers should not have leading zeros. Integers as 02 and 043 are not allowed.

Example 1:
Input: n = 3, k = 7
Output: [181,292,707,818,929]
Explanation: Note that 070 is not a valid number, because it has leading zeroes.

Example 2:
Input: n = 2, k = 1
Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]

Constraints:
- 2 <= n <= 9
- 0 <= k <= 9
```

## Observations

1. **No Leading Zeros**: The first digit must be between 1-9 (not 0) to avoid leading zeros.

2. **Consecutive Difference Constraint**: For each digit at position `i`, the next digit at position `i+1` must differ by exactly `k` from the current digit. This means if the current digit is `d`, the next digit can be either:
   - `d + k` (if it's in range [0, 9])
   - `d - k` (if it's in range [0, 9])

3. **Edge Case - k=0**: When k=0, both `d + k` and `d - k` give the same result `d`, so we need to avoid duplicates by using a set.

4. **Backtracking/DFS Approach**: We can build numbers digit by digit using DFS, starting from each valid first digit (1-9) and exploring all valid next digits.

5. **Number of Digits**: Since n ≤ 9, the maximum number length is small, making DFS efficient.

## Solution

### Approach: Depth-First Search (Backtracking)

The solution uses DFS to build valid numbers digit by digit:

**Algorithm Steps:**
1. Initialize an empty result list
2. For each starting digit from 1 to 9:
   - Start DFS with this digit as the first digit
   - In each DFS call:
     - If we've built n digits, convert the digit list to a number and add to result
     - Otherwise, calculate possible next digits: `current_digit ± k`
     - For each valid next digit (in range [0, 9]):
       - Recursively call DFS with the new digit appended
3. Return the result list

**Key Implementation Details:**

```python
class Solution:
    def numsSameConsecDiff(self, n: int, k: int) -> List[int]:
        res = []
        
        def dfs(i: int, tmp: List[int]) -> None:
            # Base case: we've built n digits
            if i == n - 1:
                # Convert digit list to integer
                num = 0
                for val in tmp:
                    num = num * 10 + val
                res.append(num)
                return
            
            # Try both next possible digits: current ± k
            # Use set() to avoid duplicates when k=0
            for val in set([tmp[-1] - k, tmp[-1] + k]):
                # Check if digit is valid (0-9)
                if val >= 0 and val <= 9:
                    dfs(i + 1, tmp + [val])
        
        # Start DFS from each non-zero first digit
        for start in range(1, 10):
            dfs(0, [start])
        
        return res
```

**Why `set([tmp[-1] - k, tmp[-1] + k])`?**
- When k=0, both expressions evaluate to the same value
- Using a set automatically removes the duplicate
- Example: if current digit is 5 and k=0, set([5-0, 5+0]) = set([5, 5]) = {5}

**Time Complexity:** O(2^n) in the worst case
- For each position (except first), we potentially have 2 choices
- However, the constraint that digits must be in [0, 9] prunes many branches
- We have 9 starting points (digits 1-9)

**Space Complexity:** O(n)
- Recursion depth is at most n (number of digits)
- The `tmp` list stores at most n digits at any level

**Example Walkthrough (n=3, k=7):**
- Start with 1: 1 → 8 (1+7) → 1 (8-7) = **181** ✓
- Start with 2: 2 → 9 (2+7) → 2 (9-7) = **292** ✓
- Start with 7: 7 → 0 (7-7) → 7 (0+7) = **707** ✓
- Start with 8: 8 → 1 (8-7) → 8 (1+7) = **818** ✓
- Start with 9: 9 → 2 (9-7) → 9 (2+7) = **929** ✓

# Tags

`Backtracking` `Depth-First Search` `Recursion` `Number Building`


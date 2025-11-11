## Problem

https://leetcode.com/problems/unique-3-digit-even-numbers/

```
You are given an array of digits called digits. Your task is to determine the number of distinct three-digit even numbers that can be formed using these digits.

Note: Each copy of a digit can only be used once per number, and there may not be leading zeros.

Example 1:

Input: digits = [1,2,3,4]

Output: 12

Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.

Example 2:

Input: digits = [0,2,2]

Output: 2

Explanation: The only 3-digit even numbers that can be formed are 202 and 220. Note that the digit 2 can be used twice because it appears twice in the array.

Example 3:

Input: digits = [6,6,6]

Output: 1

Explanation: Only 666 can be formed.

Example 4:

Input: digits = [1,3,5]

Output: 0

Explanation: No even 3-digit numbers can be formed.

Constraints:

3 <= digits.length <= 10
0 <= digits[i] <= 9
```

## Observations

1. **Problem Constraints**: 
   - We need to form exactly 3-digit numbers (100-999)
   - Numbers must be even (last digit must be 0, 2, 4, 6, or 8)
   - No leading zeros allowed (first digit cannot be 0)
   - Each digit from the input array can only be used once per number
   - We need to count distinct numbers (avoid duplicates)

2. **Key Requirements**:
   - **Valid 3-digit number**: First digit ∈ [1,9], middle digit ∈ [0,9], last digit ∈ [0,2,4,6,8]
   - **No duplicate digits per number**: Each position must use a different element from the input array
   - **Even constraint**: Last digit must have even parity
   - **Uniqueness**: Same number shouldn't be counted multiple times

3. **Edge Cases**:
   - Input with no even digits → Result = 0
   - Input with only zeros → Result = 0 (can't have leading zero)
   - Input with duplicate digits → Can form same number in multiple ways, but count only once

4. **Approach Insight**:
   - This is a backtracking/permutation problem with constraints
   - Need to generate all possible 3-digit combinations and filter valid ones
   - Use a set to track unique valid numbers to avoid duplicates

## Solution

The solution uses **backtracking with constraint checking** to generate all valid 3-digit even numbers.

### Algorithm Breakdown:

1. **Setup**:
   - `s`: Set to track which digit indices are currently being used (prevents reusing same digit)
   - `ss`: Set to store unique valid numbers as tuples (prevents counting duplicates)
   - `temp`: Current number being constructed (as list of 3 digits)
   - `count`: Final count of valid numbers

2. **DFS Function (`dfs(idx)`)**:
   - **Base Case** (`idx == 3`): We've filled all 3 positions
     - Check if number is valid: `temp[-1] % 2 == 0` (even) AND `temp[0] != 0` (no leading zero)
     - Check if number is unique: `tuple(temp) not in ss`
     - If valid and unique, add to set and increment counter
   
   - **Recursive Case** (`idx < 3`): Try each available digit
     - For each unused digit index `i` (where `i not in s`):
       - Add digit to current position: `temp.append(digits[i])`
       - Mark index as used: `s.add(i)`
       - Recursively fill next position: `dfs(idx + 1)`
       - Backtrack: `s.remove(i)` and `temp.pop()`

3. **Validation Checks**:
   - **Even number**: `temp[-1] % 2 == 0` ensures last digit is even
   - **No leading zero**: `temp[0] != 0` ensures first digit is non-zero
   - **Uniqueness**: `tuple(temp) not in ss` prevents duplicate counting

### Example Walkthrough:

**Input**: `digits = [1,2,3,4]`

The algorithm explores all permutations:
- Position 0: Try 1,2,3,4 (all valid since none is 0)
- Position 1: Try remaining digits  
- Position 2: Try remaining digits, but only accept if even

**Valid combinations**: 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, 432
**Result**: 12

### Complexity Analysis:
- **Time Complexity**: O(n × n!) where n is the number of digits
  - We generate at most n! permutations, each taking O(n) time to validate
- **Space Complexity**: O(n) for recursion stack + O(k) for storing unique numbers where k is the result count

### Why This Approach Works:
- **Systematic exploration**: DFS ensures we explore all possible combinations
- **Constraint enforcement**: Checks ensure only valid 3-digit even numbers are counted
- **Duplicate prevention**: Using sets prevents counting the same number multiple times
- **Backtracking**: Allows us to reuse digits for different combinations while respecting the "no reuse within single number" constraint

# Tags

Array, Backtracking, Permutation, Set


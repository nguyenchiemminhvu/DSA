## Problem

https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/

```
You are given a positive integer n.

A binary string x is valid if all substrings of x of length 2 contain at least one "1".

Return all valid strings with length n, in any order.

Example 1:

Input: n = 3

Output: ["010","011","101","110","111"]

Explanation:

The valid strings of length 3 are: "010", "011", "101", "110", and "111".

Example 2:

Input: n = 1

Output: ["0","1"]

Explanation:

The valid strings of length 1 are: "0" and "1".

Constraints:

1 <= n <= 18
```

## Observations

1. **Problem Understanding**: We need to generate all binary strings of length `n` where no two adjacent characters are both '0'. In other words, the substring "00" should not appear anywhere in the string.

2. **Valid Patterns**: 
   - "01", "10", "11" are all valid 2-character substrings
   - "00" is the only invalid 2-character substring

3. **Brute Force Approach**: The solution uses a brute force approach by:
   - Generating all possible binary numbers from 0 to 2^n - 1
   - Converting each number to its binary representation
   - Checking if the binary string is valid (no adjacent zeros)

4. **Bit Manipulation**: The solution cleverly uses bit manipulation to:
   - Generate all possible n-bit numbers
   - Check for adjacent zeros using bitwise AND with `0b11` (binary 11, decimal 3)
   - Extract individual bits to construct the string

5. **Time Complexity**: O(n × 2^n) - we check each of the 2^n possible strings, and each validation takes O(n) time
6. **Space Complexity**: O(2^n) for storing the result (in the worst case, all strings might be valid)

## Solution

The solution uses a **brute force approach with bit manipulation**:

### Algorithm Steps:

1. **Generate all possible n-bit numbers**: From 0 to 2^n - 1
2. **Validate each number**: Check if its binary representation has no adjacent zeros
3. **Convert valid numbers to strings**: Extract bits and build the string representation

### Key Components:

#### `valid(val: int) -> bool` function:
```python
def valid(val:int) -> bool:
    for i in range(1, n):
        if (val & 0b11) == 0:  # Check if last 2 bits are both 0
            return False
        val >>= 1              # Shift right to check next pair
    return True
```

- Uses a sliding window of 2 bits (`0b11` mask)
- `val & 0b11` extracts the last 2 bits
- If both bits are 0, the result is 0, making the string invalid
- Right shift (`>>= 1`) moves to the next bit position

#### Main algorithm:
```python
total = (1 << n)           # Calculate 2^n
for t in range(total):     # Try all possible n-bit numbers
    if valid(t):           # Check if binary representation is valid
        # Convert number to binary string
        s = []
        for i in range(n):
            bit = int(((1 << i) & t) > 0)  # Extract i-th bit
            s.append(str(bit))
        s.reverse()            # Reverse to get correct bit order
        res.append("".join(s))
```

### Example Walkthrough (n=3):

For n=3, we check numbers 0-7:
- 0 (000): Invalid - has "00"
- 1 (001): Invalid - has "00" 
- 2 (010): Valid ✓
- 3 (011): Valid ✓
- 4 (100): Invalid - has "00"
- 5 (101): Valid ✓
- 6 (110): Valid ✓
- 7 (111): Valid ✓

Result: ["010", "011", "101", "110", "111"]

### Alternative Approaches:
1. **Backtracking**: Build strings character by character, avoiding invalid states
2. **Dynamic Programming**: Count valid strings ending with '0' vs '1'
3. **Recursive**: Generate strings by making valid choices at each position

## Tags

array, string, backtracking, brute force, bit manipulation
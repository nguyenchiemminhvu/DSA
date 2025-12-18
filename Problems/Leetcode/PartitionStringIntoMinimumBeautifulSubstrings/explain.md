## Problem

https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/description/

Given a binary string `s`, partition it into one or more substrings where each substring is **beautiful**.

A string is **beautiful** if:
1. It doesn't contain leading zeros
2. It's the binary representation of a number that is a power of 5

Return the minimum number of substrings in such partition. If impossible, return -1.

**Example 1:**
```
Input: s = "1011"
Output: 2
Explanation: ["101", "1"] where "101" = 5¹ = 5 and "1" = 5⁰ = 1
```

**Example 2:**
```
Input: s = "111"
Output: 3
Explanation: ["1", "1", "1"] where each "1" = 5⁰ = 1
```

**Example 3:**
```
Input: s = "0"
Output: -1
Explanation: Cannot partition into beautiful substrings (leading zero)
```

**Constraints:**
- 1 <= s.length <= 15
- s[i] is either '0' or '1'

## Observations

1. **Valid Beautiful Substrings**: First, we need to identify which values are powers of 5 in binary:
   - 5⁰ = 1 → "1"
   - 5¹ = 5 → "101"
   - 5² = 25 → "11001"
   - 5³ = 125 → "1111101"
   - 5⁴ = 625 → "1001110001"
   - 5⁵ = 3125 → "110000110101"
   - Since max length is 15, we only need to consider powers up to around 5⁶

2. **No Leading Zeros**: Any substring starting with '0' is automatically invalid, which helps prune our search space.

3. **DFS/Backtracking Approach**: Since we need to find the minimum partition:
   - Try all possible ways to partition the string
   - For each position, try all valid substrings starting from that position
   - Skip substrings with leading zeros
   - Check if the substring represents a power of 5
   - Recursively solve for the remaining string

4. **Small Input Size**: With length ≤ 15, a backtracking solution is feasible despite potentially exponential complexity.

## Solution

The solution uses **DFS (Depth-First Search) with backtracking** to explore all possible partitions:

### Algorithm:

1. **Helper Function - `is_power_of_5(val)`**:
   - Check if a number is a power of 5
   - Repeatedly divide by 5, checking if there's no remainder
   - Return true only if we reach exactly 1

2. **Main DFS Function**:
   - **Base Case**: If we've processed the entire string (`i >= n`), update the minimum count
   - **Recursive Case**: For each position `i`, try all substrings from `i` to `j`:
     - Skip if substring starts with '0' (leading zero)
     - Convert binary substring to decimal value
     - If value is a power of 5, add to current partition and recurse
     - Backtrack by removing the substring

3. **Binary to Decimal Conversion**:
   - Use bit shifting: `val = (val << 1) | int(c)`
   - Equivalent to: `val = val * 2 + int(c)`

### Code Walkthrough:

```python
class Solution:
    def minimumBeautifulSubstrings(self, s: str) -> int:
        # Helper to check if a number is a power of 5
        def is_power_of_5(val: int) -> bool:
            while val > 1:
                if val % 5 != 0:
                    return False
                val //= 5
            return val == 1
        
        n = len(s)
        count = [float('inf')]  # Use list to allow modification in nested function
        tmp = []  # Current partition
        
        def dfs(i: int) -> None:
            # Base case: reached end of string
            if i >= n:
                count[0] = min(count[0], len(tmp))
                return
            
            # Try all substrings starting at position i
            for j in range(i, n):
                sub = s[i:j+1]
                
                # Skip substrings with leading zeros
                if sub[0] == '0':
                    continue
                
                # Convert binary string to decimal
                val = 0
                for c in sub:
                    val = (val << 1) | int(c)  # Shift left and add bit
                
                # If it's a power of 5, explore this partition
                if is_power_of_5(val):
                    tmp.append(sub)
                    dfs(j + 1)  # Recurse on remaining string
                    tmp.pop()   # Backtrack
        
        dfs(0)
        return -1 if count[0] == 0 or count[0] == float('inf') else count[0]
```

### Complexity Analysis:

**Time Complexity**: O(2^n × n × log m)
- 2^n: In worst case, explore all possible partitions
- n: For each partition, iterate through substring
- log m: Check if number is power of 5 (where m is the value)
- Since n ≤ 15, this is manageable

**Space Complexity**: O(n)
- Recursion depth at most n
- tmp array stores at most n substrings

### Potential Optimizations:

1. **Memoization**: Cache results for each starting position with remaining string
2. **Pre-compute Powers**: Store all valid powers of 5 in a set for O(1) lookup
3. **Dynamic Programming**: Bottom-up approach with dp[i] = minimum partitions for s[0:i]

# Tags

- Backtracking
- DFS
- String
- Dynamic Programming
- Bit Manipulation


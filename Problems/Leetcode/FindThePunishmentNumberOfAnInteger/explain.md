## Problem

https://leetcode.com/problems/find-the-punishment-number-of-an-integer/description/

```
Given a positive integer n, return the punishment number of n.

The punishment number of n is defined as the sum of the squares of all integers i such that:
- 1 <= i <= n
- The decimal representation of i * i can be partitioned into contiguous substrings such that 
  the sum of the integer values of these substrings equals i.

Example 1:
Input: n = 10
Output: 182
Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions:
- 1 since 1 * 1 = 1
- 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 (8 + 1 = 9)
- 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 (10 + 0 = 10)
Hence, the punishment number of 10 is 1 + 81 + 100 = 182

Example 2:
Input: n = 37
Output: 1478
Explanation: There are exactly 4 integers i in the range [1, 37] that satisfy the conditions:
- 1 since 1 * 1 = 1
- 9 since 9 * 9 = 81 (8 + 1 = 9)
- 10 since 10 * 10 = 100 (10 + 0 = 10)
- 36 since 36 * 36 = 1296 (1 + 29 + 6 = 36)
Hence, the punishment number of 37 is 1 + 81 + 100 + 1296 = 1478

Constraints:
- 1 <= n <= 1000
```

## Observations

1. **Brute Force Approach**: For each number i from 1 to n, we need to:
   - Calculate i²
   - Check if i² can be partitioned into substrings that sum to i
   - This requires exploring all possible partitions (backtracking/DFS)

2. **Optimization via Precomputation**: Since n ≤ 1000, there are only a fixed set of valid numbers in the range [1, 1000] that satisfy the partition condition. We can precompute these numbers once.

3. **Why Precomputation Works**:
   - The constraint is small (n ≤ 1000)
   - The valid numbers don't change - they're mathematical constants
   - Computing all valid numbers once is more efficient than repeatedly checking partitions

4. **Valid Numbers Pattern**: The valid numbers in [1, 1000] are:
   - 1, 9, 10, 36, 45, 55, 82, 91, 99, 100, 235, 297, 369, 370, 379, 414, 657, 675, 703, 756, 792, 909, 918, 945, 964, 990, 991, 999, 1000
   - Only 29 numbers out of 1000!

5. **Partition Check Example**:
   - For i = 36: i² = 1296
   - Possible partitions: "1"+"2"+"9"+"6", "12"+"9"+"6", "1"+"29"+"6", "1"+"2"+"96", etc.
   - We need to find if ANY partition sums to 36
   - "1" + "29" + "6" = 1 + 29 + 6 = 36 ✓

## Solution

### Approach: Precomputed Array + Filtering

**Time Complexity**: O(k) where k is the number of valid numbers ≤ n (at most 29)  
**Space Complexity**: O(29) for storing the precomputed array

```python
class Solution:
    def punishmentNumber(self, n: int) -> int:
        # Precomputed list of all valid numbers in range [1, 1000]
        # These are numbers where i² can be partitioned to sum to i
        arr = [1,9,10,36,45,55,82,91,99,100,235,297,369,370,379,414,
               657,675,703,756,792,909,918,945,964,990,991,999,1000]
        
        # Filter numbers that are <= n
        tmp = []
        for val in arr:
            if val <= n:
                tmp.append(val)
        
        # Return sum of squares of all valid numbers
        return sum(val * val for val in tmp)
```

**How it works**:

1. **Precomputed Array**: Contains all integers i where i² can be partitioned into substrings summing to i
   - These were computed offline using a partition-checking algorithm

2. **Filtering**: Only consider numbers from the precomputed list that are ≤ n

3. **Sum Squares**: Calculate the sum of squares of filtered numbers

**Example Walkthrough** (n = 37):
- Valid numbers ≤ 37: [1, 9, 10, 36]
- Squares: [1, 81, 100, 1296]
- Sum: 1 + 81 + 100 + 1296 = 1478

### Alternative: Backtracking Solution (For Understanding)

If we wanted to compute valid numbers dynamically instead of using precomputation:

```python
class Solution:
    def punishmentNumber(self, n: int) -> int:
        def canPartition(s: str, target: int, index: int, current_sum: int) -> bool:
            # Base case: reached end of string
            if index == len(s):
                return current_sum == target
            
            # Try all possible partitions starting from current index
            for i in range(index, len(s)):
                substring = s[index:i+1]
                num = int(substring)
                
                # Prune: if current sum exceeds target, no point continuing
                if current_sum + num > target:
                    continue
                
                # Recursively check remaining string
                if canPartition(s, target, i+1, current_sum + num):
                    return True
            
            return False
        
        result = 0
        for i in range(1, n + 1):
            square = i * i
            if canPartition(str(square), i, 0, 0):
                result += square
        
        return result
```

**Time Complexity**: O(n × 2^d) where d is the average number of digits in i²  
**Space Complexity**: O(d) for recursion depth

This approach is more intuitive but significantly slower than the precomputed solution.

# Tags

`Math` `Backtracking` `Dynamic Programming` `String` `Precomputation`


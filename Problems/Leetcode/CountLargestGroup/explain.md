## Problem

https://leetcode.com/problems/count-largest-group/description/

```
You are given an integer n.

We need to group the numbers from 1 to n according to the sum of its digits. For example, the numbers 14 and 5 belong to the same group, whereas 13 and 3 belong to different groups.

Return the number of groups that have the largest size, i.e. the maximum number of elements.

Example 1:

Input: n = 13
Output: 4
Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
[1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
There are 4 groups with largest size.

Example 2:

Input: n = 2
Output: 2
Explanation: There are 2 groups [1], [2] of size 1.

Constraints:

1 <= n <= 104
```

## Observations

1. **Problem Understanding**: We need to group numbers from 1 to n based on their digit sum, then count how many groups have the maximum size.

2. **Key Insight**: The digit sum acts as a grouping key. Numbers with the same digit sum belong to the same group.

3. **Examples Analysis**:
   - For n=13: 
     - Group by digit sum: {1:[1,10], 2:[2,11], 3:[3,12], 4:[4,13], 5:[5], 6:[6], 7:[7], 8:[8], 9:[9]}
     - Group sizes: [2,2,2,2,1,1,1,1,1] → max size is 2, occurs 4 times → answer: 4
   - For n=2:
     - Groups: {1:[1], 2:[2]} → max size is 1, occurs 2 times → answer: 2

4. **Digit Sum Range**: For n ≤ 10⁴, the maximum digit sum is 9+9+9+9 = 36 (for 9999), so we'll have at most 36 different groups.

5. **Algorithm Steps**:
   - Calculate digit sum for each number 1 to n
   - Count frequency of each digit sum
   - Find the maximum frequency
   - Count how many digit sums have this maximum frequency

## Solution

**Time Complexity**: O(n × log₁₀(n))
- We iterate through n numbers
- For each number, we calculate digit sum which takes O(log₁₀(n)) time (number of digits)

**Space Complexity**: O(min(n, 36))
- We store at most min(n, 36) different digit sums in the frequency map
- Since max digit sum for numbers ≤ 10⁴ is 36, space is effectively O(36) = O(1)

**Key Optimizations**:
1. Using `f.get(s, 0) + 1` for safe frequency counting
2. Using generator expression in `sum()` for memory efficiency
3. Direct calculation of digit sum without string conversion

# Tags

Hash Table, Math, Simulation


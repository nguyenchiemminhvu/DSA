## Problem

https://leetcode.com/problems/split-a-string-in-balanced-strings/

```
Balanced strings are those that have an equal quantity of 'L' and 'R' characters.

Given a balanced string s, split it into some number of substrings such that:

Each substring is balanced.
Return the maximum number of balanced strings you can obtain.

Example 1:

Input: s = "RLRRLLRLRL"
Output: 4
Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.

Example 2:

Input: s = "RLRRRLLRLL"
Output: 2
Explanation: s can be split into "RL", "RRRLLRLL", each substring contains same number of 'L' and 'R'.
Note that s cannot be split into "RL", "RR", "RL", "LR", "LL", because the 2nd and 5th substrings are not balanced.

Example 3:

Input: s = "LLLLRRRR"
Output: 1
Explanation: s can be split into "LLLLRRRR".

Constraints:

2 <= s.length <= 1000
s[i] is either 'L' or 'R'.
s is a balanced string.
```

## Observations

1. **Greedy Approach**: To maximize the number of balanced substrings, we should split the string as soon as we find a balanced portion. This is because any longer balanced substring could potentially be split into multiple smaller balanced substrings.

2. **Balance Tracking**: We need to keep track of the count of 'L' and 'R' characters as we traverse the string. When they become equal, we've found a balanced substring.

3. **Reset After Split**: Once we find a balanced substring, we can reset our counters and start looking for the next balanced substring independently.

4. **Example Analysis**:
   - `"RLRRLLRLRL"` → `"RL"` (1st), `"RRLL"` (2nd), `"RL"` (3rd), `"RL"` (4th) = 4 balanced substrings
   - We could have `"RLRRLL"` + `"RLRL"`, but that gives us only 2 substrings instead of 4

5. **Key Insight**: The greedy approach works because if we have a balanced substring, splitting it earlier (when possible) will always give us at least the same number of substrings, potentially more.

## Solution

**Algorithm**: Greedy Single Pass

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - only using constant extra space

**Approach**:
1. Initialize counters for 'L' characters (`left`), 'R' characters (`right`), and balanced substrings (`count`)
2. Iterate through each character in the string:
   - Increment `left` if character is 'L'
   - Increment `right` if character is 'R'
   - When `left == right`, we've found a balanced substring:
     - Increment `count`
     - Reset both `left` and `right` to 0
3. Return the total count

**Why this works**:
- The greedy strategy ensures we get the maximum number of balanced substrings
- Since the input string is guaranteed to be balanced, we don't need to worry about edge cases
- Each time we find equal counts of 'L' and 'R', we can safely split there without affecting future possibilities

**Alternative Implementation** (more concise):
```python
def balancedStringSplit(self, s: str) -> int:
    count = balance = 0
    for c in s:
        balance += 1 if c == 'R' else -1
        if balance == 0:
            count += 1
    return count
```
This version uses a single `balance` variable: increment for 'R', decrement for 'L'. When balance reaches 0, we have equal counts.

## Tags

array, string, greedy
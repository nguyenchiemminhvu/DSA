## Problem

https://leetcode.com/problems/construct-the-longest-new-string/description

# Construct The Longest New String

## Problem

**LeetCode Link:** https://leetcode.com/problems/construct-the-longest-new-string/description

You are given three integers `x`, `y`, and `z`.

- You have `x` strings equal to `"AA"` (2 characters each)
- You have `y` strings equal to `"BB"` (2 characters each)  
- You have `z` strings equal to `"AB"` (2 characters each)

You want to choose some (possibly all or none) of these strings and concatenate them in some order to form a new string.

**Constraint:** This new string must not contain `"AAA"` or `"BBB"` as a substring.

**Goal:** Return the maximum possible length of the new string.

**Examples:**

**Example 1:**
```
Input: x = 2, y = 5, z = 1
Output: 12
Explanation: We can concatenate "BB", "AA", "BB", "AA", "BB", "AB" in that order.
Result: "BBAABBAABBAB" (length 12)
```

**Example 2:**
```
Input: x = 3, y = 2, z = 2
Output: 14
Explanation: We can concatenate "AB", "AB", "AA", "BB", "AA", "BB", "AA" in that order.
Result: "ABABAABBAABBAA" (length 14)
```

---

## Observations

### Key Insights

1. **Character Frequency Analysis:**
   - `"AA"` contributes 2 A's each
   - `"BB"` contributes 2 B's each
   - `"AB"` contributes 1 A and 1 B each
   - Total: `2x + z` A's and `2y + z` B's are available

2. **Constraint Analysis:**
   - We cannot have 3 consecutive A's (`"AAA"`)
   - We cannot have 3 consecutive B's (`"BBB"`)
   - The maximum consecutive same character is 2

3. **Greedy Strategy:**
   - To maximize length, we should use as many strings as possible
   - The limiting factor is the balance between A's and B's
   - If we have too many A's, we can't use all of them without violating the `"AAA"` constraint
   - Similarly for B's

4. **Interleaving Pattern:**
   - The optimal strategy is to **alternate** between blocks of A's and B's
   - Each block should have at most 2 consecutive same characters
   - Pattern like: `AA`, `BB`, `AA`, `BB`, ... with `AB` strings filling gaps

5. **Balance Requirement:**
   - If one character appears too frequently, we're forced to skip some strings
   - If counts are balanced, we can use all `z` strings (they help balance) plus maximum A/B pairs
   - If one side has excess, we can use at most `min(x, y) + 1` pairs of the excess character

### Mathematical Insight

- Best case: Use all `z` strings + all of `x` AA's + all of `y` BB's (if well-balanced)
- The optimal configuration uses:
  - All `z` strings (always beneficial for balance)
  - All strings from the character with fewer pairs
  - Most strings from the character with more pairs (up to a limit)
  
- If we denote `count_A = 2x + z` and `count_B = 2y + z`:
  - If counts are equal, we use all strings
  - If counts differ, we limit the excess to be at most `count_B + 2` (or vice versa)
  - This ensures we never get 3+ consecutive same characters

---

## Solution

### Intuition

The problem is fundamentally about balancing A's and B's. Let's think of it as an **interleaving problem**:

1. We want to place blocks of AA's and BB's alternately to prevent three consecutive characters
2. We use AB strings to help maintain this balance
3. The key is to determine how many of each string we can use without violating the constraint

### Approach: Greedy with Mathematical Formula

The optimal strategy works as follows:

```
Total available: count_A = 2x + z, count_B = 2y + z

- We can always use all z "AB" strings (they provide balance and don't create issues)
- For AA and BB pairs, we can use min(x, y) pairs of both
- If x != y (imbalanced), we can use one more pair from the more abundant character

Result = 2 * (z + 2 * min(x, y) + (x != y))
```

**Breaking down the formula:**

- `2 * z`: All AB strings (each contributes 2 characters)
- `2 * min(x, y) * 2 = 4 * min(x, y)`: Minimum count of AA and BB pairs, each contributing 2 characters
- `2 * (x != y)`: If x ≠ y, we can use one additional pair from the majority (contributes 2 characters)

### Why Does This Work?

Let's say `x ≤ y` (without loss of generality):

1. **Use all z AB strings:** Contributes `2z` characters. These are "free" resources that help balance.

2. **Use min(x, y) AA's and min(x, y) BB's:** Contributes `2 * min(x, y) * 2 = 4 * min(x, y)` characters.
   - This ensures we have equal blocks of AA and BB

3. **Use 1 more pair if x ≠ y:** 
   - If `x < y`, we have `y - x` extra BB's remaining
   - We can add one more BB block at the beginning or end without violating constraints
   - Adds 2 more characters

4. **Arrangement example (x=2, y=5, z=1):**
   - min(x,y) = 2
   - Use: 2 AA's, 2 BB's, 1 AB, and 1 extra BB (since y > x)
   - Total: 2 + 4 + 2 + 2 = 10... wait let me recalculate
   - Formula: `2 * (1 + 2*2 + 1) = 2 * 6 = 12` ✓

### Code Implementation

```python
class Solution:
    def longestString(self, x: int, y: int, z: int) -> int:
        # z: number of "AB" strings
        # min(x, y): balanced pairs of AA and BB
        # (x != y): one extra pair from the majority side
        return 2 * (z + 2 * min(x, y) + (x != y))
```

**Complexity Analysis:**
- **Time Complexity:** O(1) - Single arithmetic calculation
- **Space Complexity:** O(1) - No additional space needed

### Example Walkthrough

**Example 1: x=2, y=5, z=1**
```
count_min = min(2, 5) = 2
has_extra = (2 != 5) = 1 (True)
result = 2 * (1 + 2*2 + 1) = 2 * 6 = 12 ✓

We use: 2 AA's, 3 BB's (2 balanced + 1 extra), 1 AB
One possible arrangement: "BB", "AA", "BB", "AA", "BB", "AB"
String: "BBAABBAABBAB" (length 12)
```

**Example 2: x=3, y=2, z=2**
```
count_min = min(3, 2) = 2
has_extra = (3 != 2) = 1 (True)
result = 2 * (2 + 2*2 + 1) = 2 * 7 = 14 ✓

We use: 3 AA's (2 balanced + 1 extra), 2 BB's (all), 2 AB's
One possible arrangement: "AB", "AB", "AA", "BB", "AA", "BB", "AA"
String: "ABABAABBAABBAA" (length 14)
```

---

## Tags

- **Difficulty:** Medium
- **Category:** Greedy, Math, String
- **Key Concepts:** 
  - Greedy algorithms
  - Mathematical optimization
  - Constraint satisfaction
  - Balance problems
- **Similar Problems:**
  - Rearrange String k Distance Apart
  - Task Scheduler
  - Reorganize String

## Observations

## Solution

# Tags


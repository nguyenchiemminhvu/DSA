## Problem

https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/description/

You are given a 0-indexed string `s` of even length `n`. The string consists of exactly `n / 2` opening brackets `'['` and `n / 2` closing brackets `']'`.

A string is called **balanced** if and only if:
- It is the empty string, or
- It can be written as `AB`, where both `A` and `B` are balanced strings, or
- It can be written as `[C]`, where `C` is a balanced string.

You may swap the brackets at any two indices any number of times.

**Return** the minimum number of swaps to make `s` balanced.

### Examples

**Example 1:**
```
Input: s = "][]["
Output: 1
Explanation: You can make the string balanced by swapping index 0 with index 3.
The resulting string is "[[]]".
```

**Example 2:**
```
Input: s = "]]][[["
Output: 2
Explanation: You can do the following to make the string balanced:
- Swap index 0 with index 4. s = "[]][][".
- Swap index 1 with index 5. s = "[[][]]".
The resulting string is "[[][]]".
```

**Example 3:**
```
Input: s = "[]"
Output: 0
Explanation: The string is already balanced.
```

### Constraints
- `n == s.length`
- `2 <= n <= 10^6`
- `n` is even
- `s[i]` is either `'['` or `']'`
- The number of opening brackets `'['` equals `n / 2`, and the number of closing brackets `']'` equals `n / 2`

## Observations

1. **Equal Count Guarantee**: Since we have exactly `n/2` opening brackets and `n/2` closing brackets, we know a balanced configuration is always possible.

2. **Greedy Matching**: We can process the string from left to right, trying to match each closing bracket `']'` with a previous opening bracket `'['`.

3. **Unmatched Closing Brackets**: When we encounter a closing bracket `']'` but have no unmatched opening bracket `'['` to pair it with, we have found an "imbalanced" position.

4. **Swap Strategy**: When we find an unmatched closing bracket, we need to swap it with an opening bracket that appears later in the string. Each swap fixes **two** unmatched brackets at once:
   - The unmatched `']'` becomes `'['`
   - The `'['` we swap with becomes `']'` (but at a later position where it can be matched)

5. **Counting Unmatched**: We only need to count how many closing brackets cannot be matched. The number of swaps needed is `⌈unmatched / 2⌉` because each swap fixes two brackets.

## Solution

### Algorithm

The solution uses a **single-pass greedy approach**:

1. **Track Opening Brackets**: Maintain a counter `count_open` to track unmatched opening brackets.

2. **Process Each Character**:
   - If we see `'['`: Increment `count_open` (we have one more opening bracket available for matching)
   - If we see `']'`:
     - If `count_open > 0`: We can match this closing bracket with a previous opening bracket, so decrement `count_open`
     - If `count_open == 0`: We have an unmatched closing bracket. This needs a swap.
       - Increment `swap` counter
       - Increment `count_open` by 1 (simulating that we've swapped this `']'` with a future `'['`)

3. **Return Result**: The `swap` counter contains the minimum number of swaps needed.

### Why This Works

When we encounter an unmatched `']'`:
- We conceptually swap it with the nearest unmatched `'['` that comes later
- This swap converts the unmatched `']'` into `'['`, which is why we increment `count_open`
- The `'['` we swap with moves to where the `']'` was, and it will naturally be matched when we process future characters
- Each physical swap fixes one unmatched closing bracket, which is why we increment `swap` by 1

### Code Implementation

```python
class Solution:
    def minSwaps(self, s: str) -> int:
        count_open = 0  # Track unmatched opening brackets
        swap = 0        # Count minimum swaps needed
        
        for c in s:
            if c == '[':
                count_open += 1
            else:  # c == ']'
                if count_open > 0:
                    # Match with previous opening bracket
                    count_open -= 1
                else:
                    # Unmatched closing bracket - need a swap
                    swap += 1
                    count_open += 1  # After swap, we have an opening bracket
        
        return swap
```

### Example Walkthrough

Let's trace through Example 2: `s = "]]][[[""`

| Index | Char | count_open | swap | Explanation |
|-------|------|------------|------|-------------|
| 0 | `]` | 0 → 1 | 0 → 1 | Unmatched `]`, need swap, imagine it becomes `[` |
| 1 | `]` | 1 → 0 | 1 | Can match with previous (imaginary) `[` |
| 2 | `]` | 0 → 1 | 1 → 2 | Unmatched `]`, need swap, imagine it becomes `[` |
| 3 | `[` | 1 → 2 | 2 | Add opening bracket |
| 4 | `[` | 2 → 3 | 2 | Add opening bracket |
| 5 | `[` | 3 → 4 | 2 | Add opening bracket |

**Result**: 2 swaps needed ✓

### Complexity Analysis

- **Time Complexity**: O(n) - Single pass through the string
- **Space Complexity**: O(1) - Only using two integer variables

### Alternative Perspective

Another way to think about this problem: The minimum number of swaps equals `⌈max_imbalance / 2⌉`, where `max_imbalance` is the maximum number of unmatched closing brackets we encounter at any point.

In the code above, `swap` effectively tracks this value because each time we can't match a `]`, we increment `swap`. When we later see `[` brackets, they can match with the unmatched positions, but those already require swaps.

This greedy approach ensures we always get the minimum number of swaps.

# Tags

`Stack`, `String`, `Greedy`, `Two Pointers`


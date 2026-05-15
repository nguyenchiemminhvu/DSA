## Problem

https://leetcode.com/problems/russian-doll-envelopes/description/

You are given a 2D array of integers `envelopes` where `envelopes[i] = [wi, hi]` represents the width and height of an envelope.

One envelope can fit inside another **if and only if** both the width **and** height of one envelope are **strictly greater** than the width and height of the other envelope.

Return the **maximum number of envelopes** you can Russian doll (i.e., put one inside the other).

> Note: You cannot rotate an envelope.

**Example 1:**
```
Input:  envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: [2,3] => [5,4] => [6,7]
```

**Example 2:**
```
Input:  envelopes = [[1,1],[1,1],[1,1]]
Output: 1
```

**Constraints:**
- `1 <= envelopes.length <= 10^5`
- `envelopes[i].length == 2`
- `1 <= wi, hi <= 10^5`

## Observations

- The problem is essentially asking for the **Longest Increasing Subsequence (LIS)** but in 2D — we need a chain where both dimensions are strictly increasing.
- A naive approach would be to sort by width and then find the LIS on heights, but we must be careful: two envelopes with the **same width** cannot nest (strict inequality). If we naively take LIS on heights after sorting by width ascending, we might incorrectly count two envelopes of the same width (e.g., `[6,4]` and `[6,7]`).
- **Key trick:** Sort by width **ascending**, but for envelopes with the **same width**, sort by height **descending**. This ensures that among equal-width envelopes, at most one can be selected in any increasing subsequence of heights — because heights are decreasing within that group, so no two can form an increasing pair.
- After this sorting, the problem reduces to finding the **LIS of the heights array**, which can be solved in `O(n log n)` using a patience-sorting / binary-search approach (`tails` array + `bisect_left`).

## Solution

```python
import bisect
from typing import List

class Solution:
    def maxEnvelopes(self, pairs: List[List[int]]) -> int:
        # Sort by width ascending; for equal widths, sort by height descending.
        # This prevents two same-width envelopes from both entering the LIS.
        pairs.sort(key=lambda x: (x[0], -x[1]))

        # `tails[i]` holds the smallest possible tail value for an increasing
        # subsequence of length i+1 seen so far.
        tails = []
        for w, h in pairs:
            # Binary search: find the leftmost position where tails[idx] >= h
            idx = bisect.bisect_left(tails, h)
            if idx == len(tails):
                # h extends the longest subsequence found so far
                tails.append(h)
            else:
                # Replace to keep the tail as small as possible (greedy)
                tails[idx] = h

        # Length of `tails` equals the length of the LIS on heights,
        # which is the answer.
        return len(tails)
```

**Step-by-step on Example 1:** `[[5,4],[6,4],[6,7],[2,3]]`

| Step | Pair (w,h) | `bisect_left` result | Action | `tails` |
|------|-----------|----------------------|--------|---------|
| Sort result | — | — | `[[2,3],[5,4],[6,7],[6,4]]` | `[]` |
| h=3 | (2,3) | 0 (empty) | append | `[3]` |
| h=4 | (5,4) | 1 | append | `[3, 4]` |
| h=7 | (6,7) | 2 | append | `[3, 4, 7]` |
| h=4 | (6,4) | 1 | replace index 1 | `[3, 4, 7]` |

Result: `len(tails) = 3` ✓

> `[6,4]` comes **after** `[6,7]` due to descending-height sort for equal widths, so h=4 only replaces an existing slot and never extends the sequence — correctly preventing two same-width envelopes from nesting.

**Complexity:**
- Time: `O(n log n)` — sorting + one binary search per element
- Space: `O(n)` — the `tails` array

# Tags
- Sorting
- Binary Search
- Longest Increasing Subsequence (LIS)
- Dynamic Programming

```markdown
## Problem

https://leetcode.com/problems/custom-sort-string/description/

You are given two strings `order` and `s`. All characters of `order` are unique and define a **custom sort order**.

Permute the characters of `s` so that they match the order defined by `order`. Specifically, if character `x` appears before character `y` in `order`, then `x` should appear before `y` in the result.

Characters in `s` that do not appear in `order` can be placed anywhere in the result.

**Example 1:**
```
Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: "c", "b", "a" follow the custom order. "d" is not in order, so it can go anywhere.
```

**Example 2:**
```
Input: order = "bcafg", s = "abcd"
Output: "bcad"
Explanation: "b", "c", "a" follow the custom order. "d" is not in order.
```

**Constraints:**
- `1 <= order.length <= 26`
- `1 <= s.length <= 200`
- `order` and `s` consist of lowercase English letters.
- All characters of `order` are unique.

## Observations

1. **Core Problem**: We need to reorder characters of `s` based on the priority defined by `order`. Characters not present in `order` have no relative constraint — they can go anywhere.

2. **Priority Mapping**: The simplest way to capture the custom order is to build a **rank map**: assign each character in `order` a numeric priority equal to its index (`order[0]` → 0, `order[1]` → 1, ...). Characters not in `order` get no entry (or a default high rank).

3. **Separation Strategy**: Partition `s` into two groups:
   - Characters **in** `order` — these must be sorted by their rank in the map.
   - Characters **not in** `order` — these can be appended in any order.

4. **Sorting**: Sort the first group using the rank map as the key. Then concatenate both groups.

5. **Why This Works**: After sorting the "in-order" group by rank, all relative ordering constraints from `order` are satisfied. Appending the remaining characters at the end doesn't violate any constraint since they have no ordering requirement.

## Solution

### Approach: Rank Map + Partition + Sort

**Time Complexity**: O(n log n) where n = len(s) — dominated by the sort step.  
**Space Complexity**: O(n) for the two partitioned lists.

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        # Step 1: Build rank map from order string
        mp = {}
        for i, c in enumerate(order):
            mp[c] = i
        
        # Step 2: Partition s into ordered and non-ordered characters
        non_order = []
        ordered = []
        for c in s:
            if c not in mp:
                non_order.append(c)
            else:
                ordered.append(c)
        
        # Step 3: Sort the ordered characters by their rank in order
        ordered.sort(key=lambda x: mp[x])

        # Step 4: Append non-ordered characters at the end
        return "".join(ordered + non_order)
```

### Walkthrough Example

**Input:** `order = "cba"`, `s = "abcd"`

**Step 1 — Rank Map:**
```
mp = {'c': 0, 'b': 1, 'a': 2}
```

**Step 2 — Partition `s`:**
```
ordered     = ['a', 'b', 'c']   # all appear in order
non_ordered = ['d']              # 'd' not in order
```

**Step 3 — Sort `ordered` by rank:**
```
'a' → rank 2
'b' → rank 1
'c' → rank 0

After sort: ['c', 'b', 'a']
```

**Step 4 — Concatenate:**
```
"cba" + "d" = "cbad"
```

---

**Input:** `order = "bcafg"`, `s = "abcd"`

**Rank Map:** `{'b': 0, 'c': 1, 'a': 2, 'f': 3, 'g': 4}`

**Partition:**
```
ordered     = ['a', 'b', 'c']
non_ordered = ['d']
```

**Sort by rank:** `['b'(0), 'c'(1), 'a'(2)]`

**Result:** `"bca" + "d"` = `"bcad"` ✓

# Tags

Hash Map, String, Sorting, Greedy


```

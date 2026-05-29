## Problem

https://leetcode.com/problems/count-number-of-teams/description

There are `n` soldiers standing in a line, each assigned a **unique** rating value.

Form a team of 3 soldiers with indices `(i, j, k)` such that:
- `0 <= i < j < k < n`
- `rating[i] < rating[j] < rating[k]` (**strictly increasing**), **OR**
- `rating[i] > rating[j] > rating[k]` (**strictly decreasing**)

Return the **number of valid teams** that can be formed. A soldier can be part of multiple teams.

**Examples:**
- `[2,5,3,4,1]` → `3` — teams: `(2,3,4)`, `(5,4,1)`, `(5,3,1)`
- `[2,1,3]` → `0`
- `[1,2,3,4]` → `4`

**Constraints:** `3 <= n <= 1000`, `1 <= rating[i] <= 10^5`, all ratings are unique.

---

## Observations

1. **Brute force** would try all `O(n³)` triples `(i, j, k)` — valid for `n ≤ 1000` but not elegant.

2. **Key insight:** Fix the **middle element** `j`. For every soldier at position `j`, count:
   - `left_smaller`: how many elements to the **left** of `j` are **smaller** than `rating[j]`
   - `left_greater`: how many elements to the **left** of `j` are **greater** than `rating[j]`
   - `right_smaller`: how many elements to the **right** of `j` are **smaller** than `rating[j]`
   - `right_greater`: how many elements to the **right** of `j` are **greater** than `rating[j]`

3. With these counts, the number of valid teams where `j` is the middle:
   - **Increasing** teams `(i < j < k, rating[i] < rating[j] < rating[k])`:  
     → `left_smaller × right_greater`
   - **Decreasing** teams `(i < j < k, rating[i] > rating[j] > rating[k])`:  
     → `left_greater × right_smaller`

4. This reduces the problem to `O(n²)` — for each of the `n` middle elements, we do two linear scans.

---

## Solution Explanation

```python
class Solution:
    def numTeams(self, rating: List[int]) -> int:
        n = len(rating)
        res = 0
        
        for i in range(n):
            left_smaller, left_greater = 0, 0
            right_smaller, right_greater = 0, 0

            for j in range(i):                        # scan left of middle
                left_smaller += int(rating[j] < rating[i])
                left_greater += int(rating[j] > rating[i])
            
            for j in range(i + 1, n):                 # scan right of middle
                right_smaller += int(rating[j] < rating[i])
                right_greater += int(rating[j] > rating[i])
            
            res += (left_smaller * right_greater)     # increasing teams
            res += (left_greater * right_smaller)     # decreasing teams
            
        return res
```

**Step-by-step logic:**

- Iterate over every index `i`, treating `rating[i]` as the **middle element** of the triplet.
- Scan everything to the **left** of `i` to count how many values are smaller or greater.
- Scan everything to the **right** of `i` to count how many values are smaller or greater.
- By the **multiplication principle**: if there are `left_smaller` valid left partners and `right_greater` valid right partners, then `left_smaller × right_greater` unique increasing triplets exist with `i` as the middle.
- Similarly, `left_greater × right_smaller` gives the count of decreasing triplets with `i` as the middle.
- Sum contributions from all middle positions.

**Walkthrough on `[2,5,3,4,1]`:**

| Middle `i` | rating[i] | left_s | left_g | right_s | right_g | +incr | +decr |
|:-----------:|:---------:|:------:|:------:|:-------:|:-------:|:-----:|:-----:|
| 0           | 2         | 0      | 0      | 2       | 2       | 0     | 0     |
| 1           | 5         | 1      | 0      | 3       | 0       | 0     | 0     |
| 2           | 3         | 1      | 1      | 1       | 1       | 1     | 1     |
| 3           | 4         | 2      | 1      | 1       | 0       | 0     | 1     |
| 4           | 1         | 0      | 4      | 0       | 0       | 0     | 0     |

Total = `0 + 0 + (1×1) + (1×1) + (2×0) + (1×1) + 0` = **3** ✓

**Complexity:**
- **Time:** `O(n²)` — two linear scans per element
- **Space:** `O(1)` — only a few counters

## Problem

https://leetcode.com/problems/successful-pairs-of-spells-and-potions/description

```
You are given two positive integer arrays spells and potions, of length n and m respectively, where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.

You are also given an integer success. A spell and potion pair is considered successful if the product of their strengths is at least success.

Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair with the ith spell.

Example 1:

Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.

Example 2:

Input: spells = [3,1,2], potions = [8,5,8], success = 16
Output: [2,0,2]
Explanation:
- 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
- 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful. 
- 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful. 
Thus, [2,0,2] is returned.

Constraints:

n == spells.length
m == potions.length
1 <= n, m <= 105
1 <= spells[i], potions[i] <= 105
1 <= success <= 1010
```

## Observations

1. **Problem Understanding**: We need to find, for each spell, how many potions can form a "successful pair" where `spell * potion >= success`.

2. **Brute Force Approach**: A naive solution would be to check every spell-potion pair, resulting in O(n*m) time complexity, which could be too slow for the given constraints (up to `10^5` elements).

3. **Key Insight**: For a given spell `s`, we need potions `p` such that `s * p >= success`, which means `p >= success / s`. If we sort the potions array, we can use binary search to find the first potion that satisfies this condition.

4. **Binary Search Optimization**: Once we find the first valid potion using binary search, all potions to the right (larger values) will also be valid since the array is sorted.

5. **Mathematical Relationship**: For spell `s`, we need `potion >= ceil(success / s)`. However, since we're dealing with real division, we can use `success / s` directly in our binary search.

6. **Edge Cases**: 
   - If no potion satisfies the condition, lower_bound returns `len(potions)`
   - If all potions satisfy the condition, lower_bound returns `0`

## Solution

**Algorithm Overview:**

1. **Sort Potions**: Sort the potions array to enable binary search
2. **For Each Spell**: Calculate the minimum potion strength needed (`success / spell`)
3. **Binary Search**: Use a custom `lower_bound` function to find the first potion that meets the requirement
4. **Count Valid Potions**: The number of valid potions is `len(potions) - lower_bound_index`

**Detailed Explanation:**

```python
def lower_bound(arr: List[int], target: int) -> int:
    left, right = 0, len(arr) - 1
    found = right + 1  # Default: no element found
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] >= target:
            found = mid      # Potential answer
            right = mid - 1  # Look for smaller index
        else:
            left = mid + 1   # Need larger values
    return found
```

The `lower_bound` function finds the first index where `arr[index] >= target`. This is a classic binary search variant.

**Main Algorithm Steps:**

1. **Sort potions** in `O(m log m)` time
2. **For each spell** (`O(n)` iterations):
   - Calculate `remain = success / spell` (minimum potion strength needed)
   - Find first valid potion using binary search in `O(log m)` time
   - Count valid potions: `len(potions) - lower_bound_index`

**Time Complexity**: `O(m log m + n log m)`
- Sorting potions: `O(m log m)  `
- For each spell, binary search: `O(n log m)`

**Space Complexity**: `O(1)` extra space (not counting input/output arrays)

**Example Walkthrough** (`spells=[5,1,3], potions=[1,2,3,4,5], success=7`):

1. Sort potions: `[1,2,3,4,5]` (already sorted)

2. Spell 5: need `potion >= 7/5 = 1.4`
   - `lower_bound([1,2,3,4,5], 1.4) = 1` (first element >= 1.4 is at index 1, value 2)
   - Valid potions: `5 - 1 = 4 ✓`

3. Spell 1: need `potion >= 7/1 = 7`
   - `lower_bound([1,2,3,4,5], 7) = 5` (no element >= 7)
   - Valid potions: `5 - 5 = 0 ✓`

4. Spell 3: need `potion >= 7/3 = 2.33...`
   - `lower_bound([1,2,3,4,5], 2.33) = 2` (first element >= 2.33 is at index 2, value 3)
   - Valid potions: `5 - 2 = 3 ✓`

## Tags

array, binary search
## Problem

https://leetcode.com/problems/avoid-flood-in-the-city/description/

```
Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.

Given an integer array rains where:

rains[i] > 0 means there will be rains over the rains[i] lake.
rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
Return an array ans where:

ans.length == rains.length
ans[i] == -1 if rains[i] > 0.
ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.

Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.

Example 1:

Input: rains = [1,2,3,4]
Output: [-1,-1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day full lakes are [1,2,3]
After the fourth day full lakes are [1,2,3,4]
There's no day to dry any lake and there is no flood in any lake.

Example 2:

Input: rains = [1,2,0,0,2,1]
Output: [-1,-1,2,1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day, we dry lake 2. Full lakes are [1]
After the fourth day, we dry lake 1. There is no full lakes.
After the fifth day, full lakes are [2].
After the sixth day, full lakes are [1,2].
It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another acceptable scenario.

Example 3:

Input: rains = [1,2,0,1,2]
Output: []
Explanation: After the second day, full lakes are  [1,2]. We have to dry one lake in the third day.
After that, it will rain over lakes [1,2]. It's easy to prove that no matter which lake you choose to dry in the 3rd day, the other one will flood.

Constraints:

1 <= rains.length <= 105
0 <= rains[i] <= 109
```

## Observations

Each lake can be in one of two states: empty or full. A lake becomes full when it rains (rains[i] > 0), and becomes empty when we choose to dry it on a dry day (rains[i] == 0).

A flood occurs when it rains on a lake that is already full. This is the critical constraint we must avoid.

We only have control on dry days (rains[i] == 0). On these days, we must decide which lake to dry, and this decision affects future flood possibilities.

If a lake appears twice in the sequence, we must dry it between these two occurrences. There must be at least one dry day between duplicate lake numbers.

The problem allows multiple valid answers, indicating that there might be several ways to avoid floods, but we only need to find one.

**Impossibility Cases**: 
- When a lake appears twice with no dry days in between
- When there are more conflicts than available dry days to resolve them

The problem has a greedy structure - we need to make immediate decisions on dry days without knowing future rain patterns completely.

Dry days are limited resources that must be allocated optimally to prevent future floods.

For dry days that aren't needed to prevent floods, we can choose any lake number (even 1), since drying an empty lake has no effect.

With up to 10^5 days and lake numbers up to 10^9, efficient data structures and algorithms are necessary (`O(n)`).

## Solution

Declare a `last_rain_day` dictionary for tracking the last day each lake had rain
Declare a `dry_days` list of available dry days (automatically sorted by day index)

**Step 1: Process Each Day**
```python
for day, slot in enumerate(rains):
    if slot == 0:
        # Dry day - add to available dry days
        dry_days.append(day)
    else:
        # Rain day - check for potential flood
```

**Step 2: Handle Rain Days**
When it rains on lake `slot`:
- If this lake has rained before (`slot in last_rain_day`):
  - **Critical Decision Point**: We must have dried this lake between its last occurrence and now
  - Use binary search to find the first dry day after `last_rain_day[slot]`
  - If no such dry day exists → flood is inevitable → return `[]`
  - Otherwise, assign this dry day to dry the current lake and remove it from available days

**Step 3: Binary Search for Optimal Dry Day**
```python
found_day_to_dry = upper_bound(dry_days, last_rain_day[slot])
```

- `upper_bound` finds the first dry day that comes **after** the lake's last rain day
- This ensures we dry the lake between its occurrences (prevents flood)
- Choosing the **earliest** available dry day is optimal (greedy choice)

**Step 4: Finalize Remaining Dry Days**
```python
for day in dry_days:
    res[day] = 1  # Can use any lake number for unused dry days
```

#### Example Walkthrough:

Input: `rains = [1,2,0,0,2,1]`

1. Day 0: Lake 1 rains → `last_rain_day[1] = 0`
2. Day 1: Lake 2 rains → `last_rain_day[2] = 1`  
3. Day 2: Dry day → `dry_days = [2]`
4. Day 3: Dry day → `dry_days = [2,3]`
5. Day 4: Lake 2 rains again → Find dry day after day 1 → Use day 2 → `res[2] = 2`
6. Day 5: Lake 1 rains again → Find dry day after day 0 → Use day 3 → `res[3] = 1`

Final result: `[-1,-1,2,1,-1,-1]`

## Tags

array, binary search, hash table, greedy
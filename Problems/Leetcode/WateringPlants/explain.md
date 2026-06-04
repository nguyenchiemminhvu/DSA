```markdown
## Problem

https://leetcode.com/problems/watering-plants/description/

You want to water `n` plants arranged in a row (labeled `0` to `n-1` at positions `x = 0` to `x = n-1`). A river sits at `x = -1` where you start with a full watering can.

Rules:
- Water plants strictly left to right.
- After watering a plant, if the remaining water is **not enough** for the next plant, walk back to the river to refill (fully), then continue.
- You **cannot** refill early.
- Each unit of movement on the x-axis costs 1 step.

**Goal:** Return the total number of steps to water all plants.

---

## Observations

1. **Walking forward is always 1 step per plant** — every plant costs at least 1 step to reach from the previous position.

2. **A refill trip adds a back-and-forth detour** — if you must refill before plant `i` (0-indexed), you walk back from position `i-1` to the river (`i` steps back, since river is at `-1`, distance = `i-1 - (-1) = i`), then walk forward to plant `i` (`i+1` steps). Combined: `i + (i+1) = 2i + 1` steps instead of just `1` step.

3. **No refill needed for the last plant** — you never need to check water after the last plant.

4. **Greedy simulation is sufficient** — just track the current water level and simulate step by step; no look-ahead or dynamic programming is needed.

---

## Solution Explanation

```python
class Solution:
    def wateringPlants(self, plants: List[int], cap: int) -> int:
        n = len(plants)
        steps = 0
        cur_water = cap          # start with a full can at the river
        for i in range(n):
            if plants[i] <= cur_water:
                # Enough water: just walk one step to this plant and water it
                cur_water -= plants[i]
                steps += 1
            else:
                # Not enough water: walk back to river and forward to plant i
                # Distance: (i steps back to river) + (i+1 steps to plant i) = 2i + 1
                cur_water = cap - plants[i]
                steps += (i * 2) + 1
        return steps
```

### Step-by-step logic

| Situation | Steps added | Explanation |
|---|---|---|
| `cur_water >= plants[i]` | `+1` | Simply walk one step forward to plant `i` |
| `cur_water < plants[i]` | `+(2i + 1)` | Walk back `i` steps to river (from position `i-1`), refill, walk `i+1` steps to plant `i` |

### Walkthrough — Example 1
`plants = [2,2,3,3]`, `capacity = 5`

| Plant | cur_water before | Action | Steps added | cur_water after |
|---|---|---|---|---|
| 0 | 5 | water (5 ≥ 2) | +1 | 3 |
| 1 | 3 | water (3 ≥ 2) | +1 | 1 |
| 2 | 1 | refill (1 < 3), i=2 → 2×2+1=5 | +5 | 2 |
| 3 | 2 | refill (2 < 3), i=3 → 2×3+1=7 | +7 | 2 |

Total: `1 + 1 + 5 + 7 = 14` ✓

### Complexity
- **Time:** $O(n)$ — single pass through the array.
- **Space:** $O(1)$ — only a few variables used.
```

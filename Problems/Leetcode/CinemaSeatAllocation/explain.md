## Problem

LeetCode: [Cinema Seat Allocation](https://leetcode.com/problems/cinema-seat-allocation/description/)

A cinema has `n` rows, each row has seats `1..10`.

Some seats are reserved: `reservedSeats[i] = [row_i, seat_i]`.

We need to place as many **4-person groups** as possible, where each group must sit in exactly one of these seat blocks in the same row:

- `[2, 3, 4, 5]`
- `[4, 5, 6, 7]`
- `[6, 7, 8, 9]`

Each seat can be used by at most one group.

Return the **maximum** number of groups that can be seated.

---

## Observations

1. **Only seats 2..9 matter** for 4-person placement.
   - Seat `1` and seat `10` do not belong to any valid 4-seat block.

2. In one row, there are only 3 candidate blocks:
   - Left block: `2..5`
   - Middle block: `4..7`
   - Right block: `6..9`

3. For a row with no reservations affecting these seats, we can place **2 groups**:
   - one in left block (`2..5`) and one in right block (`6..9`), non-overlapping.

4. `n` can be as large as `10^9`, but `reservedSeats.length <= 10^4`.
   - So we cannot iterate all rows.
   - We should process only rows that actually appear in `reservedSeats`.

---

## Solution Idea (matching the given code)

Start with the optimistic answer:

- `res = 2 * n` (assume every row can host 2 groups).

Then correct this value only for rows that have reserved seats.

### Step 1: Group reservations by row

Use a hash map: `row -> list of reserved seats in that row`.

### Step 2: For each affected row, test block availability

For each row, maintain three flags:

- `opt1` for block `2..5`
- `opt2` for block `4..7`
- `opt3` for block `6..9`

Initially all `1` (available).

For each reserved seat in that row:

- if `2 <= seat <= 5`, then `opt1 = 0`
- if `4 <= seat <= 7`, then `opt2 = 0`
- if `6 <= seat <= 9`, then `opt3 = 0`

After scanning seats in the row:

- If left and right are both available, we can seat `opt1 + opt3` groups (could be `2`, `1`, or `0`).
- Middle gives at most `1` group (`opt2`).

So the maximum groups in this row is:

`max_opt = max(opt1 + opt3, opt2)`

### Step 3: Adjust from baseline

Baseline assumed 2 groups for this row, but actual is `max_opt`.

Subtract the loss:

- `res -= (2 - max_opt)`

Do this for every affected row; untouched rows remain at 2 groups each.

---

## Why this is correct

For any single row, the only feasible 4-seat choices are exactly the three blocks above.

- The left (`2..5`) and right (`6..9`) blocks are disjoint, so they can coexist.
- The middle block (`4..7`) overlaps both left and right, so if we pick middle, we cannot pick either of the others.

Therefore, per row, the only optimal possibilities are:

- use left + right (up to 2 groups), or
- use middle (1 group), or
- use none.

Thus `max(opt1 + opt3, opt2)` is exactly the maximum groups for that row.
Summing this row-wise optimum over all rows (implemented via baseline correction) gives the global optimum.

---

## Complexity

Let `m = len(reservedSeats)`.

- Time: `O(m)` (each reserved seat is processed once)
- Space: `O(m)` in the map (in worst case all reservations are in distinct rows/lists)

Efficient enough for constraints (`m <= 10^4`).

---

## Reference Code

```python
from collections import defaultdict
from typing import List


class Solution:
	def maxNumberOfFamilies(self, n: int, reserved: List[List[int]]) -> int:
		res = 2 * n

		mp_row = defaultdict(list)
		for row, seat in reserved:
			mp_row[row].append(seat)

		for row, arr in mp_row.items():
			opt1, opt2, opt3 = 1, 1, 1
			for seat in arr:
				if 2 <= seat <= 5:
					opt1 = 0
				if 4 <= seat <= 7:
					opt2 = 0
				if 6 <= seat <= 9:
					opt3 = 0

			max_opt = max(opt1 + opt3, opt2)
			res -= (2 - max_opt)
		return res
```

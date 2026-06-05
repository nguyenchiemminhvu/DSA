## Problem

https://leetcode.com/problems/circular-array-loop/description/

You are given a circular array `nums` of non-zero integers. Each `nums[i]` denotes the number of steps you must move from index `i`:
- If `nums[i]` is **positive**, move `nums[i]` steps **forward**.
- If `nums[i]` is **negative**, move `abs(nums[i])` steps **backward**.

The array is circular: moving forward past the last element wraps to the first, and moving backward before the first element wraps to the last.

A **valid cycle** must satisfy all three conditions:
1. Following movement rules produces a repeating index sequence of length `k > 1`.
2. All elements in the cycle move in the **same direction** (all positive or all negative).
3. The cycle length `k > 1` (a single-element self-loop is NOT a valid cycle).

Return `true` if there is a valid cycle in `nums`, otherwise return `false`.

---

## Observations

- The circular nature of the array means index arithmetic must always use modulo: `next = ((i + nums[i]) % n + n) % n`. The `+ n` before `% n` handles negative offsets correctly.
- A **direction change** within a traversal path means no valid cycle can exist along that path. Two indices have the same direction when `nums[a] * nums[b] > 0` (both positive or both negative).
- A **self-loop** (`next_idx(i) == i`) is a cycle of length 1 and must be rejected since `k > 1` is required.
- This problem is essentially **cycle detection in a directed graph** where each node has exactly one outgoing edge.
- **Floyd's Tortoise and Hare** (slow/fast pointer) is a natural fit: it detects cycles in O(n) time and O(1) space, since each node has exactly one successor.
- For each starting index `i`, the `slow` pointer moves one step at a time and `fast` moves two steps at a time. If they meet, a cycle exists — but only if the cycle is valid (same direction throughout, length > 1).

---

## Solution Explanation

```python
class Solution:
    def circularArrayLoop(self, nums: List[int]) -> bool:
        n = len(nums)

        def next_idx(i: int) -> int:
            return ((i + nums[i]) + n) % n
        
        for i in range(n):
            slow = i
            fast = next_idx(i)

            while nums[slow] * nums[fast] > 0 and nums[slow] * nums[next_idx(fast)] > 0:
                if slow == fast:
                    if slow != next_idx(slow):
                        return True
                    break
                slow = next_idx(slow)
                fast = next_idx(next_idx(fast))
        
        return False
```

### Step-by-step walkthrough

**1. `next_idx(i)` — circular index helper**

```
next = ((i + nums[i]) + n) % n
```

The `+ n` before `% n` ensures the result is never negative when `nums[i]` is negative (Python's `%` handles it, but this makes the intent explicit and works in all languages).

---

**2. Outer loop — try every starting index**

```python
for i in range(n):
    slow = i
    fast = next_idx(i)
```

`slow` starts at `i`, and `fast` starts one step ahead. This is the standard Floyd's initialization — both are in the same "chain" but offset by one step.

---

**3. While loop guard — same direction check**

```python
while nums[slow] * nums[fast] > 0 and nums[slow] * nums[next_idx(fast)] > 0:
```

- `nums[slow] * nums[fast] > 0` → `slow` and `fast` point in the same direction.
- `nums[slow] * nums[next_idx(fast)] > 0` → the node *after* `fast` also points in the same direction (since `fast` will move there next).

If either condition fails, the path changes direction, so no valid cycle can exist starting from `i`. We stop and try the next starting index.

---

**4. Cycle detection — slow == fast**

```python
if slow == fast:
    if slow != next_idx(slow):
        return True
    break
```

When `slow` meets `fast`, a cycle has been detected. Before returning `true`, we verify it is **not** a self-loop by checking `slow != next_idx(slow)`. If `next_idx(slow) == slow`, the cycle has length 1 — invalid, so we `break` and try the next starting index.

---

**5. Advance pointers**

```python
slow = next_idx(slow)
fast = next_idx(next_idx(fast))
```

Classic Floyd's: `slow` moves one step, `fast` moves two steps. They are guaranteed to meet inside any cycle.

---

### Complexity

| | Complexity |
|---|---|
| **Time** | O(n) — each index is visited a constant number of times across all outer iterations |
| **Space** | O(1) — only a few index variables, no auxiliary data structures |

---

### Dry run — Example 1: `nums = [2, -1, 1, 2, 2]`

```
next_idx:  0→2, 1→0, 2→3, 3→0, 4→1

i=0: slow=0, fast=2
  Check: nums[0]*nums[2]=2>0 ✓, nums[0]*nums[3]=4>0 ✓
  slow≠fast → advance: slow=2, fast=0
  Check: nums[2]*nums[0]=2>0 ✓, nums[2]*nums[2]=1>0 ✓
  slow≠fast → advance: slow=3, fast=3
  slow==fast → check self-loop: next_idx(3)=0 ≠ 3 → CYCLE FOUND → return True
```

### Dry run — Example 2: `nums = [-1, -2, -3, -4, -5, 6]`

```
next_idx:  0→4, 1→4, 2→4, 3→4, 4→4, 5→5 (self-loop)

i=0: slow=0, fast=4
  Check: nums[0]*nums[4]=-1*-5=5>0 ✓, nums[0]*nums[4]=5>0 ✓
  slow≠fast → advance: slow=4, fast=4
  slow==fast → check self-loop: next_idx(4)=4 == 4 → self-loop, break

i=1..4: same path, all end at self-loop on index 4

i=5: slow=5, fast=next_idx(5)=5
  Guard: nums[5]*nums[5]=36>0 ✓, nums[5]*nums[5]=36>0 ✓
  slow==fast → next_idx(5)=5 == 5 → self-loop, break

→ return False
```

### Dry run — Example 3: `nums = [1, -1, 5, 1, 4]`

```
next_idx:  0→1, 1→0, 2→2 (self-loop), 3→4, 4→3

i=0: slow=0, fast=1
  Check: nums[0]*nums[1]=1*-1=-1 < 0 → direction mismatch → exit while

i=3: slow=3, fast=4
  Check: nums[3]*nums[4]=1*4>0 ✓, nums[3]*nums[3]=1>0 ✓
  slow≠fast → advance: slow=4, fast=4
  slow==fast → next_idx(4)=3 ≠ 4 → CYCLE FOUND → return True
```

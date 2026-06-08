## Problem

https://leetcode.com/problems/construct-target-array-with-multiple-sums/description

You are given an array `target` of `n` integers. Starting from `arr = [1, 1, ..., 1]` (n ones), you may repeatedly:

1. Let `x` = sum of all elements in `arr`.
2. Choose any index `i` and set `arr[i] = x`.

Return `true` if it is possible to construct `target` from `arr`, otherwise return `false`.

**Examples:**

- `target = [9,3,5]` → `true`  
  `[1,1,1]` → `[1,3,1]` → `[1,3,5]` → `[9,3,5]`
- `target = [1,1,1,2]` → `false`
- `target = [8,5]` → `true`

**Constraints:**
- `1 <= n <= 5 * 10^4`
- `1 <= target[i] <= 10^9`

---

## Observations

1. **Work backwards.** Instead of building forward from `[1,1,...,1]`, reverse the process: repeatedly undo the last operation. The last operation must have replaced some element with the current total sum, so the largest element in `target` must have been the result of that step.

2. **The largest element is always the one last placed.** At each reverse step, the maximum element `largest` was set equal to the array sum at that moment. Before it was set, it had some smaller value `prev`. We know:
   $$\text{largest} = \text{prev} + \text{rest}, \quad \text{rest} = s - \text{largest}$$
   Therefore: $\text{prev} = \text{largest} - \text{rest}$

3. **Use modulo to skip many steps at once.** If `rest` is small and `largest` is huge, we'd need to subtract `rest` many times. Instead of looping, we compute:
   $$\text{prev} = \text{largest} \mod \text{rest}$$
   This skips directly to the value `largest` would have had before all those repeated additions.

4. **Edge cases:**
   - If `rest == 1`, the only way to reach this state is from `[1, 1, ..., 1]`, so return `true`.
   - If `rest < 1` or `largest <= rest`, it's impossible to have arrived here — return `false`.
   - If `largest % rest == 0`, `prev` would be `0` which is invalid (arrays start with 1s), so we set `prev = rest` instead (it means the value was `rest` before the last addition, which only works if `rest == 1`... but this is already caught above as the `rest == 1` early return).

5. **Single element case.** If `n == 1`, the only reachable target is `[1]`, because you can never change the one element (sum = element itself, so it stays the same after assignment).

---

## Solution Explanation

The solution runs the construction **in reverse** using a **max-heap** to always identify the largest element efficiently.

```python
class Solution:
    def isPossible(self, target: List[int]) -> bool:
        n = len(target)
        if n == 1:
            return target[0] == 1

        pq = []
        s = 0
        for val in target:
            s += val
            heapq.heappush(pq, -val)   # max-heap via negation
                
        while pq and -pq[0] > 1:
            largest = -heapq.heappop(pq)
            rest = s - largest          # sum of all other elements

            if rest == 1:
                return True             # can always reduce to [1,1,...,1]
            
            if rest < 1 or largest <= rest:
                return False            # impossible state

            next_val = largest % rest   # undo multiple steps at once
            if next_val == 0:
                next_val = rest         # prevent zero; only valid if rest == 1

            s = rest + next_val
            heapq.heappush(pq, -next_val)

        return True
```

**Step-by-step walkthrough with `target = [9, 3, 5]`:**

| Heap (desc)  | `s` | `largest` | `rest` | `next_val` |
|:---:|:---:|:---:|:---:|:---:|
| `[9, 5, 3]` | 17 | 9 | 8 | 9 % 8 = **1** |
| `[5, 3, 1]` | 9  | 5 | 4 | 5 % 4 = **1** |
| `[3, 1, 1]` | 5  | 3 | 2 | 3 % 2 = **1** |
| `[1, 1, 1]` | 3  | —  | —  | all 1s → `true` |

**Step-by-step walkthrough with `target = [8, 5]`:**

| Heap (desc) | `s` | `largest` | `rest` | `next_val` |
|:---:|:---:|:---:|:---:|:---:|
| `[8, 5]` | 13 | 8 | 5 | 8 % 5 = **3** |
| `[5, 3]` | 8  | 5 | 3 | 5 % 3 = **2** |
| `[3, 2]` | 5  | 3 | 2 | 3 % 2 = **1** |
| `[2, 1]` | 3  | 2 | 1 | `rest == 1` → `true` |

**Complexity:**
- **Time:** $O(n \log n + k \log n)$ where $k$ is the number of reverse steps. Due to the modulo trick, $k$ is at most $O(\log(\max(\text{target})))$, making the overall complexity roughly $O(n \log n \cdot \log(\max))$.
- **Space:** $O(n)$ for the heap.

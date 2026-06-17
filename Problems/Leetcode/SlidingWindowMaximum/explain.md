## Problem

Link: https://leetcode.com/problems/sliding-window-maximum

Given an integer array `nums` and an integer `k`, a window of size `k` moves from left to right by one position at a time.
For each window position, return the maximum value inside that window.

---

## Observations

1. A brute-force solution checks all `k` elements for each window:
	 - Number of windows: `n - k + 1`
	 - Time: $O((n-k+1) \cdot k)$, which can be too slow for `n` up to $10^5$.

2. We need a data structure that can quickly give the current maximum while the window changes.

3. Python `heapq` is a min-heap, so to simulate a max-heap we push `-value`.

4. Removing an arbitrary old element from a heap is not efficient. 
	 So we use **lazy deletion**:
	 - Keep all candidates in heap.
	 - Maintain a frequency map (`mp`) for values currently in the window.
	 - If heap top corresponds to a value with zero frequency in `mp`, pop it until top becomes valid.

---

## Explain Solution (Heap + Frequency Map + Lazy Deletion)

### Data structures

- `pq`: max-heap simulated by pushing negatives.
- `mp`: hashmap (value -> count in current window).
- `res`: output list of window maximums.

### Steps

1. **Initialize first window** (`0 ... k-1`):
	 - Add each value to `mp`.
	 - Push `-value` into `pq`.
	 - Maximum of first window is `-pq[0]`.

2. **Slide window from index `k` to `n-1`**:
	 - Add new right value `nums[i]`:
		 - `mp[nums[i]] += 1`
		 - `heappush(pq, -nums[i])`
	 - Remove outgoing left value `nums[i-k]` from frequency map:
		 - `mp[nums[i-k]] -= 1`
	 - Clean invalid heap top values:
		 - While heap not empty and top value is not in current window (`mp[-pq[0]] <= 0`), pop it.
	 - Current maximum is again `-pq[0]`.

3. Return `res`.

### Why this works

- Heap always stores possible maximum candidates.
- Frequency map tells whether a value is still inside current window.
- Even if stale elements stay in heap, they are removed exactly when they reach the top.
- Therefore `pq[0]` always represents the correct max after cleanup.

---

## Complexity

- Let `n = len(nums)`.
- Each element is pushed once and popped at most once from heap.
- **Time:** $O(n \log n)$ in this value-based lazy deletion form.
- **Space:** $O(n)$ for heap + map in worst case.

> Note: The optimal approach uses a monotonic deque in $O(n)$ time and $O(k)$ space. 
> Your provided code is still valid and commonly accepted for this problem size.

---

## Reference Implementation (same idea as above)

```python
import heapq
from collections import defaultdict
from typing import List


class Solution:
		def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
				n = len(nums)

				res = []
				pq = []
				mp = defaultdict(int)

				# Build first window
				for i in range(k):
						mp[nums[i]] += 1
						heapq.heappush(pq, -nums[i])
				res.append(-pq[0])

				# Slide window
				for i in range(k, n):
						mp[nums[i]] += 1
						heapq.heappush(pq, -nums[i])

						left = i - k
						mp[nums[left]] -= 1

						while pq and mp[-pq[0]] <= 0:
								heapq.heappop(pq)

						res.append(-pq[0])

				return res
```

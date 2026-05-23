## Problem

https://leetcode.com/problems/video-stitching/description/

You are given a series of video clips from a sporting event that lasted `time` seconds. Each video clip is described by `clips[i] = [starti, endi]` indicating the ith clip started at `starti` and ended at `endi`.

We can cut these clips into segments freely.

**Goal**: Return the minimum number of clips needed to cover the entire sporting event `[0, time]`. If impossible, return `-1`.

**Constraints:**
- `1 <= clips.length <= 100`
- `0 <= starti <= endi <= 100`
- `1 <= time <= 100`

**Examples:**

1. `clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10` → Output: `3`
   - Take clips `[0,2]`, `[1,9]`, `[8,10]`. Cut `[1,9]` into `[1,2] + [2,8] + [8,9]` to get `[0,2] + [2,8] + [8,10]` covering `[0,10]`.

2. `clips = [[0,1],[1,2]], time = 5` → Output: `-1`
   - Cannot cover `[0,5]` with only these clips.

## Observations

1. **Greedy Approach**: We want to select clips that extend our coverage as far as possible at each step.

2. **Sorting Strategy**: Sort clips by start time (and by end time in descending order for tie-breaking) to process them in order of coverage intervals.

3. **Coverage Gap Check**: If the first clip doesn't start at 0, it's impossible to cover the entire interval.

4. **Two-Pointer Technique**:
   - `cur_end`: The current endpoint of our covered interval
   - `next_end`: The furthest point we can reach using clips that start within the current coverage
   - If `next_end` doesn't advance beyond `cur_end`, the gap cannot be filled

5. **Early Termination**: Once we reach or exceed `time`, we have our answer. If we exhaust all clips without reaching `time`, return `-1`.

## Solution

```python
class Solution:
    def videoStitching(self, clips: List[List[int]], time: int) -> int:
        # Sort by start time, then by end time (descending) for tie-breaking
        clips.sort(key=lambda x: (x[0], -x[1]))
        n = len(clips)

        # Must start at 0
        if clips[0][0] > 0:
            return -1
        
        count = 0
        i = 0
        cur_end = 0  # Current coverage endpoint
        next_end = 0  # Furthest endpoint reachable from current coverage
        
        while i < n and cur_end < time:
            # Find the clip that extends coverage the furthest
            # from within the current covered region
            while i < n and cur_end >= clips[i][0]:
                next_end = max(next_end, clips[i][1])
                i += 1
            
            # If next_end didn't advance, we have a gap
            if next_end == cur_end:
                return -1
            
            count += 1
            cur_end = next_end
        
        # Check if we covered the entire interval
        if cur_end < time:
            return -1
        
        return count
```

**Algorithm Walkthrough** (Example 1: `clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10`):

1. **Sort**: `[[0,2], [1,9], [1,5], [4,6], [5,9], [8,10]]`
2. **Initialize**: `count = 0, cur_end = 0, next_end = 0, i = 0`
3. **Iteration 1**:
   - Find clips starting ≤ 0: `[0,2]` → `next_end = 2`
   - `count = 1, cur_end = 2`
4. **Iteration 2**:
   - Find clips starting ≤ 2: `[1,9], [1,5]` → `next_end = max(2, 9, 5) = 9`
   - `count = 2, cur_end = 9`
5. **Iteration 3**:
   - Find clips starting ≤ 9: `[4,6], [5,9], [8,10]` → `next_end = max(9, 6, 9, 10) = 10`
   - `count = 3, cur_end = 10`
6. `cur_end >= time` → return `3`

**Time Complexity**: $O(n \log n)$ for sorting + $O(n)$ for the greedy scan = $O(n \log n)$

**Space Complexity**: $O(1)$ (excluding the sorting space)

# Tags
- Greedy Algorithm
- Array
- Two Pointers


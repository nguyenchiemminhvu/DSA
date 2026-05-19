## Problem

https://leetcode.com/problems/find-good-days-to-rob-the-bank/description

You and a gang of thieves are planning on robbing a bank. You are given a **0-indexed integer array `security`**, where `security[i]` is the number of guards on duty on the i-th day. The days are numbered starting from 0. You are also given an **integer `time`**.

The i-th day is a **good day to rob the bank** if and only if:
1. There are **at least `time` days before and after** the i-th day
2. The number of guards **before** i are **non-increasing**: `security[i - time] >= security[i - time + 1] >= ... >= security[i]`
3. The number of guards **after** i are **non-decreasing**: `security[i] <= ... <= security[i + time - 1] <= security[i + time]`

### Examples

**Example 1:**
```
Input: security = [5,3,3,3,5,6,2], time = 2
Output: [2,3]
```
- Day 2: `5 >= 3 >= 3 <= 3 <= 5` ✓
- Day 3: `3 >= 3 >= 3 <= 5 <= 6` ✓

**Example 2:**
```
Input: security = [1,1,1,1,1], time = 0
Output: [0,1,2,3,4]
```
When `time = 0`, every day is valid (no surrounding days needed).

**Example 3:**
```
Input: security = [1,2,3,4,5,6], time = 2
Output: []
```
No valid day exists (strictly increasing array means no non-increasing sequences).

---

## Observations

### 1. **Pattern Recognition Problem**
- We need to find **consecutive non-increasing sequences** of length >= `time` before day i
- We need to find **consecutive non-decreasing sequences** of length >= `time` after day i
- This is about detecting monotonic subsequences, not subarrays

### 2. **Key Insight: Sequence Length Tracking**
- For each position, we can precompute:
  - `left[i]` = length of **non-increasing sequence ending at i** (including i itself)
  - `right[i]` = length of **non-decreasing sequence starting at i** (including i itself)
- A day i is good if `left[i] > time` AND `right[i] > time`

### 3. **Why `> time` instead of `>= time`?**
- We need **`time` days BEFORE and `time` days AFTER**
- `left[i]` should include the current day at index i, so we need at least `time + 1` elements total
- Example: if `time = 2`, we need indices [i-2, i-1, i], that's 3 elements, so `left[i]` must be > 2

### 4. **Index Boundary Constraints**
- A day i can only be good if `i >= time` and `i <= n - 1 - time`
- This ensures at least `time` days exist on both sides
- This is equivalent to `time <= i < n - time`

### 5. **Time Complexity Analysis**
- **Brute Force**: Check each day with window validation = O(n × time)
- **Optimized**: Precompute sequences = O(n)
- **Space**: O(n) for `left` and `right` arrays

---

## Solution

### Algorithm: Precompute Monotonic Sequences

```python
class Solution:
    def goodDaysToRobBank(self, nums: List[int], time: int) -> List[int]:
        n = len(nums)
        
        # left[i] = length of non-increasing sequence ending at i
        left = [1] * n
        for i in range(1, n):
            if nums[i] <= nums[i - 1]:
                left[i] = left[i - 1] + 1
        
        # right[i] = length of non-decreasing sequence starting at i
        right = [1] * n
        for i in range(n - 2, -1, -1):
            if nums[i] <= nums[i + 1]:
                right[i] = right[i + 1] + 1
        
        # Collect valid days
        res = []
        for i in range(time, n - time):
            if left[i] > time and right[i] > time:
                res.append(i)
        
        return res
```

### Step-by-Step Walkthrough (Example 1: `security = [5,3,3,3,5,6,2], time = 2`)

**Step 1: Build `left` array (non-increasing sequences)**
```
Index:  0 1 2 3 4 5 6
nums:   5 3 3 3 5 6 2
left:   1 2 3 4 1 1 1
        ↑ ↑ ↑ ↑
    Single non-increasing: 5→3→3→3
```
- `left[0] = 1` (start)
- `left[1] = 2` (5 >= 3, so continue: length 2)
- `left[2] = 3` (3 <= 3, so continue: length 3)
- `left[3] = 4` (3 <= 3, so continue: length 4)
- `left[4] = 1` (5 > 3, break sequence)
- `left[5] = 1` (6 > 5, break sequence)
- `left[6] = 1` (2 < 6, no increment needed)

**Step 2: Build `right` array (non-decreasing sequences)**
```
Index:  0 1 2 3 4 5 6
nums:   5 3 3 3 5 6 2
right:  1 1 1 3 2 1 1
            ↑ ↑ ↑
        Non-decreasing: 3→5→6
```
- `right[6] = 1` (end)
- `right[5] = 1` (6 > 2, break sequence)
- `right[4] = 2` (5 <= 6, continue: length 2)
- `right[3] = 3` (3 <= 5, continue: length 3)
- `right[2] = 1` (3 > 3, no — wait, 3 <= 3 is true!)
- `right[2] = 1` (3 <= 3? Yes! But we need to check: 3 <= 3, so continue)

*Correction:*
```
Index:  0 1 2 3 4 5 6
nums:   5 3 3 3 5 6 2
right:  1 1 3 3 2 1 1
```
Going backwards:
- `right[6] = 1`
- `right[5] = 1` (6 > 2, break)
- `right[4] = 2` (5 <= 6)
- `right[3] = 3` (3 <= 5)
- `right[2] = 3` (3 <= 3)
- `right[1] = 1` (3 > 3? No, 3 <= 3, so continue)

Wait, let me recalculate:
- `right[1]` should check if `nums[1] <= nums[2]` → `3 <= 3`? Yes, so `right[1] = right[2] + 1 = 4`

Let me trace more carefully:
```
i = 5: nums[5] = 6, nums[6] = 2, 6 > 2, so right[5] = 1
i = 4: nums[4] = 5, nums[5] = 6, 5 <= 6, so right[4] = right[5] + 1 = 2
i = 3: nums[3] = 3, nums[4] = 5, 3 <= 5, so right[3] = right[4] + 1 = 3
i = 2: nums[2] = 3, nums[3] = 3, 3 <= 3, so right[2] = right[3] + 1 = 4
i = 1: nums[1] = 3, nums[2] = 3, 3 <= 3, so right[1] = right[2] + 1 = 5
i = 0: nums[0] = 5, nums[1] = 3, 5 > 3, so right[0] = 1
```

```
Index:  0 1 2 3 4 5 6
nums:   5 3 3 3 5 6 2
right:  1 5 4 3 2 1 1
```

**Step 3: Find valid days (time = 2)**
```
Range: i in [2, 5) → i ∈ {2, 3, 4}
```
- `i = 2`: `left[2] = 3 > 2` ✓ AND `right[2] = 4 > 2` ✓ → **VALID**
- `i = 3`: `left[3] = 4 > 2` ✓ AND `right[3] = 3 > 2` ✓ → **VALID**
- `i = 4`: `left[4] = 1 > 2` ✗ → **INVALID**

**Result: `[2, 3]`** ✓

---

## Complexity Analysis

| Aspect | Complexity |
|--------|------------|
| **Time** | O(n) - Three linear passes |
| **Space** | O(n) - Two auxiliary arrays |

---

## Key Takeaways

1. **Precomputation is powerful**: Instead of rechecking windows repeatedly, precompute monotonic sequence lengths
2. **Off-by-one matters**: Remember `> time` not `>= time` because we're counting total length including the current day
3. **Two-pass approach**: Build left (forward) and right (backward) independently for clean logic
4. **Boundary checking**: Always validate that enough elements exist on both sides before checking a position

# Tags

- **Difficulty**: Medium
- **Topics**: Array, Monotonic, Dynamic Programming (DP-like pattern matching)
- **Pattern**: Precomputation, Monotonic Sequences
- **Similar Problems**: 
  - [Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)
  - [Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/)
  - [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)


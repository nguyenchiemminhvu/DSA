## Problem

https://leetcode.com/problems/split-array-into-consecutive-subsequences/description/

You are given an integer array `nums` that is sorted in non-decreasing order.

Determine if it is possible to split `nums` into one or more subsequences such that both of the following conditions are true:

1. Each subsequence is a **consecutive increasing sequence** (i.e. each integer is exactly one more than the previous integer).
2. All subsequences have a **length of 3 or more**.

Return `true` if you can split `nums` according to the above conditions, or `false` otherwise.

**Example 1:**
```
Input: nums = [1,2,3,3,4,5]
Output: true
Explanation: nums can be split into the following subsequences:
[1,2,3,3,4,5] --> 1, 2, 3
[1,2,3,3,4,5] --> 3, 4, 5
```

**Example 2:**
```
Input: nums = [1,2,3,3,4,4,5,5]
Output: true
Explanation: nums can be split into the following subsequences:
[1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
[1,2,3,3,4,4,5,5] --> 3, 4, 5
```

**Example 3:**
```
Input: nums = [1,2,3,4,4,5]
Output: false
Explanation: It is impossible to split nums into consecutive increasing subsequences of length 3 or more.
```

**Constraints:**
- 1 <= nums.length <= 10^4
- -1000 <= nums[i] <= 1000
- nums is sorted in non-decreasing order

## Observations

1. **Key Constraint**: Each subsequence must be consecutive (each element is exactly +1 from previous) and have length >= 3.

2. **Greedy Strategy**: When we encounter a number, we have two choices:
   - **Append to existing subsequence**: If there's a subsequence ending at `val-1` that needs `val` to continue, it's always better to extend it.
   - **Start new subsequence**: If we can't append, we must start a new subsequence with at least 3 consecutive numbers.

3. **Why Greedy Works**: Extending an existing subsequence is always preferable to starting a new one because:
   - It uses fewer numbers to satisfy the "length >= 3" requirement
   - It leaves more numbers available for other subsequences
   - If we can't extend, we need `val`, `val+1`, and `val+2` immediately available

4. **Two Dictionaries Needed**:
   - `freq`: Tracks how many of each number are still available to use
   - `need`: Tracks how many subsequences are waiting for a particular number to extend

## Solution

### Algorithm Explanation

The solution uses a **greedy two-pass approach**:

**First Pass**: Count frequency of each number
```python
for val in nums:
    freq[val] = freq.get(val, 0) + 1
```

**Second Pass**: For each number, make the greedy choice
```python
for val in nums:
    # Skip if this number is already used
    if freq.get(val, 0) == 0:
        continue
    
    # Case 1: Can we extend an existing subsequence?
    if need.get(val, 0) > 0:
        need[val] -= 1           # One less subsequence needs 'val'
        freq[val] -= 1           # Use this occurrence of 'val'
        need[val + 1] += 1       # Now this subsequence needs 'val+1'
    
    # Case 2: Must start a new subsequence
    else:
        # Check if we can form [val, val+1, val+2]
        if freq.get(val + 1, 0) == 0 or freq.get(val + 2, 0) == 0:
            return False         # Can't form valid subsequence
        
        # Use three consecutive numbers to start new subsequence
        freq[val] -= 1
        freq[val + 1] -= 1
        freq[val + 2] -= 1
        need[val + 3] += 1       # This new subsequence will need 'val+3' next
```

### Example Walkthrough

**Example**: `nums = [1,2,3,3,4,5]`

**Initial State**:
- `freq = {1:1, 2:1, 3:2, 4:1, 5:1}`
- `need = {}`

**Processing**:

1. **val = 1**: 
   - No subsequence needs 1 → Start new: use [1,2,3]
   - `freq = {1:0, 2:0, 3:1, 4:1, 5:1}`
   - `need = {4:1}` (subsequence [1,2,3] needs 4)

2. **val = 2**: 
   - `freq[2] = 0` → Skip (already used)

3. **val = 3** (first occurrence):
   - `freq[3] = 1` → Skip (already used)

4. **val = 3** (second occurrence):
   - No subsequence needs 3 → Start new: use [3,4,5]
   - `freq = {1:0, 2:0, 3:0, 4:0, 5:0}`
   - `need = {4:0, 6:1}` (subsequence [3,4,5] needs 6)

5. **val = 4**:
   - `freq[4] = 0` → Skip (already used)

6. **val = 5**:
   - `freq[5] = 0` → Skip (already used)

**Result**: Return `true` ✓

### Complexity Analysis

- **Time Complexity**: O(n)
  - First pass: O(n) to build frequency map
  - Second pass: O(n) to process each element
  - All dictionary operations are O(1) on average

- **Space Complexity**: O(n)
  - `freq` dictionary: O(unique values in nums)
  - `need` dictionary: O(unique values that subsequences need)
  - In worst case, could be O(n)

### Code

```python
class Solution:
    def isPossible(self, nums: List[int]) -> bool:
        freq = {}
        need = {}
        
        # Count frequency of each number
        for val in nums:
            freq[val] = freq.get(val, 0) + 1
        
        # Process each number greedily
        for val in nums:
            # Skip if already used
            if freq.get(val, 0) == 0:
                continue
            
            # Try to extend existing subsequence
            if need.get(val, 0) > 0:
                need[val] -= 1
                freq[val] -= 1
                need[val + 1] = need.get(val + 1, 0) + 1
            
            # Must start new subsequence
            else:
                # Need at least 3 consecutive numbers
                if freq.get(val + 1, 0) == 0 or freq.get(val + 2, 0) == 0:
                    return False
                
                # Start new subsequence of length 3
                need[val + 3] = need.get(val + 3, 0) + 1
                freq[val] -= 1
                freq[val + 1] -= 1
                freq[val + 2] -= 1
        
        return True
```

### Key Insights

1. **Greedy Choice**: Always prefer extending existing subsequences over starting new ones
2. **Order Matters**: Process numbers in sorted order to make greedy decisions work
3. **Immediate Validation**: When starting a new subsequence, we must have all 3 consecutive numbers available immediately
4. **Tracking Future Needs**: The `need` dictionary elegantly tracks what each "active" subsequence needs next

# Tags
#greedy #hashmap #array #subsequence #medium


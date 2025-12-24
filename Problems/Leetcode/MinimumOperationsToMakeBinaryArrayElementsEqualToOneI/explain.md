## Problem

https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/description/

You are given a binary array `nums`.

You can do the following operation on the array any number of times (possibly zero):
- Choose any 3 consecutive elements from the array and flip all of them.
- Flipping an element means changing its value from 0 to 1, and from 1 to 0.

Return the minimum number of operations required to make all elements in `nums` equal to 1. If it is impossible, return -1.

**Example 1:**
```
Input: nums = [0,1,1,1,0,0]
Output: 3

Explanation:
- Choose indices 0, 1, 2: nums = [1,0,0,1,0,0]
- Choose indices 1, 2, 3: nums = [1,1,1,0,0,0]
- Choose indices 3, 4, 5: nums = [1,1,1,1,1,1]
```

**Example 2:**
```
Input: nums = [0,1,1,1]
Output: -1

Explanation: It is impossible to make all elements equal to 1.
```

**Constraints:**
- `3 <= nums.length <= 10^5`
- `0 <= nums[i] <= 1`

## Observations

### Key Insights

1. **Greedy Left-to-Right Approach**: Since we can only flip 3 consecutive elements, we should process the array from left to right. Once we fix an element to 1, we never want to flip it again.

2. **When to Flip**: Whenever we encounter a 0 at position `i`, we must flip the triplet `[i, i+1, i+2]` to make `nums[i]` become 1.

3. **Last Two Elements are Critical**: 
   - We can only flip triplets starting at positions `0` through `n-3`
   - The last two elements (`nums[n-2]` and `nums[n-1]`) can only be affected by flips at position `n-3` or earlier
   - If either of the last two elements is 0 after processing all possible flips, it's impossible to fix them

4. **Impossibility Condition**: If after processing indices `0` to `n-3`, either `nums[n-2]` or `nums[n-1]` is still 0, return -1.

5. **Flip Operation**: Flipping means toggling: `0 → 1` and `1 → 0`. This can be implemented as `(value + 1) % 2` or `1 - value` or `value ^ 1`.

### Why This Works

- By greedily fixing elements from left to right, we ensure that once `nums[i]` becomes 1, we never need to flip it again
- Any flip at position `i` affects `nums[i]`, `nums[i+1]`, and `nums[i+2]`
- We process positions `i = 0` to `n-3`, ensuring each position is set to 1
- The last two positions are automatically handled by previous flips, or they remain unfixable

## Solution

### Algorithm

```python
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        op = 0
        
        # Process from index 0 to n-3
        for i in range(0, n - 2):
            if nums[i] == 0:
                # Flip the triplet [i, i+1, i+2]
                nums[i + 1] = (nums[i + 1] + 1) % 2
                nums[i + 2] = (nums[i + 2] + 1) % 2
                op += 1
        
        # Check if last two elements are 1
        if nums[-2] == 0 or nums[-1] == 0:
            return -1
        
        return op
```

### Explanation

1. **Iterate through positions 0 to n-3**:
   - For each position `i`, check if `nums[i] == 0`
   - If yes, we must flip the triplet starting at `i`
   - Note: We don't need to flip `nums[i]` explicitly because we know it will become 1 after the flip

2. **Flip operation**:
   - Toggle `nums[i+1]` and `nums[i+2]`
   - We skip flipping `nums[i]` since we already know it's 0 and will become 1
   - Increment operation counter

3. **Final validation**:
   - After all possible flips, check the last two elements
   - If either is 0, it's impossible to fix, return -1
   - Otherwise, return the operation count

### Complexity Analysis

- **Time Complexity**: O(n)
  - Single pass through the array from index 0 to n-3
  - Each iteration performs constant work

- **Space Complexity**: O(1)
  - We modify the input array in-place
  - Only use a constant amount of extra space for the counter
  - If modifying input is not allowed, we'd need O(n) space for a copy

### Example Walkthrough

**Input**: `nums = [0,1,1,1,0,0]`

```
Initial: [0,1,1,1,0,0]

i=0: nums[0]=0 → flip [0,1,2]
     [1,0,0,1,0,0], op=1

i=1: nums[1]=0 → flip [1,2,3]
     [1,1,1,0,0,0], op=2

i=2: nums[2]=1 → skip

i=3: nums[3]=0 → flip [3,4,5]
     [1,1,1,1,1,1], op=3

Check last two: nums[4]=1, nums[5]=1 ✓

Output: 3
```

**Input**: `nums = [0,1,1,1]`

```
Initial: [0,1,1,1]

i=0: nums[0]=0 → flip [0,1,2]
     [1,0,0,1], op=1

i=1: nums[1]=0 → flip [1,2,3]
     [1,1,1,0], op=2

Check last two: nums[2]=1, nums[3]=0 ✗

Output: -1
```

# Tags

#greedy #array #simulation #bit-manipulation


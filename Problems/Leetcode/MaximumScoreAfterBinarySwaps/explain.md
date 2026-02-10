## Problem

https://leetcode.com/problems/maximum-score-after-binary-swaps/description/

```
You are given an integer array nums of length n and a binary string s of the same length.

Initially, your score is 0. Each index i where s[i] = '1' contributes nums[i] to the score.

You may perform any number of operations (including zero). In one operation, you may choose an 
index i such that 0 <= i < n - 1, where s[i] = '0', and s[i + 1] = '1', and swap these two 
characters.

Return an integer denoting the maximum possible score you can achieve.

Example 1:
Input: nums = [2,1,5,2,3], s = "01010"
Output: 7
Explanation:
- Swap at index i = 0: "01010" → "10010"
- Swap at index i = 2: "10010" → "10100"
- Positions 0 and 2 contain '1', contributing nums[0] + nums[2] = 2 + 5 = 7

Example 2:
Input: nums = [4,7,2,9], s = "0000"
Output: 0
Explanation: No '1' characters means no swaps can be performed. Score remains 0.

Constraints:
- n == nums.length == s.length
- 1 <= n <= 10^5
- 1 <= nums[i] <= 10^9
- s[i] is either '0' or '1'
```

## Observations

1. **Swap Operation**: We can only swap "01" → "10", which means we can move '1's to the left but never to the right.

2. **Key Insight**: A '1' at position i can potentially be moved to any position j where j <= i through a series of swaps. This means each '1' can "claim" any value from positions 0 to its current position.

3. **Greedy Strategy**: To maximize the score, we should assign each '1' to the largest available value at or before its position. This is because:
   - The number of '1's is fixed (cannot create or destroy them)
   - Each '1' should be paired with the highest possible value
   - The heap allows us to greedily select the maximum available value

4. **No Need for Actual Swapping**: We don't need to simulate the swaps. We just need to determine which positions the '1's should end up at to maximize the sum.

## Solution

**Algorithm**: Greedy with Max Heap

The solution uses a greedy approach with a max heap to efficiently assign each '1' to the maximum available value:

```python
import heapq

class Solution:
    def maximumScore(self, nums: List[int], s: str) -> int:
        n = len(s)
        total_1 = s.count('1')
        if total_1 == 0:
            return 0
        
        res = 0
        pq = []  # max heap (using negative values)
        for i, ch in enumerate(s):
            # Add current position's value to the heap
            heapq.heappush(pq, -nums[i])
            
            # If we encounter a '1', assign it to the maximum value seen so far
            if ch == '1':
                res += -heapq.heappop(pq)
        
        return res
```

**How It Works**:

1. **Iterate Left to Right**: Process each position from left to right.

2. **Maintain Max Heap**: At each position i, add nums[i] to a max heap. This heap contains all values from positions 0 to i.

3. **Assign '1's Greedily**: When we encounter a '1' at position i:
   - Pop the maximum value from the heap
   - Add it to the result
   - This represents moving that '1' to the position with the maximum value

4. **Why This Works**:
   - When we reach position i with a '1', we've already seen all positions 0 to i
   - The '1' can be moved to any of these positions through swaps
   - Greedy choice: assign it to the position with the maximum value
   - The heap efficiently tracks the best available position

**Example Walkthrough** (nums = [2,1,5,2,3], s = "01010"):

```
i=0, s[0]='0': heap = [-2]
i=1, s[1]='1': heap = [-2,-1], pop -2, res = 2, heap = [-1]
i=2, s[2]='0': heap = [-5,-1]
i=3, s[3]='1': heap = [-5,-1,-2], pop -5, res = 7, heap = [-2,-1]
i=4, s[4]='0': heap = [-3,-2,-1]
Final result: 7
```

**Complexity**:
- **Time**: O(n log n) - n iterations, each with heap operations
- **Space**: O(n) - heap can contain up to n elements

# Tags
- Greedy
- Heap
- Max Heap
- String Manipulation
- Array


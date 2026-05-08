## Problem

https://leetcode.com/problems/count-indices-with-opposite-parity/description/

Given an integer array `nums` of length `n`, find the score of each index `i` where the score is defined as the count of indices `j` such that:
- `i < j < n` (j is to the right of i)
- `nums[i]` and `nums[j]` have different parity (one is even, the other is odd)

Return an array `answer` where `answer[i]` is the score of index `i`.

**Example 1:**
```
Input: nums = [1,2,3,4]
Output: [2,1,1,0]

Explanation:
- nums[0] = 1 (odd) → indices 1,3 have even values → score = 2
- nums[1] = 2 (even) → index 2 has odd value → score = 1
- nums[2] = 3 (odd) → index 3 has even value → score = 1
- nums[3] = 4 (even) → no indices to the right → score = 0
```

**Example 2:**
```
Input: nums = [1]
Output: [0]
```

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

## Observations

1. **Parity Check**: A number is odd if `(num & 1) == 1`, even if `(num & 1) == 0`

2. **Brute Force Approach**: For each index `i`, count all indices `j > i` with opposite parity
   - Time Complexity: O(n²)
   - Space Complexity: O(n) for the result array

3. **Efficient Approach - Reverse Iteration**:
   - Process the array from right to left (n-1 to 0)
   - Maintain a count of even and odd numbers seen so far (to the right)
   - For each position `i`, the score is the count of numbers with opposite parity seen so far
   - Time Complexity: O(n)
   - Space Complexity: O(1) excluding the result array

4. **Key Insight**: By processing right to left, we build up information about what's to the right of the current position, which is exactly what we need to answer the query

## Solution

```python
from collections import defaultdict

class Solution:
    def countOppositeParity(self, nums: list[int]) -> list[int]:
        """
        Count indices with opposite parity for each position.
        
        Algorithm: Reverse iteration with parity counting
        - Traverse array from right to left (backwards)
        - Maintain count of even and odd numbers to the right
        - For each index i:
          * Get its parity (nums[i] & 1)
          * Score = count of opposite parity numbers to the right
          * Update count for current parity
        
        Time Complexity: O(n) - single pass
        Space Complexity: O(1) excluding result array
        """
        m = defaultdict(int)  # m[0] = even count, m[1] = odd count
        n = len(nums)
        res = [0] * n
        
        # Process from right to left
        for i in range(n - 1, -1, -1):
            # Get parity: 0 for even, 1 for odd
            parity = nums[i] & 1
            
            # Score = count of opposite parity numbers seen so far (to the right)
            res[i] = m[(parity + 1) % 2]
            
            # Increment count for current parity
            m[parity] += 1
        
        return res
```

### Step-by-Step Walkthrough (nums = [1,2,3,4])

```
Initial: m = {}, res = [0,0,0,0]

i=3: nums[3]=4 (even, parity=0)
  - res[3] = m[(0+1)%2] = m[1] = 0 (no odd numbers to the right)
  - m[0] += 1 → m = {0: 1}

i=2: nums[2]=3 (odd, parity=1)
  - res[2] = m[(1+1)%2] = m[0] = 1 (one even number: 4)
  - m[1] += 1 → m = {0: 1, 1: 1}

i=1: nums[1]=2 (even, parity=0)
  - res[1] = m[(0+1)%2] = m[1] = 1 (one odd number: 3)
  - m[0] += 1 → m = {0: 2, 1: 1}

i=0: nums[0]=1 (odd, parity=1)
  - res[0] = m[(1+1)%2] = m[0] = 2 (two even numbers: 2, 4)
  - m[1] += 1 → m = {0: 2, 1: 2}

Result: res = [2,1,1,0] ✓
```

### Why This Works

1. **Right-to-Left Processing**: Ensures all elements to the right of position `i` are counted before we process position `i`

2. **Parity Tracking**: Using `defaultdict(int)` automatically initializes missing keys to 0, so we don't need to handle uninitialized cases

3. **Opposite Parity Formula**: 
   - If current element is even (parity = 0), opposite is odd: `(0+1)%2 = 1`
   - If current element is odd (parity = 1), opposite is even: `(1+1)%2 = 0`

4. **Efficiency**: We only iterate through the array once and use a simple dictionary lookup, making this optimal

## Tags

- Array
- Counting
- Two Pointers / Right-to-Left Traversal
- Parity/Bit Manipulation
- LeetCode Medium


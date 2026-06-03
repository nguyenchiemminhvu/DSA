# Maximum XOR For Each Query

## Problem Statement

https://leetcode.com/problems/maximum-xor-for-each-query/description/

You are given a sorted array `nums` of `n` non-negative integers and an integer `maximumBit`. You want to perform the following query `n` times:

1. Find a non-negative integer `k < 2^maximumBit` such that:
   ```
   nums[0] XOR nums[1] XOR ... XOR nums[nums.length-1] XOR k
   ```
   is **maximized**.
2. `k` is the answer to the current query.
3. Remove the last element from the current array `nums`.

Return an array `answer`, where `answer[i]` is the answer to the `i`-th query.

### Constraints

- `nums.length == n`
- `1 <= n <= 10^5`
- `1 <= maximumBit <= 20`
- `0 <= nums[i] < 2^maximumBit`
- `nums` is sorted in ascending order

### Examples

**Example 1:**
```
Input: nums = [0,1,1,3], maximumBit = 2
Output: [0,3,2,3]

Explanation:
1st query: nums = [0,1,1,3], k = 0 since 0 XOR 1 XOR 1 XOR 3 XOR 0 = 3
2nd query: nums = [0,1,1], k = 3 since 0 XOR 1 XOR 1 XOR 3 = 3
3rd query: nums = [0,1], k = 2 since 0 XOR 1 XOR 2 = 3
4th query: nums = [0], k = 3 since 0 XOR 3 = 3
```

**Example 2:**
```
Input: nums = [2,3,4,7], maximumBit = 3
Output: [5,2,6,5]

Explanation:
1st query: nums = [2,3,4,7], k = 5 since 2 XOR 3 XOR 4 XOR 7 XOR 5 = 7
2nd query: nums = [2,3,4], k = 2 since 2 XOR 3 XOR 4 XOR 2 = 7
3rd query: nums = [2,3], k = 6 since 2 XOR 3 XOR 6 = 7
4th query: nums = [2], k = 5 since 2 XOR 5 = 7
```

---

## Observations

### Key Insights

1. **XOR Properties:**
   - XOR is associative and commutative: `a XOR b XOR c = c XOR b XOR a`
   - `a XOR a = 0` and `a XOR 0 = a`
   - XOR with all 1s flips all bits

2. **Prefix XOR:**
   - We can compute the XOR of all elements in the current array incrementally
   - The XOR of prefix changes as we remove elements from the end

3. **Maximizing XOR:**
   - To maximize `current_xor XOR k`, we want `k` to flip the bits where `current_xor` has 0s
   - The maximum value we can get is when all bits up to `maximumBit` are set to 1
   - Maximum possible value = `2^maximumBit - 1` (all bits set to 1)
   - If `current_xor = x`, then `k = x XOR (2^maximumBit - 1)` maximizes `x XOR k`
   - This gives us: `x XOR (x XOR mask) = mask = 2^maximumBit - 1`

4. **Reverse Processing:**
   - Instead of removing elements from the end, we can compute answers in reverse
   - Process from last element to first, building up the XOR value
   - Reverse the results at the end

5. **Time Complexity:**
   - Single pass through array: O(n)
   - Reversing result: O(n)
   - Overall: **O(n)**
   - Space: O(n) for result array

---

## Solution Explanation

```python
class Solution:
    def getMaximumXor(self, nums: List[int], maximumBit: int) -> List[int]:
        n = len(nums)
        
        # Create mask with all bits set up to maximumBit
        mask = (1 << maximumBit) - 1
        
        res = []
        x = 0  # Current XOR of elements processed
        
        # Process elements from first to last
        for i in range(n):
            x ^= nums[i]  # Accumulate XOR
            # To maximize x XOR k, set k = x XOR mask
            # This gives us x XOR (x XOR mask) = mask
            res.append(x ^ mask)
        
        # Reverse because we processed forward but queries go backward
        res.reverse()
        return res
```

### Step-by-Step Walkthrough (Example 1: nums = [0,1,1,3], maximumBit = 2)

```
mask = (1 << 2) - 1 = 0b11 = 3

Step 1: i=0, nums[0]=0
  x = 0 XOR 0 = 0
  res.append(0 XOR 3) = 0
  res = [0]

Step 2: i=1, nums[1]=1
  x = 0 XOR 1 = 1
  res.append(1 XOR 3) = 2
  res = [0, 2]

Step 3: i=2, nums[2]=1
  x = 1 XOR 1 = 0
  res.append(0 XOR 3) = 3
  res = [0, 2, 3]

Step 4: i=3, nums[3]=3
  x = 0 XOR 3 = 3
  res.append(3 XOR 3) = 0
  res = [0, 2, 3, 0]

After reverse: res = [0, 3, 2, 0]
```

Wait, let me recalculate to match the expected output [0,3,2,3]:

The key insight: **Reverse processing means the last computed value corresponds to the 1st query**.

Actually, let me trace through the logic more carefully:

When we process forward and accumulate:
- After processing index 0: XOR of [0] = 0, k that maximizes = 0 XOR 3 = 3... but answer should be 0
- After processing index 1: XOR of [0,1] = 1, k = 1 XOR 3 = 2
- After processing index 2: XOR of [0,1,1] = 0, k = 0 XOR 3 = 3  ✓ (2nd query)
- After processing index 3: XOR of [0,1,1,3] = 3, k = 3 XOR 3 = 0... but answer should be 0 ✓

Actually the answer IS [0,3,2,0] reversed to [0,2,3,0]... Let me recalculate.

After XORing [0,1,1,3]: 0 XOR 1 XOR 1 XOR 3 = 3
To maximize with k: need k such that 3 XOR k is maximum.
k = 3 XOR (2^2 - 1) = 3 XOR 3 = 0 ✓
Result = 3 XOR 0 = 3... this should be the 1st query answer!

After reversing [0,2,3,0] → [0,3,2,0]... Still doesn't match.

Let me reconsider: The XOR value BEFORE adding the element is what we need!

Actually the solution should compute backwards:
- 1st query: all 4 elements, k=0, result=3
- Then remove last: [0,1,1]
- 2nd query: XOR of [0,1,1]=0, k such that 0 XOR k = max, k=3, result=3
- Then remove last: [0,1]
- 3rd query: XOR of [0,1]=1, k such that 1 XOR k = max, k=2, result=3
- Then remove last: [0]
- 4th query: XOR of [0]=0, k such that 0 XOR k = max, k=3, result=3

Expected output: [0,3,2,3]

So the algorithm computes forward and reverses:
- Step 1: x=0, append 0 XOR 3 = 3
- Step 2: x=1, append 1 XOR 3 = 2
- Step 3: x=0, append 0 XOR 3 = 3
- Step 4: x=3, append 3 XOR 3 = 0

Result = [3,2,3,0], reverse = [0,3,2,3] ✓

### Why This Works

1. **Forward XOR Accumulation:** By processing elements forward and accumulating XOR, we build up the XOR values we would get when processing backward (query by query).

2. **Bit Flipping Property:** To maximize `current_xor XOR k`:
   - We want `k` to set bits where `current_xor` is 0
   - And unset bits where `current_xor` is 1
   - This is exactly `k = current_xor XOR mask`
   - Result = `current_xor XOR k = current_xor XOR (current_xor XOR mask) = mask`

3. **Reverse Mapping:** The results array computed forward matches the reverse order of queries:
   - Forward position 0 → corresponds to backward query (most elements)
   - Forward position n-1 → corresponds to backward query (least elements)

---

## Complexity Analysis

| Aspect | Complexity |
|--------|-----------|
| Time | O(n) - single pass forward + reversal |
| Space | O(n) - for result array |

---

## Code Solution

```python
from typing import List

class Solution:
    def getMaximumXor(self, nums: List[int], maximumBit: int) -> List[int]:
        """
        Find the maximum XOR for each query as we progressively remove
        the last element from the array.
        
        Key insight: Process forward with XOR accumulation, then reverse
        the results. For each XOR value x, the k that maximizes x XOR k
        is x XOR mask, where mask = 2^maximumBit - 1.
        
        Args:
            nums: Sorted array of non-negative integers
            maximumBit: Maximum number of bits (defines maximum possible k)
        
        Returns:
            Array of answers, where answer[i] is the answer to the i-th query
        """
        n = len(nums)
        
        # Mask with all bits set up to maximumBit
        mask = (1 << maximumBit) - 1
        
        res = []
        x = 0  # Accumulated XOR
        
        # Process elements from first to last
        for i in range(n):
            x ^= nums[i]  # Update XOR with current element
            # k that maximizes x XOR k = x XOR mask
            # Result: x XOR (x XOR mask) = mask
            res.append(x ^ mask)
        
        # Reverse because forward processing matches backward query order
        res.reverse()
        return res


# Test cases
if __name__ == "__main__":
    sol = Solution()
    
    # Example 1
    assert sol.getMaximumXor([0, 1, 1, 3], 2) == [0, 3, 2, 3]
    
    # Example 2
    assert sol.getMaximumXor([2, 3, 4, 7], 3) == [5, 2, 6, 5]
    
    # Example 3
    assert sol.getMaximumXor([0, 1, 2, 2, 5, 7], 3) == [4, 3, 6, 4, 6, 7]
    
    print("All tests passed!")
```

## Problem

https://leetcode.com/problems/maximum-product-after-k-increments/description/

```
You are given an array of non-negative integers nums and an integer k. In one operation, 
you may choose any element from nums and increment it by 1.

Return the maximum product of nums after at most k operations. Since the answer may be 
very large, return it modulo 10^9 + 7. Note that you should maximize the product before 
taking the modulo.

Example 1:
Input: nums = [0,4], k = 5
Output: 20
Explanation: Increment the first number 5 times.
Now nums = [5, 4], with a product of 5 * 4 = 20.

Example 2:
Input: nums = [6,3,3,2], k = 2
Output: 216
Explanation: Increment the second number 1 time and increment the fourth number 1 time.
Now nums = [6, 4, 3, 3], with a product of 6 * 4 * 3 * 3 = 216.

Constraints:
- 1 <= nums.length, k <= 10^5
- 0 <= nums[i] <= 10^6
```

## Observations

1. **Greedy Approach**: To maximize the product, we should increment the smallest numbers first
   - Mathematical proof: If we have two numbers `a` and `b` where `a > b`, then:
     - `a * (b + 1) = a*b + a` (increment smaller)
     - `(a + 1) * b = a*b + b` (increment larger)
   - Since `a > b`, we get `a*b + a > a*b + b`
   - Therefore, incrementing the smaller number gives a larger product

2. **Key Insight**: Always increment the minimum element in the array
   - This balances the numbers and maximizes the product
   - Example: `[2, 5]` → incrementing 2 five times gives `[7, 5]` with product 35
   - But incrementing 5 five times gives `[2, 10]` with product 20 (worse!)

3. **Data Structure**: Min-heap (priority queue) is perfect for this
   - Efficiently get the minimum element: O(1)
   - After incrementing, re-insert: O(log n)
   - Total time complexity: O(k log n)

4. **Edge Cases**:
   - Array with zeros: incrementing 0 has the most impact
   - All equal numbers: they will stay relatively balanced
   - k = 0: return product as-is

## Solution

**Algorithm**:
1. Convert the array into a min-heap
2. For each of the k operations:
   - Pop the smallest element
   - Increment it by 1
   - Push it back to the heap
3. Calculate the product of all elements with modulo 10^9 + 7

**Implementation**:
```python
import heapq

class Solution:
    def maximumProduct(self, nums: List[int], k: int) -> int:
        # Convert array to min-heap
        heapq.heapify(nums)
        
        # Perform k increments on minimum elements
        for _ in range(k):
            val = heapq.heappop(nums)
            heapq.heappush(nums, val + 1)
        
        # Calculate product with modulo
        prod = 1
        mod = 10**9 + 7
        for val in nums:
            prod = ((prod % mod) * (val % mod)) % mod
        return prod
```

**Complexity Analysis**:
- Time: O(n + k log n) where n is length of nums
  - O(n) for heapify
  - O(k log n) for k heap operations
- Space: O(1) - modifying input array in-place (or O(n) if counting the heap)

**Why This Works**:
- Incrementing smaller numbers has exponentially more impact on the final product
- By always choosing the minimum, we balance the numbers optimally
- Example: `[1, 1, 10]` with k=2:
  - Greedy: `[1, 1, 10]` → `[2, 1, 10]` → `[2, 2, 10]` = 40
  - Wrong: `[1, 1, 10]` → `[1, 1, 11]` → `[1, 1, 12]` = 12

# Tags
`Greedy` `Heap (Priority Queue)` `Math` `Array`


## Problem

https://leetcode.com/problems/minimum-operations-to-halve-array-sum/description/

```
You are given an array nums of positive integers. In one operation, you can choose 
any number from nums and reduce it to exactly half the number. (Note that you may 
choose this reduced number in future operations.)

Return the minimum number of operations to reduce the sum of nums by at least half.

Example 1:
Input: nums = [5,19,8,1]
Output: 3
Explanation: The initial sum of nums is equal to 5 + 19 + 8 + 1 = 33.
The following is one of the ways to reduce the sum by at least half:
Pick the number 19 and reduce it to 9.5.
Pick the number 9.5 and reduce it to 4.75.
Pick the number 8 and reduce it to 4.
The final array is [5, 4.75, 4, 1] with a total sum of 5 + 4.75 + 4 + 1 = 14.75. 
The sum of nums has been reduced by 33 - 14.75 = 18.25, which is at least half of 
the initial sum, 18.25 >= 33/2 = 16.5.
Overall, 3 operations were used so we return 3.

Example 2:
Input: nums = [3,8,20]
Output: 3
Explanation: The initial sum of nums is equal to 3 + 8 + 20 = 31.
The following is one of the ways to reduce the sum by at least half:
Pick the number 20 and reduce it to 10.
Pick the number 10 and reduce it to 5.
Pick the number 3 and reduce it to 1.5.
The final array is [1.5, 8, 5] with a total sum of 1.5 + 8 + 5 = 14.5. 
The sum of nums has been reduced by 31 - 14.5 = 16.5, which is at least half of 
the initial sum, 16.5 >= 31/2 = 15.5.
Overall, 3 operations were used so we return 3.

Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^7
```

## Observations

1. **Greedy Approach**: To minimize the number of operations, we should always halve the largest number available. This is because halving a larger number reduces the sum more than halving a smaller number.

2. **Priority Queue (Max Heap)**: We need a data structure that efficiently gives us the maximum element and allows us to update values. A max heap is perfect for this use case.

3. **Target**: We need to reduce the sum by at least `total_sum / 2`. We can track how much we've reduced and stop when we reach this target.

4. **Floating Point Arithmetic**: Since we're dividing by 2 repeatedly, we'll be dealing with floating point numbers.

5. **Time Complexity**: Each operation involves a heap pop and push, both O(log n). In the worst case, we might need O(n log n) operations if we have to halve every element multiple times.

## Solution

```python
import heapq
from typing import List

class Solution:
    def halveArray(self, nums: List[int]) -> int:
        # Calculate total sum and the target reduction (half of total)
        total = sum(nums)
        half = total / 2
        
        # Create a max heap using negative values (Python has min heap by default)
        pq = []
        for val in nums:
            heapq.heappush(pq, -val)
        
        # Track the number of operations and total reduction achieved
        count = 0
        total = 0  # This represents the total reduction amount
        
        # Keep halving the largest element until we've reduced by at least half
        while total < half:
            # Get the largest element (negate because we stored negative values)
            val = -heapq.heappop(pq)
            
            # Halve it
            val /= 2
            
            # Add the reduction amount to our total
            total += val
            
            # Put the halved value back into the heap
            heapq.heappush(pq, -val)
            
            # Increment operation count
            count += 1
        
        return count
```

**Algorithm Explanation:**

1. **Initialize**: Calculate the original sum and determine the target (half of the sum).

2. **Build Max Heap**: Insert all numbers into a max heap. Since Python's `heapq` is a min heap, we negate all values to simulate a max heap.

3. **Greedy Halving**: 
   - Extract the maximum element from the heap
   - Halve it
   - Add the reduction amount (which equals the halved value) to our running total
   - Push the halved value back into the heap
   - Increment the operation counter

4. **Termination**: Stop when the total reduction equals or exceeds half of the original sum.

**Why This Works:**

The greedy approach is optimal because halving larger numbers always gives us more reduction per operation. For example, halving 20 reduces the sum by 10, while halving 4 reduces it by only 2. By always choosing the largest available number, we minimize the total number of operations needed.

**Complexity Analysis:**
- **Time Complexity**: O(n log n), where n is the length of nums. Building the heap takes O(n log n), and each of the potentially O(n) operations involves O(log n) heap operations.
- **Space Complexity**: O(n) for the heap storage.

# Tags
`Heap`, `Priority Queue`, `Greedy`, `Array`, `Max Heap`


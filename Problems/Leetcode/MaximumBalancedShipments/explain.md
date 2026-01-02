## Problem

https://leetcode.com/problems/maximum-balanced-shipments/description/

```
You are given an integer array weight of length n, representing the weights of n parcels 
arranged in a straight line. A shipment is defined as a contiguous subarray of parcels. 
A shipment is considered balanced if the weight of the last parcel is strictly less than 
the maximum weight among all parcels in that shipment.

Select a set of non-overlapping, contiguous, balanced shipments such that each parcel 
appears in at most one shipment (parcels may remain unshipped).

Return the maximum possible number of balanced shipments that can be formed.

Example 1:
Input: weight = [2,5,1,4,3]
Output: 2
Explanation:
- Shipment 1: [2, 5, 1] → max=5, last=1, 1<5 ✓
- Shipment 2: [4, 3] → max=4, last=3, 3<4 ✓

Example 2:
Input: weight = [4,4]
Output: 0
Explanation:
- [4,4] → max=4, last=4, 4 is not < 4 ✗
- [4] → max=4, last=4, 4 is not < 4 ✗

Constraints:
- 2 <= n <= 10^5
- 1 <= weight[i] <= 10^9
```

## Observations

1. **Key Insight - Greedy Approach**: We want to maximize the number of balanced shipments, so we should try to form shipments as soon as possible when we find a valid ending point.

2. **What makes a shipment balanced?**
   - Last element < maximum element in the shipment
   - For a shipment to be balanced, we need at least one element that is greater than the last element

3. **Greedy Strategy**: 
   - As we iterate through the array, we track the maximum element seen so far in the current potential shipment
   - When we find an element that is strictly less than the maximum we've seen, we can form a balanced shipment
   - Once we form a shipment, we reset and start looking for the next one

4. **Why Greedy Works**:
   - Forming a shipment as early as possible doesn't hurt our chances of forming more shipments later
   - Delaying wouldn't give us any advantage since shipments must be non-overlapping
   - Each time we find a valid ending point (element < current max), we should take it

5. **Algorithm Flow**:
   ```
   [2, 5, 1, 4, 3]
    ^           
    prev=2
    
   [2, 5, 1, 4, 3]
       ^
    prev=5 (update max)
    
   [2, 5, 1, 4, 3]
          ^
    1 < 5 → Form shipment [2,5,1], count=1, reset prev=-1
    
   [2, 5, 1, 4, 3]
             ^
    prev=4
    
   [2, 5, 1, 4, 3]
                ^
    3 < 4 → Form shipment [4,3], count=2, reset prev=-1
    
   Result: 2 shipments
   ```

## Solution

**Greedy Algorithm - Time: O(n), Space: O(1)**

The solution uses a greedy approach that scans the array left to right:

1. **Track Maximum**: Maintain `prev` as the maximum weight seen in the current potential shipment
2. **Check for Balance**: When we encounter an element strictly less than `prev`, we've found a balanced shipment
3. **Form Shipment**: Increment count and reset `prev` to start a new potential shipment
4. **Update Maximum**: If current element is not less than `prev`, update `prev` to the current element

```python
class Solution:
    def maxBalancedShipments(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        prev = -1  # Tracks the maximum weight in current potential shipment
        i = 0
        
        while i < n:
            if prev == -1:
                # Starting a new potential shipment
                prev = nums[i]
            else:
                if nums[i] < prev:
                    # Found a balanced shipment: last < max
                    count += 1
                    prev = -1  # Reset to start looking for next shipment
                else:
                    # Update the maximum for current potential shipment
                    prev = nums[i]
            i += 1
            
        return count
```

**Why This Works:**
- **Correctness**: By greedily forming shipments as soon as we find a valid ending, we maximize opportunities for future shipments
- **Optimality**: There's no benefit to extending a shipment beyond the first valid ending point, as this only reduces the elements available for future shipments
- **Efficiency**: Single pass through the array with constant space

**Alternative Cleaner Implementation:**
```python
class Solution:
    def maxBalancedShipments(self, nums: List[int]) -> int:
        count = 0
        max_weight = nums[0]
        
        for i in range(1, len(nums)):
            if nums[i] < max_weight:
                count += 1
                max_weight = nums[i+1] if i+1 < len(nums) else float('inf')
                i += 1  # Skip next element as it starts new shipment
            else:
                max_weight = max(max_weight, nums[i])
        
        return count
```

# Tags
#greedy #array #dynamic-programming #optimization


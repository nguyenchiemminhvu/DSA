## Problem

https://leetcode.com/problems/maximum-sum-of-three-numbers-divisible-by-three/description/

You are given an integer array `nums`.

Your task is to choose exactly three integers from `nums` such that their sum is divisible by three.

Return the maximum possible sum of such a triplet. If no such triplet exists, return 0.

**Example 1:**
- Input: `nums = [4,2,3,1]`
- Output: `9`
- Explanation: Valid triplets are (4,2,3) with sum 9 and (2,3,1) with sum 6. Maximum is 9.

**Example 2:**
- Input: `nums = [2,1,5]`
- Output: `0`
- Explanation: No triplet forms a sum divisible by 3.

**Constraints:**
- `3 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^5`

## Observations

1. **Modular Arithmetic Property**: A sum is divisible by 3 if and only if the sum of remainders (when divided by 3) is divisible by 3.

2. **Remainder Groups**: Each number can be classified into one of three groups based on its remainder when divided by 3:
   - Group 0: `num % 3 == 0`
   - Group 1: `num % 3 == 1`
   - Group 2: `num % 3 == 2`

3. **Valid Triplet Combinations**: To get a sum divisible by 3, we need one of these combinations:
   - Three numbers from Group 0 (0 + 0 + 0 = 0, divisible by 3)
   - Three numbers from Group 1 (1 + 1 + 1 = 3, divisible by 3)
   - Three numbers from Group 2 (2 + 2 + 2 = 6, divisible by 3)
   - One number from each group (0 + 1 + 2 = 3, divisible by 3)

4. **Maximization Strategy**: To maximize the sum, we should select the largest values from each required group.

## Solution

**Approach: Heap-based Greedy Selection**

**Algorithm:**
1. **Group numbers by remainder**: Create three max heaps (priority queues) to store numbers based on their remainder when divided by 3.
   - Use negative values to simulate max heaps with Python's min heap

2. **Check all valid combinations**:
   - If Group 0 has ≥3 numbers: Take the 3 largest
   - If Group 1 has ≥3 numbers: Take the 3 largest
   - If Group 2 has ≥3 numbers: Take the 3 largest
   - If all groups have ≥1 number: Take the largest from each

3. **Return maximum**: Among all valid combinations, return the maximum sum.

**Implementation:**
```python
import heapq

class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        # Create 3 max heaps for remainders 0, 1, 2
        pq = [[] for _ in range(3)]
        for val in nums:
            rem = val % 3
            heapq.heappush(pq[rem], -val)  # Negate for max heap
        
        res = 0
        
        # Case 1: Three numbers from Group 0
        if len(pq[0]) >= 3:
            temp = pq[0][:]
            a, b, c = heapq.heappop(temp), heapq.heappop(temp), heapq.heappop(temp)
            res = max(res, -a - b - c)
        
        # Case 2: Three numbers from Group 1
        if len(pq[1]) >= 3:
            temp = pq[1][:]
            a, b, c = heapq.heappop(temp), heapq.heappop(temp), heapq.heappop(temp)
            res = max(res, -a - b - c)
        
        # Case 3: Three numbers from Group 2
        if len(pq[2]) >= 3:
            temp = pq[2][:]
            a, b, c = heapq.heappop(temp), heapq.heappop(temp), heapq.heappop(temp)
            res = max(res, -a - b - c)
        
        # Case 4: One from each group (0, 1, 2)
        if pq[0] and pq[1] and pq[2]:
            res = max(res, (-pq[0][0] - pq[1][0] - pq[2][0]))
        
        return res
```

**Complexity Analysis:**
- **Time Complexity**: $O(n \log n)$ where $n$ is the length of `nums`
  - Inserting all elements into heaps: $O(n \log n)$
  - Extracting top 3 elements from each heap: $O(\log n)$ per extraction, constant number of extractions
  
- **Space Complexity**: $O(n)$ to store all elements in the heaps

**Key Insights:**
- Using heaps allows efficient retrieval of the largest values in each remainder group
- Only 4 possible combinations need to be checked (not all possible triplets)
- The solution leverages modular arithmetic properties to reduce the problem space

# Tags
Array, Greedy, Heap, Priority Queue, Modular Arithmetic, Math


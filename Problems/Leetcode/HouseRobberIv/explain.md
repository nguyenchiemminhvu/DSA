## Problem

https://leetcode.com/problems/house-robber-iv/description/?q=robber

A robber needs to steal from **at least k houses** along a street where:
- Each house has money inside
- The robber **cannot steal from adjacent houses** (can't rob house i and i+1)
- The **capability** is defined as the **maximum amount** stolen from any single house that was robbed

**Goal:** Find the **minimum possible capability** across all valid ways to rob at least k non-adjacent houses.

### Examples:

**Example 1:**
```
Input: nums = [2,3,5,9], k = 2
Output: 5

Explanation:
- Rob houses [0,2]: max(2,5) = 5 ✓ (minimum)
- Rob houses [0,3]: max(2,9) = 9
- Rob houses [1,3]: max(3,9) = 9
Answer: min(5, 9, 9) = 5
```

**Example 2:**
```
Input: nums = [2,7,9,3,1], k = 2
Output: 2

Best way: Rob houses at indices 0 and 4
Capability: max(2,1) = 2
```

### Constraints:
- 1 ≤ nums.length ≤ 10⁵
- 1 ≤ nums[i] ≤ 10⁹
- 1 ≤ k ≤ (nums.length + 1)/2

## Observations

1. **Direct DP Approach is Impractical:**
   - A straightforward DP solution to enumerate all valid robbing combinations would be exponential
   - We need a smarter approach than trying all subsets

2. **Binary Search on the Answer:**
   - The answer (capability) lies between `min(nums)` and `max(nums)`
   - Key insight: If we can rob k houses with capability ≤ x, we can also rob k houses with capability ≤ (x+1)
   - This **monotonic property** makes binary search applicable!

3. **Greedy Feasibility Check:**
   - For a given capability `cap`, we can **greedily check** if it's possible to rob ≥ k houses
   - Use a greedy approach: iterate through houses left to right
   - If `nums[i] ≤ cap`, rob this house and skip the next one (i += 2)
   - If `nums[i] > cap`, move to the next house (i += 1)
   - This greedy strategy is **optimal** for checking feasibility because:
     - Robbing earlier valid houses gives us more flexibility for future houses
     - Skipping invalid houses doesn't help us achieve k robberies

4. **Why Greedy Works for Checking:**
   - If we can rob k houses with max value ≤ cap using any strategy, the greedy approach will also find k houses
   - The greedy approach maximizes the number of valid houses we can rob within a given constraint
   - It's always safe to rob a valid house and skip the next one

## Solution

### Algorithm: Binary Search + Greedy Validation

```python
class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        n = len(nums)

        def check_possible(cap: int) -> bool:
            """
            Check if we can rob at least k houses with capability <= cap
            Greedy approach: rob houses left to right if their value <= cap
            """
            i = 0
            count = 0
            while i < n:
                if nums[i] <= cap:
                    count += 1      # Rob this house
                    i += 2          # Skip next house (non-adjacent constraint)
                else:
                    i += 1          # Can't rob this house, move to next
            return count >= k

        # Binary search on the capability value
        l, r = min(nums), max(nums)
        res = r
        
        while l <= r:
            m = l + (r - l) // 2
            if check_possible(m):
                res = m             # Can achieve this capability, try smaller
                r = m - 1
            else:
                l = m + 1           # Need higher capability
        
        return res
```

### Step-by-Step Example:

**Input:** `nums = [2,3,5,9], k = 2`

**Binary Search Process:**
```
Initial: l=2, r=9, res=9

Iteration 1: m=5
  check_possible(5)?
  - i=0: nums[0]=2 <= 5, count=1, i=2
  - i=2: nums[2]=5 <= 5, count=2, i=4 (exit loop)
  - count=2 >= k=2 ✓
  - res=5, r=4

Iteration 2: m=3
  check_possible(3)?
  - i=0: nums[0]=2 <= 3, count=1, i=2
  - i=2: nums[2]=5 > 3, i=3
  - i=3: nums[3]=9 > 3, i=4 (exit loop)
  - count=1 < k=2 ✗
  - l=4

Iteration 3: l > r (4 > 4 is false, l=4, r=4)
  m=4
  check_possible(4)?
  - i=0: nums[0]=2 <= 4, count=1, i=2
  - i=2: nums[2]=5 > 4, i=3
  - i=3: nums[3]=9 > 4, i=4
  - count=1 < k=2 ✗
  - l=5

Loop ends: l > r

Return res=5 ✓
```

### Complexity Analysis:

| Aspect | Complexity |
|--------|-----------|
| **Time** | O(n log(max(nums))) |
| **Space** | O(1) |

**Breakdown:**
- Binary search iterations: O(log(max(nums) - min(nums))) ≈ O(log 10⁹) ≈ 30 iterations
- Each `check_possible()` call: O(n)
- Total: O(n × log(max(nums)))

### Why This Works:

1. **Correctness of Greedy Check:**
   - If a feasible solution exists with capability ≤ cap, robbing houses greedily (left to right) will find at least k houses
   - Greedy is optimal for this specific check because early robbing maximizes future opportunities

2. **Binary Search Invariant:**
   - If capability c is achievable, then all capabilities > c are also achievable
   - We binary search to find the **minimum** achievable capability

3. **Optimal Solution:**
   - Returns the smallest capability value where we can rob at least k non-adjacent houses

# Tags

- **Algorithm:** Binary Search, Greedy
- **Pattern:** Search on Answer, Feasibility Check
- **Difficulty:** Medium
- **Time Complexity:** O(n log(max(nums)))
- **Space Complexity:** O(1)


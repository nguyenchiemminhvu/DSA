## Problem

https://leetcode.com/problems/maximum-total-importance-of-roads/description/

You are given an integer `n` denoting the number of cities in a country. The cities are numbered from `0` to `n - 1`.

You are also given a 2D integer array `roads` where `roads[i] = [ai, bi]` denotes that there exists a **bidirectional road** connecting cities `ai` and `bi`.

You need to assign each city with an integer value from `1` to `n`, where each value can only be used **once**. The **importance** of a road is then defined as the **sum** of the values of the two cities it connects.

Return the **maximum total importance** of all roads possible after assigning the values optimally.

**Example 1:**
```
Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
Output: 43
Explanation: The assigned values of [2,4,5,3,1] give:
- The road (0,1) has an importance of 2 + 4 = 6.
- The road (1,2) has an importance of 4 + 5 = 9.
- The road (2,3) has an importance of 5 + 3 = 8.
- The road (0,2) has an importance of 2 + 5 = 7.
- The road (1,3) has an importance of 4 + 3 = 7.
- The road (2,4) has an importance of 5 + 1 = 6.
The total importance of all roads is 6 + 9 + 8 + 7 + 7 + 6 = 43.
```

**Example 2:**
```
Input: n = 5, roads = [[0,3],[2,4],[1,3]]
Output: 20
Explanation: The assigned values of [4,3,2,5,1] give:
- The road (0,3) has an importance of 4 + 5 = 9.
- The road (2,4) has an importance of 2 + 1 = 3.
- The road (1,3) has an importance of 3 + 5 = 8.
The total importance of all roads is 9 + 3 + 8 = 20.
```

**Constraints:**
- `2 <= n <= 5 * 10^4`
- `1 <= roads.length <= 5 * 10^4`
- `roads[i].length == 2`
- `0 <= ai, bi <= n - 1`
- `ai != bi`
- There are no duplicate roads.

## Observations

1. **Key Insight - Degree Matters**: The importance of each city's assigned value is multiplied by the number of roads connected to it (its degree). A city with degree `d` contributes its value `d` times to the total importance.

2. **Greedy Strategy**: To maximize the total importance, we should assign the **highest values** to cities with the **highest degrees**. This is because:
   - If city `i` has degree `d_i` and is assigned value `v_i`, it contributes `v_i * d_i` to the total
   - Total importance = `Σ(v_i * d_i)` for all cities
   - To maximize this sum, pair highest `v_i` with highest `d_i`

3. **Graph Properties**:
   - The graph is undirected (bidirectional roads)
   - Cities can be isolated (degree 0) - they don't contribute to importance
   - Each road is counted once, but each city's value is used for all its connected roads

4. **Algorithm Approach**:
   - Count the degree (frequency) of each city
   - Sort cities by degree in descending order
   - Assign values from `n` down to `1` based on degree ranking
   - Calculate total importance by summing up all road values

## Solution

### Approach: Greedy with Degree Counting

**Time Complexity:** O(n log n) - dominated by sorting/heap operations  
**Space Complexity:** O(n) - for storing degrees and importance mappings

**Algorithm:**

1. **Count Degrees**: Iterate through all roads and count how many roads each city is connected to
2. **Sort by Degree**: Use a max heap (or sort) to order cities by their degrees in descending order
3. **Assign Values**: Assign the highest value `n` to the city with the highest degree, `n-1` to the next, and so on
4. **Calculate Total**: Sum up the importance of all roads using the assigned values

**Implementation:**

```python
import heapq
from collections import defaultdict

class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        # Step 1: Count degree (frequency) of each city
        f = defaultdict(int)
        for a, b in roads:
            f[a] += 1
            f[b] += 1
        
        # Step 2: Use max heap to sort cities by degree (descending)
        # Python has min heap, so negate the degree for max heap behavior
        pq = []
        for k, v in f.items():
            heapq.heappush(pq, (-v, k))

        # Step 3: Assign importance values from n down to 1
        importance = n
        f_imp = {}
        while pq:
            _, city = heapq.heappop(pq)
            f_imp[city] = importance
            importance -= 1
        
        # Step 4: Calculate total importance of all roads
        res = 0
        for a, b in roads:
            res += (f_imp[a] + f_imp[b])
        return res
```

**Example Walkthrough (Example 1):**

Given: `n = 5`, `roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]`

1. **Degree Count:**
   - City 0: 2 roads (connected to 1, 2)
   - City 1: 3 roads (connected to 0, 2, 3)
   - City 2: 4 roads (connected to 0, 1, 3, 4)
   - City 3: 2 roads (connected to 1, 2)
   - City 4: 1 road (connected to 2)

2. **Sorted by Degree:** [2, 1, 0, 3, 4] (degrees: 4, 3, 2, 2, 1)

3. **Value Assignment:**
   - City 2 → value 5 (highest degree)
   - City 1 → value 4
   - City 0 → value 3 (or 2, tied degree)
   - City 3 → value 2 (or 3, tied degree)
   - City 4 → value 1

4. **Total Importance:**
   - (0,1): 3 + 4 = 7
   - (1,2): 4 + 5 = 9
   - (2,3): 5 + 2 = 7
   - (0,2): 3 + 5 = 8
   - (1,3): 4 + 2 = 6
   - (2,4): 5 + 1 = 6
   - **Total: 43**

**Alternative Simpler Approach (Without Heap):**

```python
class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        # Count degrees
        degree = [0] * n
        for a, b in roads:
            degree[a] += 1
            degree[b] += 1
        
        # Sort degrees and assign values
        degree.sort()
        
        # Calculate total: each degree multiplied by its assigned value
        return sum((i + 1) * d for i, d in enumerate(degree))
```

This approach is even cleaner - it sorts the degrees and directly computes the sum without explicitly assigning values to each city.

# Tags

`Graph` `Greedy` `Sorting` `Heap` `Degree Counting`


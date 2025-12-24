## Problem

https://leetcode.com/problems/closest-dessert-cost/description/

You want to make a dessert and are preparing to buy the ingredients. You have `n` ice cream base flavors and `m` types of toppings to choose from.

### Rules:
1. There must be **exactly one** ice cream base
2. You can add **one or more types** of topping or have **no toppings** at all
3. There are **at most two** of each type of topping

### Input:
- `baseCosts`: integer array of length `n`, where `baseCosts[i]` represents the price of the `i-th` ice cream base flavor
- `toppingCosts`: integer array of length `m`, where `toppingCosts[i]` is the price of one of the `i-th` topping
- `target`: integer representing your target price for dessert

### Goal:
Make a dessert with a total cost as close to `target` as possible.

### Output:
Return the closest possible cost of the dessert to `target`. If there are multiple, return the **lower one**.

---

### Examples

**Example 1:**
```
Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
Output: 10
Explanation: 
- Choose base 1: cost 7
- Take 1 of topping 0: cost 1 × 3 = 3
- Take 0 of topping 1: cost 0 × 4 = 0
Total: 7 + 3 + 0 = 10
```

**Example 2:**
```
Input: baseCosts = [2,3], toppingCosts = [4,5,100], target = 18
Output: 17
Explanation: 
- Choose base 1: cost 3
- Take 1 of topping 0: cost 1 × 4 = 4
- Take 2 of topping 1: cost 2 × 5 = 10
- Take 0 of topping 2: cost 0 × 100 = 0
Total: 3 + 4 + 10 + 0 = 17
```

**Example 3:**
```
Input: baseCosts = [3,10], toppingCosts = [2,5], target = 9
Output: 8
Explanation: It is possible to make desserts with cost 8 and 10. Return 8 as it is the lower cost.
```

---

### Constraints:
- `n == baseCosts.length`
- `m == toppingCosts.length`
- `1 ≤ n, m ≤ 10`
- `1 ≤ baseCosts[i], toppingCosts[i] ≤ 10^4`
- `1 ≤ target ≤ 10^4`

---

## Observations

### Key Insights:

1. **Fixed Base Choice**: We must choose exactly one base, so we can iterate through all base options.

2. **Topping Combinations**: For each topping, we have 3 choices:
   - Don't use it (0 times)
   - Use it once (1 time)
   - Use it twice (2 times)

3. **State Space**: With `m` toppings and 3 choices each, we have `3^m` possible topping combinations.

4. **Constraint Analysis**: Since `m ≤ 10`, we have at most `3^10 = 59,049` combinations per base, which is computationally feasible.

5. **Optimization Strategy**: 
   - For each base, generate all possible costs with different topping combinations
   - Sort these costs
   - Use binary search to find the closest cost to the target

6. **Edge Cases**:
   - When two costs are equally close to target, choose the lower one
   - Need to check both the cost just above and just below the target

---

## Solution

### Approach: DFS + Binary Search

The solution uses **Depth-First Search (DFS)** to generate all possible topping combinations, then uses **binary search** to efficiently find the closest cost.

### Algorithm Steps:

1. **For each base cost**:
   - Start DFS from this base cost
   
2. **DFS Topping Generation**:
   - At each topping index `i`, we have 3 choices:
     - Skip this topping: `dfs(i+1, price)`
     - Add 1 topping: `dfs(i+1, price + toppingCosts[i])`
     - Add 2 toppings: `dfs(i+1, price + toppingCosts[i] * 2)`
   - When we've processed all toppings (`i >= m`), store the total price

3. **Sort the generated prices**:
   - This enables binary search

4. **Find closest cost using binary search**:
   - Use `upper_bound` to find the first cost **greater than** target
   - Check two candidates:
     - The cost at `upper` index (first cost > target)
     - The cost at `upper - 1` index (last cost ≤ target)
   - Update result if we find a closer cost or a lower cost with same distance

5. **Return the closest cost**

### Time Complexity:
- **DFS generation**: O(3^m) for each base
- **Sorting**: O(3^m × log(3^m))
- **Binary search**: O(log(3^m))
- **Total**: O(n × 3^m × m) where:
  - n = number of bases
  - m = number of toppings

### Space Complexity:
- O(3^m) for storing all possible costs
- O(m) for recursion stack depth

### Why This Works:

1. **Completeness**: DFS explores all possible topping combinations (0, 1, or 2 of each)
2. **Efficiency**: Binary search reduces the search for closest cost from O(3^m) to O(log(3^m))
3. **Correctness**: By checking both neighbors around the target, we ensure we don't miss the optimal answer
4. **Tie-breaking**: The `min(res, tmp[upper])` ensures we return the lower cost when distances are equal

### Implementation Details:

**upper_bound function:**
```python
def upper_bound(arr: List[int], target: int) -> int:
    # Find first element > target
    # Returns len(arr) if all elements ≤ target
    n = len(arr)
    left, right, found = 0, n - 1, n
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] > target:
            found = mid
            right = mid - 1
        else:
            left = mid + 1
    return found
```

**DFS function:**
```python
def dfs(i: int, price: int) -> None:
    # i: current topping index
    # price: accumulated cost so far
    if i >= m:  # Base case: processed all toppings
        tmp.append(price)
        return
    
    # Try 0, 1, or 2 of current topping
    dfs(i + 1, price)                           # 0 toppings
    dfs(i + 1, price + topping_costs[i])        # 1 topping
    dfs(i + 1, price + topping_costs[i] * 2)    # 2 toppings
```

### Example Walkthrough (Example 3):

```
baseCosts = [3,10], toppingCosts = [2,5], target = 9

Base = 3:
  DFS generates all combinations:
    - 0 of each: 3
    - 1 of topping[0]: 3+2 = 5
    - 2 of topping[0]: 3+4 = 7
    - 1 of topping[1]: 3+5 = 8
    - 1 of each: 3+2+5 = 10
    - 2 of topping[0] + 1 of topping[1]: 3+4+5 = 12
    - 2 of topping[1]: 3+10 = 13
    - etc...
  
  After sort: [3, 5, 7, 8, 10, 12, 13, 15, 17]
  upper_bound(9) = 4 (points to 10)
  
  Check tmp[4] = 10, diff = |10-9| = 1
  Check tmp[3] = 8, diff = |8-9| = 1
  Both have same distance, choose 8 (lower cost)

Base = 10:
  All combinations start from 10 (≥ target)
  Best from this base: 10, diff = 1
  Current best (8) is still better

Result: 8
```

### Code Flow:

```python
class Solution:
    def closestCost(self, base_costs: List[int], topping_costs: List[int], target: int) -> int:
        res = float('inf')
        diff = float('inf')
        
        for base in base_costs:
            tmp = []
            dfs(0, base)      # Generate all combinations
            tmp.sort()         # Enable binary search
            
            upper = upper_bound(tmp, target)
            
            # Check candidate above target
            if upper < len(tmp):
                if diff > abs(tmp[upper] - target):
                    diff = abs(tmp[upper] - target)
                    res = tmp[upper]
                elif diff == abs(tmp[upper] - target):
                    res = min(res, tmp[upper])
            
            # Check candidate at or below target
            if upper > 0:
                if diff > abs(tmp[upper - 1] - target):
                    diff = abs(tmp[upper - 1] - target)
                    res = tmp[upper - 1]
                elif diff == abs(tmp[upper - 1] - target):
                    res = min(res, tmp[upper - 1])
        
        return res
```

---

# Tags

`DFS`, `Backtracking`, `Binary Search`, `Brute Force`, `Combinatorics`


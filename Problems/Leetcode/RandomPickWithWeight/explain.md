# Random Pick with Weight

## Problem

https://leetcode.com/problems/random-pick-with-weight/

You are given a **0-indexed** array of positive integers `w` where `w[i]` describes the weight of the `i`th index.

You need to implement the function `pickIndex()`, which **randomly picks an index** in the range `[0, w.length - 1]` (inclusive) and returns it. The probability of picking an index `i` is `w[i] / sum(w)`.

**For example**, if `w = [1, 3]`:
- The probability of picking index 0 is `1 / (1 + 3) = 0.25` (i.e., 25%)
- The probability of picking index 1 is `3 / (1 + 3) = 0.75` (i.e., 75%)

### Example 1:
```
Input: ["Solution","pickIndex"]
       [[[1]],[]]
Output: [null,0]

Explanation:
Solution solution = new Solution([1]);
solution.pickIndex(); // return 0. The only option is to return 0 since there is only one element in w.
```

### Example 2:
```
Input: ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
       [[[1,3]],[],[],[],[],[]]
Output: [null,1,1,1,1,0]

Explanation:
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // return 1. It is returning the second element (index = 1) that has a probability of 3/4.
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 0. It is returning the first element (index = 0) that has a probability of 1/4.
```

Since this is a randomization problem, multiple answers are allowed.

### Constraints:
- `1 <= w.length <= 10^4`
- `1 <= w[i] <= 10^5`
- `pickIndex` will be called at most `10^4` times

---

## Observations

### Key Insights:

1. **Weighted Random Selection**: We need to pick indices with probabilities proportional to their weights.

2. **Probability Distribution**: 
   - If `w = [1, 3, 2]`, total weight = 6
   - Index 0: probability = 1/6 ≈ 16.67%
   - Index 1: probability = 3/6 = 50%
   - Index 2: probability = 2/6 ≈ 33.33%

3. **Prefix Sum (Cumulative Sum) Approach**:
   - Transform `w = [1, 3, 2]` into prefix sums: `[1, 4, 6]`
   - This creates ranges:
     - Index 0: range [1, 1] (size 1)
     - Index 1: range [2, 4] (size 3)
     - Index 2: range [5, 6] (size 2)
   - Generate a random number in `[1, total]` and find which range it falls into

4. **Binary Search Optimization**:
   - Instead of linear search, use binary search to find the correct index
   - We need to find the **first index** where `prefix[i] >= random_number`
   - This is exactly the **lower_bound** operation

5. **Visualization Example** (`w = [1, 3, 2]`):
   ```
   Weights:      [1,    3,      2]
   Prefix Sum:   [1,    4,      6]
   
   Number Line:
   1   2   3   4   5   6
   |---|-------|-------|
   idx0  idx1    idx2
   
   Random number 1 → index 0
   Random number 2,3,4 → index 1
   Random number 5,6 → index 2
   ```

---

## Solution

### Algorithm:

#### Constructor `__init__(self, w: List[int])`:
1. **Build Prefix Sum Array**:
   - Initialize `running_sum = 0`
   - For each weight `w[i]`:
     - Add `w[i]` to `running_sum`
     - Append `running_sum` to `self.percents`
   - Store `self.total` = final sum

2. **Example**: `w = [1, 3, 2]`
   ```
   i=0: running_sum = 0 + 1 = 1  → percents = [1]
   i=1: running_sum = 1 + 3 = 4  → percents = [1, 4]
   i=2: running_sum = 4 + 2 = 6  → percents = [1, 4, 6]
   total = 6
   ```

#### Method `pickIndex(self) -> int`:
1. **Generate Random Number**:
   - `rand = random.randint(1, self.total)` (inclusive range)
   - Range: [1, total], not [0, total-1] to avoid edge cases

2. **Find Lower Bound**:
   - Use binary search to find the **first index** where `percents[idx] >= rand`
   - This ensures proper probability distribution

3. **Lower Bound Binary Search**:
   ```python
   def lower_bound(arr, target):
       left, right = 0, n - 1
       idx = n  # default to end if not found
       while left <= right:
           mid = left + (right - left) // 2
           if arr[mid] >= target:
               idx = mid           # potential answer
               right = mid - 1     # search left for smaller index
           else:
               left = mid + 1      # search right
       return idx
   ```

### Step-by-Step Example:

**Given**: `w = [1, 3, 2]`

**Initialization**:
- `percents = [1, 4, 6]`
- `total = 6`

**Pick Index (rand = 3)**:
1. Generate `rand = 3` (in range [1, 6])
2. Binary search in `[1, 4, 6]` for first element >= 3:
   - `left=0, right=2, mid=1`
   - `percents[1]=4 >= 3` → `idx=1`, search left
   - `left=0, right=0, mid=0`
   - `percents[0]=1 < 3` → search right
   - `left=1, right=0` → loop ends
   - Return `idx=1` ✓

**Pick Index (rand = 1)**:
1. Generate `rand = 1`
2. Binary search for first element >= 1:
   - Return `idx=0` ✓

**Pick Index (rand = 6)**:
1. Generate `rand = 6`
2. Binary search for first element >= 6:
   - Return `idx=2` ✓

### Why Random Range is [1, total] instead of [0, total-1]:

Using `[1, total]` simplifies the logic:
- If we used `[0, total-1]`, we'd need `percents[mid] > target` instead of `>=`
- The current approach naturally maps ranges correctly:
  - `rand ∈ [1, percents[0]]` → index 0
  - `rand ∈ [percents[i-1]+1, percents[i]]` → index i

### Code Implementation

```python
class Solution:

    def __init__(self, w: List[int]):
        running_sum = 0
        self.percents = []
        for val in w:
            running_sum += val
            self.percents.append(running_sum)
        self.total = running_sum

    def pickIndex(self) -> int:
        def lower_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right = 0, n - 1
            idx = n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx
        
        rand = random.randint(1, self.total)
        lower = lower_bound(self.percents, rand)
        return lower
```

### Alternative: Using Python's `bisect` Module

```python
import random
import bisect

class Solution:

    def __init__(self, w: List[int]):
        self.prefix = []
        running_sum = 0
        for weight in w:
            running_sum += weight
            self.prefix.append(running_sum)
        self.total = running_sum

    def pickIndex(self) -> int:
        rand = random.randint(1, self.total)
        return bisect.bisect_left(self.prefix, rand)
```

**Note**: `bisect_left` finds the leftmost position to insert `rand`, which works correctly with our approach.

### Complexity Analysis

**Time Complexity**:
- **Constructor**: **O(n)** - Building prefix sum array requires one pass through weights
- **pickIndex()**: **O(log n)** - Binary search on prefix sum array of size n

**Space Complexity**: **O(n)** - Store prefix sum array of size n

---

## Key Takeaways

1. **Prefix Sum** transforms weighted probability into range-based selection
2. **Binary Search** (lower_bound) efficiently finds the correct index in O(log n)
3. **Random range [1, total]** simplifies the boundary conditions
4. This pattern applies to many weighted sampling problems
5. Understanding the geometric interpretation (number line ranges) helps visualize correctness

# Tags

`Binary Search` `Prefix Sum` `Randomization` `Probability` `Array`


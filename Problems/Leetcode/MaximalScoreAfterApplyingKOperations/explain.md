# Maximal Score After Applying K Operations

## Problem

**Link:** https://leetcode.com/problems/maximal-score-after-applying-k-operations/description/

You are given a 0-indexed integer array `nums` and an integer `k`. You have a starting score of 0.

In one operation:
1. Choose an index `i` such that `0 <= i < nums.length`
2. Increase your score by `nums[i]`
3. Replace `nums[i]` with `ceil(nums[i] / 3)`

Return the maximum possible score you can attain after applying exactly `k` operations.

**Note:** The ceiling function `ceil(val)` is the least integer greater than or equal to `val`.

### Examples

**Example 1:**
```
Input: nums = [10,10,10,10,10], k = 5
Output: 50
Explanation: Apply the operation to each array element exactly once. 
The final score is 10 + 10 + 10 + 10 + 10 = 50.
```

**Example 2:**
```
Input: nums = [1,10,3,3,3], k = 3
Output: 17
Explanation: You can do the following operations:
Operation 1: Select i = 1, so nums becomes [1,4,3,3,3]. Your score increases by 10.
Operation 2: Select i = 1, so nums becomes [1,2,3,3,3]. Your score increases by 4.
Operation 3: Select i = 2, so nums becomes [1,2,1,3,3]. Your score increases by 3.
The final score is 10 + 4 + 3 = 17.
```

### Constraints
- `1 <= nums.length, k <= 10^5`
- `1 <= nums[i] <= 10^9`

---

## Observations

1. **Greedy Strategy**: To maximize the score, we should always pick the largest available element in each operation. This is because:
   - We want to accumulate the highest values possible
   - After taking an element, it gets reduced to `ceil(value/3)`, which is significantly smaller
   - The next operation should again pick the largest available value

2. **Element Reusability**: After an operation on an element, we can select it again in future operations (after it's been reduced). This means we need to maintain a dynamic structure that allows us to:
   - Quickly find the maximum element
   - Remove and re-insert elements efficiently

3. **Heap Data Structure**: A max heap is perfect for this problem because:
   - `O(1)` to peek at the maximum element
   - `O(log n)` to extract the maximum
   - `O(log n)` to insert a new element
   - Maintains the max-heap property automatically

4. **Ceiling Division Trick**: `ceil(a/b)` can be computed as `(a + b - 1) // b`. For `b = 3`, this becomes `(a + 2) // 3`. This avoids floating-point operations.

5. **Time Complexity**: With `k` operations and each operation involving heap operations: `O(n + k*log(n))` where `n = len(nums)`
   - `O(n)` to build the initial heap
   - `O(k*log(n))` for k extract-max and insert operations

---

## Solution

### Algorithm

The solution implements a **greedy approach using a max heap**:

1. **Initialize Max Heap**: Create a max heap and insert all elements from `nums`
2. **Perform K Operations**:
   - Extract the maximum element from the heap (this is our score contribution)
   - Add this value to the result
   - Calculate the reduced value: `ceil(value / 3)` using the formula `(value + 2) // 3`
   - Push the reduced value back into the heap
3. **Return Result**: After k operations, return the accumulated score

### Implementation Details

#### Custom Max Heap Class
```python
class max_heap:
    def __init__(self):
        self.pq = []
    
    def __bool__(self):
        return True if self.pq else False
    
    def push(self, val: int):
        heapq.heappush(self.pq, -val)  # Negate to simulate max heap
    
    def pop(self):
        if not self.pq:
            return None
        return -heapq.heappop(self.pq)  # Negate back to get original value
```

**Why negate values?** Python's `heapq` module implements a min heap. By negating values when pushing and negating again when popping, we effectively simulate a max heap.

#### Main Solution
```python
def maxKelements(self, nums: List[int], k: int) -> int:
    heap = max_heap()
    
    # Build heap with all elements
    for val in nums:
        heap.push(val)
    
    res = 0
    # Perform k operations
    while heap and k:
        score = heap.pop()           # Get max element
        res += score                 # Add to result
        heap.push((score + 2) // 3)  # Push reduced value (ceiling division)
        k -= 1
    
    return res
```

### Why This Works

The greedy strategy is optimal because:
- At each step, choosing the maximum element gives us the highest immediate score
- The reduction factor (divide by 3) is constant for all elements
- There's no benefit to "saving" a large element for later, as it will only decrease in value

### Example Walkthrough

**Input:** `nums = [1,10,3,3,3], k = 3`

**Initial Heap:** `[10, 3, 3, 3, 1]`

**Operation 1:**
- Pop max: `10`, score = `10`
- Push back: `ceil(10/3) = 4`
- Heap: `[4, 3, 3, 3, 1]`

**Operation 2:**
- Pop max: `4`, score = `10 + 4 = 14`
- Push back: `ceil(4/3) = 2`
- Heap: `[3, 3, 3, 2, 1]`

**Operation 3:**
- Pop max: `3`, score = `14 + 3 = 17`
- Push back: `ceil(3/3) = 1`
- Heap: `[3, 3, 2, 1, 1]`

**Final Score:** `17`

---

## Complexity Analysis

**Time Complexity:** `O(n + k*log(n))`
- Building the initial heap: `O(n)` where `n = len(nums)`
- Each of the `k` operations performs:
  - One `pop()`: `O(log n)`
  - One `push()`: `O(log n)`
- Total: `O(n + k*log(n))`

**Space Complexity:** `O(n)`
- The heap stores all `n` elements from the input array
- No additional space proportional to `k`

---

## Key Takeaways

1. **Greedy + Heap Pattern**: When you need to repeatedly select the maximum (or minimum) element and modify it, a heap is usually the right data structure
2. **Ceiling Division Without Float**: Use `(a + b - 1) // b` to compute `ceil(a/b)` using integer arithmetic only
3. **Max Heap in Python**: Simulate a max heap by negating values with `heapq` (min heap)
4. **Optimal Strategy**: Always choosing the locally optimal choice (max element) leads to the globally optimal solution in this problem

---

# Tags

`Heap`, `Greedy`, `Priority Queue`, `Array`


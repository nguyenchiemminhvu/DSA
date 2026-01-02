## Problem

https://leetcode.com/problems/sum-of-subarray-minimums/description/

```
Given an array of integers arr, find the sum of min(b), where b ranges over 
every (contiguous) subarray of arr. Since the answer may be large, return the 
answer modulo 10^9 + 7.

Example 1:
Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.

Example 2:
Input: arr = [11,81,94,43,3]
Output: 444

Constraints:
- 1 <= arr.length <= 3 * 10^4
- 1 <= arr[i] <= 3 * 10^4
```

## Observations

1. **Brute Force Complexity**: If we generate all subarrays and find their minimums, 
   we'd need O(n²) to generate subarrays and O(n) to find each minimum = O(n³) total.
   This is too slow for n = 30,000.

2. **Key Insight**: Instead of finding the minimum for each subarray, we can ask:
   "For each element arr[i], in how many subarrays is it the minimum?"
   
3. **Contribution of Each Element**: If arr[i] is the minimum in k subarrays, 
   it contributes arr[i] × k to the final sum.

4. **Finding the Range**: For arr[i] to be the minimum in a subarray:
   - The subarray must include arr[i]
   - All elements in the subarray must be >= arr[i]
   - So we need to find the range where arr[i] is the smallest element

5. **Left and Right Boundaries**:
   - **left[i]**: Index of the first element to the left that is smaller than arr[i]
   - **right[i]**: Index of the first element to the right that is smaller than arr[i]
   - The range where arr[i] can be minimum is (left[i], right[i])

6. **Counting Subarrays**: If left[i] = L and right[i] = R:
   - We can choose a starting point from indices [L+1, i] → (i - L) choices
   - We can choose an ending point from indices [i, R-1] → (R - i) choices
   - Total subarrays where arr[i] is minimum = (i - L) × (R - i)

7. **Handling Duplicates**: To avoid counting duplicates twice, we use:
   - `>=` when searching from left (allow equal elements on the left)
   - `>` when searching from right (don't allow equal elements on the right)

## Solution

### Approach: Monotonic Stack

The solution uses a **monotonic stack** to efficiently find the nearest smaller elements 
on both sides for each element.

### Algorithm Steps:

1. **Initialize Arrays**:
   - `left[i]`: Stores the index of the nearest smaller element to the left (default -1)
   - `right[i]`: Stores the index of the nearest smaller element to the right (default n)

2. **Find Left Boundaries** (left to right scan):
   ```
   For each element arr[i]:
   - Pop elements from stack while they are >= arr[i]
   - If stack is not empty, left[i] = top of stack
   - Push i onto stack
   ```

3. **Find Right Boundaries** (right to left scan):
   ```
   For each element arr[i] from right to left:
   - Pop elements from stack while they are > arr[i]
   - If stack is not empty, right[i] = top of stack
   - Push i onto stack
   ```

4. **Calculate Result**:
   ```
   For each element arr[i]:
   - Count of subarrays = (i - left[i]) × (right[i] - i)
   - Contribution = arr[i] × count
   - Add to result with modulo
   ```

### Example Walkthrough:

For `arr = [3,1,2,4]`:

**Step 1: Find left boundaries**
```
i=0: arr[0]=3, stack=[], left[0]=-1, stack=[0]
i=1: arr[1]=1, pop 0 (3>=1), stack=[], left[1]=-1, stack=[1]
i=2: arr[2]=2, pop 1 (1>=2? no), left[2]=1, stack=[1,2]
i=3: arr[3]=4, left[3]=2, stack=[1,2,3]

Result: left = [-1, -1, 1, 2]
```

**Step 2: Find right boundaries**
```
i=3: arr[3]=4, stack=[], right[3]=4, stack=[3]
i=2: arr[2]=2, pop 3 (4>2), stack=[], right[2]=4, stack=[2]
i=1: arr[1]=1, pop 2 (2>1), stack=[], right[1]=4, stack=[1]
i=0: arr[0]=3, pop 1 (1>3? no), right[0]=1, stack=[1,0]

Result: right = [1, 4, 4, 4]
```

**Step 3: Calculate contributions**
```
i=0: arr[0]=3, (0-(-1))*(1-0) = 1*1 = 1 subarray,  contribution = 3*1 = 3
i=1: arr[1]=1, (1-(-1))*(4-1) = 2*3 = 6 subarrays, contribution = 1*6 = 6
i=2: arr[2]=2, (2-1)*(4-2) = 1*2 = 2 subarrays,    contribution = 2*2 = 4
i=3: arr[3]=4, (3-2)*(4-3) = 1*1 = 1 subarray,     contribution = 4*1 = 4

Total = 3 + 6 + 4 + 4 = 17 ✓
```

### Code Explanation:

```python
class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        mod = 10**9 + 7
        n = len(arr)
        left = [-1] * n   # Nearest smaller element to the left
        right = [n] * n    # Nearest smaller element to the right

        # Find left boundaries using monotonic increasing stack
        st = []
        for i in range(n):
            # Pop elements >= current (to handle duplicates correctly)
            while st and arr[st[-1]] >= arr[i]:
                st.pop()
            if st:
                left[i] = st[-1]
            st.append(i)

        # Find right boundaries using monotonic increasing stack
        st = []
        for i in range(n - 1, -1, -1):
            # Pop elements > current (strict inequality for duplicates)
            while st and arr[st[-1]] > arr[i]:
                st.pop()
            if st:
                right[i] = st[-1]
            st.append(i)

        # Calculate sum of contributions
        res = 0
        for i in range(n):
            # Number of subarrays where arr[i] is minimum
            count = (i - left[i]) * (right[i] - i)
            # Add contribution with modulo
            res = ((res % mod) + arr[i] * count % mod) % mod

        return res
```

### Complexity Analysis:

- **Time Complexity**: O(n)
  - Each element is pushed and popped from stack at most once
  - Three separate O(n) passes through the array
  
- **Space Complexity**: O(n)
  - Two arrays (left, right) of size n
  - Stack size at most n

### Key Takeaways:

1. Transform the problem from "find min of each subarray" to "count subarrays where each element is min"
2. Use monotonic stack to efficiently find nearest smaller elements
3. Handle duplicates carefully with `>=` on one side and `>` on the other
4. Remember to apply modulo at each step to prevent overflow

# Tags

`Array` `Stack` `Monotonic Stack` `Dynamic Programming` `Contribution Technique`


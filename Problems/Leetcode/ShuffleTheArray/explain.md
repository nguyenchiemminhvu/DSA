## Problem

https://leetcode.com/problems/shuffle-the-array/description/

```
Given the array nums consisting of 2n elements in the form [x1,x2,...,xn,y1,y2,...,yn].

Return the array in the form [x1,y1,x2,y2,...,xn,yn].

Example 1:

Input: nums = [2,5,1,3,4,7], n = 3
Output: [2,3,5,4,1,7] 
Explanation: Since x1=2, x2=5, x3=1, y1=3, y2=4, y3=7 then the answer is [2,3,5,4,1,7].

Example 2:

Input: nums = [1,2,3,4,4,3,2,1], n = 4
Output: [1,4,2,3,3,2,4,1]

Example 3:

Input: nums = [1,1,2,2], n = 2
Output: [1,2,1,2]

Constraints:

1 <= n <= 500
nums.length == 2n
1 <= nums[i] <= 10^3
```

## Observations

### Understanding the Problem
- We have an array with `2n` elements: `[x1, x2, ..., xn, y1, y2, ..., yn]`
- We need to shuffle them to: `[x1, y1, x2, y2, ..., xn, yn]`
- The first half elements need to be interleaved with the second half elements

### Key Insights
1. **Pattern Recognition**: 
   - Element at index `i` (where `i < n`) should go to position `2*i`
   - Element at index `i+n` should go to position `2*i + 1`

2. **Index Mapping**:
   - `nums[0]` → `result[0]`, `nums[n]` → `result[1]`
   - `nums[1]` → `result[2]`, `nums[n+1]` → `result[3]`
   - `nums[i]` → `result[2*i]`, `nums[i+n]` → `result[2*i+1]`

## Solution

### Approach 1: Simple Solution with Extra Space (Recommended for Beginners)

```python
def shuffle(self, nums: List[int], n: int) -> List[int]:
    result = []
    
    # Interleave elements from first half and second half
    for i in range(n):
        result.append(nums[i])      # x_i
        result.append(nums[i + n])  # y_i
    
    return result
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n) - for the result array

**How it works**:
1. Create a new array to store the result
2. For each position `i` from `0` to `n-1`:
   - Add `nums[i]` (from first half)
   - Add `nums[i+n]` (from second half)
3. This naturally creates the interleaved pattern

### Approach 2: In-Place Solution using Bit Manipulation (Advanced)

```python
def shuffle(self, nums: List[int], n: int) -> List[int]:
    # Step 1: Store original values in higher 16 bits
    for i in range(n * 2):
        nums[i] = (nums[i] << 16)
    
    # Step 2: Place first half elements at even positions
    for i in range(n):
        nums[i * 2] |= (nums[i] >> 16)
    
    # Step 3: Place second half elements at odd positions  
    for i in range(n):
        nums[i * 2 + 1] |= (nums[i + n] >> 16)
    
    # Step 4: Extract final values (remove higher bits)
    for i in range(n * 2):
        nums[i] = nums[i] & 0xFFFF
    
    return nums
```

**Time Complexity**: O(n)  
**Space Complexity**: O(1) - no extra space used

**How it works**:

This solution uses bit manipulation to store two values in one integer:
- **Lower 16 bits**: store the new shuffled value
- **Higher 16 bits**: store the original value

**Step by step breakdown**:

1. **Preserve original values**: `nums[i] = (nums[i] << 16)`
   - Shift each number 16 bits left to store in higher bits
   - Example: `5` becomes `327680` (5 << 16)

2. **Place first half at even positions**: `nums[i * 2] |= (nums[i] >> 16)`
   - For `i = 0, 1, 2...n-1`, place `nums[i]` at positions `0, 2, 4...`
   - Use OR operation to set lower 16 bits while preserving higher bits

3. **Place second half at odd positions**: `nums[i * 2 + 1] |= (nums[i + n] >> 16)`
   - For `i = 0, 1, 2...n-1`, place `nums[i+n]` at positions `1, 3, 5...`

4. **Extract final values**: `nums[i] = nums[i] & 0xFFFF`
   - Use AND with `0xFFFF` (65535) to keep only lower 16 bits
   - This gives us the final shuffled values

**Example walkthrough** with `nums = [2,5,1,3,4,7], n = 3`:

```
Initial: [2, 5, 1, 3, 4, 7]

Step 1 - Shift left by 16:
[131072, 327680, 65536, 196608, 262144, 458752]

Step 2 - Place first half at even positions:
[131074, 327680, 65541, 196608, 262145, 458752]
  ↑(2)     ↑         ↑(5)      ↑        ↑(1)      ↑

Step 3 - Place second half at odd positions:
[131074, 327683, 65541, 196612, 262145, 458759]
    ↑    ↑(3)       ↑    ↑(4)       ↑    ↑(7)

Step 4 - Extract lower 16 bits:
[2, 3, 5, 4, 1, 7]
```

### Why Use Bit Manipulation?
- **Space Efficiency**: No extra array needed
- **Clever Storage**: Uses the fact that `nums[i] <= 1000`, which fits in 10 bits, leaving plenty of room in a 32-bit integer
- **Interview Appeal**: Demonstrates advanced problem-solving skills

### Which Approach to Use?
- **For learning/interviews**: Start with Approach 1, then explain Approach 2 if asked about space optimization
- **For production code**: Approach 1 is more readable and maintainable
- **For competitive programming**: Approach 2 shows advanced techniques



## Tags

array, bit manimulation
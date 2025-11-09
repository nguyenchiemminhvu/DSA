## Problem

https://leetcode.com/problems/defuse-the-bomb/

```
You have a bomb to defuse, and your time is running out! Your informer will provide you with a circular array code of length of n and a key k.

To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.

If k > 0, replace the ith number with the sum of the next k numbers.
If k < 0, replace the ith number with the sum of the previous k numbers.
If k == 0, replace the ith number with 0.
As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].

Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!

Example 1:

Input: code = [5,7,1,4], k = 3
Output: [12,10,16,13]
Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.

Example 2:

Input: code = [1,2,3,4], k = 0
Output: [0,0,0,0]
Explanation: When k is zero, the numbers are replaced by 0.

Example 3:

Input: code = [2,4,9,3], k = -2
Output: [12,5,6,13]
Explanation: The decrypted code is [3+9, 2+3, 4+2, 9+4]. Notice that the numbers wrap around again. If k is negative, the sum is of the previous numbers.

Constraints:

n == code.length
1 <= n <= 100
1 <= code[i] <= 100
-(n - 1) <= k <= n - 1
```

## Observations

1. **Circular Array Property**: The array wraps around, so after the last element comes the first element, and before the first element comes the last element.

2. **Three Cases to Handle**:
   - `k = 0`: Replace all elements with 0 (trivial case)
   - `k > 0`: For each position `i`, sum the next `k` elements (wrapping around if necessary)
   - `k < 0`: For each position `i`, sum the previous `|k|` elements (wrapping around if necessary)

3. **Prefix Sum Optimization**: Instead of calculating the sum of k elements for each position individually (which would be O(n*k)), we can use prefix sums to calculate range sums in O(1) time.

4. **Array Doubling Technique**: To handle the circular nature efficiently, we can double the array and compute prefix sums. This eliminates the need for complex modular arithmetic when dealing with wraparound cases.

## Solution

The solution uses a clever approach with prefix sums and array doubling:

### Step-by-step Breakdown:

1. **Handle Edge Case**: If `k = 0`, return an array of zeros.

2. **Create Doubled Array**: `prefix = code * 2` creates `[5,7,1,4,5,7,1,4]` from `[5,7,1,4]`. This handles wraparound naturally.

3. **Build Prefix Sum Array**: Convert the doubled array into a prefix sum array where `prefix[i]` contains the sum of all elements from index 0 to i.

4. **Calculate Results**:
   - **For k > 0**: `prefix[i + k] - prefix[i]` gives sum of next k elements
   - **For k < 0**: `prefix[i + n - 1] - prefix[i + n + k] + code[(i + k) % n]` gives sum of previous |k| elements

### Example Walkthrough (code = [5,7,1,4], k = 3):

1. **Doubled array**: `[5,7,1,4,5,7,1,4]`
2. **Prefix sums**: `[5,12,13,17,22,29,30,34]`
3. **For each position**:
   - i=0: `prefix[3] - prefix[0] = 17 - 5 = 12` (sum of 7,1,4)
   - i=1: `prefix[4] - prefix[1] = 22 - 12 = 10` (sum of 1,4,5)
   - i=2: `prefix[5] - prefix[2] = 29 - 13 = 16` (sum of 4,5,7)
   - i=3: `prefix[6] - prefix[3] = 30 - 17 = 13` (sum of 5,7,1)

### Time & Space Complexity:
- **Time**: O(n) - single pass to build prefix sums, single pass to calculate results
- **Space**: O(n) - for the doubled array and result array

### Key Insights:
- Array doubling eliminates wraparound complexity
- Prefix sums convert O(k) range sum queries to O(1)
- The formula for k < 0 is more complex due to the direction of summation but follows the same principle

# Tags
Array, Prefix Sum, Sliding Window


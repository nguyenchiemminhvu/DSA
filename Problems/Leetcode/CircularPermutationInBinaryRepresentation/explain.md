## Problem

https://leetcode.com/problems/circular-permutation-in-binary-representation/description/

```
Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that:
- p[0] = start
- p[i] and p[i+1] differ by only one bit in their binary representation.
- p[0] and p[2^n -1] must also differ by only one bit in their binary representation.

Example 1:
Input: n = 2, start = 3
Output: [3,2,0,1]
Explanation: The binary representation of the permutation is (11,10,00,01). 
All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]

Example 2:
Input: n = 3, start = 2
Output: [2,6,7,5,4,0,1,3]
Explanation: The binary representation of the permutation is (010,110,111,101,100,000,001,011).

Constraints:
- 1 <= n <= 16
- 0 <= start < 2^n
```

## Observations

1. **This is a Gray Code problem**: The sequence where consecutive values differ by only one bit is called Gray Code. The circular property (first and last differ by one bit) is a natural property of Gray Code.

2. **Standard Gray Code formula**: For any number `i`, its Gray Code representation is `i ^ (i >> 1)`. This generates the standard Gray Code sequence starting from 0.

3. **Starting from a different value**: Since we need to start from `start` instead of 0, we first generate the complete Gray Code sequence, find where `start` appears, then rotate the sequence to begin from that position.

4. **Circular property is maintained**: Because Gray Code is inherently circular (the last element differs from the first by one bit), rotating the sequence preserves all required properties.

5. **Size of sequence**: For `n` bits, we need exactly `2^n` values (represented as `1 << n`).

## Solution

**Algorithm:**

1. **Generate Standard Gray Code Sequence:**
   - Iterate through all values from 0 to `2^n - 1`
   - Apply the Gray Code formula: `i ^ (i >> 1)`
   - Store these values in an array

2. **Find Start Position:**
   - Find the index where `start` appears in the Gray Code array

3. **Rotate the Sequence:**
   - Starting from the index of `start`, iterate `2^n` times
   - Use modulo arithmetic to wrap around: `arr[i % (1 << n)]`
   - This creates a circular permutation starting from `start`

**Why Gray Code Formula Works:**
- Gray Code is constructed so that consecutive numbers differ by exactly one bit
- The formula `i ^ (i >> 1)` generates this sequence:
  - For i=0: 0 ^ 0 = 0 (binary: 000)
  - For i=1: 1 ^ 0 = 1 (binary: 001)
  - For i=2: 2 ^ 1 = 3 (binary: 011)
  - For i=3: 3 ^ 1 = 2 (binary: 010)
  - For i=4: 4 ^ 2 = 6 (binary: 110)
  - etc.

**Complexity:**
- Time: O(2^n) - we generate and iterate through the complete sequence
- Space: O(2^n) - storing the Gray Code array

**Code:**
```python
class Solution:
    def circularPermutation(self, n: int, start: int) -> List[int]:
        # Generate standard Gray Code sequence
        arr = []
        for i in range(1 << n):  # 2^n iterations
            arr.append(i ^ (i >> 1))  # Gray Code formula
        
        # Find where 'start' appears in Gray Code
        idx = arr.index(start)
        
        # Rotate sequence to start from 'start'
        res = []
        for i in range(idx, idx + (1 << n)):
            res.append(arr[i % (1 << n)])  # Circular access
        
        return res
```

# Tags

array, bit manipulation
## Problem

https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/description/

```
Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.

Return the decimal value of the number in the linked list.

The most significant bit is at the head of the linked list.

Example 1:

Input: head = [1,0,1]
Output: 5
Explanation: (101) in base 2 = (5) in base 10

Example 2:

Input: head = [0]
Output: 0

Constraints:

The Linked List is not empty.
Number of nodes will not exceed 30.
Each node's value is either 0 or 1.
```

## Observations

1. **Problem Understanding**: We need to convert a binary number represented as a linked list to its decimal equivalent.

2. **Key Insights**:
   - The most significant bit (MSB) is at the head of the linked list
   - Each node contains either 0 or 1
   - We need to process nodes from left to right (MSB to LSB)
   - This is essentially base-2 to base-10 conversion

3. **Approach Options**:
   - **Option 1**: Traverse twice - first to count nodes, then calculate decimal
   - **Option 2**: Use bit manipulation to build result incrementally (more efficient)

4. **Constraints Analysis**:
   - Maximum 30 nodes means result fits comfortably in a 32-bit integer
   - No empty list concerns (constraint guarantees non-empty)

## Solution

1. **Initialize**: `res = 0` to store our decimal result

2. **For each node**:
   - `res <<= 1`: Left shift result by 1 position (equivalent to `res = res * 2`)
   - `res |= head.val`: OR the current bit with result (adds current bit to LSB position)
   - Move to next node

3. **Example walkthrough** with `[1,0,1]`:
   ```
   Initial: res = 0
   
   Node 1 (val=1):
   res <<= 1  → res = 0 << 1 = 0
   res |= 1   → res = 0 | 1 = 1
   
   Node 2 (val=0):
   res <<= 1  → res = 1 << 1 = 2 (binary: 10)
   res |= 0   → res = 2 | 0 = 2
   
   Node 3 (val=1):
   res <<= 1  → res = 2 << 1 = 4 (binary: 100)
   res |= 1   → res = 4 | 1 = 5 (binary: 101)
   
   Result: 5
   ```

**Time Complexity**: O(n) - visit each node once
**Space Complexity**: O(1) - only using constant extra space

**Why this approach is elegant**:
- No need to count nodes first
- Processes bits in natural order (MSB to LSB)
- Uses efficient bit operations
- Single pass through the linked list

# Tags

`Linked List` `Bit Manipulation` `Math` `Easy`


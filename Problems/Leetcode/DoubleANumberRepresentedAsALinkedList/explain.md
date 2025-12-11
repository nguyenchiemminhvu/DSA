## Problem

https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/description/

```
You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.

Return the head of the linked list after doubling it.

Example 1:
Input: head = [1,8,9]
Output: [3,7,8]
Explanation: The figure above corresponds to the given linked list which represents the number 189. 
Hence, the returned linked list represents the number 189 * 2 = 378.

Example 2:
Input: head = [9,9,9]
Output: [1,9,9,8]
Explanation: The figure above corresponds to the given linked list which represents the number 999. 
Hence, the returned linked list represents the number 999 * 2 = 1998.

Constraints:
- The number of nodes in the list is in the range [1, 10^4]
- 0 <= Node.val <= 9
- The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
```

## Observations

1. **Number Representation**: The linked list represents a number where each node contains a single digit, and the list is ordered from most significant digit to least significant digit (left to right).

2. **Simple Approach**: Convert the linked list to an integer, double it, then convert back to a linked list. This works for smaller numbers but has limitations:
   - Maximum integer size constraints (though Python handles big integers well)
   - Not space-efficient for very large numbers

3. **Constraints Analysis**:
   - Maximum 10^4 nodes means up to 10,000 digits
   - Python can handle arbitrarily large integers, so the simple approach works
   - For languages with fixed integer sizes, would need digit-by-digit multiplication with carry

4. **Alternative Approaches**:
   - Could reverse the list, multiply digit-by-digit with carry, then reverse back
   - Could use recursion to handle carry from right to left
   - Could use two-pass approach: detect if we need a new head node, then multiply with carry

## Solution

### Approach: Convert to Integer and Back

**Algorithm:**

1. **Extract the number**: Traverse the linked list and build the integer value
   - Start with `val = 0`
   - For each node: `val = val * 10 + node.val`
   - This builds the number digit by digit (e.g., [1,8,9] → 1 → 18 → 189)

2. **Handle edge case**: If the number is 0, return a single node with value 0

3. **Double the value**: Multiply the integer by 2

4. **Convert back to linked list**:
   - Extract digits in reverse order by repeatedly taking `val % 10` and dividing by 10
   - Store digits in an array and reverse it to get proper order
   - Build a new linked list from the digit array

**Time Complexity**: O(n) where n is the number of nodes
- O(n) to extract the number
- O(d) to extract digits where d is the number of digits in the result
- O(d) to build the linked list
- Overall: O(n)

**Space Complexity**: O(d) where d is the number of digits in the doubled number
- Array to store digits
- New linked list nodes

**Code Walkthrough** (Example: [1,8,9] → 189 → 378 → [3,7,8]):

```python
# Step 1: Extract number
head = [1,8,9]
val = 0
val = 0 * 10 + 1 = 1
val = 1 * 10 + 8 = 18
val = 18 * 10 + 9 = 189

# Step 2: Double it
val = 189 * 2 = 378

# Step 3: Extract digits (reverse order)
arr = []
378 % 10 = 8, arr = [8], val = 37
37 % 10 = 7, arr = [8,7], val = 3
3 % 10 = 3, arr = [8,7,3], val = 0
arr.reverse() → [3,7,8]

# Step 4: Build linked list
[3] → [7] → [8]
```

**Python Implementation:**
```python
class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # Step 1: Extract the number from linked list
        val = 0
        while head:
            val = val * 10 + head.val
            head = head.next
        
        # Step 2: Handle edge case
        if val == 0:
            return ListNode(0)
        
        # Step 3: Double the value
        val *= 2

        # Step 4: Extract digits in reverse order
        arr = []
        while val:
            arr.append(val % 10)
            val //= 10
        arr.reverse()

        # Step 5: Build new linked list
        dummy = ListNode(0)
        p = dummy
        for digit in arr:
            p.next = ListNode(digit)
            p = p.next
        return dummy.next
```

### Alternative: Digit-by-Digit Multiplication (More Optimal for Very Large Numbers)

For a more space-efficient solution without converting to integer:
1. Reverse the linked list
2. Traverse and multiply each digit by 2, handling carry
3. Reverse the list back

This approach uses O(1) extra space (excluding the output) and avoids potential integer overflow in languages with fixed-size integers.

# Tags

`Linked List` `Math` `Two Pointers` `Simulation`


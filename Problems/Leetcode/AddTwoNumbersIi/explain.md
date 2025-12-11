## Problem

https://leetcode.com/problems/add-two-numbers-ii/

You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example 1:**
```
Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
Explanation: 7243 + 564 = 7807
```

**Example 2:**
```
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]
Explanation: 243 + 564 = 807
```

**Example 3:**
```
Input: l1 = [0], l2 = [0]
Output: [0]
```

**Constraints:**
- The number of nodes in each linked list is in the range [1, 100]
- 0 <= Node.val <= 9
- It is guaranteed that the list represents a number that does not have leading zeros

**Follow up:** Could you solve it without reversing the input lists?

## Observations

1. **Digit Order**: Unlike the classic "Add Two Numbers" problem, the digits are stored in **most significant digit first** order (e.g., [7,2,4,3] represents 7243, not 3427).

2. **Addition Direction**: Addition must be performed from **right to left** (least significant to most significant digit), but the lists are structured from left to right.

3. **Carry Handling**: When adding digits, we need to track the carry and propagate it to more significant digits.

4. **Different Lengths**: The two linked lists may have different lengths, requiring careful handling of the shorter list.

5. **Result Construction**: Since we process digits from right to left but need to build the result list, we need a strategy to construct the output list correctly.

## Solution

### Approach: Stack-Based Addition

The key insight is to use **stacks** to reverse the order of processing without actually modifying the input lists.

**Algorithm:**

1. **Push digits onto stacks**: Traverse both linked lists and push all digits onto separate stacks. This allows us to access digits from least significant to most significant.

2. **Process from right to left**: Pop from both stacks simultaneously, adding digits along with any carry from the previous addition.

3. **Build result list in reverse**: Since we're processing from right to left but building the result from left to right, we prepend each new digit to the front of the result list.

4. **Handle different lengths**: Use 0 for missing digits when one stack is empty.

5. **Handle final carry**: After processing all digits, if there's still a carry, it becomes the most significant digit.

**Implementation:**

```python
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        stack1 = []
        stack2 = []
        
        # Push all digits of l1 onto stack1
        while l1:
            stack1.append(l1.val)
            l1 = l1.next
        
        # Push all digits of l2 onto stack2
        while l2:
            stack2.append(l2.val)
            l2 = l2.next
        
        carry = 0
        head = None  # Result list built in reverse
        
        # Add digits while stacks have elements or carry exists
        while stack1 or stack2 or carry:
            # Get digit from stack1 (or 0 if empty)
            x = stack1.pop() if stack1 else 0
            # Get digit from stack2 (or 0 if empty)
            y = stack2.pop() if stack2 else 0
            
            # Calculate sum and new carry
            total = x + y + carry
            carry = total // 10
            
            # Create new node with digit (total % 10)
            # Prepend to result list
            new_node = ListNode(total % 10)
            new_node.next = head
            head = new_node
        
        return head
```

**Complexity Analysis:**

- **Time Complexity**: O(max(m, n)) where m and n are the lengths of the two lists
  - O(m) to push l1 onto stack1
  - O(n) to push l2 onto stack2
  - O(max(m, n)) to process and add digits
  
- **Space Complexity**: O(m + n)
  - O(m) for stack1
  - O(n) for stack2
  - O(max(m, n)) for the result list

**Why This Works:**

1. Stacks naturally reverse the order of elements (LIFO - Last In First Out)
2. By pushing digits in order and popping them, we process from least to most significant
3. Prepending nodes (`new_node.next = head; head = new_node`) builds the list in correct order
4. The carry is properly propagated through each addition step

**Example Walkthrough:**

For l1 = [7,2,4,3] and l2 = [5,6,4]:

```
stack1: [7, 2, 4, 3]
stack2: [5, 6, 4]

Step 1: 3 + 4 + 0 = 7, carry = 0 → [7]
Step 2: 4 + 6 + 0 = 10, carry = 1 → [0,7]
Step 3: 2 + 5 + 1 = 8, carry = 0 → [8,0,7]
Step 4: 7 + 0 + 0 = 7, carry = 0 → [7,8,0,7]

Result: [7,8,0,7]
```

# Tags

`Linked List` `Stack` `Math` `Two Pointers`


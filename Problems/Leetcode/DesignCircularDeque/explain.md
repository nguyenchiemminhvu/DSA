## Problem

https://leetcode.com/problems/design-circular-deque/description/

```
Design your implementation of the circular double-ended queue (deque).

Implement the MyCircularDeque class:

- MyCircularDeque(int k) Initializes the deque with a maximum size of k.
- boolean insertFront() Adds an item at the front of Deque. Returns true if the operation is successful, or false otherwise.
- boolean insertLast() Adds an item at the rear of Deque. Returns true if the operation is successful, or false otherwise.
- boolean deleteFront() Deletes an item from the front of Deque. Returns true if the operation is successful, or false otherwise.
- boolean deleteLast() Deletes an item from the rear of Deque. Returns true if the operation is successful, or false otherwise.
- int getFront() Returns the front item from the Deque. Returns -1 if the deque is empty.
- int getRear() Returns the last item from Deque. Returns -1 if the deque is empty.
- boolean isEmpty() Returns true if the deque is empty, or false otherwise.
- boolean isFull() Returns true if the deque is full, or false otherwise.

Example 1:
Input: ["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront", "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
       [[3], [1], [2], [3], [4], [], [], [], [4], []]
Output: [null, true, true, true, false, 2, true, true, true, 4]

Constraints:
- 1 <= k <= 1000
- 0 <= value <= 1000
- At most 2000 calls will be made to insertFront, insertLast, deleteFront, deleteLast, getFront, getRear, isEmpty, isFull.
```

## Observations

1. **Circular Deque Requirements**: Need to support insertion/deletion from both ends with a fixed capacity
2. **Data Structure Choice**: Using a singly-linked list with head and tail pointers
3. **Capacity Tracking**: Must track current size to enforce the maximum capacity constraint
4. **Edge Cases to Handle**:
   - Empty deque (size == 0)
   - Full deque (size == cap)
   - Single element deque (head == tail)
   - Deleting the last element requires traversing to find the new tail

## Solution

**Approach**: Singly-Linked List Implementation

The solution uses a singly-linked list with head and tail pointers to implement the circular deque:

**Data Structure**:
- `ListNode`: Simple node with value and next pointer
- `head`: Points to the front of the deque
- `tail`: Points to the rear of the deque
- `cap`: Maximum capacity
- `size`: Current number of elements

**Key Operations**:

1. **insertFront(value)**: O(1)
   - Check if full (size == cap)
   - Create new node and insert at head
   - Update tail if deque was empty

2. **insertLast(value)**: O(1)
   - Check if full (size == cap)
   - Create new node and append at tail
   - Update both head and tail if deque was empty

3. **deleteFront()**: O(1)
   - Check if empty (size == 0)
   - Move head to next node
   - Clear tail if deque becomes empty

4. **deleteLast()**: O(n)
   - Check if empty (size == 0)
   - Handle single element case (head == tail)
   - Otherwise, traverse to find node before tail
   - Update tail pointer

5. **getFront()**: O(1) - Return head value or -1
6. **getRear()**: O(1) - Return tail value or -1
7. **isEmpty()**: O(1) - Check if size == 0
8. **isFull()**: O(1) - Check if size == cap

**Time Complexity**:
- Most operations: O(1)
- deleteLast(): O(n) due to singly-linked list requiring traversal to find previous node

**Space Complexity**: O(k) where k is the maximum capacity

**Trade-offs**:
- Singly-linked list makes deleteLast() O(n)
- Could use doubly-linked list for O(1) deleteLast() at cost of extra pointer per node
- Could use circular array for O(1) all operations but with fixed memory allocation

# Tags
#design #linked-list #deque #data-structure #queue


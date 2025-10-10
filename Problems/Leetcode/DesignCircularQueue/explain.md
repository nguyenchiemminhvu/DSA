## Problem

https://leetcode.com/problems/design-circular-queue/

```
Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle, and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a normal queue, once the queue becomes full, we cannot insert the next element even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.

Implement the MyCircularQueue class:

MyCircularQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return -1.
int Rear() Gets the last item from the queue. If the queue is empty, return -1.
boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
boolean isEmpty() Checks whether the circular queue is empty or not.
boolean isFull() Checks whether the circular queue is full or not.
You must solve the problem without using the built-in queue data structure in your programming language. 

Example 1:

Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]

Explanation
MyCircularQueue myCircularQueue = new MyCircularQueue(3);
myCircularQueue.enQueue(1); // return True
myCircularQueue.enQueue(2); // return True
myCircularQueue.enQueue(3); // return True
myCircularQueue.enQueue(4); // return False
myCircularQueue.Rear();     // return 3
myCircularQueue.isFull();   // return True
myCircularQueue.deQueue();  // return True
myCircularQueue.enQueue(4); // return True
myCircularQueue.Rear();     // return 4

Constraints:

1 <= k <= 1000
0 <= value <= 1000
At most 3000 calls will be made to enQueue, deQueue, Front, Rear, isEmpty, and isFull.
```

## Observations

1. **Circular Nature**: The key insight is that when we reach the end of the array, we need to wrap around to the beginning. This is achieved using modulo arithmetic `(index + 1) % capacity`.

2. **Two Pointer Approach**: We need to maintain both `head` (front) and `tail` (rear) pointers to efficiently access both ends of the queue.

3. **Size Tracking**: While we could determine if the queue is full/empty by comparing head and tail positions, maintaining a separate `size` counter makes the logic clearer and handles edge cases better.

4. **Edge Cases to Handle**:
   - Empty queue: When `size == 0`, both `head` and `tail` should be `-1`
   - Single element: When `size == 1`, both `head` and `tail` point to the same element
   - Full queue: When `size == capacity`
   - Wraparound: When adding/removing elements at array boundaries

5. **State Management**: 
   - Initialize with `head = tail = -1` for empty state
   - When adding first element, set `head = 0`
   - When removing last element, reset `head = tail = -1`

## Solution

The solution uses an array-based implementation with the following key components:

### Data Structure Design
```python
- arr: Fixed-size array to store queue elements
- cap: Maximum capacity of the queue
- size: Current number of elements
- head: Index of the front element
- tail: Index of the rear element
- INF: Sentinel value (-1) for empty slots
```

### Algorithm Analysis

**1. Initialization - O(k) time, O(k) space**
- Create array of size k filled with sentinel values
- Initialize pointers to -1 (empty state)

**2. enQueue - O(1) time**
- Check if queue is full
- Handle first insertion (set head = 0)
- Update tail using circular arithmetic: `(tail + 1) % cap`
- Insert value and increment size

**3. deQueue - O(1) time**
- Check if queue is empty
- Clear current head position
- Handle last element removal (reset pointers to -1)
- Update head using circular arithmetic: `(head + 1) % cap`
- Decrement size

**4. Front/Rear - O(1) time**
- Direct array access using head/tail indices
- Returns -1 for empty queue (handled by INF values)

**5. isEmpty/isFull - O(1) time**
- Simple size comparisons

### Key Implementation Details

1. **Circular Indexing**: Uses `% cap` to wrap around array boundaries
2. **State Consistency**: Maintains clear separation between empty (`head = tail = -1`) and occupied states
3. **Boundary Handling**: Special logic for first insertion and last deletion
4. **Memory Management**: Clears deleted elements with sentinel values (optional but good practice)

### Time Complexity
- All operations: O(1)

### Space Complexity
- O(k) where k is the capacity of the queue

## Tags

array
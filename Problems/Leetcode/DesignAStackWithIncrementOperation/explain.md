## Problem

https://leetcode.com/problems/design-a-stack-with-increment-operation/description/

Design a stack that supports increment operations on its elements.

Implement the `CustomStack` class:

- **`CustomStack(int maxSize)`** - Initializes the object with `maxSize` which is the maximum number of elements in the stack.
- **`void push(int x)`** - Adds `x` to the top of the stack if the stack has not reached the `maxSize`.
- **`int pop()`** - Pops and returns the top of the stack or `-1` if the stack is empty.
- **`void inc(int k, int val)`** - Increments the bottom `k` elements of the stack by `val`. If there are less than `k` elements in the stack, increment all the elements in the stack.

### Example 1:

```
Input
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]

Output
[null,null,null,2,null,null,null,null,null,103,202,201,-1]

Explanation
CustomStack stk = new CustomStack(3); // Stack is Empty []
stk.push(1);                          // stack becomes [1]
stk.push(2);                          // stack becomes [1, 2]
stk.pop();                            // return 2 --> Return top of the stack 2, stack becomes [1]
stk.push(2);                          // stack becomes [1, 2]
stk.push(3);                          // stack becomes [1, 2, 3]
stk.push(4);                          // stack still [1, 2, 3], Do not add another elements as size is 4
stk.increment(5, 100);                // stack becomes [101, 102, 103]
stk.increment(2, 100);                // stack becomes [201, 202, 103]
stk.pop();                            // return 103 --> Return top of the stack 103, stack becomes [201, 202]
stk.pop();                            // return 202 --> Return top of the stack 202, stack becomes [201]
stk.pop();                            // return 201 --> Return top of the stack 201, stack becomes []
stk.pop();                            // return -1 --> Stack is empty return -1.
```

### Constraints:

- `1 <= maxSize, x, k <= 1000`
- `0 <= val <= 100`
- At most `1000` calls will be made to each method of `increment`, `push` and `pop` each separately.

## Observations

1. **Stack with Capacity Limit**: Unlike a standard stack, this custom stack has a maximum capacity (`maxSize`). We need to check capacity before pushing new elements.

2. **Increment from Bottom**: The `increment` operation affects the **bottom** `k` elements, not the top. This is unusual for a stack but can be efficiently handled with array indexing.

3. **Edge Cases**:
   - Pushing when stack is full → Do nothing
   - Popping from empty stack → Return `-1`
   - Incrementing when `k > stack size` → Increment all elements
   - Incrementing when stack is empty → Do nothing

4. **Performance Considerations**:
   - **Simple Approach (Current)**: Using a list and iterating through the first `k` elements for increment operation. This is O(k) time complexity for increment.
   - **Optimized Approach**: Using lazy propagation with an auxiliary array to make increment O(1). However, for the given constraints (maxSize ≤ 1000), the simple approach is sufficient.

5. **Data Structure Choice**: A Python list works well here because:
   - It supports efficient append/pop operations at the end (O(1))
   - It allows indexing for the increment operation
   - It has dynamic sizing but we control capacity manually

## Solution

### Approach: Simple Array-Based Stack

The solution uses a straightforward implementation with a list (array) to store stack elements.

#### Key Components:

1. **Storage (`self.st`)**: A list that holds the stack elements
2. **Capacity (`self.cap`)**: Maximum number of elements allowed

#### Implementation Details:

```python
class CustomStack:

    def __init__(self, maxSize: int):
        self.st = []           # Initialize empty stack
        self.cap = maxSize     # Store maximum capacity

    def push(self, x: int) -> None:
        if len(self.st) < self.cap:  # Check if space available
            self.st.append(x)         # Add to top of stack

    def pop(self) -> int:
        if self.st:                   # Check if stack is not empty
            return self.st.pop()      # Remove and return top element
        return -1                     # Return -1 for empty stack

    def increment(self, k: int, val: int) -> None:
        # Increment bottom min(k, stack_size) elements
        for i in range(min(len(self.st), k)):
            self.st[i] += val
```

#### Time & Space Complexity:

- **`__init__(maxSize)`**: O(1) time, O(1) space
- **`push(x)`**: O(1) time
- **`pop()`**: O(1) time
- **`increment(k, val)`**: O(min(k, n)) time where n is the current stack size
- **Space Complexity**: O(maxSize) for storing the stack elements

#### How It Works:

1. **Push Operation**:
   - Check if current size is less than capacity
   - If yes, append element to the end of the list (top of stack)
   - If no, do nothing (stack is full)

2. **Pop Operation**:
   - Check if stack has elements
   - If yes, remove and return the last element (top of stack)
   - If no, return -1

3. **Increment Operation**:
   - Determine how many elements to increment: `min(k, current_size)`
   - Iterate from index 0 to that count
   - Add `val` to each element in this range
   - Note: Index 0 is the bottom of the stack, which is what we want

#### Example Walkthrough:

```python
stk = CustomStack(3)           # st = [], cap = 3
stk.push(1)                    # st = [1]
stk.push(2)                    # st = [1, 2]
stk.pop()                      # st = [1], returns 2
stk.push(2)                    # st = [1, 2]
stk.push(3)                    # st = [1, 2, 3]
stk.push(4)                    # st = [1, 2, 3] (full, no change)
stk.increment(5, 100)          # st = [101, 102, 103] (increment all 3)
stk.increment(2, 100)          # st = [201, 202, 103] (increment bottom 2)
stk.pop()                      # st = [201, 202], returns 103
stk.pop()                      # st = [201], returns 202
stk.pop()                      # st = [], returns 201
stk.pop()                      # st = [], returns -1
```

### Alternative Optimization (Lazy Propagation):

For scenarios with frequent increment operations, we can optimize to O(1) increment:

```python
class CustomStack:
    def __init__(self, maxSize: int):
        self.st = []
        self.inc_arr = []  # Lazy propagation array
        self.cap = maxSize

    def push(self, x: int) -> None:
        if len(self.st) < self.cap:
            self.st.append(x)
            self.inc_arr.append(0)

    def pop(self) -> int:
        if not self.st:
            return -1
        
        if len(self.inc_arr) > 1:
            # Propagate increment to element below
            self.inc_arr[-2] += self.inc_arr[-1]
        
        inc_val = self.inc_arr.pop()
        return self.st.pop() + inc_val

    def increment(self, k: int, val: int) -> None:
        if self.st:
            idx = min(k, len(self.st)) - 1
            self.inc_arr[idx] += val
```

**How Lazy Propagation Works**:
- Instead of updating elements immediately, store increment values in `inc_arr`
- When popping, apply the accumulated increment and propagate it down
- This makes increment O(1) but keeps pop O(1) as well
- Trade-off: Slightly more complex implementation

### Conclusion:

The simple array-based approach is clean, easy to understand, and performs well within the given constraints. The lazy propagation optimization is worth considering for more demanding scenarios with frequent increments on larger stacks.

# Tags

`Stack`, `Array`, `Design`, `Lazy Propagation`


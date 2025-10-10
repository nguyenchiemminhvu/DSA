## Problem

https://leetcode.com/problems/min-stack/description/

```
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

Constraints:

-231 <= val <= 231 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 104 calls will be made to push, pop, top, and getMin.
```

## Observations

1. **Key Challenge**: We need to maintain the minimum element at any point in time while supporting standard stack operations, all in O(1) time complexity.

2. **Standard Stack Limitation**: A regular stack can't efficiently track the minimum element because when we pop the current minimum, we need to know what the previous minimum was.

3. **Space-Time Tradeoff**: To achieve O(1) time complexity for all operations, we need to use additional space to store minimum information.

4. **Minimum Tracking Strategy**: We need to store the minimum value at each level of the stack so that when elements are popped, we still know what the minimum was before that element was pushed.

5. **Tuple Approach**: By storing pairs (value, min_at_this_point), we can maintain both the actual stack values and the minimum tracking information together.

## Solution

**Approach: Stack with Min Tracking**

The solution uses a clever approach where each element in the stack is stored as a tuple `(value, minimum_so_far)`:

1. **Initialization**: Create an empty array to store tuples.

2. **Push Operation**: 
   - For the first element: store `(val, val)` since it's both the value and minimum
   - For subsequent elements: compare the new value with the current minimum and store `(val, min(current_min, val))`

3. **Pop Operation**: Simply remove the top tuple, which automatically removes both the value and its associated minimum information.

4. **Top Operation**: Return the first element of the top tuple (the actual value).

5. **GetMin Operation**: Return the second element of the top tuple (the minimum at this stack level).

**Time Complexity**: O(1) for all operations
**Space Complexity**: O(n) where n is the number of elements (we store twice the information but it's still linear)

**Example Walkthrough:**
```
push(-2): arr = [(-2, -2)]           # min so far: -2
push(0):  arr = [(-2, -2), (0, -2)] # min so far: -2
push(-3): arr = [(-2, -2), (0, -2), (-3, -3)] # min so far: -3
getMin(): return -3
pop():    arr = [(-2, -2), (0, -2)] # min is now -2
top():    return 0
getMin(): return -2
```

This solution elegantly maintains the minimum element history without requiring additional data structures or complex logic.

## Tags

stack
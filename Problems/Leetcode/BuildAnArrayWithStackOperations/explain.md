## Problem

https://leetcode.com/problems/build-an-array-with-stack-operations/description/

```
You are given an integer array target and an integer n.

You have an empty stack with the two following operations:
- "Push": pushes an integer to the top of the stack.
- "Pop": removes the integer on the top of the stack.

You also have a stream of the integers in the range [1, n].

Use the two stack operations to make the numbers in the stack (from the bottom to the top) equal to target. 
You should follow the following rules:
- If the stream of the integers is not empty, pick the next integer from the stream and push it to the top of the stack.
- If the stack is not empty, pop the integer at the top of the stack.
- If, at any moment, the elements in the stack (from the bottom to the top) are equal to target, do not read new 
  integers from the stream and do not do more operations on the stack.

Return the stack operations needed to build target following the mentioned rules.

Example 1:
Input: target = [1,3], n = 3
Output: ["Push","Push","Pop","Push"]
Explanation: 
- Read 1 from stream, push it. Stack = [1]
- Read 2 from stream, push it. Stack = [1,2]
- Pop. Stack = [1]
- Read 3 from stream, push it. Stack = [1,3]

Example 2:
Input: target = [1,2,3], n = 3
Output: ["Push","Push","Push"]

Example 3:
Input: target = [1,2], n = 4
Output: ["Push","Push"]

Constraints:
- 1 <= target.length <= 100
- 1 <= n <= 100
- 1 <= target[i] <= n
- target is strictly increasing
```

## Observations

1. **Stream is Sequential**: The stream provides integers in order from 1 to n. We must process them sequentially.

2. **Target is Sorted**: Since target is strictly increasing, we know exactly which numbers we want to keep.

3. **Skip Unwanted Numbers**: For any number in the stream that's NOT in target, we need to:
   - Push it (because we must take the next integer from stream)
   - Immediately Pop it (to remove it from stack)

4. **Keep Wanted Numbers**: For any number that IS in target, we simply Push it and move to the next target element.

5. **Early Termination**: Once we've built the complete target array, we stop processing the stream, even if there are more numbers available.

6. **Pattern Recognition**: 
   - If current stream number < target[i]: Push then Pop (skip)
   - If current stream number == target[i]: Push (keep)

## Solution

### Approach: Simulation with Gap Filling

The key insight is to simulate the stream processing while tracking which target element we're trying to build next.

**Algorithm**:
1. Start with `cur = 1` (first number in stream) and iterate through each value in `target`
2. For each `target[i]`:
   - While `cur < target[i]`: These are numbers we need to skip
     - Push `cur` (required by rules - must take from stream)
     - Pop immediately (we don't want this number)
     - Increment `cur`
   - When `cur == target[i]`: This is a number we want
     - Push `cur` (and keep it)
     - Increment `cur`
3. Record all operations and return the history

**Time Complexity**: O(max(target)) - We process numbers from 1 up to the largest value in target
**Space Complexity**: O(max(target)) - For storing the operation history

**Example Walkthrough** (target = [1,3], n = 3):
- cur=1, target[0]=1: Push(1) → stack=[1], cur=2
- cur=2, target[1]=3: Push(2),Pop() → stack=[1], cur=3
- cur=3, target[1]=3: Push(3) → stack=[1,3], cur=4
- Result: ["Push","Push","Pop","Push"]

**Code**:
```python
class Stack:
    def __init__(self):
        self.st = []
        self.history = []
    
    def push(self, val: int) -> None:
        self.st.append(val)
        self.history.append("Push")
    
    def pop(self) -> None:
        self.st.pop()
        self.history.append("Pop")
    
    def get_history(self) -> List[str]:
        return self.history

class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        st = Stack()
        cur = 1  # Current number from stream [1, n]
        
        for val in target:
            # Skip numbers between cur and val
            while cur < val:
                st.push(cur)  # Must take from stream
                st.pop()      # But don't want it
                cur += 1
            
            # Found the target value
            st.push(cur)
            cur += 1
        
        return st.get_history()
```

**Alternative Simpler Approach** (without custom Stack class):
```python
class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        result = []
        cur = 1
        
        for val in target:
            # For each number we skip, push and pop
            while cur < val:
                result.append("Push")
                result.append("Pop")
                cur += 1
            
            # For the target number, just push
            result.append("Push")
            cur += 1
        
        return result
```

# Tags
#stack #simulation #array #greedy


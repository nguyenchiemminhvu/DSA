## Problem

https://leetcode.com/problems/flatten-nested-list-iterator/description/

```
You are given a nested list of integers nestedList. Each element is either an integer or a list whose 
elements may also be integers or other lists. Implement an iterator to flatten it.

Implement the NestedIterator class:
- NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list nestedList.
- int next() Returns the next integer in the nested list.
- boolean hasNext() Returns true if there are still some integers in the nested list and false otherwise.

Example 1:
Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by 
next should be: [1,1,2,1,1].

Example 2:
Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by 
next should be: [1,4,6].

Constraints:
- 1 <= nestedList.length <= 500
- The values of the integers in the nested list is in the range [-10^6, 10^6].
```

## Observations

1. **Problem Type**: This is an iterator design problem that requires flattening a nested structure.

2. **Key Challenges**:
   - Nested lists can have arbitrary depth (lists within lists within lists...)
   - Need to handle both integers and nested lists at any level
   - Must maintain iterator semantics (hasNext() and next() operations)

3. **Two Main Approaches**:
   - **Eager Evaluation**: Flatten the entire structure during initialization
   - **Lazy Evaluation**: Flatten on-demand during iteration (more memory efficient)

4. **Data Structure Considerations**:
   - The provided solution uses eager evaluation with a helper array
   - Could also use a stack-based approach for lazy evaluation
   - Recursion naturally handles the nested structure

## Solution

### Approach: Eager Evaluation with Recursive Flattening

**Strategy**:
1. During initialization, recursively traverse the entire nested list structure
2. Extract all integers into a flat array
3. Use an index pointer to track the current position for iteration

**Implementation Details**:

```python
class NestedIterator:
    def __init__(self, nestedList: [NestedInteger]):
        # Helper function to recursively extract integers
        def extracting(n: NestedInteger) -> List[int]:
            if n.isInteger():
                return [n.getInteger()]
            
            # If it's a list, recursively flatten each element
            tmp = []
            for inner in n.getList():
                tmp += extracting(inner)
            return tmp
        
        # Flatten the entire structure into a simple array
        self.arr = []
        for n in nestedList:
            self.arr += extracting(n)
        
        # Initialize index pointer
        self.idx = 0
    
    def next(self) -> int:
        val = self.arr[self.idx]
        self.idx += 1
        return val
    
    def hasNext(self) -> bool:
        return self.idx < len(self.arr)
```

**Time Complexity**:
- Initialization: O(N) where N is the total number of integers in the nested list (must visit every element)
- next(): O(1) - simple array access
- hasNext(): O(1) - simple comparison

**Space Complexity**:
- O(N) to store the flattened array

**Pros**:
- Simple and clean implementation
- Fast iteration operations (O(1))
- Easy to understand and debug

**Cons**:
- Uses O(N) space upfront even if not all elements are accessed
- All flattening work happens during initialization

### Alternative: Stack-Based Lazy Evaluation

For a more memory-efficient approach when dealing with very large lists where not all elements may be accessed:

```python
class NestedIterator:
    def __init__(self, nestedList: [NestedInteger]):
        # Store elements in reverse order for stack processing
        self.stack = list(reversed(nestedList))
    
    def next(self) -> int:
        # hasNext ensures the top is an integer
        return self.stack.pop().getInteger()
    
    def hasNext(self) -> bool:
        # Ensure top of stack is an integer
        while self.stack:
            top = self.stack[-1]
            if top.isInteger():
                return True
            # If it's a list, flatten one level
            self.stack.pop()
            self.stack.extend(reversed(top.getList()))
        return False
```

This approach processes elements only as needed, which can be more efficient if the iterator doesn't consume all elements.

# Tags
#iterator #design #recursion #stack #nested-structure #depth-first-search


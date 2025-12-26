# Validate Stack Sequences

## Problem

https://leetcode.com/problems/validate-stack-sequences/description/

Given two integer arrays `pushed` and `popped` each with distinct values, return `true` if this could have been the result of a sequence of push and pop operations on an initially empty stack, or `false` otherwise.

### Examples

**Example 1:**
```
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4),
pop() -> 4,
push(5),
pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
```

**Example 2:**
```
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.
```

### Constraints

- `1 <= pushed.length <= 1000`
- `0 <= pushed[i] <= 1000`
- All the elements of `pushed` are unique
- `popped.length == pushed.length`
- `popped` is a permutation of `pushed`

---

## Observations

1. **Stack Behavior**: A stack follows LIFO (Last In, First Out) principle. The last element pushed must be the first one that can be popped.

2. **Simulation Approach**: We can simulate the stack operations by actually using a stack and following the push sequence while trying to match the pop sequence.

3. **Greedy Matching**: Whenever the top of our simulation stack matches the next expected element in `popped`, we should pop it immediately. This is optimal because if we can pop it now, we must pop it now (we can't skip and come back to it later).

4. **Two Pointers**: We need to track:
   - Our position in the `pushed` array (implicitly through iteration)
   - Our position in the `popped` array (using `ip` index pointer)

5. **Validation**: If at the end our simulation stack is empty, it means all elements were successfully popped in the correct order, validating the sequence.

6. **Invalid Cases**: If we finish pushing all elements but still have elements in the stack that don't match the remaining `popped` sequence, then the sequences are invalid.

---

## Solution

### Algorithm

The solution uses a **stack simulation** approach:

1. **Initialize**: 
   - Create an empty stack `st`
   - Create a pointer `ip = 0` to track our position in the `popped` array

2. **Push Phase**:
   - Iterate through each value in the `pushed` array
   - Push the current value onto the stack
   - After each push, check if we can perform any pops:
     - While the stack is not empty AND the top element matches `popped[ip]`:
       - Pop from the stack
       - Increment `ip` to move to the next expected pop value

3. **Final Validation**:
   - After processing all pushes, check if there are remaining elements in the stack
   - Try to pop remaining elements and verify they match the remaining `popped` sequence
   - If any mismatch occurs, return `false`
   - If all elements are successfully matched, return `true`

### Why This Works

- **Greedy Property**: If the top of the stack matches the next expected popped value, we must pop it immediately. Delaying the pop would mean pushing more elements on top, which would need to be popped first (LIFO), making it impossible to reach this element again.

- **Completeness**: By following the exact push order and greedily popping whenever possible, we simulate the actual stack behavior accurately.

### Code Implementation

```python
class Solution:
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        st = []           # Simulation stack
        ip = 0            # Pointer for popped array
        
        # Process all push operations
        for val in pushed:
            st.append(val)  # Push current value
            
            # Greedily pop while we can match the popped sequence
            while st and st[-1] == popped[ip]:
                st.pop()
                ip += 1
        
        # Validate remaining elements in stack
        while st:
            val = st.pop()
            if val != popped[ip]:
                return False
            ip += 1
        
        return True
```

### Dry Run Example

**Input**: `pushed = [1,2,3,4,5]`, `popped = [4,5,3,2,1]`

| Step | Action | Stack State | ip | popped[ip] | Notes |
|------|--------|-------------|----|-----------|----|
| 1 | push(1) | [1] | 0 | 4 | Top ≠ 4, continue |
| 2 | push(2) | [1,2] | 0 | 4 | Top ≠ 4, continue |
| 3 | push(3) | [1,2,3] | 0 | 4 | Top ≠ 4, continue |
| 4 | push(4) | [1,2,3,4] | 0 | 4 | Top = 4, pop! |
| 5 | pop() | [1,2,3] | 1 | 5 | Top ≠ 5, continue |
| 6 | push(5) | [1,2,3,5] | 1 | 5 | Top = 5, pop! |
| 7 | pop() | [1,2,3] | 2 | 3 | Top = 3, pop! |
| 8 | pop() | [1,2] | 3 | 2 | Top = 2, pop! |
| 9 | pop() | [1] | 4 | 1 | Top = 1, pop! |
| 10 | pop() | [] | 5 | - | Stack empty, return true |

---

### Complexity Analysis

**Time Complexity: O(n)**
- We iterate through the `pushed` array once: O(n)
- Each element is pushed exactly once: O(n)
- Each element is popped at most once: O(n)
- Total: O(n + n) = O(n)

**Space Complexity: O(n)**
- In the worst case, we might push all elements onto the stack before any pops occur
- Example: `pushed = [1,2,3,4,5]`, `popped = [5,4,3,2,1]`
- Maximum stack size would be n elements

---

### Optimized Version

We can eliminate the second while loop by recognizing that if we've processed all pushes correctly, the stack should be empty:

```python
class Solution:
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        st = []
        ip = 0
        
        for val in pushed:
            st.append(val)
            while st and st[-1] == popped[ip]:
                st.pop()
                ip += 1
        
        return len(st) == 0  # Stack should be empty if valid
```

### Key Insights

1. **No Backtracking Needed**: The greedy approach is optimal - we never need to "undo" decisions
2. **One Pass**: We only need to go through each array once
3. **In-Place Simulation**: We could theoretically use the `pushed` array itself as a stack to achieve O(1) extra space, but it would modify the input

---

### Edge Cases

1. **Single Element**: `pushed = [1]`, `popped = [1]` → `true`
2. **Reverse Order**: `pushed = [1,2,3]`, `popped = [3,2,1]` → `true` (all push, then all pop)
3. **Same Order**: `pushed = [1,2,3]`, `popped = [1,2,3]` → `true` (push-pop-push-pop pattern)
4. **Invalid Interleaving**: `pushed = [1,2,3]`, `popped = [3,1,2]` → `false`
5. **All Push Then All Pop**: Maximum stack size scenario

# Tags

`Stack` `Array` `Simulation` `Two Pointers` `Greedy`


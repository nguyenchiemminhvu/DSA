## Problem

https://leetcode.com/problems/asteroid-collision/description

We are given an array `asteroids` of integers representing asteroids in a row. The indices represent their relative positions in space.

For each asteroid:
- The absolute value represents its **size**
- The sign represents its **direction** (positive = right, negative = left)
- Each asteroid moves at the **same speed**

**Task:** Find the state of asteroids after all collisions occur.

**Collision Rules:**
- If two asteroids meet, the **smaller one explodes**
- If both are the **same size, both explode**
- Asteroids moving in the **same direction never meet**

### Examples

**Example 1:**
```
Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
```

**Example 2:**
```
Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.
```

**Example 3:**
```
Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
```

**Example 4:**
```
Input: asteroids = [3,5,-6,2,-1,4]
Output: [-6,2,4]
Explanation: The asteroid -6 makes the asteroid 3 and 5 explode, and then continues going left. 
On the other side, the asteroid 2 makes the asteroid -1 explode and then continues going right, 
without reaching asteroid 4.
```

### Constraints
- $2 \leq \text{asteroids.length} \leq 10^4$
- $-1000 \leq \text{asteroids[i]} \leq 1000$
- $\text{asteroids[i]} \neq 0$

## Observations

1. **Sequential Processing is Key:** We only need to check collisions between a right-moving asteroid and a left-moving asteroid that comes after it. Left-moving asteroids that come before right-moving ones never collide.

2. **Stack-based Approach:** We can use a stack to store asteroids that haven't been destroyed:
   - If current asteroid moves right (`> 0`), it can only collide with future left-moving asteroids, so we push it to the stack
   - If current asteroid moves left (`< 0`), it might collide with asteroids on the stack (which are moving right)

3. **Collision Logic:** When a left-moving asteroid encounters right-moving asteroids in the stack:
   - Compare their absolute values
   - The smaller one is destroyed
   - If equal, both are destroyed
   - If the stack asteroid is larger, the current asteroid is destroyed

4. **Efficiency:** Each asteroid is processed at most twice (once pushed, once popped), giving us $O(n)$ time complexity.

5. **Direction Matters:** A left-moving asteroid can only collide with right-moving asteroids. If the stack is empty or only contains left-moving asteroids, the current asteroid survives.

## Solution

```python
class Solution:
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:
        st = []
        for obj in asteroids:
            # Right-moving asteroids are always added to the stack
            if obj > 0:
                st.append(obj)
            # Left-moving asteroids may collide with right-moving ones
            else:
                self_destroyed = False
                # Process collisions with right-moving asteroids in the stack
                while st and st[-1] > 0:
                    # Compare absolute values
                    if abs(st[-1]) < abs(obj):
                        # Stack asteroid is smaller, it explodes
                        st.pop()
                    elif abs(st[-1]) > abs(obj):
                        # Current asteroid is smaller, it explodes
                        self_destroyed = True
                        break
                    else:
                        # Both same size, both explode
                        st.pop()
                        self_destroyed = True
                        break
                # Add current asteroid if it wasn't destroyed
                if not self_destroyed:
                    st.append(obj)
        return st
```

### Algorithm Walkthrough

Let's trace through Example 4: `[3,5,-6,2,-1,4]`

```
Step 1: obj = 3 (right-moving)
  Stack: [3]
  
Step 2: obj = 5 (right-moving)
  Stack: [3, 5]
  
Step 3: obj = -6 (left-moving)
  - Compare with 5: |5| = 5 < 6, so 5 explodes. Pop 5.
  - Compare with 3: |3| = 3 < 6, so 3 explodes. Pop 3.
  - Stack is empty, -6 survives.
  Stack: [-6]
  
Step 4: obj = 2 (right-moving)
  Stack: [-6, 2]
  
Step 5: obj = -1 (left-moving)
  - Compare with 2: |2| = 2 > 1, so -1 explodes.
  - self_destroyed = True, don't add -1.
  Stack: [-6, 2]
  
Step 6: obj = 4 (right-moving)
  Stack: [-6, 2, 4]
  
Return: [-6, 2, 4]
```

### Time & Space Complexity

- **Time Complexity:** $O(n)$ where $n$ is the number of asteroids. Each asteroid is processed at most once (pushed and popped from stack).
- **Space Complexity:** $O(n)$ for the stack to store remaining asteroids.

### Key Insights

1. **Monotonic Stack Pattern:** This is a classic monotonic stack problem where we maintain the order of non-colliding asteroids.

2. **Direction-Based Logic:** Only right-moving asteroids in the stack can collide with the current left-moving asteroid. Left-moving asteroids in the stack are "safe" and won't collide.

3. **Early Termination:** Once we find that a left-moving asteroid collides with a right-moving one and the right-moving one is larger, we immediately stop checking the rest of the stack.

4. **Order Preservation:** The stack naturally maintains the original order of surviving asteroids, which is what we need for the output.

# Tags
- Stack
- Simulation
- Monotonic Stack
- Array


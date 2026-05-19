## Problem

https://leetcode.com/problems/push-dominoes/description

# Push Dominoes

## Problem

https://leetcode.com/problems/push-dominoes/description

There are n dominoes in a line, placed vertically upright. Some dominoes are pushed either left ('L') or right ('R'), while others remain untouched ('.'). 

**Rules:**
- Each domino falling left pushes its left neighbor
- Each domino falling right pushes its right neighbor  
- A domino pushed from both sides stays upright (balanced forces)
- A falling domino has no additional effect on already falling/fallen dominoes

**Input:** String `dominoes` where:
- `'L'` = pushed left
- `'R'` = pushed right
- `'.'` = not pushed

**Output:** Final state as a string showing which dominoes fall and in which direction

### Examples

**Example 1:**
```
Input: "RR.L"
Output: "RR.L"
Explanation: First domino has no force on second. Third domino doesn't get pushed far enough.
```

**Example 2:**
```
Input: ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."
```

---

## Observations

### Key Insights:

1. **Isolated Dominoes:** A domino only falls if it can be reached by a force from either direction
   - `.` surrounded by `.` stays as `.`
   - `.L` becomes `LL` (left force propagates)
   - `R.` becomes `RR` (right force propagates)

2. **Force Propagation:**
   - Right force propagates right until it meets left force or boundary
   - Left force propagates left until it meets right force or boundary
   - When forces meet: depends on their distances

3. **Four Cases Between Two Forces:**
   - `R...R`: All dominoes in between fall right
   - `L...L`: All dominoes in between fall left
   - `R...L`: 
     - If even spacing: outer two fall (R and L), middle stays upright
     - If odd spacing: middle point becomes equilibrium
   - `L...R`: No dominoes in between are affected (opposite directions)

4. **Boundary Handling:** Treat the problem as having virtual boundary forces:
   - Virtual `L` at index -1 (no left force initially)
   - Virtual `R` at index n (no right force initially)

### Force Dynamics:

```
Position: 0 1 2 3 4 5 6 7 8 9
Input:    . L . R . . . L R . . L . .
          
Between ops, we need to:
- Propagate forces to untouched dominoes
- Resolve conflicts when forces meet
```

---

## Solution

The algorithm uses a **pairwise force approach**: track significant positions (forces) and resolve dominoes between them.

### Approach:

1. **Create operations list:** Record all meaningful positions with their force directions
   - Add virtual `L` at -1 and virtual `R` at n for boundary handling
   - Record all actual `'L'` and `'R'` positions

2. **Process pairs of operations:** For each consecutive pair, determine how dominoes between them fall

3. **Three cases:**
   - **Same direction** (`L..L` or `R..R`): Fill all dots with that direction
   - **Right then Left** (`R...L`): Fill from both ends toward middle
   - **Left then Right** (`L...R`): No change between them

### Code Analysis:

```python
class Solution:
    def pushDominoes(self, s: str) -> str:
        n = len(s)
        
        # Build operations list with boundaries
        ops = [(-1, 'L')]  # Virtual left boundary (no force)
        for i in range(n):
            if s[i] != '.':
                ops.append((i, s[i]))
        ops.append((n, 'R'))  # Virtual right boundary (no force)
        
        res = list(s)  # Result array
        
        # Process each pair of consecutive operations
        for i in range(1, len(ops)):
            i1, ch1 = ops[i - 1]  # Previous operation
            i2, ch2 = ops[i]      # Current operation
            
            if ch1 == ch2:  # Case 1: L..L or R..R
                # All dominoes between fall in same direction
                for j in range(i1 + 1, i2):
                    res[j] = ch1
                    
            elif ch1 == 'R' and ch2 == 'L':  # Case 2: R...L
                # Fill from both ends toward middle
                l, r = i1 + 1, i2 - 1
                while l < r:
                    res[l] = 'R'      # Left pointer gets R
                    res[r] = 'L'      # Right pointer gets L
                    l += 1
                    r -= 1
                # If l == r, middle stays '.' (balanced)
            
            # Case 3: L...R (ch1 == 'L' and ch2 == 'R')
            # No dominoes between are affected, skip
        
        return "".join(res)
```

### Why This Works:

**Virtual Boundaries:**
- `(-1, 'L')`: Ensures leading dominoes don't get falsely marked (L from left means nothing)
- `(n, 'R')`: Ensures trailing dominoes handle right forces correctly

**Case 1: `L..L` or `R..R`**
- Force direction is consistent, so all intermediate dots become that direction
- Example: `R..R` → `RRR` (all get pushed right)

**Case 2: `R...L`**
- Right force conflicts with left force
- The conflict zone fills from outside-in:
  - Position `i1+1` gets `R` (pushed from right)
  - Position `i2-1` gets `L` (pushed from left)
  - They meet in the middle
- If the gap is even, the middle position stays `'.'` (balanced forces meet at same time)
- If the gap is odd, dominoes cancel naturally

Example: `R...L` (gap=3)
```
Positions: 0 1 2 3
Initial:   R . . L
Step 1:    R R . L  (l=1, r=3)
Step 2:    R R L L  (l=2, r=2, they meet - exit loop)
Result:    R R L L  (middle two have forces from opposite sides)
```

**Case 3: `L...R`**
- Left force pushes left, right force pushes right
- They move apart, nothing happens between them
- These remain as dots

### Complexity Analysis:

- **Time:** $O(n)$ - Single pass through dominoes to build ops, then single pass through ops pairs
  - Building ops: $O(n)$
  - Processing pairs: $O(\text{number of ops})$ which is at most $O(n)$
  - Total: $O(n)$

- **Space:** $O(n)$ for the result array and ops list

---

## Tags

- **Level:** Medium
- **Topics:** Two Pointers, Greedy, Simulation
- **Patterns:** 
  - Force propagation
  - Boundary handling with sentinels
  - Pairwise processing
- **Similar Problems:**
  - Trapping Rain Water
  - Container With Most Water

## Observations

## Solution

# Tags


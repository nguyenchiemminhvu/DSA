## Problem

https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/description/

Given an integer `n`, find a sequence with elements in the range `[1, n]` that satisfies all of the following:

1. The integer `1` occurs once in the sequence.
2. Each integer between `2` and `n` occurs twice in the sequence.
3. For every integer `i` between `2` and `n`, the distance between the two occurrences of `i` is exactly `i`.
4. The distance between two numbers on the sequence, `a[i]` and `a[j]`, is the absolute difference of their indices, `|j - i|`.

Return the **lexicographically largest** sequence. It is guaranteed that under the given constraints, there is always a solution.

**Example 1:**
```
Input: n = 3
Output: [3,1,2,3,2]
Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest.
```

**Example 2:**
```
Input: n = 5
Output: [5,3,1,4,3,5,2,4,2]
```

**Constraints:**
- `1 <= n <= 20`

## Observations

1. **Sequence Length**: The sequence has length `2*n - 1` because:
   - Number `1` appears once
   - Numbers `2` to `n` each appear twice
   - Total: `1 + 2*(n-1) = 2*n - 1`

2. **Placement Constraint**: For a number `i` (where `i >= 2`), if we place it at position `idx`, the second occurrence must be at position `idx + i`. This means:
   - Both positions must be within bounds
   - Both positions must be empty

3. **Lexicographically Largest**: To get the lexicographically largest sequence, we should:
   - Try to place larger numbers first
   - Fill positions from left to right
   - At each position, try the largest available number

4. **Backtracking Nature**: This is a constraint satisfaction problem that requires backtracking:
   - We need to try different number placements
   - If a placement leads to no solution, backtrack and try another number
   - The greedy approach of always choosing the largest won't work without backtracking

5. **State Tracking**: We need to track:
   - Which numbers have been used
   - Which positions in the sequence are filled
   - Current position being filled

## Solution

### Approach: Backtracking with Greedy Number Selection

The solution uses backtracking to explore different valid placements while greedily trying larger numbers first to ensure lexicographically largest result.

### Algorithm Steps:

1. **Initialize**:
   - Create result array of size `2*n - 1` filled with zeros
   - Track used numbers with a boolean array

2. **Backtracking Function**:
   - Skip already filled positions (find next empty slot)
   - If all positions filled, return `True` (solution found)
   - Try numbers from `n` down to `1`:
     - Skip if number already used
     - For number `1`: place once and recurse
     - For number `> 1`: check if second position `idx + num` is valid and empty
       - If valid, place both occurrences and recurse
       - If recursion succeeds, return `True`
       - Otherwise, backtrack (remove placements and mark as unused)
   - If no number works, return `False`

3. **Why This Works**:
   - **Correctness**: Backtracking explores all valid placements
   - **Lexicographic Order**: By trying larger numbers first at each position, we naturally build the lexicographically largest sequence
   - **Efficiency**: Early termination when solution found; pruning through validity checks

### Code Walkthrough:

```python
def constructDistancedSequence(self, n: int) -> List[int]:
    length = 2 * n - 1
    res = [0] * length  # 0 means unfilled
    used = [False] * (n + 1)  # Track which numbers are used
    
    def backtrack(idx: int) -> bool:
        # Skip filled positions - move to next empty slot
        while idx < length and res[idx] != 0:
            idx += 1
        
        # All positions filled - solution found
        if idx == length:
            return True
        
        # Try numbers from largest to smallest (lexicographic order)
        for num in range(n, 0, -1):
            if used[num]:
                continue
            
            if num == 1:
                # Special case: 1 appears only once
                res[idx] = 1
                used[1] = True
                if backtrack(idx + 1):
                    return True
                # Backtrack
                res[idx] = 0
                used[1] = False
            else:
                # num appears twice with distance num
                j = idx + num
                if j < length and res[j] == 0:
                    res[idx] = res[j] = num
                    used[num] = True
                    if backtrack(idx + 1):
                        return True
                    # Backtrack
                    res[idx] = res[j] = 0
                    used[num] = False
        
        return False
    
    backtrack(0)
    return res
```

### Example Trace (n = 3):

```
Sequence length = 2*3 - 1 = 5
Positions: [_, _, _, _, _]

idx=0, try 3: place at 0 and 3 → [3, _, _, 3, _]
idx=1, try 2: can't place (1+2=3, already filled)
idx=1, try 1: place at 1 → [3, 1, _, 3, _]
idx=2, try 2: place at 2 and 4 → [3, 1, 2, 3, 2]
idx=5: all filled, return True

Result: [3, 1, 2, 3, 2]
```

### Complexity Analysis:

- **Time Complexity**: $O(n!)$ in worst case
  - We try each number at various positions
  - With backtracking, we explore different permutations
  - Pruning reduces actual complexity significantly
  - For `n <= 20`, this is acceptable

- **Space Complexity**: $O(n)$
  - Result array: $O(2n - 1) = O(n)$
  - Used array: $O(n)$
  - Recursion stack: $O(n)$ depth

### Key Insights:

1. **Greedy + Backtracking**: Pure greedy doesn't work, but greedy choice with backtracking ensures lexicographically largest solution
2. **Early Skip**: Skipping to next empty position avoids unnecessary recursion
3. **Distance Constraint**: The key constraint `distance = value` simplifies placement logic
4. **Guaranteed Solution**: Problem guarantees solution exists, so we don't need to handle "no solution" case

# Tags

`Backtracking` `Array` `Greedy` `Constraint Satisfaction`


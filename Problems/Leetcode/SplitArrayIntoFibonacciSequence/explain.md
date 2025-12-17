## Problem

https://leetcode.com/problems/split-array-into-fibonacci-sequence/

You are given a string of digits `num`, such as `"123456579"`. We can split it into a Fibonacci-like sequence `[123, 456, 579]`.

Formally, a Fibonacci-like sequence is a list `f` of non-negative integers such that:
- `0 <= f[i] < 2^31` (each integer fits in a 32-bit signed integer type)
- `f.length >= 3`
- `f[i] + f[i + 1] == f[i + 2]` for all `0 <= i < f.length - 2`

**Important**: When splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number `0` itself.

Return any Fibonacci-like sequence split from `num`, or return `[]` if it cannot be done.

**Examples:**

Example 1:
```
Input: num = "1101111"
Output: [11,0,11,11]
Explanation: The output [110, 1, 111] would also be accepted.
```

Example 2:
```
Input: num = "112358130"
Output: []
Explanation: The task is impossible.
```

Example 3:
```
Input: num = "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
```

**Constraints:**
- `1 <= num.length <= 200`
- `num` contains only digits

## Observations

### Key Insights

1. **Fibonacci Property Determines Everything**: Once we fix the first two numbers, all subsequent numbers are uniquely determined by the formula `f[i] = f[i-2] + f[i-1]`. This means we only need to search for valid first two numbers.

2. **Search Space for First Two Numbers**: 
   - First number: can be 1 to n-2 characters long (need space for at least second and third numbers)
   - Second number: starts where first ends, can extend to near the end
   - Total combinations: O(n²)

3. **Validation Constraints**:
   - **Leading Zeros**: Any number with length > 1 starting with '0' is invalid (except "0" itself)
   - **Integer Overflow**: All numbers must be < 2³¹ = 2,147,483,648
   - **Minimum Length**: Final sequence must have at least 3 numbers

4. **Early Termination Opportunities**:
   - If we encounter leading zero in a substring, no longer substring starting at same position will be valid (break)
   - If a number exceeds MAX, longer substrings will also exceed (break)
   - If we can't find a matching sum, try different substring length

5. **Backtracking Nature**: When building the sequence after first two numbers, if we hit a dead end (can't match remaining string), we need to backtrack and try different first two numbers.

### Why DFS/Backtracking?

- After choosing first two numbers, we need to recursively verify if the rest of the string can form a valid Fibonacci sequence
- At each position, we try different substring lengths to find one that matches the required sum
- If no valid substring is found, we backtrack to try different first two numbers

## Solution

### Algorithm: Backtracking with DFS

The solution uses a two-phase approach:

#### Phase 1: Enumerate First Two Numbers
```python
for i in range(1, n):              # First number: s[0:i]
    for j in range(i + 1, n + 1):  # Second number: s[i:j]
```
- Try all possible ways to split the first two numbers
- For each pair, validate:
  - No leading zeros (unless the number is "0")
  - Both numbers fit in 32-bit signed integer
- If valid, proceed to Phase 2 with these two numbers

#### Phase 2: Build Remaining Sequence with DFS
```python
def dfs(i: int, tmp: List[int]) -> bool:
    # i: current position in string
    # tmp: current sequence being built
```

**Base Case:**
- If `i >= n` (reached end of string):
  - Return `True` if `len(tmp) >= 3` (valid Fibonacci sequence)
  - Return `False` if `len(tmp) <= 2` (sequence too short)

**Recursive Case:**
- Try all possible substrings starting from position `i` to position `j` (where `i <= j < n`)
- For each substring `s[i:j+1]`:
  1. **Leading Zero Check**: If length > 1 and starts with '0', return `False` (no point trying longer substrings)
  2. **Overflow Check**: If value > 2³¹-1, return `False` (longer substrings will also overflow)
  3. **Fibonacci Check**: If `val == tmp[-1] + tmp[-2]`:
     - Add `val` to sequence
     - Recursively call `dfs(j+1, tmp)`
     - If recursive call returns `True`, propagate success
     - Otherwise, backtrack by removing `val` and try next substring length
- If no valid substring found, return `False`

### Code Walkthrough

```python
class Solution:
    def splitIntoFibonacci(self, s: str) -> List[int]:
        n = len(s)
        MAX = [2 ** 31 - 1]  # Using list to allow modification in nested function
        
        def dfs(i: int, tmp: List[int]) -> bool:
            # Base case: reached end of string
            if i >= n:
                if len(tmp) <= 2:
                    return False  # Need at least 3 numbers
                return True
            
            # Try all possible substrings starting at position i
            for j in range(i, n):
                sub = s[i:j+1]
                
                # Invalid: leading zero (except "0" itself)
                if len(sub) > 1 and sub[0] == '0':
                    return False  # No point trying longer substrings
                
                val = int(sub)
                
                # Invalid: overflow
                if val > MAX[0]:
                    return False  # Longer substrings will also overflow
                
                # Check Fibonacci property: current = previous + second_previous
                if val == tmp[-1] + tmp[-2]:
                    tmp.append(val)
                    if dfs(j + 1, tmp):  # Recurse to next position
                        return True
                    tmp.pop()  # Backtrack
            
            return False  # No valid substring found
        
        # Try all possible first two numbers
        for i in range(1, n):
            for j in range(i + 1, n + 1):
                sa = s[:i]      # First number
                sb = s[i:j]     # Second number
                
                # Validate: no leading zeros
                if (len(sa) > 1 and sa[0] == '0') or (len(sb) > 1 and sb[0] == '0'):
                    break  # No point trying longer substrings
                
                a = int(sa)
                b = int(sb)
                
                # Validate: no overflow
                if a > MAX[0] or b > MAX[0]:
                    break  # Longer substrings will also overflow
                
                # Try to build sequence starting with [a, b]
                tmp = [a, b]
                if dfs(j, tmp):
                    return tmp  # Found valid sequence
        
        return []  # No valid sequence exists
```

### Why This Works

1. **Exhaustive Search**: We try all possible combinations of first two numbers, ensuring we don't miss any valid solution.

2. **Deterministic After First Two**: The Fibonacci property uniquely determines all subsequent numbers, so DFS can efficiently validate.

3. **Efficient Pruning**: 
   - Break on leading zeros (no longer substrings will be valid)
   - Break on overflow (longer substrings will also overflow)
   - Return immediately when valid sequence is found

4. **Backtracking**: If a particular choice doesn't lead to complete sequence, we backtrack and try alternatives.

### Example Walkthrough

**Input**: `num = "1101111"`

**Step 1**: Try `a = 11` (s[0:2]), `b = 0` (s[2:3])
- Sequence: `[11, 0]`
- Call `dfs(3, [11, 0])`

**Step 2**: DFS from position 3
- Need: `11 + 0 = 11`
- Try `s[3:5] = "11"` → value = 11 ✓
- Sequence: `[11, 0, 11]`
- Call `dfs(5, [11, 0, 11])`

**Step 3**: DFS from position 5
- Need: `0 + 11 = 11`
- Try `s[5:7] = "11"` → value = 11 ✓
- Sequence: `[11, 0, 11, 11]`
- Call `dfs(7, [11, 0, 11, 11])`

**Step 4**: DFS from position 7
- Position 7 >= length 7 (reached end)
- Length of sequence = 4 (>= 3) ✓
- Return `True`

**Result**: `[11, 0, 11, 11]`

### Complexity Analysis

**Time Complexity**: O(n³)
- Outer loops: O(n²) combinations for first two numbers
- DFS: At each position, try O(n) substring lengths
- With pruning, practical performance is much better
- Worst case: O(n²) × O(n) = O(n³)

**Space Complexity**: O(n)
- Recursion stack depth: O(n) in worst case (each number is single digit)
- Result list: O(n) numbers at most
- Total: O(n)

### Edge Cases

1. **All Zeros**: `"000"` → `[0, 0, 0]` ✓
2. **Leading Zeros**: `"0123"` → `[]` (invalid)
3. **Single Digit**: `"1"` → `[]` (too short)
4. **Overflow**: Numbers > 2³¹-1 are rejected
5. **No Valid Split**: `"112358130"` → `[]`
6. **Multiple Solutions**: Return any one valid solution

# Tags
- Backtracking
- Depth-First Search (DFS)
- String
- Recursion


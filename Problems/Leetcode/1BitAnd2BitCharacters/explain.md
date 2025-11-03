## Problem

https://leetcode.com/problems/1-bit-and-2-bit-characters/description/

```
We have two special characters:

The first character can be represented by one bit 0.
The second character can be represented by two bits (10 or 11).
Given a binary array bits that ends with 0, return true if the last character must be a one-bit character.

Example 1:

Input: bits = [1,0,0]
Output: true
Explanation: The only way to decode it is two-bit character and one-bit character.
So the last character is one-bit character.

Example 2:

Input: bits = [1,1,1,0]
Output: false
Explanation: The only way to decode it is two-bit character and two-bit character.
So the last character is not one-bit character.

Constraints:

1 <= bits.length <= 1000
bits[i] is either 0 or 1.
```

## Observations

1. **Character Encoding Rules**:
   - One-bit character: `0`
   - Two-bit character: `10` or `11`

2. **Key Constraints**:
   - The array always ends with `0`
   - We need to determine if this final `0` represents a one-bit character or is part of a two-bit character `10`

3. **Parsing Strategy**:
   - We must parse from left to right following the encoding rules
   - When we encounter `0`, it's always a one-bit character (consume 1 bit)
   - When we encounter `1`, it's always the start of a two-bit character (consume 2 bits)

4. **Decision Point**:
   - If we can reach exactly the last position (n-1) and find a `0` there, then the last character is a one-bit character
   - If we overshoot the last position, it means the last `0` was part of a `10` two-bit character

## Solution

The solution uses a recursive approach to simulate the parsing process:

```python
class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        if bits[-1] == 1:
            return False
        
        n = len(bits)
        def check(i: int) -> bool:
            if i == n - 1 and bits[i] == 0:
                return True
            if i >= n:
                return False
            
            if bits[i] == 0:
                return check(i + 1)
            return check(i + 2)
        
        return check(0)
```

**Algorithm Explanation**:

1. **Early Return**: If the last bit is `1`, return `False` immediately (violates the constraint that array ends with `0`)

2. **Recursive Parsing**: The `check(i)` function simulates parsing from position `i`:
   - **Base Case 1**: If we reach exactly the last position (n-1) and it's `0`, we found a one-bit character at the end → return `True`
   - **Base Case 2**: If we overshoot the array bounds, the last `0` was consumed as part of a two-bit character → return `False`
   - **Recursive Case 1**: If current bit is `0`, it forms a one-bit character → move to next position `check(i+1)`
   - **Recursive Case 2**: If current bit is `1`, it starts a two-bit character → skip 2 positions `check(i+2)`

**Time Complexity**: O(n) - we visit each position at most once
**Space Complexity**: O(n) - recursion stack depth in worst case

**Example Walkthrough**:
- `bits = [1,0,0]`: Start at 0 → `1` (2-bit) → jump to 2 → `0` at position 2 (last position) → `True`
- `bits = [1,1,1,0]`: Start at 0 → `1` (2-bit) → jump to 2 → `1` (2-bit) → jump to 4 → overshoot → `False`

# Tags

- Array
- Greedy
- Simulation
- Recursion


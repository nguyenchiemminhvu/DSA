# Additive Number

## Problem

https://leetcode.com/problems/additive-number/description/

An **additive number** is a string whose digits can form an additive sequence.

A valid additive sequence should contain **at least three numbers**. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits, return `true` if it is an additive number or `false` otherwise.

**Note:** Numbers in the additive sequence **cannot have leading zeros**, so sequence `1, 2, 03` or `1, 02, 3` is invalid.

### Examples

**Example 1:**
```
Input: "112358"
Output: true
Explanation: 
The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
```

**Example 2:**
```
Input: "199100199"
Output: true
Explanation: 
The additive sequence is: 1, 99, 100, 199. 
1 + 99 = 100, 99 + 100 = 199
```

### Constraints
- `1 <= num.length <= 35`
- `num` consists only of digits

### Follow-up
How would you handle overflow for very large input integers?

---

## Observations

1. **Sequence Determination**: Once we fix the first two numbers, the entire sequence is determined (each subsequent number must be the sum of the previous two).

2. **Search Space**: We need to try different splits for the first two numbers:
   - First number can be of length 1 to n-2
   - Second number can start after the first and extend to leave room for at least one more number

3. **Leading Zeros**: A number cannot have leading zeros unless it is "0" itself:
   - Valid: "0", "5", "10"
   - Invalid: "01", "003", "00"

4. **Early Termination**: 
   - If the current substring has leading zeros (length > 1 and starts with '0'), we can stop exploring that branch
   - If we find any valid additive sequence, we can return true immediately

5. **Greedy Matching**: For the remaining part after the first two numbers, we must check if the next substring equals the sum of the last two numbers. We can't just pick any substring.

---

## Solution

### Approach: Backtracking with DFS

The solution uses a two-phase approach:

1. **Phase 1 - Select First Two Numbers** (Outer loops):
   - Try all valid positions to split the string into two initial numbers
   - Skip pairs where either number has leading zeros

2. **Phase 2 - Validate Remaining Sequence** (DFS):
   - Starting with the two selected numbers, recursively check if the rest forms a valid additive sequence
   - At each step, try different lengths for the next number
   - Only accept a substring if it equals the sum of the last two numbers

### Algorithm

```python
class Solution:
    def isAdditiveNumber(self, s: str) -> bool:
        n = len(s)
        
        def dfs(i: int, tmp: List[int]) -> bool:
            # Base case: reached the end of string
            if i >= n:
                # Need at least 3 numbers
                if len(tmp) <= 2:
                    return False
                return True
            
            # Try different lengths for the next number
            for j in range(i, n):
                sub = s[i:j+1]
                
                # Check for leading zeros
                if len(sub) > 1 and sub[0] == '0':
                    return False  # No point trying longer substrings
                
                val = int(sub)
                
                # Check if this number equals sum of last two
                if val == tmp[-1] + tmp[-2]:
                    tmp.append(val)
                    if dfs(j + 1, tmp):
                        return True
                    tmp.pop()  # Backtrack
            
            return False
        
        # Try all possible splits for first two numbers
        for i in range(1, n):
            for j in range(i + 1, n + 1):
                sa = s[:i]      # First number
                sb = s[i:j]     # Second number
                
                # Skip if either has leading zeros
                if (len(sa) > 1 and sa[0] == '0') or (len(sb) > 1 and sb[0] == '0'):
                    continue
                
                a = int(sa)
                b = int(sb)
                
                # Try to build sequence starting with a and b
                if dfs(j, [a, b]):
                    return True
        
        return False
```

### Complexity Analysis

**Time Complexity:** $O(n^3)$
- Outer loops: $O(n^2)$ - trying all pairs for first two numbers
- For each pair, DFS explores at most $O(n)$ possibilities
- In practice, much better due to early termination

**Space Complexity:** $O(n)$
- Recursion stack depth: $O(n)$ in worst case
- `tmp` list stores at most $O(n)$ numbers

### Example Walkthrough

**Input:** `"112358"`

1. Try first number = "1", second number = "1":
   - Start: [1, 1]
   - Next must be 1+1=2, check "2" at position 2 ✓
   - tmp = [1, 1, 2]
   - Next must be 1+2=3, check "3" at position 3 ✓
   - tmp = [1, 1, 2, 3]
   - Next must be 2+3=5, check "5" at position 4 ✓
   - tmp = [1, 1, 2, 3, 5]
   - Next must be 3+5=8, check "8" at position 5 ✓
   - tmp = [1, 1, 2, 3, 5, 8]
   - Reached end with 6 numbers ✓
   - **Return true**

### Key Insights

1. **Why DFS only checks `val == tmp[-1] + tmp[-2]`**: Because once we have the first two numbers, every subsequent number is uniquely determined. We're not searching for any valid split—we're checking if a specific required sum exists at that position.

2. **Leading Zero Optimization**: In the DFS loop, when we encounter a leading zero (length > 1 and starts with '0'), we return false immediately rather than continue, because extending the substring will still have that leading zero.

3. **Backtracking**: The `tmp.pop()` operation ensures we can try different path lengths without creating a new list each time.

### Edge Cases

1. **All zeros**: "000" → false (can't form "00, 0, 0" due to leading zeros)
2. **Leading zeros**: "101" → true (sequence: 0, 1, 1)
3. **Large numbers**: "198019823962" → Potential overflow (see follow-up)
4. **Minimum length**: "123" → true (sequence: 1, 2, 3)

---

## Follow-up: Handling Overflow

For very large input integers (num.length up to 35), numbers can exceed even 64-bit integer limits.

**Solution:** Use **string-based addition** instead of integer arithmetic:

```python
def addStrings(a: str, b: str) -> str:
    """Add two numbers represented as strings"""
    i, j = len(a) - 1, len(b) - 1
    carry = 0
    result = []
    
    while i >= 0 or j >= 0 or carry:
        digit_a = int(a[i]) if i >= 0 else 0
        digit_b = int(b[j]) if j >= 0 else 0
        total = digit_a + digit_b + carry
        result.append(str(total % 10))
        carry = total // 10
        i -= 1
        j -= 1
    
    return ''.join(reversed(result))

def isAdditiveNumber(self, s: str) -> bool:
    n = len(s)
    
    def dfs(i: int, tmp: List[str]) -> bool:
        if i >= n:
            return len(tmp) > 2
        
        for j in range(i, n):
            sub = s[i:j+1]
            if len(sub) > 1 and sub[0] == '0':
                return False
            
            # Compare as strings
            if sub == addStrings(tmp[-2], tmp[-1]):
                tmp.append(sub)
                if dfs(j + 1, tmp):
                    return True
                tmp.pop()
        
        return False
    
    # Rest remains similar but work with strings
    for i in range(1, n):
        for j in range(i + 1, n + 1):
            sa = s[:i]
            sb = s[i:j]
            if (len(sa) > 1 and sa[0] == '0') or (len(sb) > 1 and sb[0] == '0'):
                continue
            if dfs(j, [sa, sb]):
                return True
    return False
```

This avoids integer overflow entirely by keeping all numbers as strings and performing string-based arithmetic.

# Tags

`String` `Backtracking` `DFS` `Math`


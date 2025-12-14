## Problem

https://leetcode.com/problems/restore-ip-addresses/description/

```
A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.

Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.

Example 1:
Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]

Example 2:
Input: s = "0000"
Output: ["0.0.0.0"]

Example 3:
Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

Constraints:
- 1 <= s.length <= 20
- s consists of digits only.
```

## Observations

1. **Fixed Structure**: A valid IP address has exactly 4 segments, so we need to place exactly 3 dots in the string.

2. **Segment Length**: Each segment can have 1-3 digits:
   - 1 digit: 0-9 (always valid if in range)
   - 2 digits: 10-99 (cannot start with 0)
   - 3 digits: 100-255 (cannot start with 0, must be ≤ 255)

3. **Leading Zeros**: The only valid segment starting with '0' is "0" itself. "01", "001", "010" are all invalid.

4. **String Length Constraints**: For a valid IP:
   - Minimum length: 4 (e.g., "0.0.0.0")
   - Maximum length: 12 (e.g., "255.255.255.255")
   - If len(s) < 4 or len(s) > 12, no valid IP exists

5. **Search Space**: We need to try all possible positions for the 3 dots, which gives us O(n³) combinations where n ≤ 12.

## Solution

### Approach: Brute Force with Three Nested Loops

The solution uses three nested loops to try all possible positions for the three dots that separate the four IP segments.

```python
class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        n = len(s)
        res = []
        
        # Try all positions for first dot (after index i)
        for i in range(0, n-3):
            # Try all positions for second dot (after index j)
            for j in range(i + 1, n-2):
                # Try all positions for third dot (after index k)
                for k in range(j + 1, n-1):
                    l = k + 1
                    
                    # Extract four segments
                    a = s[:i + 1]
                    b = s[i + 1:j + 1]
                    c = s[j + 1:k + 1]
                    d = s[k + 1:]
                    
                    tmp = [a, b, c, d]
                    valid = True
                    
                    # Validate each segment
                    for sub in tmp:
                        val = int(sub)
                        
                        # Check if value exceeds 255
                        if val > 255:
                            valid = False
                            break
                        
                        # Check for invalid leading zeros (e.g., "01", "010")
                        if val > 0 and sub[0] == '0':
                            valid = False
                            break
                        
                        # Check if zero has leading zeros (e.g., "00", "000")
                        if val == 0 and len(sub) > 1:
                            valid = False
                            break
                    
                    if valid:
                        res.append(".".join(tmp))
        
        return res
```

**How It Works:**

1. **Three Loops for Three Dots**:
   - `i`: Position after first segment (range: 0 to n-4)
   - `j`: Position after second segment (range: i+1 to n-3)
   - `k`: Position after third segment (range: j+1 to n-2)
   - This ensures each segment has at least 1 character

2. **Extract Segments**:
   - Segment 1: `s[0:i+1]`
   - Segment 2: `s[i+1:j+1]`
   - Segment 3: `s[j+1:k+1]`
   - Segment 4: `s[k+1:]`

3. **Validation Checks**:
   - Value must be ≤ 255
   - No leading zeros: if value > 0, first char cannot be '0'
   - Zero must be single digit: if value == 0, length must be 1

**Time Complexity**: O(n³) where n ≤ 12, effectively O(1) constant time
**Space Complexity**: O(1) not counting the output array

## Alternative Solutions

### Alternative 1: Backtracking (More Elegant)

```python
class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        def is_valid(segment):
            # Check if segment is valid
            if not segment or len(segment) > 3:
                return False
            if segment[0] == '0' and len(segment) > 1:  # Leading zeros
                return False
            return int(segment) <= 255
        
        def backtrack(start, path):
            # Base case: found 4 segments and used all characters
            if len(path) == 4:
                if start == len(s):
                    result.append('.'.join(path))
                return
            
            # Try segments of length 1, 2, 3
            for length in range(1, 4):
                if start + length > len(s):
                    break
                
                segment = s[start:start + length]
                if is_valid(segment):
                    backtrack(start + length, path + [segment])
        
        result = []
        backtrack(0, [])
        return result
```

**Advantages**:
- More readable and maintainable
- Easier to understand the recursive structure
- Better for interview settings

**Time Complexity**: O(3⁴) = O(81) = O(1)
**Space Complexity**: O(4) for recursion depth = O(1)

### Alternative 2: Iterative with Early Pruning

```python
class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        def is_valid(segment):
            if not segment or len(segment) > 3:
                return False
            if len(segment) > 1 and segment[0] == '0':
                return False
            return int(segment) <= 255
        
        n = len(s)
        # Early pruning: check if length is valid
        if n < 4 or n > 12:
            return []
        
        result = []
        
        # Try all combinations with length pruning
        for len1 in range(1, min(4, n-2)):  # First segment
            if not is_valid(s[:len1]):
                continue
                
            for len2 in range(1, min(4, n-len1-1)):  # Second segment
                if not is_valid(s[len1:len1+len2]):
                    continue
                    
                for len3 in range(1, min(4, n-len1-len2)):  # Third segment
                    len4 = n - len1 - len2 - len3  # Fourth segment
                    
                    if len4 < 1 or len4 > 3:
                        continue
                    
                    seg3 = s[len1+len2:len1+len2+len3]
                    seg4 = s[len1+len2+len3:]
                    
                    if is_valid(seg3) and is_valid(seg4):
                        ip = f"{s[:len1]}.{s[len1:len1+len2]}.{seg3}.{seg4}"
                        result.append(ip)
        
        return result
```

**Advantages**:
- Early pruning with length checks
- Cleaner validation logic with helper function
- Avoids processing invalid strings upfront

### Alternative 3: DFS with Memoization (Overkill but Educational)

```python
class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        def is_valid(segment):
            if not segment or len(segment) > 3:
                return False
            if len(segment) > 1 and segment[0] == '0':
                return False
            return int(segment) <= 255
        
        def dfs(index, segments):
            # Base cases
            if len(segments) == 4:
                return ['.'.join(segments)] if index == len(s) else []
            
            if index >= len(s) or len(segments) > 4:
                return []
            
            result = []
            # Try adding segments of length 1, 2, 3
            for length in range(1, 4):
                if index + length > len(s):
                    break
                
                segment = s[index:index + length]
                if is_valid(segment):
                    result.extend(dfs(index + length, segments + [segment]))
            
            return result
        
        return dfs(0, [])
```

**Note**: Memoization isn't really needed here since we don't revisit states, but this shows how DFS naturally explores the solution space.

## Comparison

| Approach | Time | Space | Readability | Interview-Friendly |
|----------|------|-------|-------------|-------------------|
| Brute Force (3 loops) | O(1) | O(1) | Medium | Yes |
| Backtracking | O(1) | O(1) | High | ⭐ Best |
| Iterative with Pruning | O(1) | O(1) | Medium | Yes |
| DFS | O(1) | O(1) | High | Yes |

**Recommendation**: Use **Backtracking** approach for interviews as it's most intuitive and demonstrates understanding of recursive problem-solving.

# Tags

`String` `Backtracking` `Brute Force` `IP Address` `Validation`


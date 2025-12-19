## Problem

https://leetcode.com/problems/ambiguous-coordinates/description/

We had some 2-dimensional coordinates, like `(1, 3)` or `(2, 0.5)`. Then, we removed all commas, decimal points, and spaces and ended up with the string `s`.

**For example:**
- `(1, 3)` becomes `s = "(13)"`
- `(2, 0.5)` becomes `s = "(205)"`

Return a list of strings representing all possibilities for what our original coordinates could have been.

**Important Rules:**
- Our original representation never had extraneous zeroes
- Never started with: `"00"`, `"0.0"`, `"0.00"`, `"1.0"`, `"001"`, `"00.01"`, or any number that can be represented with fewer digits
- A decimal point within a number never occurs without at least one digit before it (no `".1"`)
- The final answer list can be returned in any order
- All coordinates must have exactly one space between them (after the comma)

**Examples:**

Example 1:
```
Input: s = "(123)"
Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
```

Example 2:
```
Input: s = "(0123)"
Output: ["(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12, 3)"]
Explanation: 0.0, 00, 0001 or 00.01 are not allowed.
```

Example 3:
```
Input: s = "(00011)"
Output: ["(0, 0.011)","(0.001, 1)"]
```

**Constraints:**
- `4 <= s.length <= 12`
- `s[0] == '('` and `s[s.length - 1] == ')'`
- The rest of `s` are digits

---

## Observations

### 1. **Problem Structure**
- We need to split the digit string into two parts: left coordinate and right coordinate
- Each part can have at least 1 digit
- For string of length `n`, there are `n-1` ways to split it

### 2. **Valid Number Rules**

**For numbers WITHOUT decimal point:**
- Can be `"0"` (single zero is valid)
- Cannot start with `"0"` if it has multiple digits (e.g., `"01"`, `"001"` are invalid)

**For numbers WITH decimal point:**
- Left part (before decimal):
  - Can be `"0"` exactly
  - Cannot have leading zeros with multiple digits (e.g., `"00"`, `"01"` invalid)
- Right part (after decimal):
  - Cannot end with `"0"` (e.g., `"1.0"`, `"1.20"` are invalid as they can be written as `"1"`, `"1.2"`)
  - Can start with zeros (e.g., `"0.01"`, `"0.001"` are valid)

### 3. **Key Insights**
- We need to generate all valid representations for each substring
- A number can be valid as-is (without decimal) OR with decimal point inserted at different positions
- Not all positions for decimal points are valid - must satisfy the rules above
- We combine valid representations from left and right parts using Cartesian product

---

## Solution

### Approach: Split + Generate Valid Numbers

**Step 1: Extract Digits**
```python
digits = s[1:-1]  # Remove '(' and ')'
```
- Remove parentheses to work with just the digits

**Step 2: Helper Function - Generate Valid Numbers**

The `dfs(num)` function generates all valid number representations for a substring:

```python
def dfs(num: str) -> List[str]:
    res = []
    
    # Case 1: Number without decimal
    if num == "0" or not num.startswith("0"):
        res.append(num)
    
    # Case 2: Numbers with decimal
    for i in range(1, len(num)):
        left = num[:i]
        right = num[i:]
        
        # Validate left part
        if left.startswith("0") and left != "0":
            continue
        
        # Validate right part
        if right.endswith("0"):
            continue
        
        res.append(left + "." + right)
    
    return res
```

**Case 1: Without Decimal**
- If the number is exactly `"0"`, it's valid
- If it doesn't start with `"0"`, it's valid (no leading zeros)
- Examples: `"123"` ✓, `"0"` ✓, `"01"` ✗

**Case 2: With Decimal**
- Try placing decimal at every position from index 1 to len-1
- Check left part: must be `"0"` or not start with `"0"`
- Check right part: cannot end with `"0"`
- Examples from `"123"`:
  - `"1.23"` ✓ (left=`"1"`, right=`"23"`)
  - `"12.3"` ✓ (left=`"12"`, right=`"3"`)

**Step 3: Split and Combine**

```python
for i in range(1, n):
    left_part = digits[:i]
    right_part = digits[i:]
    
    left_numbers = dfs(left_part)
    right_numbers = dfs(right_part)
    
    for l in left_numbers:
        for r in right_numbers:
            result.append(f"({l}, {r})")
```

- Try all ways to split digits into two non-empty parts
- Generate all valid numbers for each part
- Combine using Cartesian product (all left × all right)
- Format as `(left, right)` with proper spacing

---

### Complexity Analysis

**Time Complexity: O(n³)**
- Outer loop: O(n) ways to split the string
- For each split: generating valid numbers takes O(n) positions to try decimal
- For each valid number generation: O(n) to create substring
- Combining results: at most O(n²) valid numbers from each part
- Overall: O(n × n × n) = O(n³)

**Space Complexity: O(n²)**
- Storing all valid number representations: O(n²) in worst case
- Each valid number string: O(n) length
- Result list: O(n²) possible coordinate pairs

---

### Example Walkthrough

**Input:** `s = "(123)"`

**Step 1:** Extract digits = `"123"`

**Step 2:** Try all splits:

**Split 1:** left=`"1"`, right=`"23"`
- `dfs("1")` → `["1"]` (no decimal possible, length 1)
- `dfs("23")` → `["23", "2.3"]`
  - Without decimal: `"23"` ✓
  - With decimal at pos 1: `"2.3"` ✓
- Combinations: `["(1, 23)", "(1, 2.3)"]`

**Split 2:** left=`"12"`, right=`"3"`
- `dfs("12")` → `["12", "1.2"]`
  - Without decimal: `"12"` ✓
  - With decimal at pos 1: `"1.2"` ✓
- `dfs("3")` → `["3"]`
- Combinations: `["(12, 3)", "(1.2, 3)"]`

**Final Result:** `["(1, 23)", "(1, 2.3)", "(12, 3)", "(1.2, 3)"]`

---

### Edge Cases

1. **Leading zeros:**
   - `"01"` → only `"0.1"` is valid
   - `"00"` → no valid numbers

2. **Trailing zeros:**
   - `"10"` → only `"10"` is valid (not `"1.0"`)
   - `"100"` → only `"100"` is valid (not `"10.0"` or `"1.00"`)

3. **All zeros:**
   - `"(00011)"` → very limited valid combinations
   - Left part must be `"0"` or `"0.00..."` format
   - Right part must be `"..."` or have decimal not ending in 0

4. **Single digit on each side:**
   - Minimum split ensures both parts have at least 1 digit

# Tags

`String` `Backtracking` `Enumeration`


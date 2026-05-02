## Problem

https://leetcode.com/problems/string-compression/

Given an array of characters `chars`, compress it in-place using the following algorithm:

1. Begin with an empty string `s`
2. For each group of consecutive repeating characters in `chars`:
   - If the group's length is 1, append the character to `s`
   - Otherwise, append the character followed by the group's length
3. The compressed string `s` should be stored back into the input character array `chars`
4. Note that group lengths ≥ 10 will be split into multiple characters (e.g., "bbbbbbbbbbbb" becomes "b12")

**Constraints:**
- You must write an algorithm that uses **only constant extra space**
- 1 ≤ chars.length ≤ 2000
- chars[i] is a lowercase/uppercase English letter, digit, or symbol
- Return the new length of the array after compression

**Examples:**

Example 1: `["a","a","b","b","c","c","c"]` → `"a2b2c3"` → return 6

Example 2: `["a"]` → `"a"` (unchanged, single character) → return 1

Example 3: `["a","b","b","b","b","b","b","b","b","b","b","b","b"]` → `"ab12"` → return 4

## Observations

**Key Insights:**

1. **Two-Pointer Technique (Read and Write Pointers):** The core strategy uses separate `read` and `write` pointers:
   - `read` pointer: scans through the array to identify character groups
   - `write` pointer: writes compressed results back into the array
   - This enables in-place modification without requiring extra array space

2. **Consecutive Character Grouping:** Use a nested loop where:
   - Inner loop counts consecutive identical characters
   - After counting, write the character and (if count > 1) the count itself

3. **Handling Multi-digit Counts:** When a count ≥ 10 (like 12), convert it to a string and write each digit separately. This is why "bbbbbbbbbbbb" (12 b's) becomes "b" followed by "1" and "2"

4. **Why Constant Space Works:** 
   - We write back to the same array
   - The write position (`write`) never catches up to the read position (`read`) because compression always reduces or maintains size
   - No extra data structures needed

5. **Algorithm Guarantee:** Compression never expands the array beyond its original size:
   - Best case: "aaaa" → "a4" (4 chars → 2 chars)
   - Worst case: "abcd" → "a1b1c1d1" (4 chars → 8 chars, but still ≤ 2000)

## Solution

```python
class Solution:
    def compress(self, chars: List[str]) -> int:
        n = len(chars)
        read = 0      # Pointer to scan the array
        write = 0     # Pointer to write compressed data
        
        while read < n:
            cur = chars[read]     # Current character being processed
            count = 0             # Count consecutive occurrences
            
            # Count consecutive identical characters
            while read < n and chars[read] == cur:
                read += 1
                count += 1
            
            # Write the character
            chars[write] = cur
            write += 1
            
            # Write the count if it's greater than 1
            if count > 1:
                s_count = str(count)  # Convert count to string
                for c in s_count:     # Write each digit separately
                    chars[write] = c
                    write += 1
        
        return write  # Return new length of compressed array
```

**Step-by-Step Walkthrough (Example 1: `["a","a","b","b","c","c","c"]`):**

1. **Initialization:** `read=0, write=0, n=7`

2. **First Iteration (Group "aa"):**
   - `cur = 'a'`, count consecutive: `read=0→2, count=2`
   - Write 'a': `chars[0]='a', write=1`
   - Write count '2': `chars[1]='2', write=2`
   - Array state: `['a','2','b','b','c','c','c']`

3. **Second Iteration (Group "bb"):**
   - `cur = 'b'`, count consecutive: `read=2→4, count=2`
   - Write 'b': `chars[2]='b', write=3`
   - Write count '2': `chars[3]='2', write=4`
   - Array state: `['a','2','b','2','c','c','c']`

4. **Third Iteration (Group "ccc"):**
   - `cur = 'c'`, count consecutive: `read=4→7, count=3`
   - Write 'c': `chars[4]='c', write=5`
   - Write count '3': `chars[5]='3', write=6`
   - Array state: `['a','2','b','2','c','3','c']`

5. **Return:** `write=6` (first 6 characters form the compressed string)

**Step-by-Step Walkthrough (Example 3: Multi-digit Count `["a","b","b","b",...,"b"]` with 12 b's):**

1. First group "a": write 'a' at position 0, `write=1`
2. Second group "bbbbbbbbbbbb" (12 b's):
   - Write 'b': `chars[1]='b', write=2`
   - Convert 12 to string "12"
   - Write '1': `chars[2]='1', write=3`
   - Write '2': `chars[3]='2', write=4`
   - Compressed: `['a','b','1','2',...rest ignored...]`
   - Return 4

**Complexity Analysis:**

- **Time Complexity:** O(n) - Single pass through the array with the `read` pointer, plus at most O(n) work writing digits
- **Space Complexity:** O(1) - Only using two pointers, no auxiliary data structures (output array doesn't count as extra space)

**Why This Solution is Optimal:**

1. ✅ Meets the constant space constraint
2. ✅ Linear time complexity
3. ✅ In-place modification prevents memory waste
4. ✅ Elegantly handles multi-digit counts with string conversion

# Tags

Two Pointers | String Compression | In-place Modification | Array Manipulation


## Problem

https://leetcode.com/problems/largest-3-same-digit-number-in-string/description/

```
You are given a string num representing a large integer. An integer is good if it meets the following conditions:

It is a substring of num with length 3.
It consists of only one unique digit.
Return the maximum good integer as a string or an empty string "" if no such integer exists.

Note:

A substring is a contiguous sequence of characters within a string.
There may be leading zeroes in num or a good integer.

Example 1:

Input: num = "6777133339"
Output: "777"
Explanation: There are two distinct good integers: "777" and "333".
"777" is the largest, so we return "777".

Example 2:

Input: num = "2300019"
Output: "000"
Explanation: "000" is the only good integer.

Example 3:

Input: num = "42352338"
Output: ""
Explanation: No substring of length 3 consists of only one unique digit. Therefore, there are no good integers.

Constraints:

3 <= num.length <= 1000
num only consists of digits.
```

## Observations

1. **Problem Definition**: We need to find the largest "good integer" which is a substring of length 3 consisting of the same digit repeated 3 times.

2. **Key Insights**:
   - We only care about consecutive identical digits that appear at least 3 times in a row
   - Among all valid 3-digit sequences (like "777", "333", "000"), we want the lexicographically largest one
   - String comparison works naturally for this since "9" > "8" > ... > "1" > "0"

3. **Edge Cases**:
   - No valid 3-digit sequences exist → return empty string
   - Multiple valid sequences → return the maximum one
   - Leading zeros are allowed (e.g., "000" is valid)

4. **Algorithm Approach**:
   - Single pass through the string
   - Track consecutive identical characters
   - When we find 3 consecutive identical digits, add to candidates
   - Return the maximum candidate or empty string if none exist

## Solution

**Algorithm**: Single Pass with Counter

**Time Complexity**: O(n) where n is the length of the input string
**Space Complexity**: O(1) - at most 10 possible candidates (digits 0-9)

**Step-by-step breakdown**:

1. **Initialize Variables**:
   - `count = 0`: tracks consecutive identical characters
   - `prev = '#'`: stores the previous character (initialized to non-digit)
   - `candidates = []`: stores all valid 3-digit sequences found

2. **Main Loop Logic**:
   - For each character `c` in the string:
     - If `c == prev`: increment count (found another consecutive identical char)
     - If `count == 3`: we found a valid 3-digit sequence, add `c * 3` to candidates
     - If `c != prev`: reset count to 1 (start new sequence)
     - Update `prev = c` for next iteration

3. **Return Result**:
   - If no candidates found: return empty string
   - Otherwise: return `max(candidates)` (lexicographically largest)

**Example Walkthrough** with "6777133339":
```
c='6': count=1, prev='6', candidates=[]
c='7': count=1, prev='7', candidates=[]
c='7': count=2, prev='7', candidates=[]
c='7': count=3, prev='7', candidates=['777']
c='1': count=1, prev='1', candidates=['777']
c='3': count=1, prev='3', candidates=['777']
c='3': count=2, prev='3', candidates=['777']
c='3': count=3, prev='3', candidates=['777', '333']
c='3': count=4, prev='3', candidates=['777', '333']
c='9': count=1, prev='9', candidates=['777', '333']

Result: max(['777', '333']) = '777'
```

**Why This Works**:
- The algorithm efficiently detects all consecutive sequences of identical digits
- It only adds candidates when exactly 3 consecutive identical digits are found
- String comparison (`max()`) naturally gives us the lexicographically largest sequence
- Single pass ensures optimal time complexity

# Tags

- **String Manipulation**
- **Two Pointers / Sliding Window**
- **Greedy Algorithm**
- **Array/String Traversal**


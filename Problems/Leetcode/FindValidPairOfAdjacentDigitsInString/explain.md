## Problem

https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/description/

```
You are given a string s consisting only of digits. A valid pair is defined as two adjacent digits in s such that:

The first digit is not equal to the second.
Each digit in the pair appears in s exactly as many times as its numeric value.
Return the first valid pair found in the string s when traversing from left to right. If no valid pair exists, return an empty string.

Example 1:

Input: s = "2523533"

Output: "23"

Explanation:

Digit '2' appears 2 times and digit '3' appears 3 times. Each digit in the pair "23" appears in s exactly as many times as its numeric value. Hence, the output is "23".

Example 2:

Input: s = "221"

Output: "21"

Explanation:

Digit '2' appears 2 times and digit '1' appears 1 time. Hence, the output is "21".

Example 3:

Input: s = "22"

Output: ""

Explanation:

There are no valid adjacent pairs.
```

## Observations

1. **Problem Understanding**: We need to find the first valid adjacent pair of digits in a string where:
   - The two digits are different (a ≠ b)
   - Each digit appears in the string exactly as many times as its numeric value
   - For example, digit '3' should appear exactly 3 times in the string

2. **Key Insight**: The solution uses frequency counting to check the second condition efficiently.
   - Use `Counter` to count occurrences of each digit in the entire string
   - For each adjacent pair (a,b), check if `int(a) == frequency[a]` and `int(b) == frequency[b]`

3. **Algorithm Strategy**:
   - Pre-compute frequency of all digits using `Counter(list(s))`
   - Iterate through adjacent pairs from left to right
   - Return the first pair that satisfies both conditions

4. **Time Complexity**: O(n) where n is the length of string
   - O(n) to build the frequency counter
   - O(n) to iterate through adjacent pairs
   
5. **Space Complexity**: O(1) since we only store frequencies for digits 0-9

6. **Edge Cases**:
   - String with only identical digits → No valid pairs (condition 1 fails)
   - String where digit frequencies don't match their values → No valid pairs (condition 2 fails)
   - Empty or single character string → No adjacent pairs possible

## Solution

**Approach**: Single Pass with Frequency Pre-computation

**Algorithm**:
1. **Pre-process**: Count frequency of each digit using `Counter(list(s))`
2. **Iterate**: For each adjacent pair `s[i-1:i+1]` starting from index 1:
   - Extract digits `a = s[i-1]` and `b = s[i]`
   - **Check Condition 1**: `a != b` (different digits)
   - **Check Condition 2**: `int(a) == f[a]` and `int(b) == f[b]` (frequency matches value)
   - If both conditions satisfied, return the pair
3. **Return**: Empty string if no valid pair found

**Example Walkthrough** (`s = "2523533"`):
- Frequencies: {'2': 2, '5': 1, '3': 3}
- Check pair "25": '2' ≠ '5' ✓, but int('5') = 5 ≠ f['5'] = 1 ✗
- Check pair "52": '5' ≠ '2' ✓, but int('5') = 5 ≠ f['5'] = 1 ✗  
- Check pair "23": '2' ≠ '3' ✓, int('2') = 2 = f['2'] ✓, int('3') = 3 = f['3'] ✓ → Return "23"

# Tags

String, Hash Table, Frequency Count, Two Pointers


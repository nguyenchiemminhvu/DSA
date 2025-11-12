## Problem

https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/description/

```
You are given a string s consisting of lowercase English letters.

Your task is to find the maximum difference diff = freq(a1) - freq(a2) between the frequency of characters a1 and a2 in the string such that:

a1 has an odd frequency in the string.
a2 has an even frequency in the string.
Return this maximum difference.

Example 1:

Input: s = "aaaaabbc"

Output: 3

Explanation:

The character 'a' has an odd frequency of 5, and 'b' has an even frequency of 2.
The maximum difference is 5 - 2 = 3.

Example 2:

Input: s = "abcabcab"

Output: 1

Explanation:

The character 'a' has an odd frequency of 3, and 'c' has an even frequency of 2.
The maximum difference is 3 - 2 = 1.

Constraints:

3 <= s.length <= 100
s consists only of lowercase English letters.
s contains at least one character with an odd frequency and one with an even frequency.
```

## Observations

1. **Problem Understanding**: 
   - We need to find the maximum difference between an odd frequency and an even frequency
   - The difference is calculated as: `max_odd_frequency - min_even_frequency`
   - This maximizes the difference by using the largest odd frequency and smallest even frequency

2. **Guaranteed Constraints**: 
   - The problem guarantees at least one character with odd frequency and one with even frequency
   - This means we don't need to handle edge cases where no odd or even frequencies exist

3. **Frequency Analysis**:
   - Count frequency of each character in the string
   - Separate frequencies into odd and even categories
   - Find maximum among odd frequencies and minimum among even frequencies

4. **Mathematical Insight**:
   - To maximize `odd - even`, we want:
     - Largest possible odd frequency (maximum odd)
     - Smallest possible even frequency (minimum even)
   - This gives us the formula: `max(odd_frequencies) - min(even_frequencies)`

5. **Implementation Details**:
   - Use `Counter` for efficient frequency counting
   - Use bitwise AND (`val & 1`) to check if frequency is odd (more efficient than modulo)
   - Use modulo (`val % 2 == 0`) to check if frequency is even (for clarity)

## Solution

### Approach: Frequency Counting + Min/Max Finding

**Algorithm**:
1. **Count Frequencies**: Use `Counter` to count frequency of each character
2. **Separate by Parity**: Iterate through all frequencies and separate into odd/even groups
3. **Find Extremes**: 
   - Find maximum frequency among odd frequencies
   - Find minimum frequency among even frequencies
4. **Calculate Difference**: Return `max_odd - min_even`

**Example Walkthrough** (`s = "aaaaabbc"`):
1. **Frequency Count**: `{'a': 5, 'b': 2, 'c': 1}`
2. **Odd Frequencies**: `[5, 1]` → Maximum = 5
3. **Even Frequencies**: `[2]` → Minimum = 2  
4. **Result**: `5 - 2 = 3`

**Time Complexity**: O(n) where n is the length of string
- O(n) to count frequencies
- O(k) to find max/min where k is number of unique characters (k ≤ n)

**Space Complexity**: O(k) where k is the number of unique characters for the Counter

**Key Optimizations**:
- Using `val & 1` for odd check is slightly more efficient than `val % 2 == 1`
- `Counter(list(s))` can be simplified to `Counter(s)` - both work the same
- Generator expressions in max/min are memory efficient

# Tags
frequency-counting, hash-map, string-processing, math


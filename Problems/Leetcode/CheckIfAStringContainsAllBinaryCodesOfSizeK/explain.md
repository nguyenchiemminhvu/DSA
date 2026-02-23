## Problem

https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/description/

```
Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.

Example 1:
Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.

Example 2:
Input: s = "0110", k = 1
Output: true
Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring. 

Example 3:
Input: s = "0110", k = 2
Output: false
Explanation: The binary code "00" is of length 2 and does not exist in the array.

Constraints:
- 1 <= s.length <= 5 * 10^5
- s[i] is either '0' or '1'.
- 1 <= k <= 20
```

## Observations

1. **Total binary codes of length k**: For binary codes of length k, there are exactly `2^k` possible combinations (each position can be 0 or 1).

2. **Minimum string length required**: For a string to contain all binary codes of length k, it needs at least `2^k + k - 1` characters. This is because:
   - We need at least `2^k` substrings of length k
   - Substrings can overlap, so the minimum length is when they overlap maximally
   - However, checking this isn't necessary since we can just extract all substrings and count unique ones

3. **Sliding window approach**: We can use a sliding window of size k to extract all possible substrings of length k from the input string.

4. **Using a set for uniqueness**: A set data structure is perfect for tracking unique substrings, as it automatically handles duplicates.

5. **Early termination possibility**: If the string length is less than `2^k + k - 1`, we can immediately return false. However, the provided solution doesn't use this optimization.

## Solution

**Approach: Sliding Window + Hash Set**

The solution uses a sliding window technique combined with a hash set to track all unique binary codes of length k found in the string.

**Algorithm:**
1. Create an empty set `sub_arr` to store unique substrings of length k
2. Iterate through the string with a sliding window of size k:
   - For each position i from 0 to `n - k` (where n is the length of string s)
   - Extract substring `s[i:i+k]` and add it to the set
3. After processing all substrings, check if the set size equals `2^k` (calculated using bit shift: `1 << k`)
4. If the set contains exactly `2^k` unique substrings, all binary codes are present

**Time Complexity**: O(n * k)
- We iterate through n - k + 1 positions: O(n)
- Each substring extraction takes O(k) time
- Set operations (add, size check) are O(1) on average

**Space Complexity**: O(2^k * k)
- In the worst case, we store all `2^k` unique binary codes
- Each code has length k
- Total space: O(2^k * k)

**Why it works:**
- If every binary code of length k exists as a substring, the set will contain exactly `2^k` unique elements
- If any binary code is missing, the set will have fewer than `2^k` elements
- The set automatically handles duplicate substrings, so we only count unique codes

**Python Implementation:**
```python
class Solution:
    def hasAllCodes(self, s: str, k: int) -> bool:
        sub_arr = set()
        n = len(s)
        for i in range(n - k + 1):
            sub_arr.add(s[i:i+k])
        
        return len(sub_arr) == (1 << k)
```

**Optimization notes:**
- Early termination: Could add `if len(s) < (1 << k) + k - 1: return False` at the beginning
- Could also add early success: `if len(sub_arr) == (1 << k): break` inside the loop

# Tags
#sliding-window #hash-set #string #binary #bit-manipulation


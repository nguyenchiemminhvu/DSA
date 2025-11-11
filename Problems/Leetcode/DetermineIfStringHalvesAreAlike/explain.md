## Problem

https://leetcode.com/problems/determine-if-string-halves-are-alike/description/

```
You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.

Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.

Return true if a and b are alike. Otherwise, return false.

Example 1:

Input: s = "book"
Output: true
Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.

Example 2:

Input: s = "textbook"
Output: false
Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
Notice that the vowel o is counted twice.

Constraints:

2 <= s.length <= 1000
s.length is even.
s consists of uppercase and lowercase letters.
```

## Observations

1. **Problem Requirements:**
   - Split string `s` into two equal halves
   - Count vowels in each half (both lowercase and uppercase: 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U')
   - Return true if both halves have the same number of vowels

2. **Key Insights:**
   - String length is guaranteed to be even, so we can safely split into two equal parts
   - We don't need to actually store the halves - just iterate through indices
   - Instead of counting vowels in each half separately, we can use a single counter:
     - Increment for vowels in first half
     - Decrement for vowels in second half
     - If final count is 0, both halves have equal vowel counts

3. **Edge Cases:**
   - Minimum length is 2 (constraint), so no empty string concerns
   - Mixed case vowels are handled by checking both cases in the vowel set

## Solution

**Approach: Single Pass with Counter**

The solution uses an elegant counter approach:

1. **Initialize counter**: Start with `count = 0`

2. **First half processing** (indices 0 to n//2-1):
   - For each vowel found, increment the counter
   - This represents the vowel count in the first half

3. **Second half processing** (indices n//2 to n-1):
   - For each vowel found, decrement the counter
   - This subtracts the vowel count in the second half

4. **Final check**: If `count == 0`, both halves have equal vowel counts

**Time Complexity:** O(n) - single pass through the string
**Space Complexity:** O(1) - only using a counter variable

**Example walkthrough with s = "book":**
- First half "bo": 'o' is vowel → count = 1
- Second half "ok": 'o' is vowel → count = 1 - 1 = 0
- Result: count == 0 → true (both halves have 1 vowel each)

**Why this works:**
- If first half has `x` vowels and second half has `y` vowels
- Final count = x - y
- count == 0 means x == y (equal vowel counts)
- count != 0 means x != y (unequal vowel counts)

# Tags

`String` `Counting` `Two Pointers`


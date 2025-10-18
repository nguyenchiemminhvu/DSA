## Problem

https://leetcode.com/problems/longest-happy-string/description/

```
A string s is called happy if it satisfies the following conditions:

s only contains the letters 'a', 'b', and 'c'.
s does not contain any of "aaa", "bbb", or "ccc" as a substring.
s contains at most a occurrences of the letter 'a'.
s contains at most b occurrences of the letter 'b'.
s contains at most c occurrences of the letter 'c'.
Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".

A substring is a contiguous sequence of characters within a string.

Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.

Example 2:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It is the only correct answer in this case.

Constraints:

0 <= a, b, c <= 100
a + b + c > 0
```

## Observations

1. **Constraint Analysis**: A "happy string" cannot have three consecutive identical characters ('aaa', 'bbb', or 'ccc').

2. **Greedy Strategy**: To maximize the length, we should always try to use the character with the highest remaining count first, as this gives us more flexibility for future choices.

3. **Conflict Resolution**: When adding a character would create three consecutive identical characters, we need to use the character with the second-highest count instead.

4. **Max Heap Usage**: A max heap (priority queue) is perfect for this problem because:
   - We always need the character with the highest remaining count
   - After using a character, we need to reinsert it with updated count
   - The heap automatically maintains the ordering

5. **Edge Cases**: 
   - When we can't add the most frequent character (would create 3 consecutive), but no alternative exists
   - When all characters are exhausted

6. **String Padding**: Using `s = "##"` as initial padding and returning `s[2:]` is a clever trick to simplify boundary checks when looking at the last two characters.

## Solution

The algorithm uses a **greedy approach with a max heap**:

### Algorithm Steps:

1. **Initialize Max Heap**: Add all non-zero character counts to a max heap (using negative values since Python's heapq is a min heap)

2. **Greedy Selection Loop**:
   - Extract the character with the highest count
   - **Check Constraint**: If adding this character would create three consecutive identical characters:
     - Try to use the character with the second-highest count instead
     - If no alternative exists, terminate (we can't extend the string further)
   - **Add Character**: Append the selected character to the result
   - **Update Heap**: If the character still has remaining count, put it back in the heap

3. **Termination**: Continue until the heap is empty or we can't add any more characters

### Key Implementation Details:

- **Padding**: `s = "##"` allows us to safely check `s[-2] == s[-1] == first_letter` without boundary issues
- **Heap Operations**: Use negative counts for max heap behavior in Python's min heap
- **Constraint Check**: `s[-2] == s[-1] and s[-1] == first_letter` detects the forbidden pattern
- **Alternative Selection**: When the primary choice is blocked, use the second most frequent character

### Example Walkthrough:
For `a=1, b=1, c=7`:
1. Heap: `[(-7,'c'), (-1,'a'), (-1,'b')]`
2. Add 'c': `"##c"`, heap: `[(-6,'c'), (-1,'a'), (-1,'b')]`
3. Add 'c': `"##cc"`, heap: `[(-5,'c'), (-1,'a'), (-1,'b')]`
4. Can't add 'c' (would make "ccc"), use 'a': `"##cca"`, heap: `[(-5,'c'), (-1,'b')]`
5. Continue this pattern...

### Complexity:
- **Time**: O((a+b+c) × log 3) = O(a+b+c) since we have at most 3 elements in heap
- **Space**: O(1) constant space for the heap (max 3 elements)

## Tags

array, string, greedy, max heap
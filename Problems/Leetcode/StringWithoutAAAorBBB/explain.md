## Problem

https://leetcode.com/problems/string-without-aaa-or-bbb/

```
Given two integers a and b, return any string s such that:

s has length a + b and contains exactly a 'a' letters, and exactly b 'b' letters,
The substring 'aaa' does not occur in s, and
The substring 'bbb' does not occur in s.

Example 1:

Input: a = 1, b = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.

Example 2:

Input: a = 4, b = 1
Output: "aabaa"

Constraints:

0 <= a, b <= 100
It is guaranteed such an s exists for the given a and b.
```

## Observations

1. **Constraint Understanding**: We need to build a string of length `a + b` with exactly `a` 'a's and `b` 'b's, but we cannot have three consecutive identical characters ('aaa' or 'bbb').

2. **Greedy Strategy**: To avoid three consecutive characters, we should prioritize using the character with the higher remaining count. This ensures we don't get stuck with too many of one character at the end.

3. **Priority Queue Approach**: Using a max-heap (priority queue) helps us always pick the character with the highest remaining count first.

4. **Conflict Resolution**: When the last character in our result is the same as the character we want to add next, we need to use the other character instead to avoid creating three consecutive identical characters.

5. **Character Placement Logic**:
   - If we can safely add the most frequent character (no conflict), we can add up to 2 of them at once
   - If there's a conflict (same as last character), we must use the other character first
   - We only add 1 character when resolving conflicts to maintain balance

6. **Edge Cases**: 
   - When one character runs out completely
   - When we have a conflict but no alternative character available

## Solution

The solution uses a **greedy approach with a priority queue (max-heap)**:

### Algorithm Steps:

1. **Initialize Priority Queue**: Store both characters with their counts in a max-heap (using negative values since Python's heapq is a min-heap).

2. **Main Loop**: While we have characters remaining:
   - Pop the character with the highest count
   - **Check for Conflict**: If this character is the same as the last character in our result:
     - Use the other character instead (if available)
     - Add only 1 of the alternative character
     - Push both characters back if they still have remaining count
   - **No Conflict**: 
     - Add up to 2 of the current character (greedy choice)
     - This helps consume the more frequent character faster

3. **Termination**: Continue until no more characters can be added.

### Key Insights:

- **Why up to 2 characters?** Adding 2 at once when possible helps balance the counts and prevents getting stuck with too many of one character.
- **Why priority queue?** Always processing the most frequent character first ensures optimal distribution.
- **Conflict handling**: When we can't use the most frequent character, we use the alternative and add minimal amount (1) to maintain flexibility.

### Time Complexity: O((a+b) log 2) = O(a+b)
### Space Complexity: O(1) - only storing 2 characters in the heap

### Example Trace (a=4, b=1):
```
Initial: heap=[(-4,'a'), (-1,'b')], result=""
Step 1: Use 'a', add 2 → result="aa", heap=[(-2,'a'), (-1,'b')]
Step 2: Use 'a', conflict! Use 'b' → result="aab", heap=[(-2,'a')]  
Step 3: Use 'a', add 2 → result="aabaa", heap=[]
Final: "aabaa"
```

## Tags

array, string, greedy, priority queue
## Problem

https://leetcode.com/problems/construct-string-with-repeat-limit/

```
You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString using the characters of s such that no letter appears more than repeatLimit times in a row. You do not have to use all characters from s.

Return the lexicographically largest repeatLimitedString possible.

A string a is lexicographically larger than a string b if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b. If the first min(a.length, b.length) characters do not differ, then the longer string is the lexicographically larger one.

Example 1:

Input: s = "cczazcc", repeatLimit = 3
Output: "zzcccac"
Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
The letter 'a' appears at most 1 time in a row.
The letter 'c' appears at most 3 times in a row.
The letter 'z' appears at most 2 times in a row.
Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.

Example 2:

Input: s = "aababab", repeatLimit = 2
Output: "bbabaa"
Explanation: We use only some of the characters from s to construct the repeatLimitedString "bbabaa". 
The letter 'a' appears at most 2 times in a row.
The letter 'b' appears at most 2 times in a row.
Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
The string is the lexicographically largest repeatLimitedString possible so we return "bbabaa".
Note that the string "bbabaaa" is lexicographically larger but the letter 'a' appears more than 2 times in a row, so it is not a valid repeatLimitedString.

Constraints:

1 <= repeatLimit <= s.length <= 105
s consists of lowercase English letters.
```

## Observations

### Key Insights:
1. **Lexicographically largest**: We need to prioritize characters that appear later in the alphabet (z > y > x > ... > a)
2. **Repeat limit constraint**: No character can appear more than `repeatLimit` consecutive times
3. **Greedy approach**: Always try to use the largest available character first
4. **Break ties with alternation**: When we hit the repeat limit, we need to insert a different character to "break" the sequence

### Problem Analysis:
- We want to maximize lexicographical order, so we should use characters in descending order (z, y, x, ..., a)
- When we reach the repeat limit for a character, we must insert a different character before continuing with the original one
- We need to track frequency of each character to know how many times we can still use it
- A max-heap (priority queue) is perfect for always getting the largest available character

### Edge Cases:
- What if we run out of alternative characters to break a sequence?
- What if the last character in result is the same as the one we want to add next?
- What if we have remaining characters but can't use them due to repeat limit?

## Solution

### Algorithm Explanation:

The solution uses a **greedy approach with a max-heap (priority queue)** to construct the lexicographically largest string while respecting the repeat limit.

#### Step-by-Step Breakdown:

1. **Frequency Counting**:
   ```python
   freq = {}
   for c in s:
       freq[c] = freq.get(c, 0) + 1
   ```
   - Count frequency of each character in the input string

2. **Max-Heap Setup**:
   ```python
   pq = []
   for c, f in freq.items():
       heapq.heappush(pq, (-ord(c), f))
   ```
   - Use negative ASCII values to simulate max-heap (since Python's heapq is min-heap)
   - Higher ASCII values (later alphabet letters) get higher priority

3. **Greedy Construction**:
   ```python
   while pq:
       c, f = heapq.heappop(pq)
       c *= -1  # Convert back to positive ASCII
   ```
   - Always pick the lexicographically largest available character

4. **Handle Consecutive Character Limit**:
   ```python
   if len(res) > 0 and chr(c) == res[-1]:
       # Need to use a different character to break the sequence
       if pq:
           cc, ff = heapq.heappop(pq)
           cc *= -1
           res += chr(cc)
           ff -= 1
           if ff > 0:
               heapq.heappush(pq, (-cc, ff))
       else:
           break  # No more characters available to break sequence
   ```
   - If the last character in result is the same as current character, we need to insert a different one
   - Use the next largest available character to break the sequence
   - If no other character is available, we must stop

5. **Add Characters Respecting Repeat Limit**:
   ```python
   else:
       n = min(f, repeatLimit)
       res += chr(c) * n
       f -= n
   ```
   - Add up to `repeatLimit` consecutive characters
   - Update the remaining frequency

6. **Re-insert Remaining Characters**:
   ```python
   if f > 0:
       heapq.heappush(pq, (-c, f))
   ```
   - If we still have characters left, put them back in the heap for later use

### Time Complexity: O(n log k)
- n = length of string s
- k = number of unique characters (at most 26)
- Each character is pushed/popped from heap at most twice

### Space Complexity: O(k)
- Space for frequency map and priority queue
- k = number of unique characters

### Example Walkthrough:
For `s = "cczazcc"`, `repeatLimit = 3`:

1. Frequencies: {c: 4, z: 2, a: 1}
2. Heap: [(-122, 2), (-99, 4), (-97, 1)] → [(z, 2), (c, 4), (a, 1)]
3. Process z: add "zz" (use all 2 z's), result = "zz"
4. Process c: add "ccc" (use 3 out of 4 c's), result = "zzccc"
5. Process a: last char is 'c', different from 'a', so add "a", result = "zzcccaa"
6. Process remaining c: last char is 'a', different from 'c', so add "c", result = "zzcccac"

Final result: "zzcccac"

## Tags

array, string, greedy, hash table, priority queue, 
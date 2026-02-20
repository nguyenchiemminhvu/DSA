## Problem

https://leetcode.com/problems/maximize-the-confusion-of-an-exam/description/

```
A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false. 
He wants to confuse the students by maximizing the number of consecutive questions with the same answer 
(multiple trues or multiple falses in a row).

You are given a string answerKey, where answerKey[i] is the original answer to the ith question. 
In addition, you are given an integer k, the maximum number of times you may perform the following operation:

Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').

Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation 
at most k times.

Example 1:
Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".

Example 2:
Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.

Example 3:
Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT". 

Constraints:
- n == answerKey.length
- 1 <= n <= 5 * 10^4
- answerKey[i] is either 'T' or 'F'
- 1 <= k <= n
```

## Observations

1. **Sliding Window Problem**: We need to find the longest substring where we can make all characters the same with at most k flips.

2. **Key Insight**: Instead of thinking "which characters to flip", think about it as finding the longest window where the **minority character count ≤ k**. If we have a window with `count_t` T's and `count_f` F's, we can make them all the same character by flipping the minority, as long as `min(count_t, count_f) <= k`.

3. **No Need to Track Both Cases Separately**: We don't need separate passes for "make all T's" and "make all F's". By tracking both counts and checking `min(count_t, count_f) <= k`, we automatically handle both cases in one pass.

4. **Window Validity**: A window `[l, r]` is valid if we can flip at most k characters to make all characters the same. This happens when the count of the less frequent character is at most k.

## Solution

### Approach: Sliding Window

We use the **sliding window** technique with two pointers:

1. **Expand Window**: Move right pointer and include characters, updating counts for T's and F's.

2. **Maintain Valid Window**: A window is valid when `min(count_t, count_f) <= k`, meaning we can flip the minority characters to match the majority.

3. **Shrink Window**: When the window becomes invalid (`min(count_t, count_f) > k`), move the left pointer to shrink the window until it becomes valid again.

4. **Track Maximum**: Keep track of the maximum window size seen.

### Algorithm

```python
class Solution:
    def maxConsecutiveAnswers(self, keys: str, k: int) -> int:
        n = len(keys)
        res = 0
        count_t = 0
        count_f = 0
        l = 0
        
        for r in range(n):
            # Expand window: add keys[r]
            if keys[r] == 'T':
                count_t += 1
            else:
                count_f += 1
            
            # Shrink window if invalid
            # Window is invalid when we need to flip more than k characters
            while min(count_t, count_f) > k:
                if keys[l] == 'T':
                    count_t -= 1
                else:
                    count_f -= 1
                l += 1
            
            # Update result with current valid window size
            if min(count_t, count_f) <= k:
                res = max(res, r - l + 1)
        
        return res
```

### Complexity Analysis

- **Time Complexity**: O(n) where n is the length of the answer key. Each character is visited at most twice (once by right pointer, once by left pointer).

- **Space Complexity**: O(1) as we only use a constant amount of extra space (two counters and a few variables).

### Why This Works

Consider a window with 7 T's and 3 F's:
- If k = 3, we can flip all 3 F's to T's → get 10 consecutive T's ✓
- If k = 2, we can't flip all F's, so this window is invalid ✗

The key insight is that we want to maximize the window where the **minority count ≤ k**, because we'll flip those minority characters to match the majority.

# Tags
`Sliding Window`, `Two Pointers`, `String`


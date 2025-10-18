## Problem

https://leetcode.com/problems/maximum-swap/

```
You are given an integer num. You can swap two digits at most once to get the maximum valued number.

Return the maximum valued number you can get.

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.

Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.

Constraints:

0 <= num <= 108
```

## Observations

1. **Goal**: Maximize the number by swapping at most two digits once.

2. **Key Insight**: To maximize the number, we want to place the largest possible digit in the leftmost position possible.

3. **Strategy**: 
   - Scan from left to right to find the first position where a larger digit exists to the right
   - Among all larger digits to the right, choose the largest one that appears rightmost (to maximize the swap benefit)
   - If multiple digits have the same maximum value, choose the rightmost one to preserve the original order of other digits

4. **Edge Cases**:
   - Already sorted in descending order (e.g., 9973) → No swap needed
   - Single digit → No swap possible
   - All digits are the same → No beneficial swap

5. **Examples**:
   - `2736`: First position (2) can be improved by swapping with 7 → `7236`
   - `9973`: Already in optimal form, no beneficial swap
   - `1234`: Swap 1 with 4 → `4231`

## Solution

The solution uses a **greedy approach with rightmost maximum selection**:

### Algorithm Steps:

1. **Convert to character array**: `s = list(str(num))` for easy digit manipulation

2. **Left-to-right scan**: For each position `left`:
   - Extract the substring from current position to end: `s_right = s[left:]`
   - Find the maximum digit in this substring
   - Locate the **rightmost occurrence** of this maximum digit using reverse indexing

3. **Rightmost maximum strategy**:
   ```python
   reverse_s_right = s_right[::-1]
   max_idx = len(s_right) - 1 - reverse_s_right.index(max(s_right))
   ```
   - Reverse the substring to find the rightmost occurrence of max digit
   - Convert back to original index using `len(s_right) - 1 - reverse_index`

4. **Swap condition**: Only swap if:
   - `max_idx > 0` (maximum digit is not at the first position)
   - `s_right[0] != s_right[max_idx]` (digits are different)

5. **Early termination**: Break after the first beneficial swap is made

### Why Rightmost Maximum?

Consider `54321`:
- At position 0: max digit in `54321` is `5`, but it's already at position 0
- At position 1: max digit in `4321` is `4`, but it's already at position 0 of substring
- Continue until no beneficial swap found

Consider `1993`:
- At position 0: max digit in `1993` is `9`
- There are two `9`s at indices 1 and 2 in the substring
- Choose the rightmost `9` (index 2) to get `9913` instead of `9193`

### Time Complexity: O(n²)
- Outer loop: O(n) positions
- For each position: O(n) to find max and locate rightmost occurrence
- Overall: O(n²) where n is the number of digits

### Space Complexity: O(n)
- Character array conversion and substring operations

### Key Insights:
- **Greedy choice**: Always try to improve the leftmost position first
- **Rightmost selection**: Among equal maximum digits, choose the rightmost one
- **Single pass optimization**: Stop after the first beneficial swap
- **In-place swapping**: Modify the array directly for efficiency

## Tags

array, string, greedy
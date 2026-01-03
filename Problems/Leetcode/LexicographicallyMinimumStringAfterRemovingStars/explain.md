## Problem

https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/description/

```
<problem_description>
```

## Observations

1. **Greedy Approach**: When we encounter a '*', we should always remove the smallest character to its left. This ensures we keep larger characters when possible, making the result lexicographically smaller.

2. **Multiple Occurrences**: If there are multiple instances of the smallest character, we can delete any of them. The key insight is that we should track indices to maintain proper ordering.

3. **Order Matters**: Characters appear in a specific order in the string. When we remove characters, we need to preserve the relative order of remaining characters.

4. **Two-Pass Strategy**: 
   - First pass: Mark which indices to keep (process deletions)
   - Second pass: Reconstruct the string from kept indices

## Solution

**Approach: Multiple Stacks (One per Character)**

**Key Idea**: Use 26 stacks (one for each letter a-z) to track the indices of each character. This allows O(1) access to the smallest available character.

**Algorithm**:

1. **Initialize**: Create 26 empty stacks, one for each lowercase letter
   
2. **First Pass - Process each character**:
   - If character is `'*'`:
     - Find the first non-empty stack (from 'a' to 'z')
     - Pop from that stack (removes the index of the smallest character)
   - If character is a letter:
     - Push its index onto the corresponding stack
     
3. **Second Pass - Reconstruct**:
   - Collect all remaining indices from all stacks into a set
   - Iterate through original string and keep characters whose indices are in the set

**Time Complexity**: O(26 × n) = O(n)
- Processing each character: O(26) in worst case to find smallest character
- Reconstructing string: O(n)

**Space Complexity**: O(n)
- 26 stacks collectively store up to n indices
- Result set stores remaining indices

**Why It Works**:
- Stacks are ordered by index (when we push), so we naturally get the order of characters
- By organizing stacks alphabetically (index 0 = 'a', index 1 = 'b', etc.), we can quickly find the smallest character by checking stacks from left to right
- Popping removes the most recent occurrence of that character, which is valid since any occurrence can be removed

# Tags
`stack` `greedy` `string` `hash-table`


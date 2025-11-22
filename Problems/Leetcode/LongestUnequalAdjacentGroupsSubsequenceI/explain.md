## Problem

https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/

```
You are given a string array words and a binary array groups both of length n.

A subsequence of words is alternating if for any two consecutive strings in the sequence, their corresponding elements at the same indices in groups are different (that is, there cannot be consecutive 0 or 1).

Your task is to select the longest alternating subsequence from words.

Return the selected subsequence. If there are multiple answers, return any of them.

Note: The elements in words are distinct.

Example 1:

Input: words = ["e","a","b"], groups = [0,0,1]

Output: ["e","b"]

Explanation: A subsequence that can be selected is ["e","b"] because groups[0] != groups[2]. Another subsequence that can be selected is ["a","b"] because groups[1] != groups[2]. It can be demonstrated that the length of the longest subsequence of indices that satisfies the condition is 2.

Example 2:

Input: words = ["a","b","c","d"], groups = [1,0,1,1]

Output: ["a","b","c"]

Explanation: A subsequence that can be selected is ["a","b","c"] because groups[0] != groups[1] and groups[1] != groups[2]. Another subsequence that can be selected is ["a","b","d"] because groups[0] != groups[1] and groups[1] != groups[3]. It can be shown that the length of the longest subsequence of indices that satisfies the condition is 3.

Constraints:

1 <= n == words.length == groups.length <= 100
1 <= words[i].length <= 10
groups[i] is either 0 or 1.
words consists of distinct strings.
words[i] consists of lowercase English letters.
```

## Observations

1. **Greedy Strategy**: Since we want the longest alternating subsequence, we can greedily select elements. The optimal approach is to always keep the first element and then include any subsequent element that has a different group value from the previously selected one.

2. **Sequential Processing**: We don't need complex algorithms like dynamic programming. A single pass through the array while maintaining the alternating property gives us the optimal solution.

3. **In-place Filtering**: The solution uses a two-pointer technique to filter elements in-place, which is memory efficient.

4. **Key Insight**: The problem reduces to removing consecutive elements with the same group value, keeping the first occurrence of each consecutive group.

## Solution

The solution uses an elegant in-place filtering approach:

### Algorithm Steps:

1. **Create Index-Value Pairs**: 
   ```python
   arr = [(val, i) for i, val in enumerate(groups)]
   ```
   Store both the group value and original index to maintain word mapping.

2. **In-place Filtering with Two Pointers**:
   - `ia` (insertion pointer): tracks where the next valid element should be placed
   - `i` (scanning pointer): iterates through all elements
   - When `arr[i][0] != arr[ia][0]` (different group values), we:
     - Increment `ia` to the next insertion position
     - Swap current element to position `ia`

3. **Extract Result**: 
   - Keep only the first `ia + 1` elements (valid alternating sequence)
   - Map back to original words using stored indices

### Example Walkthrough:
For `words = ["a","b","c","d"]`, `groups = [1,0,1,1]`:

- Initial: `arr = [(1,0), (0,1), (1,2), (1,3)]`
- After filtering: `arr = [(1,0), (0,1), (1,2)]` 
- Result: `["a", "b", "c"]`

### Time Complexity: O(n) - single pass through the array
### Space Complexity: O(n) - for the pairs array

The solution is optimal because any alternating subsequence must follow this greedy pattern - we cannot skip a valid alternating element and find a longer sequence later.

# Tags

array
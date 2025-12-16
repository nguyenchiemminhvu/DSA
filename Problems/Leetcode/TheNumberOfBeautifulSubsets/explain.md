## Problem

https://leetcode.com/problems/the-number-of-beautiful-subsets/

```
You are given an array nums of positive integers and a positive integer k.

A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.

Return the number of non-empty beautiful subsets of the array nums.

A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. 
Two subsets are different if and only if the chosen indices to delete are different.

Example 1:
Input: nums = [2,4,6], k = 2
Output: 4
Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
It can be proved that there are only 4 beautiful subsets in the array [2,4,6].

Example 2:
Input: nums = [1], k = 1
Output: 1
Explanation: The beautiful subset of the array nums is [1].
It can be proved that there is only 1 beautiful subset in the array [1].

Constraints:
1 <= nums.length <= 18
1 <= nums[i], k <= 1000
```

## Observations

1. **Subset Generation**: We need to explore all possible non-empty subsets of the array, which means we're dealing with a power set problem (2^n total subsets).

2. **Constraint Check**: A subset is "beautiful" if no two elements have an absolute difference equal to k. This means for any element `x` in the subset, neither `x - k` nor `x + k` can be present.

3. **Small Input Size**: With `nums.length <= 18`, the maximum number of subsets is 2^18 = 262,144, which is manageable for backtracking approaches.

4. **Conflict Detection**: For each number we want to add, we only need to check two specific values: `val - k` and `val + k`. We don't need to check all other elements.

5. **Sorting Benefit**: Sorting the array doesn't change the subsets but can help with optimization in some approaches (though not strictly necessary for this solution).

## Solution

### Approach: DFS with Backtracking

The solution uses depth-first search (DFS) with backtracking to explore all possible subsets while maintaining the "beautiful" constraint.

**Key Components:**

1. **Frequency Map (`used`)**: A `defaultdict(int)` that tracks which numbers are currently in the subset being constructed. The value represents the count/frequency of each number.

2. **DFS Function**: Explores two choices at each position:
   - **Option 1**: Skip the current element and move to the next
   - **Option 2**: Include the current element (if valid) and move to the next

3. **Validity Check**: Before adding `nums[i]`, we verify:
   - `used[val - k] == 0`: The number `val - k` is not in current subset
   - `used[val + k] == 0`: The number `val + k` is not in current subset

**Algorithm Steps:**

```
1. Sort the array (optional, for consistency)
2. Initialize frequency map and result counter
3. Start DFS from index 0:
   a. Base case: If we've processed all elements, return
   b. Skip current element: recurse to next index
   c. Try to include current element:
      - Check if val-k and val+k are NOT in current subset
      - If valid:
        * Add val to frequency map
        * Increment result (count this new subset)
        * Recurse to next index
        * Backtrack: remove val from frequency map
4. Return total count
```

**Why It Works:**

- By exploring both choices (skip/take) at each position, we generate all possible subsets
- The frequency map ensures we only count valid "beautiful" subsets
- Incrementing `res` when we successfully add an element counts each non-empty subset exactly once
- Backtracking allows us to reuse the same frequency map for different subset explorations

**Example Walkthrough:**

For `nums = [2,4,6], k = 2`:

```
Start: used = {}, res = 0

DFS(0): Consider num=2
  - Skip 2: DFS(1)
  - Take 2: used={2:1}, res=1, DFS(1)
    
    DFS(1): Consider num=4
      - Skip 4: DFS(2)
      - Take 4: Check used[2]=1 (4-2=2), invalid! Skip
    
    DFS(1) (from skip branch): Consider num=4
      - Skip 4: DFS(2)
      - Take 4: used={4:1}, res=2, DFS(2)
        
        DFS(2): Consider num=6
          - Skip 6: return
          - Take 6: Check used[4]=1 (6-2=4), invalid! Skip
        
        DFS(2) (from skip branch): Consider num=6
          - Skip 6: return
          - Take 6: used={6:1}, res=3, return
          
DFS(0) (continuing from skip 2 branch):
  - Take 6: used={2:1,6:1}, res=4, DFS(1)
    ...
```

Final count: 4 beautiful subsets: [2], [4], [6], [2,6]

**Time Complexity**: O(2^n) where n is the length of nums, as we explore all possible subsets.

**Space Complexity**: O(n) for the recursion stack and the frequency map.

# Tags
#backtracking #dfs #subsets #hash-map #recursion


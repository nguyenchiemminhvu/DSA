## Problem

https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/

```
There are n people that are split into some unknown number of groups. Each person is labeled with a unique ID from 0 to n - 1.

You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.

Return a list of groups such that each person i is in a group of size groupSizes[i].

Each person should appear in exactly one group, and every person must be in a group. If there are multiple answers, return any of them. It is guaranteed that there will be at least one valid solution for the given input.

Example 1:

Input: groupSizes = [3,3,3,3,3,1,3]
Output: [[5],[0,1,2],[3,4,6]]
Explanation: 
The first group is [5]. The size is 1, and groupSizes[5] = 1.
The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] = groupSizes[2] = 3.
The third group is [3,4,6]. The size is 3, and groupSizes[3] = groupSizes[4] = groupSizes[6] = 3.
Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].

Example 2:

Input: groupSizes = [2,1,3,3,3,2]
Output: [[1],[0,5],[2,3,4]]

Constraints:

groupSizes.length == n
1 <= n <= 500
1 <= groupSizes[i] <= n
```

## Observations

1. **Each person has a specific group size requirement**: Person `i` must be in a group of exactly `groupSizes[i]` people.

2. **Greedy grouping strategy**: Since we need to form groups of specific sizes, we can greedily group people with the same group size requirements together.

3. **No overlap constraint**: Each person appears in exactly one group, so once we place someone in a group, they're done.

4. **Guaranteed solution**: The problem states there's always at least one valid solution, meaning the input is always valid.

5. **Order doesn't matter**: We can return any valid grouping, so we don't need to worry about maintaining the original order of people.

6. **Key insight**: If we sort people by their group size requirements, we can process them in chunks of the required size.

## Solution

1. **Create pairs**: First, we create pairs of `(group_size, person_index)` for each person. This allows us to track both the required group size and the original person ID.

2. **Sort by group size**: We sort the pairs by group size (first element of each pair). This brings together all people who need the same group size.

3. **Process in chunks**: We iterate through the sorted pairs and process them in chunks:
   - At position `i`, we look at `pairs[i][0]` to get the required group size
   - We take exactly that many people starting from position `i`
   - We extract just the person indices (second element of each pair) to form a group

4. **Move to next chunk**: We advance `i` by the size of the group we just created and repeat.

### Example walkthrough:
For `groupSizes = [3,3,3,3,3,1,3]`:

1. **pairs**: `[(3,0), (3,1), (3,2), (3,3), (3,4), (1,5), (3,6)]`
2. **After sorting**: `[(1,5), (3,0), (3,1), (3,2), (3,3), (3,4), (3,6)]`
3. **Processing**:
   - `i=0`: Take 1 person → `[5]`, `i` becomes 1
   - `i=1`: Take 3 people → `[0,1,2]`, `i` becomes 4  
   - `i=4`: Take 3 people → `[3,4,6]`, `i` becomes 7
4. **Result**: `[[5], [0,1,2], [3,4,6]]`

### Time Complexity: O(n log n) due to sorting
### Space Complexity: O(n) for the pairs array and result

## Tags

array, greedy
## Problem

https://leetcode.com/problems/find-the-town-judge/description/

```
In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

The town judge trusts nobody.
Everybody (except for the town judge) trusts the town judge.
There is exactly one person that satisfies properties 1 and 2.
You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.

Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

Example 1:

Input: n = 2, trust = [[1,2]]
Output: 2

Example 2:

Input: n = 3, trust = [[1,3],[2,3]]
Output: 3

Example 3:

Input: n = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1

Constraints:

1 <= n <= 1000
0 <= trust.length <= 104
trust[i].length == 2
All the pairs of trust are unique.
ai != bi
1 <= ai, bi <= n
```

## Observations

1. **Special case**: If `n = 1`, there's only one person who must be the judge (no one to trust or be trusted by).

2. **Trust relationships**: Each `trust[i] = [a, b]` means person `a` trusts person `b`.

3. **Judge properties**:
   - The judge trusts **nobody** (out-degree = 0)
   - **Everyone else** trusts the judge (in-degree = n-1)
   - There's exactly **one** such person

4. **Graph perspective**: This is essentially finding a node with:
   - In-degree = n-1 (everyone trusts them)
   - Out-degree = 0 (they trust nobody)

5. **Counting approach**: We can solve this by counting incoming and outgoing trust relationships for each person.

## Solution

1. **Base case**: If `n = 1`, return 1 (only one person exists, must be judge)

2. **Initialize counters**:
   - `count_in[i]`: Number of people who trust person `i`
   - `count_out[i]`: Number of people that person `i` trusts
   - Size `n+1` to use 1-based indexing directly

3. **Count relationships**: For each trust relationship `[a, b]`:
   - Increment `count_in[b]` (person b gains a trusting relationship)
   - Increment `count_out[a]` (person a trusts someone)

4. **Find the judge**: Look for person `i` where:
   - `count_in[i] == n-1` (everyone except themselves trusts them)
   - `count_out[i] == 0` (they trust nobody)

5. **Return result**: Return the judge's label, or -1 if no judge exists

**Time Complexity**: O(n + trust.length) - linear scan through trust array and people
**Space Complexity**: O(n) - two arrays of size n+1

**Key insight**: The judge is the unique person who is trusted by exactly n-1 people and trusts nobody themselves.

# Tags

Graph, Array, Counting, In-degree/Out-degree


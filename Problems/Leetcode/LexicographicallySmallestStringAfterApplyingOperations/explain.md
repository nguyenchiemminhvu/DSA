## Problem

https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/description/

```
You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.

You can apply either of the following two operations any number of times and in any order on s:

Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.

Example 1:

Input: s = "5525", a = 9, b = 2
Output: "2050"
Explanation: We can apply the following operations:
Start:  "5525"
Rotate: "2555"
Add:    "2454"
Add:    "2353"
Rotate: "5323"
Add:    "5222"
Add:    "5121"
Rotate: "2151"
Add:    "2050"​​​​​
There is no way to obtain a string that is lexicographically smaller than "2050".

Example 2:

Input: s = "74", a = 5, b = 1
Output: "24"
Explanation: We can apply the following operations:
Start:  "74"
Rotate: "47"
​​​​​​​Add:    "42"
​​​​​​​Rotate: "24"​​​​​​​​​​​​
There is no way to obtain a string that is lexicographically smaller than "24".

Example 3:

Input: s = "0011", a = 4, b = 2
Output: "0011"
Explanation: There are no sequence of operations that will give us a lexicographically smaller string than "0011".

Constraints:

2 <= s.length <= 100
s.length is even.
s consists of digits from 0 to 9 only.
1 <= a <= 9
1 <= b <= s.length - 1
```

## Observations

1. **Two Operations Available:**
   - **Add Operation**: Add `a` to all digits at odd indices (1, 3, 5, ...). Digits wrap around after 9 (modulo 10).
   - **Rotate Operation**: Right rotate the string by `b` positions.

2. **Key Insights:**
   - We can apply these operations any number of times in any order.
   - The problem asks for the lexicographically smallest string possible.
   - Since we can apply operations unlimited times, we need to explore all possible states reachable from the initial string.

3. **State Space Analysis:**
   - The add operation only affects odd indices, and since digits are modulo 10, each odd position has at most 10 different values.
   - The rotate operation cycles through different rotations of the string.
   - The total number of unique states is finite, so we can use BFS to explore all reachable states.

4. **Important Properties:**
   - **Add Operation**: Only affects odd-indexed positions, so even-indexed positions remain unchanged by this operation.
   - **Rotate Operation**: Changes the positions of all digits but doesn't change their values.
   - **Finite State Space**: Since string length is at most 100 and each position has 10 possible digits, the state space is bounded.

5. **BFS Approach Rationale:**
   - Since we want to find all possible strings we can generate, BFS will systematically explore all reachable states.
   - We use a set to avoid revisiting the same state (string configuration).
   - After exploring all states, we simply return the lexicographically smallest one.

## Solution

**Algorithm: BFS State Space Exploration**

The solution uses BFS to explore all possible string states that can be reached by applying the two operations:

### Step-by-Step Breakdown:

1. **Initialization:**
   - Convert the input string to a list of integers for easier manipulation.
   - Use a set (`in_set`) to track visited states and avoid cycles.
   - Use a queue for BFS traversal.
   - Maintain a list of all reachable candidates.

2. **BFS Exploration:**
   - For each current state, apply both operations to generate new states:
     - **Add Operation**: Add `a` to all odd-indexed digits (modulo 10).
     - **Rotate Operation**: Right rotate the array by `b` positions.
   - Add new unique states to the queue and visited set.
   - Continue until all reachable states are explored.

3. **Find Minimum:**
   - Convert all candidate integer arrays back to strings.
   - Return the lexicographically smallest string.

### Code Analysis:

```python
def operation_add(arr: List[int]) -> None:
    for i in range(1, len(arr), 2):  # Only odd indices
        arr[i] = (arr[i] + a) % 10   # Add a, wrap around at 10

def operation_rotate(arr: List[int]) -> None:
    arr[:] = arr[-b:] + arr[:-b]     # Right rotate by b positions
```

### Time & Space Complexity:

- **Time Complexity**: O(N × S) where N is the string length and S is the number of unique states reachable. In worst case, S could be up to 10^N, but typically much smaller due to the constraints of the operations.
- **Space Complexity**: O(S) for storing all reachable states in the set and candidates list.

### Why This Works:

1. **Completeness**: BFS ensures we explore all possible states reachable from the initial string.
2. **Optimality**: Since we collect all possible states and return the minimum, we're guaranteed to find the lexicographically smallest string.
3. **Termination**: The finite state space ensures the algorithm terminates.

### Alternative Approaches:

- **Mathematical Analysis**: For specific patterns of `a` and `b`, we might be able to derive the answer mathematically without full state exploration.
- **Optimized BFS**: We could potentially prune the search space by stopping early if we find a string starting with '0's, but the current approach is safer and more general.

## Tags

array, string, hash table, BFS, DFS
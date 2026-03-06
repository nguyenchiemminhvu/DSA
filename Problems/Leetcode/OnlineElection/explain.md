## Problem

https://leetcode.com/problems/online-election/description/

You are given two integer arrays `persons` and `times`. In an election, the `i`-th vote was cast for `persons[i]` at time `times[i]`.

For each query at a time `t`, find the person that was **leading the election at time `t`**. Votes cast at time `t` count towards the query. In the case of a tie, the **most recent vote** (among tied candidates) wins.

Implement the `TopVotedCandidate` class:
- `TopVotedCandidate(int[] persons, int[] times)` — Initializes the object with the `persons` and `times` arrays.
- `int q(int t)` — Returns the number of the person leading the election at time `t`.

**Example:**
```
Input:
["TopVotedCandidate", "q", "q", "q", "q", "q", "q"]
[[[0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30]], [3], [12], [25], [15], [24], [8]]

Output: [null, 0, 1, 1, 0, 0, 1]
```

**Constraints:**
- `1 <= persons.length <= 5000`
- `times.length == persons.length`
- `0 <= persons[i] < persons.length`
- `0 <= times[i] <= 10^9`
- `times` is sorted in strictly increasing order
- `times[0] <= t <= 10^9`
- At most `10^4` calls will be made to `q`

## Observations

- The `times` array is **strictly increasing**, which means it is already sorted — this is a key property that enables binary search.
- Each vote changes the state of the "current leader". We can precompute the leader **at every recorded time point** and store it.
- For a query `t`, we need the leader at the **latest recorded time ≤ t**. Since `times` is sorted, this is exactly the rightmost index `i` such that `times[i] <= t` — a classic **upper_bound - 1** binary search.
- Tie-breaking: if a new vote ties the current top vote count, the **most recent voter wins**. This means we update the leader whenever a candidate's count is `>=` the current top (not strictly greater).

## Solution

**Preprocessing (constructor):**

Iterate through all `(person, time)` pairs and maintain a running vote frequency map and the current top candidate. After processing each vote, record the pair `(time, current_leader)` in an array `arr`.

Tie-breaking is handled by updating `top_person = person` when `freq[person] >= top_vote` (since the current vote is the most recent among ties).

**Query (`q(t)`):**

Use binary search (upper bound) on `arr` to find the last entry whose time is `<= t`. Return the leader stored at that index.

- Preprocessing: $O(n)$ time, $O(n)$ space
- Each query: $O(\log n)$ time

```python
from collections import defaultdict
from typing import List

class TopVotedCandidate:

    def __init__(self, persons: List[int], times: List[int]):
        self.arr = []  # (time, top_person)
        freq = defaultdict(int)
        top_vote = 0
        top_person = -1
        for person, t in zip(persons, times):
            freq[person] += 1
            if freq[person] >= top_vote:
                top_vote = freq[person]
                top_person = person
            self.arr.append((t, top_person))

    def q(self, t: int) -> int:
        # Find rightmost index where arr[i][0] <= t
        left, right = 0, len(self.arr) - 1
        while left < right:
            mid = (left + right + 1) // 2
            if self.arr[mid][0] <= t:
                left = mid
            else:
                right = mid - 1
        return self.arr[left][1]
```

# Tags
`Binary Search` `Design` `Array`


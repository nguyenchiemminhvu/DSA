## Problem

https://leetcode.com/problems/queue-reconstruction-by-height/description/

You are given an array `people` where `people[i] = [hi, ki]` represents a person of height `hi` with exactly `ki` other people in front who have a height **greater than or equal to** `hi`. Reconstruct and return the original queue.

**Example:**
```
Input:  [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
```

---

## Observations

**1. People with k=0 are the easiest to place first.**  
If `k=0`, nobody taller or equal stands in front of you. We can collect all such people and sort them by height **ascending**. This ordering is necessary: if a taller k=0 person were placed before a shorter k=0 person, the shorter one would have a taller-or-equal person in front, violating its `k=0` constraint.

```
k=0 group from example: [7,0], [5,0]
Sorted ascending by height → [[5,0], [7,0]]  ✓
```

**2. After placing the k=0 group, process remaining people tallest-first.**  
For a person `[h, k]` being inserted into the current result:
- All **already-inserted** people have height ≥ `h` (because we sort others by height descending).
- All **not-yet-inserted** people have height ≤ `h` — they will **not** count toward `h`'s `k` when inserted later.

This means at insertion time, the only people who could "count" as taller-or-equal are already in the result, and we can precisely locate the right slot.

**3. Finding the insertion position.**  
Scan through the current result. Count how many people have height ≥ `h`. As soon as that count reaches `k`, insert `[h, k]` right after that position — there are now exactly `k` taller-or-equal people in front.

---

## Solution Walkthrough

```python
class Solution:
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
        n = len(people)

        zero = []
        others = []
        for p in people:
            if p[1] == 0:
                zero.append(p)
            else:
                others.append(p)
        
        zero.sort(key=lambda x: x[0])            # sort k=0 group by height ascending
        others.sort(key=lambda x: (-x[0], x[1])) # sort others: height desc, then k asc

        res = zero[:]
        for p in others:
            count = 0
            for i in range(len(res)):
                if p[0] <= res[i][0]:   # res[i] is taller or equal to p
                    count += 1
                if count == p[1]:       # found the k-th taller-or-equal person
                    res.insert(i + 1, p)
                    break
        return res
```

**Step-by-step on Example 1:** `[[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]`

| Step | Processing | Result |
|------|-----------|--------|
| Init | zero = [[5,0],[7,0]], others sorted = [[7,1],[6,1],[5,2],[4,4]] | `[[5,0],[7,0]]` |
| [7,1] | Count res[1]=[7,0] → count=1==k, insert after idx 1 | `[[5,0],[7,0],[7,1]]` |
| [6,1] | Count res[1]=[7,0] → count=1==k, insert after idx 1 | `[[5,0],[7,0],[6,1],[7,1]]` |
| [5,2] | res[0]=5≥5 → c=1; res[1]=7≥5 → c=2==k, insert after idx 1 | `[[5,0],[7,0],[5,2],[6,1],[7,1]]` |
| [4,4] | All of res[0..3] ≥ 4 → c=4==k at idx 3, insert after | `[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]` ✓ |

---

## Complexity

| | |
|---|---|
| **Time** | O(n²) — for each of the n persons, we scan and insert into a list in O(n) |
| **Space** | O(n) — for the result array |

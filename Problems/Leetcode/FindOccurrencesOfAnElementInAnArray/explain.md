## Problem

https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/description/

Given an integer array `nums`, an integer array `queries`, and an integer `x`.

For each `queries[i]`, find the index of the `queries[i]`th occurrence of `x` in `nums`. If there are fewer than `queries[i]` occurrences of `x`, the answer should be `-1` for that query.

Return an integer array `answer` containing the answers to all queries.

### Examples

**Example 1:**
- Input: `nums = [1,3,1,7]`, `queries = [1,3,2,4]`, `x = 1`
- Output: `[0,-1,2,-1]`
- Explanation:
  - Query 1: the 1st occurrence of `1` is at index `0`.
  - Query 2: only 2 occurrences exist → `-1`.
  - Query 3: the 2nd occurrence of `1` is at index `2`.
  - Query 4: only 2 occurrences exist → `-1`.

**Example 2:**
- Input: `nums = [1,2,3]`, `queries = [10]`, `x = 5`
- Output: `[-1]`
- Explanation: `5` doesn't exist in `nums` → `-1`.

### Constraints

- `1 <= nums.length, queries.length <= 10^5`
- `1 <= queries[i] <= 10^5`
- `1 <= nums[i], x <= 10^4`

## Observations

1. **Pre-collect occurrence indices**: Instead of scanning `nums` for every query, we can do a single pass over `nums` and collect all indices where `nums[i] == x` into a list `occurrences`. This reduces repeated work.

2. **1-based query index**: Each `queries[i]` is 1-based (i.e., "the k-th occurrence"), so the corresponding index in `occurrences` is `queries[i] - 1` (0-based).

3. **Bounds check**: If `queries[i] > len(occurrences)`, there are not enough occurrences and the answer is `-1`.

4. **No sorting needed**: Since we scan `nums` left-to-right, `occurrences` is already in ascending order of indices.

5. **Complexity**: Pre-collecting is O(n), and each query is answered in O(1), giving an overall complexity of O(n + q) where `n = len(nums)` and `q = len(queries)`.

## Solution

### Approach: Pre-collect + Direct Lookup

```python
def occurrencesOfElement(nums, queries, x):
    occurrences = [i for i, v in enumerate(nums) if v == x]
    answer = []
    for q in queries:
        if q > len(occurrences):
            answer.append(-1)
        else:
            answer.append(occurrences[q - 1])
    return answer
```

**How it works:**

1. **Build `occurrences`**: Single pass over `nums`, store each index where the value equals `x`.

2. **Answer each query in O(1)**:
   - Convert the 1-based query `q` to 0-based index `q - 1`.
   - If `q - 1` is out of bounds, append `-1`; otherwise append `occurrences[q - 1]`.

**Example Walkthrough** (`nums = [1,3,1,7]`, `queries = [1,3,2,4]`, `x = 1`):

```
occurrences = [0, 2]   (indices where nums[i] == 1)

query 1 → occurrences[0] = 0
query 3 → index 2 out of bounds → -1
query 2 → occurrences[1] = 2
query 4 → index 3 out of bounds → -1

answer = [0, -1, 2, -1]
```

**Complexity:**
- Time: O(n + q) — one pass to build `occurrences`, one pass over `queries`
- Space: O(k) where `k` is the number of occurrences of `x` in `nums`

# Tags

#array #indexing #simulation

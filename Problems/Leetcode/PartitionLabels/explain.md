## Problem

https://leetcode.com/problems/partition-labels/description/

```
You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part. For example, the string "ababcc" can be partitioned into ["abab", "cc"], but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.

Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.

Return a list of integers representing the size of these parts.

Example 1:

Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.

Example 2:

Input: s = "eccbbbbdec"
Output: [10]

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
```

## Observations

1. **Key Constraint**: Each character must appear in at most one partition - this means once a character appears in a partition, ALL occurrences of that character must be in the same partition.

2. **Greedy Approach**: We want to maximize the number of partitions, so we should make each partition as small as possible while satisfying the constraint.

3. **Critical Insight**: For any partition, we need to find the rightmost position of all characters that appear in that partition. The partition must extend at least to that position.

4. **Two-Pass Strategy**:
   - First pass: Record the last occurrence index of each character
   - Second pass: Use this information to determine partition boundaries

5. **Dynamic Boundary Extension**: As we scan through the string, we may encounter new characters whose last occurrence is further right, requiring us to extend the current partition boundary.

## Solution

### Algorithm Explanation

The solution uses a **greedy two-pass approach**:

**Pass 1: Build Last Occurrence Map**
```python
last = {} # char -> last index
for i, c in enumerate(s):
    last[c] = i
```
- Records the rightmost index where each character appears
- This tells us the minimum extent each partition must reach

**Pass 2: Determine Partition Boundaries**
```python
i = 0
n = len(s)
res = []
sum_res = 0
while i < n:
    last_idx = last[s[i]]  # Initial boundary for current partition
    j = i
    while j <= last_idx:
        last_idx = max(last_idx, last[s[j]])  # Extend boundary if needed
        j += 1
    res.append(last_idx - sum_res + 1)  # Calculate partition size
    sum_res += res[-1]                  # Update cumulative size
    i = last_idx + 1                    # Move to next partition
```

**Key Logic:**
1. Start a new partition at position `i`
2. Find the last occurrence of the starting character: `last_idx = last[s[i]]`
3. Scan from `i` to `last_idx`, and for each character encountered, extend `last_idx` if that character's last occurrence is further right
4. Once we've scanned up to `last_idx` without needing further extension, we've found a valid partition
5. Calculate the partition size and move to the next partition

### Example Walkthrough

For `s = "ababcbacadefegdehijhklij"`:

**Pass 1 - Build last occurrence map:**
```
a: 8, b: 5, c: 7, d: 14, e: 15, f: 11, g: 13, h: 19, i: 22, j: 23, k: 20, l: 21
```

**Pass 2 - Find partitions:**
1. **Partition 1**: Start at i=0 ('a')
   - Initial boundary: last['a'] = 8
   - Scan positions 0-8: encounter 'a','b','a','b','c','b','a','c','a'
   - Extend boundary: last['b']=5 (≤8), last['c']=7 (≤8) 
   - Final boundary: 8, size = 9
   - Partition: "ababcbaca"

2. **Partition 2**: Start at i=9 ('d')
   - Initial boundary: last['d'] = 14
   - Scan positions 9-14: encounter 'd','e','f','e','g','d'
   - Extend boundary: last['e']=15, last['f']=11, last['g']=13
   - Final boundary: 15, size = 7
   - Partition: "defegde"

3. **Partition 3**: Start at i=16 ('h')
   - Initial boundary: last['h'] = 19
   - Continue extending as we encounter 'i','j','k','l'
   - Final boundary: 23, size = 8
   - Partition: "hijhklij"

### Complexity Analysis

- **Time Complexity**: O(n) where n is the length of string
  - First pass: O(n) to build the last occurrence map
  - Second pass: O(n) total iterations (each character visited once)
- **Space Complexity**: O(1) since we have at most 26 lowercase letters in the hash map

### Why This Works (Correctness Proof)

1. **Completeness**: Every character is included in exactly one partition
2. **Constraint Satisfaction**: By extending the partition boundary to include the last occurrence of every character we encounter, we ensure no character spans multiple partitions
3. **Optimality**: We create a new partition as soon as possible (greedy approach), maximizing the number of partitions

## Tags

array, hash table, greedy
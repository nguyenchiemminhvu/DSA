## Problem

https://leetcode.com/problems/sequential-digits/description/

An integer has **sequential digits** if and only if each digit in the number is one more than the previous digit.

Return a **sorted list** of all the integers in the range `[low, high]` inclusive that have sequential digits.

**Example 1:**
```
Input: low = 100, high = 300
Output: [123, 234]
```

**Example 2:**
```
Input: low = 1000, high = 13000
Output: [1234, 2345, 3456, 4567, 5678, 6789, 12345]
```

**Constraints:**
- `10 <= low <= high <= 10^9`

---

## Observations

1. **Finite candidate set:** There are very few sequential digit numbers in total. A sequential digit number of length `L` starts at digit `d` and ends at digit `d + L - 1`. Since digits are `1–9`, we need `d + L - 1 <= 9`, so `d` ranges from `1` to `10 - L`. For lengths 2 through 9, the total count of all sequential digit numbers is:
   - Length 2: 8 numbers (12, 23, ..., 89)
   - Length 3: 7 numbers (123, 234, ..., 789)
   - ...
   - Length 9: 1 number (123456789)
   - **Total: 8 + 7 + ... + 1 = 36 numbers**

2. **Natural sorted order:** If we enumerate candidates by increasing length first, and then by increasing starting digit within the same length, the resulting list is already sorted in ascending order. This is because all numbers of length `L` are smaller than all numbers of length `L+1`, and within the same length, larger starting digit means larger number.

3. **No digit 0:** Sequential digits are always formed from digits `1–9` only, since each digit must be one more than the previous and we start from at least `1`.

4. **Construction is straightforward:** Any sequential digit number can be built by choosing a starting digit `d` and a length `L`, then forming the number `d, d+1, d+2, ..., d+L-1`.

5. **Range check is simple:** Since the candidate set is tiny (at most 36 numbers), filtering by `[low, high]` is trivial.

---

## Approaches

### Approach 1: Enumerate All Candidates (Optimal)

**Idea:** Pre-generate all 36 possible sequential digit numbers, then filter those that fall within `[low, high]`.

**Steps:**
1. For each length `L` from `2` to `9`:
   - For each starting digit `d` from `1` to `10 - L`:
     - Build the sequential number starting at `d` with length `L`.
     - If the number is within `[low, high]`, add it to the result.
2. Return the result (already sorted due to enumeration order).

**Time Complexity:** O(1) — at most 36 candidates regardless of input.  
**Space Complexity:** O(1) — output aside.

```
for L in 2..9:
    for d in 1..(10 - L):
        num = build_sequential(d, L)
        if low <= num <= high:
            result.append(num)
```

---

### Approach 2: Sliding Window on the String "123456789"

**Idea:** All sequential digit numbers are substrings of the string `"123456789"`. Extract all substrings of length `L` (for `L` from 2 to 9), convert them to integers, and filter by range.

**Steps:**
1. Define `digits = "123456789"`.
2. For each window length `L` from `2` to `9`:
   - Slide a window of size `L` over `digits`.
   - Convert each window substring to an integer.
   - If within `[low, high]`, collect it.
3. Return sorted results.

**Time Complexity:** O(1).  
**Space Complexity:** O(1).

This approach is essentially the same as Approach 1 but expressed more elegantly using string slicing.

---

### Approach 3: BFS / Queue-based Generation

**Idea:** Use a queue. Initialize with single digits `1–9`. At each step, take a number, append `(last_digit + 1)` to it if possible, forming a longer sequential number.

**Steps:**
1. Start with queue containing `[1, 2, ..., 9]`.
2. While queue is not empty:
   - Dequeue a number.
   - If it's within `[low, high]`, add to result.
   - If its last digit `< 9`, enqueue the new number formed by appending `(last_digit + 1)`.
3. Sort and return result.

**Time Complexity:** O(1).  
**Space Complexity:** O(1).

This approach naturally builds all sequential digit numbers in a tree-like expansion and is easy to reason about correctness.

---

## Recommended Approach

**Approach 1 or 2** are the simplest and most direct. Since the total number of candidates is fixed at 36, iterating over all possible `(length, start_digit)` pairs is clean, efficient, and easy to implement correctly in any language.


## Problem

https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/description/

You are given an array `nums` consisting of **positive** integers.

You have to take each integer in the array, **reverse its digits**, and add it to the end of the array. You should apply this operation to the original integers in `nums`.

Return the number of **distinct** integers in the final array.

**Example 1:**
```
Input: nums = [1,13,10,12,31]
Output: 6
Explanation: After including the reverse of each number, the resulting array is [1,13,10,12,31,1,31,1,21,13].
The number of distinct integers in this array is 6 (The numbers 1, 10, 12, 13, 21, and 31).
```

**Example 2:**
```
Input: nums = [2,2,2]
Output: 1
Explanation: After including the reverse of each number, the resulting array is [2,2,2,2,2,2].
The number of distinct integers in this array is 1 (The number 2).
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^6`

---

## Observations

1. **Reversing a number can produce a duplicate.** For example, reversing `1` gives `1`, and reversing `13` gives `31` which is already in the array. We only care about the final count of unique values, not the order or how many times a value appears.

2. **Leading zeros collapse.** When you reverse `10`, you get `"01"` → `int("01") = 1`. Python's `int()` conversion handles this automatically by stripping leading zeros.

3. **A set is the natural tool.** Since we only need distinct integers, inserting every original number and every reversed number into a set and taking its size is both correct and efficient.

4. **We only need to reverse the originals.** The problem says "apply this operation to the original integers in `nums`", so we iterate over the original array only — not the extended one.

---

## Solution Explanation

```python
class Solution:
    def countDistinctIntegers(self, nums: List[int]) -> int:
        s = set(nums)
        for val in nums:
            s.add(int(str(val)[::-1]))
        return len(s)
```

**Step-by-step:**

1. `s = set(nums)` — Start by inserting all original integers into a set. This deduplicates the originals immediately.

2. `for val in nums` — Iterate only over the **original** array (not the growing set), as required by the problem.

3. `str(val)[::-1]` — Convert the integer to a string and reverse it using Python's slice `[::-1]`.

4. `int(...)` — Convert back to integer. This strips any leading zeros that appeared after reversal (e.g., `"01"` → `1`).

5. `s.add(...)` — Insert the reversed number. If it already exists in the set (e.g., a palindrome like `1`, or a number whose reverse was already in `nums`), the set ignores the duplicate.

6. `return len(s)` — The size of the set is the count of all distinct integers in the final array.

**Complexity:**
- Time: O(n · d), where n is the length of `nums` and d is the number of digits (at most 7 for `10^6`). Effectively O(n).
- Space: O(n) for the set.

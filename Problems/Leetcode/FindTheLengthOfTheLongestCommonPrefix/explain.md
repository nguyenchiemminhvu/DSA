## Problem

https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/description

# Find the Length of the Longest Common Prefix

## Problem

**LeetCode:** https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/description

You are given two arrays with positive integers `arr1` and `arr2`.

A **prefix** of a positive integer is an integer formed by one or more of its digits, starting from its leftmost digit. For example, `123` is a prefix of the integer `12345`, while `234` is not.

A **common prefix** of two integers `a` and `b` is an integer `c`, such that `c` is a prefix of both `a` and `b`. For example, `5655359` and `56554` have common prefixes `565` and `5655` while `1223` and `43456` do not have a common prefix.

You need to find the length of the **longest common prefix** between all pairs of integers `(x, y)` such that `x` belongs to `arr1` and `y` belongs to `arr2`.

**Return** the length of the longest common prefix among all pairs. If no common prefix exists among them, return `0`.

### Constraints

- `1 <= arr1.length, arr2.length <= 5 * 10^4`
- `1 <= arr1[i], arr2[i] <= 10^8`

### Examples

**Example 1:**
```
Input: arr1 = [1,10,100], arr2 = [1000]
Output: 3
Explanation: There are 3 pairs (arr1[i], arr2[j]):
- The longest common prefix of (1, 1000) is 1.
- The longest common prefix of (10, 1000) is 10.
- The longest common prefix of (100, 1000) is 100.
The longest common prefix is 100 with a length of 3.
```

**Example 2:**
```
Input: arr1 = [1,2,3], arr2 = [4,4,4]
Output: 0
Explanation: There exists no common prefix for any pair (arr1[i], arr2[j]), hence we return 0.
```

---

## Observations

1. **Prefix Extraction:** We need to generate all possible prefixes for each number. For example, from `123`, we extract prefixes: `1`, `12`, `123`.

2. **String Representation:** To get prefixes, we can repeatedly divide by 10 (removing the last digit) or convert to string and take substrings. The division approach is more efficient.

3. **Set Intersection:** After collecting all prefixes from both arrays, we need to find common prefixes. Using sets makes intersection operations efficient (O(1) lookup and O(n) intersection).

4. **Longest Prefix:** Among all common prefixes, we need the one with the maximum length. This corresponds to the largest number that appears in both sets (numerically).

5. **Key Insight:** A prefix is uniquely identified by its numeric value. If `c` is a prefix of both `a` and `b`, then `c` will appear in the prefix set of `a` AND in the prefix set of `b`. The longer the prefix, the larger the numeric value (since we're removing digits from the right).

6. **Time Complexity Considerations:**
   - Generating prefixes: For each number up to `10^8`, we have at most 9 prefixes (since `10^8` has 9 digits). So extracting all prefixes is O(n * 9) = O(n).
   - Set intersection: O(min(len(prefix_a), len(prefix_b)))
   - Overall: O(n) where n is the total count of elements

---

## Solution

### Approach: Hash Set + Prefix Extraction

**Algorithm:**
1. Extract all prefixes from `arr1` and store them in a set `prefix_a`
2. Extract all prefixes from `arr2` and store them in a set `prefix_b`
3. Find the intersection of both sets to get all common prefixes
4. Return the length of the string representation of the largest common prefix (or 0 if no common prefix exists)

**Why This Works:**
- Converting numbers to strings allows us to get their length
- The largest number in the intersection set represents the longest common prefix
- By converting to string, we naturally get the correct length

```python
from typing import List

class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:
        # Extract all prefixes from arr1
        prefix_a = set()
        for val in arr1:
            temp = val
            while temp:
                prefix_a.add(temp)
                temp //= 10
        
        # Extract all prefixes from arr2
        prefix_b = set()
        for val in arr2:
            temp = val
            while temp:
                prefix_b.add(temp)
                temp //= 10
        
        # Find common prefixes
        common = prefix_a & prefix_b
        
        if not common:
            return 0
        
        # Return length of the longest (largest) common prefix
        return len(str(max(common)))
```

### Trace Through Example 1

**Input:** `arr1 = [1,10,100]`, `arr2 = [1000]`

**Step 1: Extract prefixes from arr1**
- From `1`: {1}
- From `10`: {10, 1}
- From `100`: {100, 10, 1}
- `prefix_a = {1, 10, 100}`

**Step 2: Extract prefixes from arr2**
- From `1000`: {1000, 100, 10, 1}
- `prefix_b = {1, 10, 100, 1000}`

**Step 3: Find intersection**
- `common = {1, 10, 100}`

**Step 4: Find longest**
- `max(common) = 100`
- `len(str(100)) = 3`
- **Output: 3** ✓

### Trace Through Example 2

**Input:** `arr1 = [1,2,3]`, `arr2 = [4,4,4]`

**Step 1: Extract prefixes from arr1**
- `prefix_a = {1, 2, 3}`

**Step 2: Extract prefixes from arr2**
- `prefix_b = {4}`

**Step 3: Find intersection**
- `common = {}` (empty set)

**Step 4: Return 0**
- **Output: 0** ✓

---

## Complexity Analysis

- **Time Complexity:** O(n * d) where n is the total number of elements and d is the average number of digits (at most 9 for numbers up to 10^8)
  - Extracting prefixes: O(n * 9)
  - Set intersection: O(min(len(prefix_a), len(prefix_b)))
  - Overall: O(n)

- **Space Complexity:** O(n * d) for storing all prefixes in both sets
  - Each number contributes at most 9 prefixes
  - Maximum space: O(n * 9) = O(n)

---

## Tags

- `Hash Set`
- `String Processing`
- `Set Intersection`
- `Prefix Extraction`

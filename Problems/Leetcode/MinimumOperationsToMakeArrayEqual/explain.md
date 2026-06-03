# Minimum Operations to Make Array Equal

## Problem Statement

Given an integer `n`, you have an array `arr` of length `n` where `arr[i] = (2 * i) + 1` for all valid values of `i` (i.e., `0 <= i < n`).

In one operation, you can:
- Select two indices `x` and `y` where `0 <= x, y < n`
- Subtract 1 from `arr[x]` and add 1 to `arr[y]`

**Goal:** Make all elements of the array equal using the minimum number of operations.

**Constraint:** All elements can be made equal (guaranteed).

### Examples

**Example 1:**
```
Input: n = 3
Output: 2
Explanation:
  arr = [1, 3, 5]
  Operation 1: x = 2, y = 0 → arr = [2, 3, 4]
  Operation 2: x = 2, y = 0 → arr = [3, 3, 3]
```

**Example 2:**
```
Input: n = 6
Output: 9
```

---

## Observations

### Key Insight 1: Array Structure
- Array is always odd numbers: `[1, 3, 5, 7, ..., 2n-1]`
- Example for `n = 6`: `[1, 3, 5, 7, 9, 11]`

### Key Insight 2: Target Value
- The sum of all elements is `n²` (sum of first n odd numbers)
- After operations, each element must equal `n²/n = n`
- All elements become equal to `n` (the middle value for odd n, or close to it for even n)

**Proof of sum:**
$$\sum_{i=0}^{n-1} (2i + 1) = n^2$$

### Key Insight 3: Symmetry
- The array is symmetric around the center
- Elements equidistant from center need equal redistribution
- Only need to calculate operations for one half

### Key Insight 4: Cost Calculation
- Distance from element to target determines operation count
- An element at position `i` needs to move `|arr[i] - target|` units
- But each unit moves from left to center or from center to right

---

## Solution Analysis

### Algorithm: Greedy Middle Approach

```python
class Solution:
    def minOperations(self, n: int) -> int:
        res = 0
        i = n // 2
        op = 0
        if n % 2 == 0:
            i -= 1
            op += 1
        
        for j in range(i, -1, -1):
            res += op
            op += 2
        return res
```

### How It Works

**Step 1: Find Starting Position**
```
i = n // 2
```
- For odd n: start from the middle element (n // 2)
- For even n: start from one position left of middle

**Step 2: Handle Even vs Odd**
```
if n % 2 == 0:
    i -= 1
    op += 1
```
- For even n, middle two elements aren't equal, add 1 to operations initially
- For odd n, middle element doesn't need change, start with op = 0

**Step 3: Accumulate Operations**
```
for j in range(i, -1, -1):
    res += op
    op += 2
```
- Iterate from middle toward the beginning
- Each element to the left requires more operations
- Operation count increases by 2 for each step left (arithmetic progression)

### Example Walkthrough (n = 6)

```
arr = [1, 3, 5, 7, 9, 11]
target = 6

n = 6 (even):
  i = 6 // 2 = 3
  op = 0
  i -= 1 → i = 2
  op += 1 → op = 1

Loop (j from 2 down to 0):
  j = 2: res += 1 → res = 1, op += 2 → op = 3
  j = 1: res += 3 → res = 4, op += 2 → op = 5
  j = 0: res += 5 → res = 9, op += 2 → op = 7

Result: 9 ✓
```

### Example Walkthrough (n = 3)

```
arr = [1, 3, 5]
target = 3

n = 3 (odd):
  i = 3 // 2 = 1
  op = 0
  (skip if block)

Loop (j from 1 down to 0):
  j = 1: res += 0 → res = 0, op += 2 → op = 2
  j = 0: res += 2 → res = 2, op += 2 → op = 4

Result: 2 ✓
```

---

## Mathematical Explanation

### Why the Operations Follow an Arithmetic Progression

For an array of length n:
- Target value: `n`
- Differences from left:
  - Position 0: `arr[0] = 1`, needs to gain `n - 1`
  - Position 1: `arr[1] = 3`, needs to gain `n - 3`
  - Position 2: `arr[2] = 5`, needs to gain `n - 5`

The difference pattern: `(n-1), (n-3), (n-5), ...` which forms an arithmetic sequence with common difference of -2.

When moving from right to left, we sum these differences:
$$\text{Operations} = \sum_{k=0}^{\lfloor n/2 \rfloor - 1} (2k + 1) = \left(\left\lfloor \frac{n}{2} \right\rfloor\right)^2 = \frac{n^2}{4}$$

(for even n: exactly $\frac{n^2}{4}$, for odd n: $\frac{n^2-1}{4}$)

---

## Complexity Analysis

| Aspect | Complexity | Explanation |
|--------|-----------|-------------|
| **Time** | $O(n)$ | Loop runs n/2 times |
| **Space** | $O(1)$ | Only using constant extra space |

---

## Alternative Approaches

### Approach 1: Direct Formula (Optimal)
```python
def minOperations(self, n: int) -> int:
    return (n * n) // 4
```
This uses the mathematical insight directly without looping.

### Approach 2: Calculate Total Difference
```python
def minOperations(self, n: int) -> int:
    target = n
    total = 0
    for i in range(n // 2):
        total += (target - (2*i + 1))
    return total
```
This explicitly calculates how much each element differs from target.

---

## Key Takeaways

1. **Recognize patterns:** The array consists of consecutive odd numbers
2. **Use symmetry:** Only calculate for half the array
3. **Arithmetic progression:** Operations follow a predictable pattern
4. **Mathematical insight:** Can reduce O(n) to O(1) with formula
5. **Greedy works:** Always move closer to target value

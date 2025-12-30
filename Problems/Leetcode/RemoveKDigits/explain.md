# Remove K Digits

## Problem

https://leetcode.com/problems/remove-k-digits/description/

Given a string `num` representing a non-negative integer and an integer `k`, return the smallest possible integer after removing `k` digits from `num`.

### Examples

**Example 1:**
```
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
```

**Example 2:**
```
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
```

**Example 3:**
```
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
```

### Constraints

- `1 <= k <= num.length <= 10^5`
- `num` consists of only digits
- `num` does not have any leading zeros except for the zero itself

---

## Observations

1. **Greedy Approach**: To get the smallest number, we want to keep smaller digits towards the left (more significant positions).

2. **Monotonic Stack Pattern**: We can use a stack to maintain digits in non-decreasing order. When we encounter a smaller digit, we should remove larger digits before it (if we still have removals left).

3. **Key Insight**: If we have a digit sequence like "432", and we need to remove digits, we should remove from left to right when a digit is larger than the next one. This keeps the smallest digits in the most significant positions.

4. **Edge Cases**:
   - Leading zeros must be removed from the result
   - If all digits are removed, return "0"
   - If we haven't removed k digits after scanning, remove from the end (handles monotonic increasing sequences like "123")

5. **Why Stack?**: 
   - Stack allows us to efficiently remove previous digits when we find a smaller digit
   - We can build the result incrementally while maintaining the optimal structure

6. **Mathematical Reasoning**:
   - For a number to be smallest, we want smaller digits in higher place values
   - If `num[i] > num[i+1]`, removing `num[i]` will always result in a smaller number
   - This is because we're replacing a larger digit in a more significant position with a smaller digit

---

## Solution

### Algorithm

The solution uses a **monotonic stack** approach:

1. **Iterate through each digit** in the input string
2. **While conditions are met**:
   - We still have removals left (`k > 0`)
   - Stack is not empty
   - Top of stack is greater than current digit
   - **Action**: Pop from stack (remove the larger digit) and decrement `k`
3. **Add current digit** to the stack
4. **Handle remaining removals**: If `k > 0` after processing all digits, remove from the end
5. **Remove leading zeros**: Skip zeros from the beginning
6. **Return result**: Join remaining digits, or return "0" if empty

### Step-by-Step Example

Let's trace `num = "1432219"`, `k = 3`:

```
Initial: st = [], k = 3

Process '1': 
  - No digits to remove
  - st = ['1'], k = 3

Process '4': 
  - '1' < '4', don't remove
  - st = ['1', '4'], k = 3

Process '3': 
  - '4' > '3' and k > 0, pop '4'
  - st = ['1'], k = 2
  - Append '3'
  - st = ['1', '3'], k = 2

Process '2': 
  - '3' > '2' and k > 0, pop '3'
  - st = ['1'], k = 1
  - Append '2'
  - st = ['1', '2'], k = 1

Process '2': 
  - '2' not > '2', don't remove
  - st = ['1', '2', '2'], k = 1

Process '1': 
  - '2' > '1' and k > 0, pop '2'
  - st = ['1', '2'], k = 0
  - Append '1'
  - st = ['1', '2', '1'], k = 0

Process '9': 
  - k = 0, no more removals
  - st = ['1', '2', '1', '9'], k = 0

No leading zeros to remove
Result: "1219"
```

### Another Example: Monotonic Increasing

`num = "123456"`, `k = 3`:

```
Process all digits: st = ['1', '2', '3', '4', '5', '6'], k = 3
(No digit is greater than the next, so no removals during scan)

Remove from end: 
  - Pop '6', k = 2
  - Pop '5', k = 1
  - Pop '4', k = 0
  - st = ['1', '2', '3']

Result: "123"
```

### Code Implementation

```python
class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        n = len(num)
        st = []
        
        # Build the monotonic stack
        for c in num:
            # Remove larger digits before current smaller digit
            while k and st and st[-1] > c:
                st.pop()
                k -= 1
            st.append(c)
        
        # Remove remaining digits from the end
        while k:
            st.pop()
            k -= 1
        
        # Remove leading zeros
        i = 0
        while i < len(st) and st[i] == '0':
            i += 1
        
        # Build result
        res = "".join(st[i:])
        return '0' if not res else res
```

### Complexity Analysis

**Time Complexity**: O(n)
- Each digit is pushed to the stack exactly once: O(n)
- Each digit is popped from the stack at most once: O(n)
- Leading zero removal: O(n)
- Overall: O(n)

**Space Complexity**: O(n)
- Stack can contain at most n digits
- Result string: O(n)

---

## Key Takeaways

1. **Greedy Strategy**: Always try to keep smaller digits in more significant positions by removing larger digits that appear before smaller ones.

2. **Monotonic Stack**: Perfect data structure for maintaining relative order while allowing efficient removal of previous elements.

3. **Three-Phase Approach**:
   - **Phase 1**: Build stack while removing larger digits when we find smaller ones
   - **Phase 2**: Handle leftover removals (important for monotonic increasing sequences)
   - **Phase 3**: Clean up leading zeros

4. **Edge Case Handling**: 
   - Must handle empty result (return "0")
   - Remove all leading zeros
   - Handle case where all digits need to be removed

5. **Why This Works**: The greedy choice of always removing the first larger digit before a smaller digit is locally optimal and leads to a globally optimal solution.

# Tags

`Stack`, `Monotonic Stack`, `Greedy`, `String`, `Medium`


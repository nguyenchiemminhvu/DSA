## Problem

https://leetcode.com/problems/compute-decimal-representation/description/

```
You are given a positive integer n.

A positive integer is a base-10 component if it is the product of a single digit from 1 to 9 
and a non-negative power of 10. For example, 500, 30, and 7 are base-10 components, while 537, 
102, and 11 are not.

Express n as a sum of only base-10 components, using the fewest base-10 components possible.

Return an array containing these base-10 components in descending order.

Example 1:
Input: n = 537
Output: [500,30,7]
Explanation: We can express 537 as 500 + 30 + 7. It is impossible to express 537 as a sum using 
fewer than 3 base-10 components.

Example 2:
Input: n = 102
Output: [100,2]
Explanation: We can express 102 as 100 + 2. 102 is not a base-10 component, which means 2 base-10 
components are needed.

Example 3:
Input: n = 6
Output: [6]
Explanation: 6 is a base-10 component.

Constraints:
- 1 <= n <= 10^9
```

## Observations

1. **Base-10 Component Definition**: A base-10 component is a single non-zero digit multiplied by a power of 10 (e.g., 7×10^0=7, 3×10^1=30, 5×10^2=500).

2. **Unique Decomposition**: Every positive integer has a unique decomposition into base-10 components - this is essentially breaking down the number by its decimal place values.

3. **Digit Extraction**: We need to extract each digit from the number and multiply it by its corresponding power of 10:
   - Units place: digit × 10^0
   - Tens place: digit × 10^1
   - Hundreds place: digit × 10^2
   - And so on...

4. **Skip Zeros**: Digits that are 0 don't contribute to the sum (e.g., in 102, we skip the tens place).

5. **Minimum Components**: Since each digit can only contribute one component (its value × power of 10), the minimum number of components equals the number of non-zero digits.

## Solution

1. **Initialize Variables**:
   - `res`: List to store the base-10 components
   - `base`: Tracks the current power of 10 (starts at 0 for the units place)

2. **Extract Digits from Right to Left**:
   - Use `n % 10` to extract the rightmost digit
   - Multiply this digit by `10^base` to get the component value
   - If the component is non-zero (i.e., the digit wasn't 0), add it to the result

3. **Move to Next Digit**:
   - Use integer division `n //= 10` to remove the processed digit
   - Increment `base` to move to the next power of 10

4. **Reverse the Result**:
   - Since we extracted digits from right to left (least significant to most significant), reverse the list to get descending order

**Example Walkthrough (n = 537)**:
- Iteration 1: digit=7, base=0 → component=7×10^0=7 → res=[7]
- Iteration 2: digit=3, base=1 → component=3×10^1=30 → res=[7,30]
- Iteration 3: digit=5, base=2 → component=5×10^2=500 → res=[7,30,500]
- After reverse: res=[500,30,7]

**Complexity Analysis**:
- **Time Complexity**: O(d) where d is the number of digits in n. Since d = log₁₀(n), this is O(log n).
- **Space Complexity**: O(d) for storing the result array.

# Tags
#math #digit-manipulation #implementation


## Problem

https://leetcode.com/problems/count-operations-to-obtain-zero/description/

```
You are given two non-negative integers num1 and num2.

In one operation, if num1 >= num2, you must subtract num2 from num1, otherwise subtract num1 from num2.

For example, if num1 = 5 and num2 = 4, subtract num2 from num1, thus obtaining num1 = 1 and num2 = 4. However, if num1 = 4 and num2 = 5, after one operation, num1 = 4 and num2 = 1.
Return the number of operations required to make either num1 = 0 or num2 = 0.

Example 1:

Input: num1 = 2, num2 = 3
Output: 3
Explanation: 
- Operation 1: num1 = 2, num2 = 3. Since num1 < num2, we subtract num1 from num2 and get num1 = 2, num2 = 3 - 2 = 1.
- Operation 2: num1 = 2, num2 = 1. Since num1 > num2, we subtract num2 from num1.
- Operation 3: num1 = 1, num2 = 1. Since num1 == num2, we subtract num2 from num1.
Now num1 = 0 and num2 = 1. Since num1 == 0, we do not need to perform any further operations.
So the total number of operations required is 3.

Example 2:

Input: num1 = 10, num2 = 10
Output: 1
Explanation: 
- Operation 1: num1 = 10, num2 = 10. Since num1 == num2, we subtract num2 from num1 and get num1 = 10 - 10 = 0.
Now num1 = 0 and num2 = 10. Since num1 == 0, we are done.
So the total number of operations required is 1.

Constraints:

0 <= num1, num2 <= 105
```

## Observations

1. **Pattern Recognition**: This problem is essentially the Euclidean Algorithm for finding GCD, but counting the operations instead of finding the remainder.

2. **Operation Analysis**: 
   - If `num1 >= num2`, we subtract `num2` from `num1` repeatedly until `num1 < num2`
   - This is equivalent to `num1 = num1 % num2` and counting `num1 // num2` operations
   - Then we swap the numbers and repeat

3. **Optimization Insight**: Instead of subtracting one by one, we can use division and modulo:
   - `num1 // num2` gives us the number of times we can subtract `num2` from `num1`
   - `num1 % num2` gives us the remainder after all those subtractions

4. **Base Cases**:
   - If either number becomes 0, we stop
   - If both numbers are equal, it takes 1 operation to make one of them 0

5. **Time Complexity**: O(log(min(num1, num2))) - same as Euclidean algorithm
6. **Space Complexity**: O(1) - only using constant extra space

## Solution

1. **Initialize counter**: `op = 0` to track total operations

2. **Main loop**: Continue while both numbers are non-zero
   - `op += num1 // num2`: Add the number of subtractions we can perform
   - `num1 %= num2`: Update num1 to the remainder
   - `num1, num2 = num2, num1`: Swap numbers for next iteration

3. **Loop invariant**: After each iteration, we ensure `num1 < num2` (except when num1 becomes 0)

4. **Termination**: Loop ends when one number becomes 0

### Example Walkthrough:
For `num1 = 2, num2 = 3`:
- Iteration 1: `2 // 3 = 0`, `2 % 3 = 2`, swap → `num1 = 3, num2 = 2`, `op = 0`
- Iteration 2: `3 // 2 = 1`, `3 % 2 = 1`, swap → `num1 = 2, num2 = 1`, `op = 1`  
- Iteration 3: `2 // 1 = 2`, `2 % 1 = 0`, swap → `num1 = 1, num2 = 0`, `op = 3`
- Loop ends since `num2 = 0`, return `op = 3`

# Tags

- **Algorithm**: Euclidean Algorithm, Math
- **Technique**: Simulation, Optimization
- **Complexity**: O(log n) time, O(1) space
- **Difficulty**: Easy-Medium


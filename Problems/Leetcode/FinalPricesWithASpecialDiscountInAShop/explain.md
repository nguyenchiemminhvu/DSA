## Problem

https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/

```
You are given an integer array prices where prices[i] is the price of the ith item in a shop.

There is a special discount for items in the shop. If you buy the ith item, then you will receive a discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <= prices[i]. Otherwise, you will not receive any discount at all.

Return an integer array answer where answer[i] is the final price you will pay for the ith item of the shop, considering the special discount.

Example 1:

Input: prices = [8,4,6,2,3]
Output: [4,2,4,2,3]
Explanation: 
For item 0 with price[0]=8 you will receive a discount equivalent to prices[1]=4, therefore, the final price you will pay is 8 - 4 = 4.
For item 1 with price[1]=4 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 4 - 2 = 2.
For item 2 with price[2]=6 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 6 - 2 = 4.
For items 3 and 4 you will not receive any discount at all.

Example 2:

Input: prices = [1,2,3,4,5]
Output: [1,2,3,4,5]
Explanation: In this case, for all items, you will not receive any discount at all.

Example 3:

Input: prices = [10,1,1,6]
Output: [9,0,1,6]

Constraints:

1 <= prices.length <= 500
1 <= prices[i] <= 1000
```

## Observations

1. **Problem Pattern**: This is a classic "Next Smaller Element" problem where we need to find the first smaller or equal element to the right of each element.

2. **Key Insight**: For each item at index `i`, we need to find the minimum index `j` where `j > i` and `prices[j] <= prices[i]`. This is the discount amount we subtract from the original price.

3. **Monotonic Stack Approach**: We can use a stack to efficiently find the next smaller/equal element for each position by processing elements from right to left.

4. **Edge Cases**: 
   - If no smaller/equal element exists to the right, no discount applies
   - Elements at the end of the array typically don't get discounts

## Solution

The solution uses a **monotonic decreasing stack** approach:

### Algorithm Steps:

1. **Initialize**: 
   - `prefix` array to store the index of the next smaller/equal element
   - `st` stack to maintain indices in decreasing order of their values

2. **Process from right to left**:
   - For each element at index `i`, remove elements from stack that are greater than `prices[i]`
   - If stack is not empty, the top element is the next smaller/equal element
   - Add current index to stack

3. **Calculate final prices**:
   - For each item, subtract the discount (if available) from original price

### Example Trace: `prices = [8,4,6,2,3]`

| i | prices[i] | Stack before | Action | Stack after | prefix[i] |
|---|-----------|--------------|--------|-------------|-----------|
| 4 | 3 | [] | Add 4 | [4] | -1 |
| 3 | 2 | [4] | Pop 4 (3>2), Add 3 | [3] | -1 |
| 2 | 6 | [3] | Keep 3 (2≤6), Add 2 | [3,2] | 3 |
| 1 | 4 | [3,2] | Keep 3 (2≤4), Add 1 | [3,1] | 3 |
| 0 | 8 | [3,1] | Keep 1 (4≤8), Add 0 | [3,1,0] | 1 |

**Final prices**: [8-4=4, 4-2=2, 6-2=4, 2-0=2, 3-0=3] = [4,2,4,2,3]

### Time Complexity: O(n)
- Each element is pushed and popped at most once from the stack

### Space Complexity: O(n) 
- For the stack and prefix array

# Tags

- **Stack**
- **Monotonic Stack** 
- **Array**
- **Next Smaller Element**


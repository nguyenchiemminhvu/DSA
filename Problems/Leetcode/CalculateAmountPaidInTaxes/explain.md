## Problem

https://leetcode.com/problems/calculate-amount-paid-in-taxes/description/

```
You are given a 0-indexed 2D integer array brackets where brackets[i] = [upperi, percenti] means that the ith tax bracket has an upper bound of upperi and is taxed at a rate of percenti. The brackets are sorted by upper bound (i.e. upperi-1 < upperi for 0 < i < brackets.length).

Tax is calculated as follows:

The first upper0 dollars earned are taxed at a rate of percent0.
The next upper1 - upper0 dollars earned are taxed at a rate of percent1.
The next upper2 - upper1 dollars earned are taxed at a rate of percent2.
And so on.
You are given an integer income representing the amount of money you earned. Return the amount of money that you have to pay in taxes. Answers within 10-5 of the actual answer will be accepted.

Example 1:

Input: brackets = [[3,50],[7,10],[12,25]], income = 10
Output: 2.65000
Explanation:
Based on your income, you have 3 dollars in the 1st tax bracket, 4 dollars in the 2nd tax bracket, and 3 dollars in the 3rd tax bracket.
The tax rate for the three tax brackets is 50%, 10%, and 25%, respectively.
In total, you pay $3 * 50% + $4 * 10% + $3 * 25% = $2.65 in taxes.

Example 2:

Input: brackets = [[1,0],[4,25],[5,50]], income = 2
Output: 0.25000
Explanation:
Based on your income, you have 1 dollar in the 1st tax bracket and 1 dollar in the 2nd tax bracket.
The tax rate for the two tax brackets is 0% and 25%, respectively.
In total, you pay $1 * 0% + $1 * 25% = $0.25 in taxes.

Example 3:

Input: brackets = [[2,50]], income = 0
Output: 0.00000
Explanation:
You have no income to tax, so you have to pay a total of $0 in taxes.

Constraints:

1 <= brackets.length <= 100
1 <= upperi <= 1000
0 <= percenti <= 100
0 <= income <= 1000
upperi is sorted in ascending order.
All the values of upperi are unique.
The upper bound of the last tax bracket is greater than or equal to income.
```

## Observations

1. **Progressive Tax System**: This is a classic progressive tax problem where different income ranges are taxed at different rates.

2. **Tax Brackets Structure**: Each bracket `[upper_bound, tax_rate]` defines:
   - The maximum income that falls under this bracket
   - The tax percentage for income in this bracket

3. **Key Insight**: We need to calculate tax for each bracket sequentially:
   - For bracket i: tax = (income_in_bracket) × (tax_rate / 100)
   - Income in bracket = min(remaining_income, bracket_upper_bound - previous_upper_bound)

4. **Edge Cases**:
   - Income = 0: No tax to pay
   - Income fits entirely in first bracket
   - Income spans multiple brackets

## Solution

1. **Initialization**:
   - `idx = 0`: Current bracket index
   - `res = 0`: Total tax accumulated
   - `prev_upper = 0`: Upper bound of previous bracket
   - `remain = income`: Remaining income to be taxed

2. **Main Loop**: While there's remaining income to tax:
   - Get current bracket's upper bound and tax rate
   - Calculate taxable income for this bracket:
     ```python
     taxed_income = min(income, cur_upper) - prev_upper
     ```
     This ensures we don't tax more than what's available in this bracket
   
3. **Tax Calculation**:
   - Subtract taxed amount from remaining income
   - Add calculated tax to result: `taxed_income * cur_percent / 100`
   - Update previous upper bound for next iteration

**Example Walkthrough** (`brackets = [[3,50],[7,10],[12,25]]`, `income = 10`):

- **Bracket 1** [3, 50%]: Tax $3 at 50% = $1.50
- **Bracket 2** [7, 10%]: Tax $4 (7-3) at 10% = $0.40  
- **Bracket 3** [12, 25%]: Tax $3 (10-7) at 25% = $0.75
- **Total**: $1.50 + $0.40 + $0.75 = $2.65

**Time Complexity**: O(n) where n is the number of tax brackets
**Space Complexity**: O(1) - only using constant extra space

# Tags


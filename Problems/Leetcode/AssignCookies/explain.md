## Problem

https://leetcode.com/problems/assign-cookies/description/

```
Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.

Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Example 1:

Input: g = [1,2,3], s = [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.

Example 2:

Input: g = [1,2], s = [1,2,3]

Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.

Constraints:

1 <= g.length <= 3 * 104
0 <= s.length <= 3 * 104
1 <= g[i], s[j] <= 231 - 1
```

## Observations

1. **Goal**: Maximize the number of content children by matching cookies to children optimally.

2. **Key Constraint**: Each child can receive at most one cookie, and a cookie satisfies a child only if `s[j] >= g[i]`.

3. **Greedy Strategy**: 
   - Sort both arrays to enable efficient matching from smallest to largest
   - Try to satisfy children with minimum greed using the smallest possible cookies
   - This ensures we don't waste larger cookies on children who could be satisfied with smaller ones

4. **Why Greedy Works**:
   - If we can satisfy a child with greed `g[i]` using cookie `s[j]`, using any larger cookie `s[k]` (where `k > j`) would be wasteful
   - By satisfying less greedy children first with smaller cookies, we save larger cookies for greedier children
   - This locally optimal choice leads to a globally optimal solution

5. **Edge Cases**:
   - Empty cookie array: return 0
   - More cookies than children: some cookies remain unused
   - More children than cookies: some children remain unsatisfied

### Complexity Analysis

- **Time Complexity**: O(n log n + m log m)
  - Sorting `g`: O(n log n) where n = len(g)
  - Sorting `s`: O(m log m) where m = len(s)
  - Two-pointer traversal: O(n + m)
  - Overall: O(n log n + m log m)

- **Space Complexity**: O(1) or O(n + m)
  - O(1) extra space if sorting is done in-place
  - O(n + m) if the sorting algorithm requires additional space (e.g., Timsort in Python)

### Algorithm Steps

1. **Sort both arrays**: This enables greedy matching from smallest to largest
2. **Initialize two pointers**: One for children (`ig`), one for cookies (`iz`)
3. **Iterate with two pointers**:
   - If current cookie is too small (`g[ig] > s[iz]`): skip to next cookie
   - If current cookie satisfies current child (`g[ig] <= s[iz]`): match them and move both pointers
4. **Return result**: The child pointer `ig` indicates how many children were satisfied

### Why This Works

The greedy approach works because:
- Sorting ensures we process in optimal order (smallest first)
- Matching the least greedy child with the smallest sufficient cookie is always optimal
- This leaves larger cookies available for greedier children
- We can't improve the solution by reassigning cookies differently

## Tags

array, greedy
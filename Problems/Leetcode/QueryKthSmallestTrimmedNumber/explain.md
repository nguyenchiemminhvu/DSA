## Problem

https://leetcode.com/problems/query-kth-smallest-trimmed-number/

```
You are given a 0-indexed array of strings nums, where each string is of equal length and consists of only digits.

You are also given a 0-indexed 2D integer array queries where queries[i] = [ki, trimi]. For each queries[i], you need to:

Trim each number in nums to its rightmost trimi digits.
Determine the index of the kith smallest trimmed number in nums. If two trimmed numbers are equal, the number with the lower index is considered to be smaller.
Reset each number in nums to its original length.
Return an array answer of the same length as queries, where answer[i] is the answer to the ith query.

Note:

To trim to the rightmost x digits means to keep removing the leftmost digit, until only x digits remain.
Strings in nums may contain leading zeros.

Example 1:

Input: nums = ["102","473","251","814"], queries = [[1,1],[2,3],[4,2],[1,2]]
Output: [2,2,1,0]
Explanation:
1. After trimming to the last digit, nums = ["2","3","1","4"]. The smallest number is 1 at index 2.
2. Trimmed to the last 3 digits, nums is unchanged. The 2nd smallest number is 251 at index 2.
3. Trimmed to the last 2 digits, nums = ["02","73","51","14"]. The 4th smallest number is 73.
4. Trimmed to the last 2 digits, the smallest number is 2 at index 0.
   Note that the trimmed number "02" is evaluated as 2.

Example 2:

Input: nums = ["24","37","96","04"], queries = [[2,1],[2,2]]
Output: [3,0]
Explanation:
1. Trimmed to the last digit, nums = ["4","7","6","4"]. The 2nd smallest number is 4 at index 3.
   There are two occurrences of 4, but the one at index 0 is considered smaller than the one at index 3.
2. Trimmed to the last 2 digits, nums is unchanged. The 2nd smallest number is 24.

Constraints:

1 <= nums.length <= 100
1 <= nums[i].length <= 100
nums[i] consists of only digits.
All nums[i].length are equal.
1 <= queries.length <= 100
queries[i].length == 2
1 <= ki <= nums.length
1 <= trimi <= nums[i].length

Follow up: Could you use the Radix Sort Algorithm to solve this problem? What will be the complexity of that solution?
```

## Observations

1. **String Trimming**: We need to trim each number to its rightmost `trim` digits. This is easily done using negative indexing in Python: `val[-trim:]`.

2. **Finding k-th Smallest**: For each query, we need to find the k-th smallest trimmed number. This is a classic "k-th smallest element" problem.

3. **Tie-Breaking**: When two trimmed numbers are equal, the one with the smaller original index is considered smaller. This means we need to track both the value and the index.

4. **Max Heap for k-th Smallest**: The solution uses a max heap of size k. By maintaining only k elements in the heap, the root (maximum element) will be the k-th smallest element overall.

5. **Negative Values Trick**: Python's `heapq` is a min heap by default. To use it as a max heap, we negate the values: `(-int(trimmed), -i)`. The negative index ensures proper tie-breaking (smaller indices stay in the heap).

6. **Independent Queries**: Each query is independent - we reset to the original numbers each time, so we process each query from scratch.

## Solution

### Approach: Max Heap

**Algorithm:**
1. For each query `[k, trim]`:
   - Create an empty max heap
   - For each number in `nums`:
     - Trim it to the rightmost `trim` digits
     - Push `(-trimmed_value, -index)` to the heap
     - If heap size exceeds `k`, pop the maximum element
   - After processing all numbers, the heap contains the k smallest elements
   - The root of the heap (maximum among k smallest) is the k-th smallest
   - Extract the index from the root: `-arr[0][1]`

**Why Max Heap of Size k?**
- We want the k-th smallest, which is the largest among the k smallest elements
- By limiting heap size to k and using a max heap, we keep only the k smallest elements
- The maximum in this set is our answer

**Time Complexity:** O(Q × N × log k)
- Q = number of queries
- N = number of elements in nums
- For each query, we do N heap operations, each costing O(log k)

**Space Complexity:** O(k) for the heap

**Example Walkthrough:**
```
nums = ["102","473","251","814"], query = [2, 3] (find 2nd smallest with 3 digits)

Trimmed numbers (all 3 digits): ["102","473","251","814"]

Building max heap of size 2:
- Add (102, 0): heap = [(-102, -0)]
- Add (473, 1): heap = [(-473, -1), (-102, -0)]
- Add (251, 2): heap size > 2, pop (-473, -1), heap = [(-251, -2), (-102, -0)]
- Add (814, 3): heap size > 2, pop (-814, -3), heap = [(-251, -2), (-102, -0)]

Final heap root: (-251, -2) → index 2
Answer: 2
```

**Alternative Approach:** The follow-up suggests using Radix Sort, which would have O(Q × N × D) complexity where D is the number of digits, avoiding the log k factor but requiring more complex implementation.

## Tags

array, string, max heap, radix sort
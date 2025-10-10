## Problem

https://leetcode.com/problems/top-k-frequent-elements/

```
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2

Output: [1,2]

Example 2:

Input: nums = [1], k = 1

Output: [1]

Example 3:

Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

Output: [1,2]

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
```

## Observations

We need to find the `k` most frequent elements in a list of integers.

Counting how many times each number appears is the first step.

To efficiently keep track of the top `k` frequent elements, a heap (priority queue) is useful.

Python’s `heapq` module provides a `min-heap`, so we can always remove the least frequent element when the heap grows beyond size `k`.

## Solution

**Count Frequencies:**

Use a dictionary to count how many times each number appears in the input list.

**Build a Min-Heap:**

For each unique number and its frequency, push a tuple (`frequency`, `number`) into the heap.

If the heap size exceeds `k`, remove the smallest frequency element.

This ensures the heap always contains the `k` most frequent numbers.

**Extract Results:**

After processing all numbers, the heap contains the top `k` frequent elements.
Return the numbers from the heap.

## Tags

array, hash table, heap
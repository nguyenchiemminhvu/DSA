## Problem

https://leetcode.com/problems/find-k-closest-elements/

```
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3

Output: [1,2,3,4]

Example 2:

Input: arr = [1,1,2,3,4,5], k = 4, x = -1

Output: [1,1,2,3]

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 104
arr is sorted in ascending order.
-104 <= arr[i], x <= 104
```

## Observations

We are asked to find the `k` closest numbers to `x` from a sorted array `arr`.

Because `arr` is sorted, we can use binary search to quickly locate the region around `x`, then expand around it to find the `k` closest elements.

Instead of directly searching for `x`, we can think of this problem as finding a window of size `k` inside `arr` that contains the `k` closest elements to `x`.

We want to find the smallest left index `L` such that the subarray `arr[L : L + k]` gives the best (closest) `k` elements.

The window of length `k` can start anywhere from index `0` to `len(arr) - k`.

For each possible starting index `L`, the window covers `arr[L]` to `arr[L + k - 1]`.

## Solution

```
if x - arr[mid] > arr[mid + k] - x:
    move right (L = mid + 1)
else:
    move left (R = mid)
```

`arr[mid]` is the left boundary of the current window.

`arr[mid + k]` is just outside the right boundary.

If `x` is closer to `arr[mid + k]`, it means we should shift the window right.

Otherwise, we stay or move left.

## Tags

array, binary search
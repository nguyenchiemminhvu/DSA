## Problem

https://leetcode.com/problems/k-th-smallest-prime-fraction/description/

```
You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.

For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].

Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

Example 1:
Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.

Example 2:
Input: arr = [1,7], k = 1
Output: [1,7]

Constraints:
- 2 <= arr.length <= 1000
- 1 <= arr[i] <= 3 * 10^4
- arr[0] == 1
- arr[i] is a prime number for i > 0
- All the numbers of arr are unique and sorted in strictly increasing order
- 1 <= k <= arr.length * (arr.length - 1) / 2
```

## Observations

1. **Problem Nature**: We need to find the k-th smallest fraction from all possible pairs (i, j) where i < j.

2. **Total Fractions**: For an array of length n, there are `n * (n - 1) / 2` possible fractions.

3. **Fraction Properties**:
   - Smaller numerator → smaller fraction (when denominator is fixed)
   - Larger denominator → smaller fraction (when numerator is fixed)
   - Since arr is sorted, arr[0] = 1 creates the smallest fractions: 1/arr[n-1], 1/arr[n-2], etc.

4. **Brute Force Approach**: Generate all fractions, sort them, and return the k-th one → O(n²log(n²)) time, O(n²) space.

5. **Optimization with Max Heap**: Instead of sorting all fractions, we can maintain only k smallest fractions using a max heap (where the largest of the k smallest sits at the top and can be removed when we find a smaller fraction).

## Solution

### Approach: Max Heap (Priority Queue)

The provided solution uses a **max heap** to keep track of the k smallest fractions efficiently.

**Algorithm**:
1. Use a max heap to store at most k fractions
2. Iterate through all possible pairs (i, j) where i < j
3. For each fraction arr[i]/arr[j]:
   - Push the negative fraction value (to simulate max heap) along with indices (i, j)
   - If heap size exceeds k, pop the largest fraction (smallest negative value)
4. After processing all fractions, the heap contains exactly k smallest fractions
5. Pop the top element (which is the k-th smallest) and return the corresponding array values

**Why Negative Values?**
Python's `heapq` implements a min heap, but we need a max heap. By storing negative values, the smallest negative (largest positive) becomes the root, effectively creating a max heap.

**Time Complexity**: O(n² log k)
- We iterate through all n²/2 pairs: O(n²)
- Each heap operation (push/pop) takes O(log k)
- Total: O(n² log k)

**Space Complexity**: O(k)
- Heap stores at most k elements

**Code Walkthrough**:
```python
pq = []  # Max heap (using negative values)
for i in range(n):
    for j in range(i + 1, n):
        # Push negative fraction to simulate max heap
        heapq.heappush(pq, (-arr[i] / arr[j], (i, j)))
        if len(pq) > k:
            heapq.heappop(pq)  # Remove largest fraction
```

After the loop, `pq[0]` contains the k-th smallest fraction.

**Better Solution (Follow-up)**: The problem asks for better than O(n²) complexity. This can be achieved using:
- **Binary Search + Two Pointers**: O(n log(max_value²)) - binary search on the fraction value
- **Min Heap with Smart Initialization**: O(k log n) - only explore necessary fractions

# Tags
#heap #priority-queue #two-pointers #binary-search #math #fractions #kth-element


## Problem

https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/description/

Given two 0-indexed integer permutations A and B of length n.

A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B.

Return the prefix common array of A and B.

A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly once.

**Example 1:**
- Input: A = [1,3,2,4], B = [3,1,2,4]
- Output: [0,2,3,4]
- Explanation: 
  - At i = 0: no number is common, so C[0] = 0.
  - At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
  - At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
  - At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.

**Example 2:**
- Input: A = [2,3,1], B = [3,1,2]
- Output: [0,1,3]
- Explanation:
  - At i = 0: no number is common, so C[0] = 0.
  - At i = 1: only 3 is common in A and B, so C[1] = 1.
  - At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.

**Constraints:**
- 1 <= A.length == B.length == n <= 50
- 1 <= A[i], B[i] <= n
- It is guaranteed that A and B are both a permutation of n integers.

## Observations

1. **Naive Approach Problem**: A naive approach would be to check for each prefix index i, which numbers from A[0..i] are also in B[0..i]. This would be O(n²) complexity.

2. **Efficient Tracking**: Instead of repeatedly checking membership, we can track which numbers we've seen in each array so far using frequency maps or sets.

3. **Key Insight**: When processing index i, we add A[i] to the count of seen numbers in A, and B[i] to the count in B. When a number becomes "common" (appears in both A and B up to index i), we increment the common count.

4. **Detection of Common Numbers**: A number becomes "common" when:
   - It's the same element at the same index in both arrays (A[i] == B[i]), OR
   - We just added it to one array, and it was already in the other array's prefix

5. **Two Dictionary Approach**: Using two dictionaries/maps to track the count of elements in the prefix of A and B allows us to check in O(1) time whether a newly added element was already seen in the other array.

## Solution

The solution uses an efficient **two-dictionary tracking approach** with O(n) time complexity:

```python
class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        n = len(A)
        res = []
        prefix_a = defaultdict(int)
        prefix_b = defaultdict(int)
        common = 0
        
        for i in range(n):
            a, b = A[i], B[i]
            prefix_a[a] += 1
            prefix_b[b] += 1
            
            # Case 1: Same element at same position
            if a == b:
                common += 1
            else:
                # Case 2: Different elements
                # Check if 'a' was already in B's prefix
                if prefix_a[a] == prefix_b[a]:
                    common += 1
                # Check if 'b' was already in A's prefix
                if prefix_a[b] == prefix_b[b]:
                    common += 1
            
            res.append(common)
        return res
```

**Algorithm Explanation:**

1. Initialize two dictionaries to track element frequencies in the prefixes of A and B
2. Initialize a `common` counter starting at 0
3. For each index i:
   - Add A[i] to prefix_a and B[i] to prefix_b
   - If A[i] == B[i], we found a matching element at the same position, increment common
   - Otherwise, check if the newly added elements were already in the other array:
     - If `prefix_a[a] == prefix_b[a]`, then 'a' just became equal in both arrays (was in B, now also counted in A)
     - If `prefix_a[b] == prefix_b[b]`, then 'b' just became equal in both arrays (was in A, now also counted in B)
   - Append the current common count to result

**Example Walkthrough (A = [1,3,2,4], B = [3,1,2,4]):**

- i=0: a=1, b=3
  - prefix_a={1:1}, prefix_b={3:1}
  - a≠b, prefix_a[1]≠prefix_b[1] (1≠0), prefix_a[3]≠prefix_b[3] (0≠1)
  - common=0 → [0]

- i=1: a=3, b=1
  - prefix_a={1:1, 3:1}, prefix_b={3:1, 1:1}
  - a≠b, prefix_a[3]==prefix_b[3] (1==1) ✓, prefix_a[1]==prefix_b[1] (1==1) ✓
  - common=2 → [0,2]

- i=2: a=2, b=2
  - prefix_a={1:1, 3:1, 2:1}, prefix_b={3:1, 1:1, 2:1}
  - a==b ✓
  - common=3 → [0,2,3]

- i=3: a=4, b=4
  - prefix_a={1:1, 3:1, 2:1, 4:1}, prefix_b={3:1, 1:1, 2:1, 4:1}
  - a==b ✓
  - common=4 → [0,2,3,4]

**Complexity Analysis:**
- **Time Complexity**: O(n) - single pass through both arrays
- **Space Complexity**: O(n) - for the two dictionaries and output array

# Tags
- Array
- Hash Table
- Prefix Sum
- Two Pointers (conceptually)
- Frequency Counting


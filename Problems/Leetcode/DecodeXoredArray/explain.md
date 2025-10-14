## Problem

https://leetcode.com/problems/decode-xored-array/

```
There is a hidden integer array arr that consists of n non-negative integers.

It was encoded into another integer array encoded of length n - 1, such that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then encoded = [1,2,3].

You are given the encoded array. You are also given an integer first, that is the first element of arr, i.e. arr[0].

Return the original array arr. It can be proved that the answer exists and is unique.

Example 1:

Input: encoded = [1,2,3], first = 1
Output: [1,0,2,1]
Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]

Example 2:

Input: encoded = [6,2,7,3], first = 4
Output: [4,2,0,7,4]

Constraints:

2 <= n <= 104
encoded.length == n - 1
0 <= encoded[i] <= 105
0 <= first <= 105
```

## Observations

1. **XOR Properties**
   - XOR is its own inverse: `a ^ b ^ b = a`
   - If `encoded[i] = arr[i] ^ arr[i+1]`, then `arr[i+1] = arr[i] ^ encoded[i]`
   
2. **Decoding Pattern**
   - Given: `encoded[i] = arr[i] ^ arr[i+1]`
   - To find `arr[i+1]`: XOR both sides with `arr[i]`
     - `encoded[i] ^ arr[i] = arr[i] ^ arr[i+1] ^ arr[i]`
     - `encoded[i] ^ arr[i] = arr[i+1]` (because `arr[i] ^ arr[i] = 0`)
   
3. **Sequential Reconstruction**
   - We know `arr[0] = first`
   - We can compute `arr[1] = arr[0] ^ encoded[0]`
   - Then `arr[2] = arr[1] ^ encoded[1]`
   - Continue until all elements are decoded

4. **Example Walkthrough**
   - Input: `encoded = [1,2,3]`, `first = 1`
   - `arr[0] = 1`
   - `arr[1] = 1 ^ 1 = 0`
   - `arr[2] = 0 ^ 2 = 2`
   - `arr[3] = 2 ^ 3 = 1`
   - Result: `[1, 0, 2, 1]`

## Solution

1. **Initialize**: Start with an array containing the first element: `arr = [first]`

2. **Iterate through encoded array**: For each value in the encoded array:
   - Get the last element of the result array: `arr[-1]`
   - XOR it with the current encoded value: `arr[-1] ^ val`
   - Append the result to the array

3. **Why it works**:
   - Since `encoded[i] = arr[i] ^ arr[i+1]`
   - We can derive: `arr[i+1] = arr[i] ^ encoded[i]`
   - Each iteration computes the next element using this relationship

4. **Complexity Analysis**:
   - **Time Complexity**: O(n) where n is the length of the encoded array. We iterate through it once.
   - **Space Complexity**: O(n) for storing the decoded array (required for output).

5. **Key Insight**: The XOR operation's self-inverse property allows us to "reverse" the encoding process simply by applying XOR again with the known element.

## Tags

array, bit manipulation
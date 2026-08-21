## Problem

https://leetcode.com/problems/minimum-operations-to-make-a-rotated-palindrome-i/description/

You are given a string `s` consisting of lowercase English letters.

You can perform the following operations any number of times (including zero) and in any order:

- **Increment**: Choose any index `i` and replace `s[i]` with the next lowercase English letter. The letter after `'z'` is `'a'`.
- **Left rotate**: Move the first character of the string to the end.

Return the **minimum number of operations** required to make `s` a palindrome.

**Example 1:**
```
Input: s = "abc"
Output: 2
Explanation:
  Left rotate: "abc" -> "bca"
  Increment 'a' to 'b': "bca" -> "bcb"
  "bcb" is a palindrome.
```

**Example 2:**
```
Input: s = "yb"
Output: 3
Explanation:
  Increment the first character three times: "yb" -> "zb" -> "ab" -> "bb"
  "bb" is a palindrome.
```

**Constraints:**
- `2 <= s.length <= 2000`
- `s` consists only of lowercase English letters.

---

## Ideas

### Key Observations

1. **Left rotate** only costs 1 operation per rotation. After `k` left rotations, the string becomes `s[k], s[k+1], ..., s[n-1], s[0], ..., s[k-1]`. Since there are exactly `n` distinct rotations (rotating `n` times returns to original), we only need to try all `n` possible rotations.

2. **Increment cost between two characters**: To make two characters `a` and `b` equal using only increment operations on either one of them, the minimum cost is the **circular distance** on the alphabet ring:
   $$\text{cost}(a, b) = \min(|a - b|,\ 26 - |a - b|)$$
   Note: We can only increment, but since the alphabet is circular (`'z'` wraps to `'a'`), incrementing enough steps in one direction simulates going the "short way" around. However, we can only increment (not decrement), so to match two characters we must choose which one to increment. Since we can increment either character, the minimum operations to make `a == b` is indeed the minimum circular distance.

3. **Cost to make a rotated string a palindrome**: For a given rotation, iterate over each mirrored pair `(s[i], s[n-1-i])` and sum up the circular distances. The total is the increment cost for that rotation.

4. **Total cost for rotation `k`**: `k` (the rotation cost) + increment cost to make the rotated string a palindrome.

5. **Answer**: Try all `n` rotations and return the minimum total cost.

### Algorithm

```
n = len(s)
answer = INF

for k in 0..n-1:
    rotated = s[k:] + s[:k]
    inc_cost = 0
    for i in 0..n/2-1:
        diff = |rotated[i] - rotated[n-1-i]|
        inc_cost += min(diff, 26 - diff)
    answer = min(answer, k + inc_cost)

return answer
```

### Complexity

- **Time**: $O(n^2)$ — for each of the `n` rotations, we scan $n/2$ pairs.
- **Space**: $O(n)$ for the rotated string (or $O(1)$ using index arithmetic).

### Notes

- We do NOT need to actually simulate rotations; just index into the original string using `(k + i) % n` and `(k + n - 1 - i) % n`.
- The rotation count `k` ranges from `0` to `n-1`; trying `k = n` is the same as `k = 0`.

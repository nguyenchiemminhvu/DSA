## Problem Description

https://leetcode.com/problems/duplicate-zeros/

```
Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.

Example 1:

Input: arr = [1,0,2,3,0,4,5,0]
Output: [1,0,0,2,3,0,0,4]
Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]

Example 2:

Input: arr = [1,2,3]
Output: [1,2,3]
Explanation: After calling your function, the input array is modified to: [1,2,3]

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 9
```

## Observations

Firstly, seeing that the constraints are small, we can simply create a buffer array length ```len(arr) + count_zero``` and copy data from original array to the buffer, make duplicate zero if facing them.

However, the target of this problem is to practice inplace operations on array.

We need to extend the buffer of ogirinal array with ```count_zero``` more elements and reorder them.

## Approaching

```python
count_zero = arr.count(0)
```

* Each zero will “expand” into **two slots** when duplicated.
* `count_zero` tells us how much extra space we temporarily need.

Example:

```
arr = [1,0,2,3,0]
count_zero = 2
```

---

### Temporarily extend the array

```python
arr.extend([0] * count_zero)
```

* Extend the array with extra zeros → creates buffer space so we don’t overwrite elements.
* This is temporary, we will shrink it back later.

Example:

```
Original: [1,0,2,3,0] (length = 5)
Extended: [1,0,2,3,0,0,0] (length = 7)
```

---

### Initialize two pointers

```python
i = n - 1                 # last index of original array
i_new = i + count_zero    # last index of extended array
```

* `i` → points to the original array (before extension).
* `i_new` → points to the extended array.
* We’ll move elements **from right to left**.

---

### Process elements backwards

```python
while i >= 0:
    if arr[i] == 0:
        arr[i_new], arr[i_new - 1] = 0, 0
        i_new -= 2
    else:
        arr[i_new] = arr[i]
        i_new -= 1
    i -= 1
```

* If the current element is **not zero**: copy it to `i_new`.
* If the current element **is zero**: duplicate it (`0,0`) into two positions.
* Move `i` back by 1, move `i_new` back by 1 or 2 depending on whether a zero was duplicated.

---

### Trim back to original size

```python
while (count_zero):
    arr.pop()
    count_zero -= 1
```

* Remove extra elements to restore the array length to its original size `n`.

---

## Example Walkthrough

Input:

```python
arr = [1,0,2,3,0,4,5,0]
```

1. Count zeros → `count_zero = 3`

2. Extend → `[1,0,2,3,0,4,5,0,0,0,0]`

3. Start pointers:

   * `i = 7` (last index of original array)
   * `i_new = 10` (last index of extended array)

4. Process backwards:

| Step | i | i_new | Action                         | Result (extended array)   |
| ---- | - | ----- | ------------------------------ | ------------------------- |
| 1    | 7 | 10    | Zero → write `[0,0]` at (10,9) | `[1,0,2,3,0,4,5,0,0,0,0]` |
| 2    | 6 | 8     | Copy `5` to index 8            | `[1,0,2,3,0,4,5,0,5,0,0]` |
| 3    | 5 | 7     | Copy `4` to index 7            | `[1,0,2,3,0,4,5,4,5,0,0]` |
| 4    | 4 | 6     | Zero → write `[0,0]` at (6,5)  | `[1,0,2,3,0,0,0,4,5,0,0]` |
| 5    | 3 | 4     | Copy `3` to index 4            | `[1,0,2,3,3,0,0,4,5,0,0]` |
| 6    | 2 | 3     | Copy `2` to index 3            | `[1,0,2,2,3,0,0,4,5,0,0]` |
| 7    | 1 | 2     | Zero → write `[0,0]` at (2,1)  | `[1,0,0,2,3,0,0,4,5,0,0]` |
| 8    | 0 | 0     | Copy `1` to index 0            | `[1,0,0,2,3,0,0,4,5,0,0]` |

5. Trim → `[1,0,0,2,3,0,0,4]`

Final output:

```
[1,0,0,2,3,0,0,4]
```

## Tags

array, in-place operation
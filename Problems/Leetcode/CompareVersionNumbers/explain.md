## Problem Description

https://leetcode.com/problems/compare-version-numbers

```
Given two version strings, version1 and version2, compare them. A version string consists of revisions separated by dots '.'. The value of the revision is its integer conversion ignoring leading zeros.

To compare version strings, compare their revision values in left-to-right order. If one of the version strings has fewer revisions, treat the missing revision values as 0.

Return the following:

If version1 < version2, return -1.
If version1 > version2, return 1.
Otherwise, return 0.

Example 1:

Input: version1 = "1.2", version2 = "1.10"

Output: -1

Explanation:

version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.

Example 2:

Input: version1 = "1.01", version2 = "1.001"

Output: 0

Explanation:

Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

Example 3:

Input: version1 = "1.0", version2 = "1.0.0.0"

Output: 0

Explanation:

version1 has less revisions, which means every missing revision are treated as "0".

Constraints:

1 <= version1.length, version2.length <= 500
version1 and version2 only contain digits and '.'.
version1 and version2 are valid version numbers.
All the given revisions in version1 and version2 can be stored in a 32-bit integer.
```

## Problem Restatement

Given two version strings, each separated by a dot ```.```

Each revision is an integer, no leading zeros.

Version has fewer revision, the missing revisions will be treated as ```0```

Three cases:
- version1 < version2 => return -1
- version1 > version2 => return 1
- version1 == version2 => return 0

## Observations

Leading zeros can be removed by casting to integer.

It is easier to compare a list (array or vector) than keeping string format separated by dots.

It is easier to comapre after making both list (array or vector) the same length.

Comparison shall go from left to right, conclusion can be made right at the time having a mismatch.

## Examples

### Example 1:

**Input:**

```version1 = "1.2"```

```version2 = "1.10"```

After converting to lists:

```L1 = [1, 2]```

```L2 = [1, 10]```

Both lists have the same length, don't need to fill the missing revisions.

Starting at index ```0```:

```1 == 1``` -> continue

```2 < 10``` -> return ```-1```

**Output:**

```-1```

### Example 2

**Input:**

```version1 = "1.01"```

```version2 = "1.001"```

After converting to lists, and remove leading zeros:

```L1 = [1, 1]```

```L2 = [1, 1]```

Both lists have the same length, don't need to fill the missing revisions.

Starting at index ```0```:

```1 == 1``` -> continue

```1 == 1``` -> return ```0```

**Output:**

```0```

### Example 3

**Input:**

```version1 = "1.0"```

```version2 = "1.0.0.0"```

After converting to lists, and remove leading zeros:

```L1 = [1, 0]```

```L2 = [1, 0, 0, 0]```

Lists don't have the same length, need to fill the missing revisions.

```L1 = [1, 0, 0, 0]```

```L2 = [1, 0, 0, 0]```

Starting at index ```0```:

```1 == 1``` -> continue

```0 == 0``` -> continue

```0 == 0``` -> continue

```0 == 0``` -> continue

**Output:**

```0```

## Complexity

**Time Complexity**: O(max(n, m)) where n and m are the number of revisions in version1 and version2.

**Space Complexity**: O(max(n, m)) for storing padded lists.

## Tags

array, string
## Problem: Maximum Tastiness After Giving Away the Best Candy

### Description

```
You are given an array of integers ( A_1, A_2, \dots, A_N ), where each value represents the **tastiness** of a candy.

You want to choose a **contiguous subarray** ([L, R]) (with (L \le R)) and buy all candies in that range.

After buying:

* You must give **exactly one candy** (the tastiest one in the chosen subarray) to Joonwon.
* You keep the rest.

Your goal is to **maximize the total tastiness of the candies you keep**, i.e.:

[
\sum_{i=L}^{R} A_i - \max_{i=L}^{R} A_i
]
```

---

### Input

```
* Integer (N) ((2 \le N \le 200{,}000))
* Array (A) of size (N), where:
  [
  -10^9 \le A_i \le 10^9
  ]
```

---

### Output

* A single integer: the **maximum possible tastiness** you can keep.

---

### Example

#### Input

```
5
3 -2 5 1 -3
```

#### Output

```
2
```
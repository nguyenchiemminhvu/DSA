## 🏔️ Problem: Gondola Lift Construction

### 📄 Description

```
There are (N) mountain peaks arranged in a line along the ridge. The peaks are numbered from **1 to N (west to east)**, and each peak has an elevation (A_i).

The government wants to build **gondola lifts** so that **every peak is reachable from any other peak** using only these lifts.
```

---

### 🔗 Rules for Building a Gondola Lift

```
You can build a gondola lift between two peaks (i) and (j) if:

* (i < j)
* (j - i \ge K) (they must be at least (K) apart)
```

---

### 💰 Cost of a Lift

```
For a lift between peaks (i) and (j), the cost is:

[
\max(A_i, A_{i+1}, \ldots, A_j)
]

That is, the **maximum elevation in the segment** ([i, j]).
```

---

### 🎯 Goal

```
* Connect all peaks (i.e., make the graph **connected**)
* Minimize the **total cost**
```

---

### ❌ If impossible, output:

```
[
-1
]
```

---

### 📥 Input

```
* First line: (N, K)
* Second line: (A_1, A_2, \ldots, A_N)
```

---

### 📤 Output

```
* Minimum total cost, or (-1) if impossible
```

## Problem

https://leetcode.com/problems/binary-tree-coloring-game/description/

Two players play a turn-based game on a binary tree with `n` nodes (n is odd, values 1..n are distinct).

- **Player 1** picks node `x` and colors it **red**.
- **Player 2** picks any other node `y` and colors it **blue**.
- Each turn, a player extends their color to an uncolored neighbor (left child, right child, or parent) of any node they already own.
- The player who colors more nodes **wins**.

You are **Player 2**. Return `true` if there exists a choice of `y` that guarantees Player 2 wins.

---

## Key Insight

Once Player 1 picks node `x`, the tree is split into **three disjoint regions** that Player 2 can try to claim by placing `y` on a neighbor of `x`:

```
         [parent side]
               |
               x          <-- Player 1 starts here
             /   \
        [left]  [right]
       subtree  subtree
```

Let:
- `L` = number of nodes in x's **left subtree**
- `R` = number of nodes in x's **right subtree**
- `P` = `n - L - R - 1` (the **parent side**: everything above x)

If Player 2 places `y` on x's left child → Player 2 can capture all `L` nodes.  
If Player 2 places `y` on x's right child → Player 2 can capture all `R` nodes.  
If Player 2 places `y` on x's parent → Player 2 can capture all `P` nodes.

Player 1 is locked inside its chosen region and cannot cross into the others.

**Player 2 wins if and only if** any one region is strictly greater than `n / 2`:

$$\max(L, R, P) > \frac{n}{2}$$

---

## Algorithm

1. **Find node `x`** in the tree via DFS/BFS.
2. **Count** `L` (size of x's left subtree) and `R` (size of x's right subtree).
3. Compute `P = n - L - R - 1`.
4. Return `max(L, R, P) > n / 2`.

**Time complexity:** O(n) — one full tree traversal to count subtree sizes.  
**Space complexity:** O(h) — recursion stack, where h is the height of the tree.

---

## Example Walkthrough

**Example 1:** `root = [1,2,3,4,5,6,7,8,9,10,11]`, `n = 11`, `x = 3`

```
            1
          /   \
         2     3       <-- x = 3
        / \   / \
       4   5 6   7
      / \ / \
     8  9 10 11
```

- Node 3 has: left child = 6 (L = 1), right child = 7 (R = 1)
- P = 11 - 1 - 1 - 1 = 8

`max(1, 1, 8) = 8 > 5` → **true** ✅  
Player 2 picks node 2 (parent side) and captures 8 nodes.

**Example 2:** `root = [1,2,3]`, `n = 3`, `x = 1`

- Node 1 is the root: L = 1, R = 1, P = 0
- `max(1, 1, 0) = 1`, which is NOT > 1.5 → **false** ❌

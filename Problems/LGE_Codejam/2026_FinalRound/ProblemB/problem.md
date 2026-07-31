https://codejam.lge.com/contest/problem/1686/2

## Description
In Squirrel Town, there is a straight trail of length $L$. The trail begins at position $0$ and ends at position $L$.
There are $N$ acorns along the trail, and the $i$-th acorn is located at position $A_i$. Squirrel wants to pick up at least $K$ of them.
Squirrel can start at an arbitrary position on the trail. Squirrel can freely move to the left or to the right, and can pick up an acorn if it reaches the position at which the acorn is located.
Squirrel plans to pick up at least $K$ acorns. Compute the minimum distance Squirrel must travel (after starting to move) to pick up $K$ or more acorns.

## Input
The first line of input will contain the length of the trail $L$, the number of acorns $N$, and the number of acorns Squirrel wants to pick up $K$, all separated by whitespace.
The second line will contain the locations of acorns, $A_1, A_2, \cdots, A_N$, separated by whitespace.

## Output
Output the minimum distance Squirrel must travel in order to pick up at least $K$ acorns.

## Limit

* $1 \le L \le 1\,000\,000\,000$
* $1 \le K \le N \le 100\,000$
* $N < L + 1$
* $0 \le A_i \le L$
* $A_i < A_{i+1}$; that is, $A_1, \cdots, A_N$ are increasing

https://codejam.lge.com/contest/problem/1686/1

## Description
You are given an integer array $A$ of length $N$ with $A = [A_1, A_2, \cdots, A_N]$ and an integer $K$.
You can pick one index $i$ (between $1$ and $N$, inclusive) and increase $A_i$ by $1$, through one operation.
Your goal is to meet the following conditions by applying $0$ or more operations on $A$ (let us call the resulting array $B$):

   1. $B_1 < B_2 < \cdots < B_N$
   2. For every $i$ with ($1 \le i < N$), the value $B_{i+1}\text{ modulo }K$ is the same as the value $B_i + 1\text{ modulo }K$.

Compute the minimum number of operations you need to satisfy the conditions.

## Input
The first line of input will contain $T$, the number of test cases.
Each test case will consist of two lines of input.
The first line of a test case input will contain $N$ and $K$, separated by whitespace.
The second line will contain $N$ integers of array $A$, $A_1, A_2, \cdots, A_N$ separated by whitespace.

## Output
For each test case, output the minimum number of operations you need to meet the conditions.

## Limit

* $1 \le T \le 100$
* $1 \le N \le 100\,000$
* $1 \le A_i \le 1\,000\,000\,000$
* $1 \le K \le 20$
* The sum of $N$ across all test cases will be at most $100\,000$.
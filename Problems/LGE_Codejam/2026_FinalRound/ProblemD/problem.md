https://codejam.lge.com/contest/problem/1686/4

## Description
There are $N$ buildings located along a straight road. The buildings are numbered $1$ to $N$ from West to East, and the $i$-th building's height is $A_i$ meters.
The Tourism Ministry wants to evaluate the View Score of this road. A tourist would pick a contiguous segment of the road, stand at the West end of the segment, and look toward the East end of the segment. Then, the taller building closer to the tourist could screen the shorter building farther from the tourist, and thus the tourist may only see a subset of the buildings in the segment.
Suppose that a tourist picks a segment $[l, r]$ with building $l$ being the left-end and building $r$ being the right-end ($1 \le l \le r \le N$). Consider building $i$ in this segment ($l \le i \le r$). For the buildings on the west side of this building -- that is, if $A_j < A_i$ for every $j$ with $l \le j < i$, then building $i$ would be visible to the tourist. (For a given building, if there is any other building on its west that is no shorter than it, then the building would be screened.) For a segment $[l, r]$, let $f(l, r)$ be the number of buildings visible to the tourist when standing at the west end.
The Tourism Ministry considers every segment equally. Hence, the total View Score is defined as the sum of $f(l, r)$ over $1 \le l \le r \le N$:
$$S = \sum_{l=1}^{N} \sum_{r=l}^{N} f(l, r)$$ 
Compute the View Score $S$ of the given road.

## Input
The first line of input will contain $N$, the number of buildings.
The second line will contain $N$ integers $A_1, A_2, \dots, A_N$, separated by whitespace.

## Output
Output the View Score $S$ in a single line.

## Limit

* $1 \le N \le 1\,000\,000$
* $1 \le A_i \le 10^9$

## Problem

https://leetcode.com/problems/destination-city/description/

```
You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi. Return the destination city, that is, the city without any path outgoing to another city.

It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be exactly one destination city.

Example 1:

Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
Output: "Sao Paulo" 
Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".

Example 2:

Input: paths = [["B","C"],["D","B"],["C","A"]]
Output: "A"
Explanation: All possible trips are: 
"D" -> "B" -> "C" -> "A". 
"B" -> "C" -> "A". 
"C" -> "A". 
"A". 
Clearly the destination city is "A".

Example 3:

Input: paths = [["A","Z"]]
Output: "Z"

Constraints:

1 <= paths.length <= 100
paths[i].length == 2
1 <= cityAi.length, cityBi.length <= 10
cityAi != cityBi
All strings consist of lowercase and uppercase English letters and the space character.
```

## Observations

1. **Graph Structure**: The problem describes a directed graph where each path represents an edge from one city to another.

2. **Destination City Property**: The destination city is the only city that has no outgoing edges (no path leading to another city).

3. **Graph Characteristics**:
   - Forms a line without loops (guaranteed)
   - Exactly one destination city exists
   - Each city can appear multiple times in the paths array (as source or destination)

4. **Key Insight**: We need to find a city that appears in the paths but never as a source city (only as a destination).

## Solution

1. **Build Graph and City Set**:
   - Create a set `s` to store all unique cities
   - Create a graph dictionary where each city maps to its adjacent cities
   - For each path [a, b]:
     - Add both cities to the set
     - Build adjacency list: city `a` has an outgoing edge to city `b`

2. **Find Destination**:
   - Iterate through all cities in the set
   - The city that is NOT in the graph dictionary is the destination
   - This city appears in paths but never has outgoing edges

**Why This Works**:
- Cities with outgoing edges are stored as keys in the graph dictionary
- The destination city only appears as a destination (right side of paths) but never as a source (left side)
- Therefore, it won't be a key in the graph dictionary

**Example Walkthrough** (paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]):

1. After processing paths:
   - `s` = {"London", "New York", "Lima", "Sao Paulo"}
   - `graph` = {"London": ["New York"], "New York": ["Lima"], "Lima": ["Sao Paulo"]}

2. Check each city:
   - "London" is in graph ✗
   - "New York" is in graph ✗  
   - "Lima" is in graph ✗
   - "Sao Paulo" is NOT in graph ✓ → Return "Sao Paulo"

**Alternative Simpler Approach**:
```python
def destCity(self, paths: List[List[str]]) -> str:
    sources = {path[0] for path in paths}
    for path in paths:
        if path[1] not in sources:
            return path[1]
```
This approach directly finds the destination by checking which city appears as a destination but never as a source.

# Tags

`Graph` `Hash Set` `Array` `String`


## Problem

https://leetcode.com/problems/design-browser-history/description/

```
You have a browser of one tab where you start on the homepage and you can visit another url, 
get back in the history number of steps or move forward in the history number of steps.

Implement the BrowserHistory class:
- BrowserHistory(string homepage): Initializes the object with the homepage of the browser.
- void visit(string url): Visits url from the current page. It clears up all the forward history.
- string back(int steps): Move steps back in history. If you can only return x steps in the history 
  and steps > x, you will return only x steps. Return the current url after moving back in history 
  at most steps.
- string forward(int steps): Move steps forward in history. If you can only forward x steps in the 
  history and steps > x, you will forward only x steps. Return the current url after forwarding in 
  history at most steps.

Example:
Input:
["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
[["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]

Output:
[null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]

Explanation:
BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
browserHistory.visit("google.com");       // You are in "leetcode.com". Visit "google.com"
browserHistory.visit("facebook.com");     // You are in "google.com". Visit "facebook.com"
browserHistory.visit("youtube.com");      // You are in "facebook.com". Visit "youtube.com"
browserHistory.back(1);                   // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
browserHistory.back(1);                   // You are in "facebook.com", move back to "google.com" return "google.com"
browserHistory.forward(1);                // You are in "google.com", move forward to "facebook.com" return "facebook.com"
browserHistory.visit("linkedin.com");     // You are in "facebook.com". Visit "linkedin.com"
browserHistory.forward(2);                // You are in "linkedin.com", you cannot move forward any steps.
browserHistory.back(2);                   // You are in "linkedin.com", move back two steps to "facebook.com" then to "google.com". return "google.com"
browserHistory.back(7);                   // You are in "google.com", you can move back only one step to "leetcode.com". return "leetcode.com"
```

## Observations

1. **Browser History Behavior**: The problem simulates a web browser's back/forward navigation where:
   - Visiting a new URL clears all forward history (like in real browsers)
   - We can go back through previously visited pages
   - We can go forward only if we haven't visited a new page after going back

2. **Data Structure Choice**: A doubly linked list is ideal because:
   - We need bidirectional traversal (back and forward)
   - We need to efficiently clear forward history when visiting a new page
   - We only need to maintain relative ordering, not random access

3. **Key Operations**:
   - **Visit**: Creates a new node, links it to current, clears forward history (by not preserving old `next` pointer)
   - **Back**: Traverse backwards up to `steps` times, bounded by available history
   - **Forward**: Traverse forwards up to `steps` times, bounded by available forward history

4. **Edge Cases**:
   - Steps exceeding available history (handled by checking `p.prev` and `p.next`)
   - Starting at homepage (no previous history)
   - Visiting after going back (forward history is lost)

## Solution

### Approach: Doubly Linked List

**Time Complexity**:
- `__init__`: O(1)
- `visit`: O(1)
- `back`: O(min(steps, history_length))
- `forward`: O(min(steps, forward_history_length))

**Space Complexity**: O(n) where n is the number of unique URLs visited

**Algorithm**:

1. **Initialization**:
   - Create a `ListNode` for the homepage
   - Set `cur` pointer to this initial node

2. **Visit Operation**:
   - Create a new node with the given URL
   - Link it to current node: `cur.next = new_node` and `new_node.prev = cur`
   - Move current pointer to the new node
   - **Important**: By creating a new node and not preserving the old `next` pointer, we automatically clear forward history

3. **Back Operation**:
   - Start from current node
   - Traverse backwards using `prev` pointers up to `steps` times
   - Stop early if we reach the beginning (when `p.prev` is None)
   - Update `cur` to the final position and return its URL

4. **Forward Operation**:
   - Start from current node
   - Traverse forwards using `next` pointers up to `steps` times
   - Stop early if we reach the end (when `p.next` is None)
   - Update `cur` to the final position and return its URL

**Why This Works**:

- The doubly linked list maintains the chronological order of visited pages
- Each node knows its previous and next page
- When visiting a new page, we only set `cur.next` to the new node, effectively discarding any forward history
- The `while` loop conditions (`p and p.prev and steps`) ensure we don't go past boundaries
- Decrementing `steps` ensures we move exactly the requested amount or until we hit a boundary

# Tags

`Linked List` `Doubly Linked List` `Design` `Data Structure`


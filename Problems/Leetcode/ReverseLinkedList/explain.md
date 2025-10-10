## Problem Description

https://leetcode.com/problems/reverse-linked-list/

```
Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:

Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:

Input: head = [1,2]
Output: [2,1]

Example 3:

Input: head = []
Output: []
```

## Solution

We can solve this problem by reversing the linked list in place using three pointers:

```prev_node``` – the head of the already reversed part of the list (starts as None).

```cur_node``` – the current node we are processing (starts as head).

```next_node``` – a temporary pointer to save the next node, so we don’t lose the rest of the list when reversing links.

At each iteration of the loop:

Save the next node: ```next_node = cur_node.next```.

Reverse the current node’s pointer: ```cur_node.next = prev_node```.

Move ```prev_node``` forward: ```prev_node = cur_node```.

Move ```cur_node``` forward: ```cur_node = next_node```.

This continues until ```cur_node``` becomes ```None```, which means we have processed the entire list. At that point, ```prev_node``` will be the new head of the reversed list.

Example walkthrough

Input: ```1 -> 2 -> 3 -> 4 -> 5 -> None```

Start: ```prev = None```, ```cur = 1```

```
Step 1: reverse 1, list looks like 1 -> None, cur = 2

Step 2: reverse 2, list looks like 2 -> 1 -> None, cur = 3

Step 3: reverse 3, list looks like 3 -> 2 -> 1 -> None, cur = 4

Step 4: reverse 4, list looks like 4 -> 3 -> 2 -> 1 -> None, cur = 5

Step 5: reverse 5, list looks like 5 -> 4 -> 3 -> 2 -> 1 -> None, cur = None
```

Loop ends, return ```prev```.

## Complexity

Time Complexity: ```O(n)``` — each node is visited once.

Space Complexity: ```O(1)``` — only three extra pointers are used.

## Tags

linked list
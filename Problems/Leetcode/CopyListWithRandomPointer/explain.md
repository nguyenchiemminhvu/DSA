## Problem Description

https://leetcode.com/problems/copy-list-with-random-pointer/

```
A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Example 1:

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Example 2:

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Example 3:

Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Constraints:

0 <= n <= 1000
-104 <= Node.val <= 104
Node.random is null or is pointing to some node in the linked list.
```

## Observations

The problem is about making a deep copy of a special linked list where each node has two pointers:

```next``` → points to the next node in the list.

```random``` → can point to any node in the list (or ```null```).

A "```deep copy```" means that we cannot reuse the old nodes. Instead, we must create entirely new nodes, where both next and random correctly connect to the copied nodes.

**Challenges:**

Normally, copying a linked list is easy when there is only the ```next``` pointer.

The difficulty here is the ```random``` pointer, since it can point anywhere.

If we only go through the list once, we don’t yet know where the ```random``` should point in the copied list, because that target node may not have been created yet.

**Key idea:**

We need a way to ```“map”``` old nodes to new nodes so that when we set the random pointer, we know which new node corresponds to the old node.

## Solutions

There are multiple ways to solve this, but your code follows a two-pass approach using an ```array```:

**First pass (create new nodes):**

Traverse the original list and create a new node for each old node.

Store these new nodes in an array (```new_arr```).

At the same time, temporarily replace the old node’s val with its ```index``` in the array. This gives us an easy way to later map ```random``` pointers by ```index```.

**Example:**

If the list is ```7 → 13 → 11```, we store new nodes ```[7', 13', 11']``` in ```new_arr```, and mark original values as indexes ```0, 1, 2```.

**Connect next pointers:**

Using the ```new_arr```, we connect each new node’s next pointer to the next one.

This makes a normal copy of the list without handling random.

**Second pass (fix random pointers):**

Go through the original list again.

If an old node has a ```random```, then:

The old node’s ```index``` (stored in its val) tells us which new node we are at.

The old node’s ```random.val``` gives the ```index``` of the target random node.

Use these indexes to set the correct ```random``` link in ```new_arr```.

Return the head of the new list:

Finally, return ```new_arr[0]```, which is the deep copy’s head.

## Tags

linked list
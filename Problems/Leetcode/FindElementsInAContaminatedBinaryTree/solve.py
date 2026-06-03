from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class FindElements:

    def __init__(self, root: Optional[TreeNode]):
        self.s = set()
        def dfs(root, val):
            if not root:
                return
            dfs(root.left, val * 2 + 1)
            self.s.add(val)
            dfs(root.right, val * 2 + 2)
        dfs(root, 0)

    def find(self, target: int) -> bool:
        return target in self.s

# Your FindElements object will be instantiated and called as such:
# obj = FindElements(root)
# param_1 = obj.find(target)
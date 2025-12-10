class ListNode:
    def __init__(self, url: str):
        self.url = url
        self.next = None
        self.prev = None

class BrowserHistory:

    def __init__(self, homepage: str):
        self.cur = ListNode(homepage)

    def visit(self, url: str) -> None:
        self.cur.next = ListNode(url)
        self.cur.next.prev = self.cur
        self.cur = self.cur.next

    def back(self, steps: int) -> str:
        p = self.cur
        while p and p.prev and steps:
            p = p.prev
            steps -= 1
        
        self.cur = p
        return p.url

    def forward(self, steps: int) -> str:
        p = self.cur
        while p and p.next and steps:
            p = p.next
            steps -= 1
        
        self.cur = p
        return p.url

# Your BrowserHistory object will be instantiated and called as such:
# obj = BrowserHistory(homepage)
# obj.visit(url)
# param_2 = obj.back(steps)
# param_3 = obj.forward(steps)
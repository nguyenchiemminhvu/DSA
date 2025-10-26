from typing import List

class Bank:
    def __init__(self, balance: List[int]):
        self.balance = balance
        self.num_acc = len(balance)

    def transfer(self, account1: int, account2: int, money: int) -> bool:
        idx1 = account1 - 1
        idx2 = account2 - 1
        if idx1 < 0 or idx1 >= self.num_acc or idx2 < 0 or idx2 >= self.num_acc:
            return False
        if self.balance[idx1] < money:
            return False
        self.balance[idx1] -= money
        self.balance[idx2] += money
        return True

    def deposit(self, account: int, money: int) -> bool:
        idx = account - 1
        if idx < 0 or idx >= self.num_acc:
            return False
        self.balance[idx] += money
        return True

    def withdraw(self, account: int, money: int) -> bool:
        idx = account - 1
        if idx < 0 or idx >= self.num_acc:
            return False
        if self.balance[idx] < money:
            return False
        self.balance[idx] -= money
        return True


# Your Bank object will be instantiated and called as such:
# obj = Bank(balance)
# param_1 = obj.transfer(account1,account2,money)
# param_2 = obj.deposit(account,money)
# param_3 = obj.withdraw(account,money)
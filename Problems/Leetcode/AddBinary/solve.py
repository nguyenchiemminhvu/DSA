import unittest

class Solution:
    def addBinary(self, a: str, b: str) -> str:
        a = [(ord(val) - ord('0')) for val in reversed(a)]
        b = [(ord(val) - ord('0')) for val in reversed(b)]
        temp = [0] * (max(len(a), len(b)) + 1)

        for i in range(0, len(a)):
            temp[i] += a[i]
        for i in range(0, len(b)):
            temp[i] += b[i]

        for i in range(0, len(temp) - 1):
            if temp[i] > 1:
                temp[i + 1] += 1
                temp[i] %= 2
        if temp[-1] == 0:
            temp.pop()
        temp = [chr(ord('0') + val) for val in reversed(temp)]
        return "".join(temp)

class TestAddBinary(unittest.TestCase):
    def setUp(self):
        self.sol = Solution()

    def test_case_1(self):
        a = "11"
        b = "1"
        expected = "100"
        self.assertEqual(self.sol.addBinary(a, b), expected)

    def test_case_2(self):
        a = "1010"
        b = "1011"
        expected = "10101"
        self.assertEqual(self.sol.addBinary(a, b), expected)

    def test_case_3(self):
        a = "0"
        b = "0"
        expected = "0"
        self.assertEqual(self.sol.addBinary(a, b), expected)

    def test_case_4(self):
        a = "111"
        b = "111"
        expected = "1110"
        self.assertEqual(self.sol.addBinary(a, b), expected)

    def test_case_5(self):
        a = "1"
        b = "111"
        expected = "1000"
        self.assertEqual(self.sol.addBinary(a, b), expected)

if __name__ == "__main__":
    unittest.main()
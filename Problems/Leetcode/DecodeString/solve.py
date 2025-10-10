from collections import deque
import unittest

class Solution:
    def decodeString(self, s: str) -> str:
        st_str = deque()
        st_num = deque()
        
        cur_num = 0
        cur_str = ""
        i = 0
        n = len(s)
        while i < n:
            if s[i] == ']':
                st_str.append(cur_str)
                cur_str = ""
                temp_str = ""
                while len(st_str) > 0 and st_str[-1] != '[':
                    temp_str = st_str[-1] + temp_str
                    st_str.pop()
                st_str.pop() # pop the open bracket [
                temp_num = st_num.pop()
                st_str.append(temp_str * temp_num)
            else:
                if s[i] == '[':
                    st_str.append(cur_str)
                    cur_num = 0
                    cur_str = ""
                    st_str.append(s[i]) # push the open bracket [
                else:
                    if s[i].isdigit():
                        # push the current string before the digits
                        if cur_str != "":
                            st_str.append(cur_str)
                            cur_str = ""
                        # build the number
                        while i < n and s[i].isdigit():
                            cur_num = cur_num * 10 + (ord(s[i]) - ord('0'))
                            i += 1
                        i -= 1
                        st_num.append(cur_num)
                    else:
                        cur_str = cur_str + s[i]
            i += 1
        
        if len(cur_str) > 0:
            st_str.append(cur_str)
        return "".join(st_str)

class TestDecodeString(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        s = "3[a]2[bc]"
        expected = "aaabcbc"
        self.assertEqual(self.solution.decodeString(s), expected)

    def test_case_2(self):
        s = "3[a2[c]]"
        expected = "accaccacc"
        self.assertEqual(self.solution.decodeString(s), expected)

    def test_case_3(self):
        s = "2[abc]3[cd]ef"
        expected = "abcabccdcdcdef"
        self.assertEqual(self.solution.decodeString(s), expected)

    def test_case_4(self):
        s = "abc3[cd]xyz"
        expected = "abccdcdcdxyz"
        self.assertEqual(self.solution.decodeString(s), expected)

    def test_case_5(self):
        s = "10[a]"
        expected = "aaaaaaaaaa"
        self.assertEqual(self.solution.decodeString(s), expected)

if __name__ == "__main__":
    unittest.main()
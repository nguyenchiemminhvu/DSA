class Solution:
    def removeOuterParentheses(self, s: str) -> str:
        res = ""
        level = 0
        cur_s = ""
        for c in s:
            if c == '(':
                level += 1
                cur_s += '('
            else:
                level -= 1
                cur_s += ')'
                if level == 0:
                    if len(cur_s) > 2:
                        res += cur_s[1:len(cur_s)-1]
                    cur_s = ""
                
        return res
from typing import List

class Solution:
    def parseBoolExpr(self, s: str) -> bool:
        def parse_not(arr: List[str]) -> bool:
            return True if arr[0] == 'f' else False
        
        def parse_and(arr: List[str]) -> bool:
            return all(val == 't' for val in arr)
        
        def parse_or(arr: List[str]) -> bool:
            return any(val == 't' for val in arr)
        
        n = len(s)
        st = []
        i = 0
        while i < n:
            c = s[i]
            if c in '&|!(':
                st.append(c)
            elif c == ')':
                arr = []
                # Safely pull elements out until reaching the opening parenthesis
                while st and st[-1] != '(':
                    val = st.pop()
                    arr.append(val)
                
                st.pop()  # Remove '('
                op = st.pop()  # Remove the operator ('!', '&', '|')
                
                if op == '!':
                    res = parse_not(arr)
                elif op == '&':
                    res = parse_and(arr)
                elif op == '|':
                    res = parse_or(arr)
                
                st.append('t' if res else 'f')
            else:
                if c in 'tf':
                    st.append(c)
            i += 1
        
        return True if st[0] == 't' else False

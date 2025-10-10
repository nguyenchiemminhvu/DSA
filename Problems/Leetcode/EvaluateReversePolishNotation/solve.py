from collections import deque

class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        st = deque()
        for token in tokens:
            try:
                val = int(token)
                st.append(val)
            except ValueError:
                # it is an operand, pick 2 values from stack to make calculation
                b = st.pop()
                a = st.pop()
                match token:
                    case "+":
                        st.append(a + b)
                    case "-":
                        st.append(a - b)
                    case "*":
                        st.append(a * b)
                    case "/":
                        st.append(int(a / b))
        return st.pop()
class Solution:
    def calculate(self, s: str) -> int:
        def precedence(op: str) -> int:
            if op in ('+', '-'):
                return 1
            return 0

        def apply_op(ops: list, values: list):
            if len(values) < 2:
                return
            val2 = values.pop()
            val1 = values.pop()
            op = ops.pop()
            if op == '+':
                values.append(val1 + val2)
            elif op == '-':
                values.append(val1 - val2)

        values = []  # Operand stack
        ops = []     # Operator stack
        i = 0
        n = len(s)
        
        # Track if the next '-' seen should be treated as a unary operator
        is_unary = True 

        while i < n:
            if s[i] == ' ':
                i += 1
                continue

            # 1. Parse multi-digit numbers
            if s[i].isdigit():
                val = 0
                while i < n and s[i].isdigit():
                    val = val * 10 + int(s[i])
                    i += 1
                values.append(val)
                is_unary = False  # Next operator will not be unary
                continue

            # 2. Handle open parenthesis
            elif s[i] == '(':
                ops.append(s[i])
                is_unary = True  # An operator right after '(' is unary

            # 3. Handle closing parenthesis
            elif s[i] == ')':
                while ops and ops[-1] != '(':
                    apply_op(ops, values)
                ops.pop()  # Remove '('
                is_unary = False  # Next operator will not be unary

            # 4. Handle operators (+, -)
            elif s[i] in ('+', '-'):
                # Resolve unary minus by pushing a dummy 0
                if s[i] == '-' and is_unary:
                    values.append(0)
                
                while ops and ops[-1] != '(' and precedence(ops[-1]) >= precedence(s[i]):
                    apply_op(ops, values)
                ops.append(s[i])
                is_unary = True  # An operator right after another operator is unary

            i += 1

        # Clear remaining operators in the stack
        while ops:
            apply_op(ops, values)

        return values[0] if values else 0

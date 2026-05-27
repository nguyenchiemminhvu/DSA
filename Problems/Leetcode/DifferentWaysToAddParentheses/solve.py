from typing import List

class Solution:
    def diffWaysToCompute(self, s: str) -> List[int]:
        # Loop through the expression
        #   Every time see an operator (+, -, *):
        #   Split the string into:
        #       left part
        #       right part
        #   Recursively compute all results for:
        #       left side
        #       right side
        # Combine results from left & right using the operator

        def F(exp: str) -> List[int]:
            res = []
            for i, c in enumerate(exp):
                if c in '+-*':
                    left_exp = exp[:i]
                    right_exp = exp[i + 1:]

                    left_arr = F(left_exp)
                    right_arr = F(right_exp)
                    for val1 in left_arr:
                        for val2 in right_arr:
                            if c == '+':
                                res.append(val1 + val2)
                            elif c == '-':
                                res.append(val1 - val2)
                            else:
                                res.append(val1 * val2)
            if not res:
                res.append(int(exp))
            
            return res
        
        return F(s)
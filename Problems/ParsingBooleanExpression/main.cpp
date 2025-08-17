/**
https://leetcode.com/problems/parsing-a-boolean-expression/description

A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:

't' that evaluates to true.
'f' that evaluates to false.
'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
Given a string expression that represents a boolean expression, return the evaluation of that expression.

It is guaranteed that the given expression is valid and follows the given rules.

Example 1:

Input: expression = "&(|(f))"
Output: false
Explanation: 
First, evaluate |(f) --> f. The expression is now "&(f)".
Then, evaluate &(f) --> f. The expression is now "f".
Finally, return false.

Example 2:

Input: expression = "|(f,f,f,t)"
Output: true
Explanation: The evaluation of (false OR false OR false OR true) is true.

Example 3:

Input: expression = "!(&(f,t))"
Output: true
Explanation: 
First, evaluate &(f,t) --> (false AND true) --> false --> f. The expression is now "!(f)".
Then, evaluate !(f) --> NOT false --> true. We return true.

Constraints:

1 <= expression.length <= 2 * 104
expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

#define BOOLEAN(x) ((x) == 't') ? true : false
#define MAKE_BOOLEAN(x) (x) ? 't' : 'f'

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    bool parseBoolExpr(const std::string& expression)
    {
        std::stack<char> st_operands;   // Stack to hold operands (t, f)
        std::stack<char> st_operators;  // Stack to hold operators (&, |, !)

        for (const char& c : expression)
        {
            if (c == '&' || c == '|' || c == '!')
            {
                st_operators.push(c);   // Push operators onto the stack
            }
            else if (c == '(' || c == 't' || c == 'f')
            {
                st_operands.push(c);    // Push operands
            }
            else if (c == ')')
            {
                char cur_operator = st_operators.top();
                st_operators.pop();

                // Evaluate based on the operator
                bool result = (cur_operator == '&') ? true : false;
                if (cur_operator == '!')
                {
                    // ! operator only works on one operand
                    result = !BOOLEAN(st_operands.top());
                    st_operands.pop(); // Remove the operand
                }
                else
                {
                    // & and | operators work on multiple operands
                    while (!st_operands.empty() && st_operands.top() != '(')
                    {
                        char cur_operand = st_operands.top();
                        st_operands.pop();

                        if (cur_operator == '&')
                        {
                            result &= BOOLEAN(cur_operand);
                        }
                        else if (cur_operator == '|')
                        {
                            result |= BOOLEAN(cur_operand);
                        }
                    }
                }

                st_operands.pop(); // Remove the opening parenthesis '('

                // Push the result back as 't' or 'f'
                st_operands.push(MAKE_BOOLEAN(result));
            }
        }

        // The final result will be the only element left in the operand stack
        return BOOLEAN(st_operands.top());
    }
};

int main()
{
    Solution sol;
    std::cout << sol.parseBoolExpr("!(&(f,t))") << std::endl;
    return 0;
}
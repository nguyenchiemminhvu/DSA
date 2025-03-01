/**
https://vjudge.net/contest/690986#problem/I
https://dmoj.ca/problem/ccc08s4

Twenty-four is a popular card game designed to be played by four players. Each player is dealt a deck of cards, which are kept face down. On every turn, each of the four players turns over the top card of his or her deck, so that it is visible to all. The goal is to find an arithmetic expression using the values of the cards (with A meaning 1, J meaning 11, Q meaning 12, and K meaning 13) that evaluates to the number 24. For example, for the example in the illustration, one possible expression would be:

\displaystyle ((A * K)- J) * Q
\displaystyle ((1*13)-11) * 12

The first player to find such an expression wins the turn, and adds all four cards to the bottom of his or her deck.

Each valid arithmetic expression must use all four cards, and must combine their values using addition, subtraction, multiplication, or division. Parentheses are allowed to specify precedence of operations. Juxtaposing cards to make multiple-digit decimal numbers is not allowed (e.g. you cannot place the cards 2 and 4 beside each other to make 24).

Non-integer quotients of division are also not allowed, even as a partial result (of a subexpression of the overall expression).

In some cases, the players may take a very long time to find an expression evaluating to 24. In fact, in some cases, no such expression exists. Your task is to determine, given four cards, an expression that evaluates to the largest number less than or equal to 24.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>

using namespace std;

class Solution
{
public:
    int findLargestLessThan24(std::vector<int>& cards)
    {
        double res = -1;
        DFS(cards, res);
        return (int)res;
    }
private:
    enum Operation
    {
        ADD,
        SUB,
        MUL,
        DIV
    };

    void DFS(std::vector<int> cards, double& res)
    {
        if (cards.size() == 1)
        {
            if (cards.front() <= 24)
            {
                res = std::max(res, (double)cards.front());
            }
            return;
        }

        for (int i = 0; i < cards.size(); i++)
        {
            for (int j = 0; j < cards.size(); j++)
            {
                if (i != j)
                {
                    std::vector<int> next;
                    for (int in = 0; in < cards.size(); in++)
                    {
                        if (in != i && in != j)
                        {
                            next.push_back(cards[in]);
                        }
                    }

                    for (int op = ADD; op <= DIV; op++)
                    {
                        switch (op)
                        {
                        case ADD:
                            next.push_back(cards[i] + cards[j]);
                            DFS(next, res);
                            next.pop_back();
                            break;
                        case SUB:
                            next.push_back(cards[i] - cards[j]);
                            DFS(next, res);
                            next.pop_back();
                            break;
                        case MUL:
                            next.push_back(cards[i] * cards[j]);
                            DFS(next, res);
                            next.pop_back();
                            break;
                        case DIV:
                            if (cards[j] != 0 && cards[i] % cards[j] == 0)
                            {
                                next.push_back(cards[i] / cards[j]);
                                DFS(next, res);
                                next.pop_back();
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
};

int main()
{
    int n;
    std::cin >> n;

    for (int t = 0; t < n; t++)
    {
        std::vector<int> cards(4);
        for (int i = 0; i < 4; i++)
        {
            int card;
            std::cin >> card;
            cards[i] = card;
        }

        Solution sol;
        std::cout << sol.findLargestLessThan24(cards) << std::endl;
    }

    return 0;
}